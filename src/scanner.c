#include <stdbool.h>
#include <stdio.h>
#include "scanner.h"


bool isWhiteSpace (Rune r) {
	return r == ' ' || r == '\t';
}


bool isLetter (Rune r) {
	return (r >= 'A' && r <= 'Z')
		|| (r >= 'a' && r <= 'z')
		|| r == '_';
}


bool isDigit (Rune r) {
	return r >= '0' && r <= '9';
}


bool isSymbol (Rune r) {
	return r == '!'
		|| r == '#'
		|| r == '$'
		|| r == '%'
		|| r == '&'
		|| r == '*'
		|| r == '+'
		|| r == '-'
		|| r == '/'
		|| r == '<'
		|| r == '='
		|| r == '>'
		|| r == '?'
		|| r == '@'
		|| r == '\\'
		|| r == '^'
		|| r == '|'
		|| r == '~';
}


bool isKeyword (String s) {
	return stringIs (s, "func");
}


Rune next (Scanner *s);
void ignore (Scanner *s);
void backup (Scanner *s);
Rune peek (Scanner *s);
void emit (Scanner *s, TokenType typ);


// LEXICAL STATES


typedef struct state {
	// The type is recursive, so it must be embedded in a struct
	struct state (*func) (Scanner *s);
} state;


state lexBetween (Scanner *s);
state lexIdentifier (Scanner *s);
state lexOperator (Scanner *s);
state lexNumber (Scanner *s);
state lexInvalid (Scanner *s);


state lexBetween (Scanner *s) {
	while (true) {
		Rune r = next (s);

		if (r == '\0') {
			emit (s, tokEOF);
			return (state) {NULL};
		}

		if (r == '\n') {
			ignore (s);
			continue;
			//return (state) {lexNewLine};
		}

		if (isWhiteSpace (r)) {
			ignore (s);
			continue;
		}

		if (r == ';') {
			emit (s, tokSemicolon);
			return (state) {lexBetween};
		}

		if (isLetter (r)) {
			return (state) {lexIdentifier};
		}

		if (isDigit (r)) {
			return (state) {lexNumber};
		}

		if (r == '-' && peek (s) == '-') {
			while (peek (s) != '\n' && peek (s) != '\0') {
				next (s);
			}
			ignore (s);
			continue;
		}

		if (isSymbol (r)) {
			return (state) {lexOperator};
		}

		// Invalid rune in input
		return (state) {lexInvalid};
	}
}


state lexIdentifier (Scanner *s) {
	while (true) {
		Rune r = next (s);

		if (isLetter (r) || isDigit (r)) {
			continue;
		}

		backup (s);
		if (isKeyword (stringSlice (s->input, s->start, s->pos))) {
			emit (s, tokKeyword);
		} else {
			emit (s, tokIdentifier);
		}
		return (state) {lexBetween};
	}
}


state lexOperator (Scanner *s) {
	while (isSymbol (peek (s))) {
		next (s);
	}

	if (stringIs (stringSlice (s->input, s->start, s->pos), "=")) {
		emit (s, tokEqual);
		return (state) {lexBetween};
	} else if (stringIs (stringSlice (s->input, s->start, s->pos), "->")) {
		emit (s, tokArrow);
		return (state) {lexBetween};
	}

	emit (s, tokOperator);
	return (state) {lexBetween};
}


state lexNumber (Scanner *s) {
	while (true) {
		Rune r = next (s);

		if (isDigit (r)) {
			continue;
		}

		backup (s);
		emit (s, tokNumber);
		return (state) {lexBetween};
	}
}


state lexInvalid (Scanner *s) {
	while (true) {
		Rune r = next (s);

		if (r == '\0' || r == '\n') {
			backup (s);
		}
		emit (s, tokInvalid);
		return (state){lexBetween};
	}
}


// SCANNER


void scanMake (Scanner *s, char *filepath, String input) {
	*s = (Scanner) {
		.name = filepath,
		.input = input,
		.start = 0,
		.pos = 0,
	};
}


void scanRun (Scanner *s) {
	state st = (state) { .func = lexBetween };
	for (; st.func != NULL; ) {
		st = st.func (s);
	}
}


Rune next (Scanner *s) {
	if (s->pos >= stringLength (s->input)) {
		return '\0';
	}
	Rune result = stringAt (s->input, s->pos);
	s->pos++;
	return result;
}


void ignore (Scanner *s) {
	s->start = s->pos;
}


void backup (Scanner *s) {
	s->pos--;
}


Rune peek (Scanner *s) {
	Rune r = next (s);
	backup (s);
	return r;
}


void emit (Scanner *s, TokenType typ) {
	Token tok = (Token) {
		.value = stringSlice (s->input, s->start, s->pos),
		.type = typ,
	};
	s->start = s->pos;
	scanPrint (tok);
}


void scanPrint (Token t) {
	if (t.type == tokEOF) {
		printf ("EOF\n");
		return;
	}

	switch (t.type) {
		case tokKeyword:
			printf ("kw<");
			stringPrint (t.value);
			printf (">");
			break;

		case tokIdentifier:
			printf ("id<");
			stringPrint (t.value);
			printf (">");
			break;

		case tokNumber:
			printf ("num<");
			stringPrint (t.value);
			printf (">");
			break;

		case tokOperator:
			printf ("op<");
			stringPrint (t.value);
			printf (">");
			break;

		case tokEqual:
			printf ("=");
			break;

		case tokArrow:
			printf ("->");
			break;

		case tokSemicolon:
			printf (";\n");
			return;
			break;

		case tokInvalid:
			printf ("invalid<");
			stringPrint (t.value);
			printf (">");
			break;

		default:
			printf ("UNKNOWN<");
			stringPrint (t.value);
			printf (">");
	}
	printf(" ");
}
