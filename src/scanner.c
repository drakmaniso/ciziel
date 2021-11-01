#include <stdbool.h>
#include <stdio.h>
#include "scanner.h"

typedef struct state {
	// The type is recursive, so it must be embedded in a struct
	struct state(*func) (Scanner *s);
} state;

state state_between(Scanner *s);
state state_identifier(Scanner *s);
state state_delimiter(Scanner *s);
state state_operator(Scanner *s);
state state_number(Scanner *s);
state state_invalid(Scanner *s);

bool is_white_space(Rune r);
bool is_letter(Rune r);
bool is_digit(Rune r);
bool is_delimiter(Rune r);
bool is_symbol(Rune r);


// SCANNER


void scan_make(Scanner *s, char *filepath, String input) {
	*s = (Scanner) {
		.name = filepath,
		.input = input,
		.start = 0,
		.pos = 0,
	};
}


void scan_run(Scanner *s) {
	state st = (state) { .func = state_between };
	for (; st.func != NULL; ) {
		st = st.func(s);
	}
}


Rune next(Scanner *s) {
	if (s->pos >= str_length(s->input)) {
		return '\0';
	}
	Rune result = str_at(s->input, s->pos);
	s->pos++;
	return result;
}


void ignore(Scanner *s) {
	s->start = s->pos;
}


void backup(Scanner *s) {
	s->pos--;
}


Rune peek(Scanner *s) {
	Rune r = next(s);
	backup(s);
	return r;
}


void emit(Scanner *s, tok_Tag tag) {
	Token token = (Token) {
		.value = str_slice(s->input, s->start, s->pos),
		.tag = tag,
	};
	s->start = s->pos;
	scan_print(token);
}


void scan_print(Token t) {
	if (t.tag == tok_EOF) {
		printf("EOF\n");
		return;
	}

	switch(t.tag) {
		case tok_Public:
			printf("public");
			break;

		case tok_Do:
			printf("do");
			break;

		case tok_End:
			printf("end");
			break;

		case tok_If:
			printf("if");
			break;

		case tok_Then:
			printf("then");
			break;

		case tok_Else:
			printf("else");
			break;

		case tok_Identifier:
			printf("\"");
			str_print(t.value);
			printf("\"");
			break;

		case tok_Number:
			printf("\"");
			str_print(t.value);
			printf("\"");
			break;

		case tok_Equal:
			printf("=");
			break;

		case tok_Arrow:
			printf("->");
			break;

		// Delimiters

		case tok_Semicolon:
			printf(";\n");
			return;
			break;

		case tok_LeftParen:
			printf("(");
			break;

		case tok_RightParen:
			printf(")");
			break;

		case tok_Comma:
			printf(",");
			break;

		case tok_Quote:
			printf("\'");
			break;

		case tok_Invalid:
			printf("invalid<");
			str_print(t.value);
			printf(">");
			break;

		default:
			printf("UNKNOWN<");
			str_print(t.value);
			printf(">");
	}
	printf(" ");
}


// LEXICAL STATES



state state_between(Scanner *s) {
	while (true) {
		Rune r = next(s);

		if (r == '\0') {
			emit(s, tok_EOF);
			return (state) {NULL};
		}

		if (r == '\n') {
			ignore(s);
			continue;
			//return (state) {lexNewLine};
		}

		if (is_white_space(r)) {
			ignore(s);
			continue;
		}

		if (is_delimiter(r)) {
			return (state) {state_delimiter};
		}

		if (is_letter(r)) {
			return (state) {state_identifier};
		}

		if (is_digit(r)) {
			return (state) {state_number};
		}

		if (r == '-' && peek(s) == '-') {
			while (peek(s) != '\n' && peek(s) != '\0') {
				next(s);
			}
			ignore(s);
			continue;
		}

		if (is_symbol(r)) {
			return (state) {state_operator};
		}

		// Invalid rune in input
		return (state) {state_invalid};
	}
}


state state_identifier(Scanner *s) {
	while (true) {
		Rune r = next(s);

		if (is_letter(r) || is_digit(r)) {
			continue;
		}

		backup(s);

		String text = str_slice(s->input, s->start, s->pos);
		if (str_is(text, "public")) {
			emit(s, tok_Public);
		} else if (str_is(text, "do")) {
			emit(s, tok_Do);
		} else if (str_is(text, "end")) {
			emit(s, tok_End);
		} else if (str_is(text, "if")) {
			emit(s, tok_If);
		} else if (str_is(text, "then")) {
			emit(s, tok_Then);
		} else if (str_is(text, "else")) {
			emit(s, tok_Else);
		} else {
			emit(s, tok_Identifier);
		}
		return (state) {state_between};
	}
}


state state_operator(Scanner *s) {
	while (is_symbol(peek(s))) {
		next(s);
	}

	if (str_is(str_slice(s->input, s->start, s->pos), "=")) {
		emit(s, tok_Equal);
		return (state) {state_between};
	} else if (str_is(str_slice(s->input, s->start, s->pos), "->")) {
		emit(s, tok_Arrow);
		return (state) {state_between};
	}

	emit(s, tok_Invalid);
	return (state) {state_between};
}


state state_delimiter(Scanner *s) {
	switch(str_at(s->input, s->start)) {
		case '\'':
			emit(s, tok_Quote);
			break;
		case '(':
			emit(s, tok_LeftParen);
			break;
		case ')':
			emit(s, tok_RightParen);
			break;
		case ',':
			emit(s, tok_Comma);
			break;
		case ';':
			emit(s, tok_Semicolon);
			break;
		default:
			emit(s, tok_Invalid);
	}
	return (state) {state_between};
}


state state_number(Scanner *s) {
	while (true) {
		Rune r = next(s);

		if (is_digit(r)) {
			continue;
		}

		backup(s);
		emit(s, tok_Number);
		return (state) {state_between};
	}
}


state state_invalid(Scanner *s) {
	while (true) {
		Rune r = next(s);

		if (r == '\0' || r == '\n') {
			backup(s);
		}
		emit(s, tok_Invalid);
		return (state){state_between};
	}
}


// UTILS

bool is_white_space(Rune r) {
	return r == ' ' || r == '\t';
}


bool is_letter(Rune r) {
	return (r >= 'A' && r <= 'Z')
		|| (r >= 'a' && r <= 'z')
		|| r == '_';
}


bool is_digit(Rune r) {
	return r >= '0' && r <= '9';
}


bool is_delimiter(Rune r) {
	return r == '\''
		|| r == ';'
		|| r == ','
		|| r == '('
		|| r == ')'
		|| r == '['
		|| r == ']'
		|| r == '{'
		|| r == '}';
}


bool is_symbol(Rune r) {
	return r == '!'
		|| r == '#'
		|| r == '$'
		|| r == '%'
		|| r == '&'
		|| r == '*'
		|| r == '+'
		|| r == '-'
		|| r == '.'
		|| r == '/'
		|| r == ':'
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
