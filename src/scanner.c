#include <stdbool.h>
#include <stdio.h>
#include "scanner.h"

typedef struct state {
	// The type is recursive, so it must be embedded in a struct
	struct state (*func) (Scanner *s);
} state;

state lex_between (Scanner *s);
state lex_identifier (Scanner *s);
state lex_operator (Scanner *s);
state lex_number (Scanner *s);
state lex_invalid (Scanner *s);

bool is_white_space (Rune r);
bool is_letter (Rune r);
bool is_digit (Rune r);
bool is_symbol (Rune r);
bool is_keyword (String s);


// SCANNER


void Scanner_make (Scanner *s, char *filepath, String input) {
	*s = (Scanner) {
		.name = filepath,
		.input = input,
		.start = 0,
		.pos = 0,
	};
}


void Scanner_run (Scanner *s) {
	state st = (state) { .func = lex_between };
	for (; st.func != NULL; ) {
		st = st.func (s);
	}
}


Rune next (Scanner *s) {
	if (s->pos >= String_length (s->input)) {
		return '\0';
	}
	Rune result = String_at (s->input, s->pos);
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


void emit (Scanner *s, Token_Tag tag) {
	Token token = (Token) {
		.value = String_slice (s->input, s->start, s->pos),
		.tag = tag,
	};
	s->start = s->pos;
	Scanner_print (token);
}


void Scanner_print (Token t) {
	if (t.tag == Token_EOF) {
		printf ("EOF\n");
		return;
	}

	switch (t.tag) {
		case Token_Keyword:
			printf ("kw<");
			String_print (t.value);
			printf (">");
			break;

		case Token_Identifier:
			printf ("id<");
			String_print (t.value);
			printf (">");
			break;

		case Token_Number:
			printf ("num<");
			String_print (t.value);
			printf (">");
			break;

		case Token_Operator:
			printf ("op<");
			String_print (t.value);
			printf (">");
			break;

		case Token_Equal:
			printf ("=");
			break;

		case Token_Arrow:
			printf ("->");
			break;

		case Token_Semicolon:
			printf (";\n");
			return;
			break;

		case Token_Invalid:
			printf ("invalid<");
			String_print (t.value);
			printf (">");
			break;

		default:
			printf ("UNKNOWN<");
			String_print (t.value);
			printf (">");
	}
	printf(" ");
}


// LEXICAL STATES



state lex_between (Scanner *s) {
	while (true) {
		Rune r = next (s);

		if (r == '\0') {
			emit (s, Token_EOF);
			return (state) {NULL};
		}

		if (r == '\n') {
			ignore (s);
			continue;
			//return (state) {lexNewLine};
		}

		if (is_white_space (r)) {
			ignore (s);
			continue;
		}

		if (r == ';') {
			emit (s, Token_Semicolon);
			return (state) {lex_between};
		}

		if (is_letter (r)) {
			return (state) {lex_identifier};
		}

		if (is_digit (r)) {
			return (state) {lex_number};
		}

		if (r == '-' && peek (s) == '-') {
			while (peek (s) != '\n' && peek (s) != '\0') {
				next (s);
			}
			ignore (s);
			continue;
		}

		if (is_symbol (r)) {
			return (state) {lex_operator};
		}

		// Invalid rune in input
		return (state) {lex_invalid};
	}
}


state lex_identifier (Scanner *s) {
	while (true) {
		Rune r = next (s);

		if (is_letter (r) || is_digit (r)) {
			continue;
		}

		backup (s);
		if (is_keyword (String_slice (s->input, s->start, s->pos))) {
			emit (s, Token_Keyword);
		} else {
			emit (s, Token_Identifier);
		}
		return (state) {lex_between};
	}
}


state lex_operator (Scanner *s) {
	while (is_symbol (peek (s))) {
		next (s);
	}

	if (String_is (String_slice (s->input, s->start, s->pos), "=")) {
		emit (s, Token_Equal);
		return (state) {lex_between};
	} else if (String_is (String_slice (s->input, s->start, s->pos), "->")) {
		emit (s, Token_Arrow);
		return (state) {lex_between};
	}

	emit (s, Token_Operator);
	return (state) {lex_between};
}


state lex_number (Scanner *s) {
	while (true) {
		Rune r = next (s);

		if (is_digit (r)) {
			continue;
		}

		backup (s);
		emit (s, Token_Number);
		return (state) {lex_between};
	}
}


state lex_invalid (Scanner *s) {
	while (true) {
		Rune r = next (s);

		if (r == '\0' || r == '\n') {
			backup (s);
		}
		emit (s, Token_Invalid);
		return (state){lex_between};
	}
}


// UTILS

bool is_white_space (Rune r) {
	return r == ' ' || r == '\t';
}


bool is_letter (Rune r) {
	return (r >= 'A' && r <= 'Z')
		|| (r >= 'a' && r <= 'z')
		|| r == '_';
}


bool is_digit (Rune r) {
	return r >= '0' && r <= '9';
}


bool is_symbol (Rune r) {
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


bool is_keyword (String s) {
	return String_is (s, "func");
}
