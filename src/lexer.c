#include <stdbool.h>
#include <stdio.h>
#include "lexer.h"

typedef struct state {
	// The type is recursive, so it must be embedded in a struct
	struct state(*func) (Lexer *s);
} state;

state state_between(Lexer *s);
state state_identifier(Lexer *s);
state state_delimiter(Lexer *s);
state state_operator(Lexer *s);
state state_number(Lexer *s);
state state_invalid(Lexer *s);

bool is_white_space(char r);
bool is_letter(char r);
bool is_digit(char r);
bool is_delimiter(char r);
bool is_symbol(char r);


// LEXER


void lexer_make(Lexer *s, char *filepath, String input) {
	*s = (Lexer) {
		.name = filepath,
		.input = input,
		.start = 0,
		.pos = 0,
	};
}


void lexer_run(Lexer *s) {
	state st = (state) { .func = state_between };
	for (; st.func != NULL; ) {
		st = st.func(s);
	}
}


char next(Lexer *s) {
	if (s->pos >= str_length(s->input)) {
		return '\0';
	}
	char result = str_at(s->input, s->pos);
	s->pos++;
	return result;
}


void ignore(Lexer *s) {
	s->start = s->pos;
}


void backtrack(Lexer *s) {
	s->pos--;
}


char peek(Lexer *s) {
	char r = next(s);
	backtrack(s);
	return r;
}


void emit(Lexer *s, Token_Tag tag) {
	Token token = (Token) {
		.value = str_slice(s->input, s->start, s->pos),
		.tag = tag,
	};
	s->start = s->pos;
	lexer_print(token);
}


void lexer_print(Token t) {
	if (t.tag == token_EOF) {
		printf("EOF\n");
		return;
	}

	switch(t.tag) {
		case token_Public:
			printf("public");
			break;

		case token_Do:
			printf("do");
			break;

		case token_End:
			printf("end");
			break;

		case token_If:
			printf("if");
			break;

		case token_Then:
			printf("then");
			break;

		case token_Else:
			printf("else");
			break;

		case token_Identifier:
			printf("\"");
			str_print(t.value);
			printf("\"");
			break;

		case token_Number:
			printf("\"");
			str_print(t.value);
			printf("\"");
			break;

		case token_Equal:
			printf("=");
			break;

		case token_Arrow:
			printf("->");
			break;

		// Delimiters

		case token_Semicolon:
			printf(";\n");
			return;
			break;

		case token_LeftParen:
			printf("(");
			break;

		case token_RightParen:
			printf(")");
			break;

		case token_Comma:
			printf(",");
			break;

		case token_Quote:
			printf("\'");
			break;

		case token_Invalid:
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



state state_between(Lexer *s) {
	while (true) {
		char r = next(s);

		if (r == '\0') {
			emit(s, token_EOF);
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


state state_identifier(Lexer *s) {
	while (true) {
		char r = next(s);

		if (is_letter(r) || is_digit(r)) {
			continue;
		}

		backtrack(s);

		String text = str_slice(s->input, s->start, s->pos);
		if (str_is(text, "public")) {
			emit(s, token_Public);
		} else if (str_is(text, "do")) {
			emit(s, token_Do);
		} else if (str_is(text, "end")) {
			emit(s, token_End);
		} else if (str_is(text, "if")) {
			emit(s, token_If);
		} else if (str_is(text, "then")) {
			emit(s, token_Then);
		} else if (str_is(text, "else")) {
			emit(s, token_Else);
		} else {
			emit(s, token_Identifier);
		}
		return (state) {state_between};
	}
}


state state_operator(Lexer *s) {
	while (is_symbol(peek(s))) {
		next(s);
	}

	if (str_is(str_slice(s->input, s->start, s->pos), "=")) {
		emit(s, token_Equal);
		return (state) {state_between};
	} else if (str_is(str_slice(s->input, s->start, s->pos), "->")) {
		emit(s, token_Arrow);
		return (state) {state_between};
	}

	emit(s, token_Invalid);
	return (state) {state_between};
}


state state_delimiter(Lexer *s) {
	switch(str_at(s->input, s->start)) {
		case '\'':
			emit(s, token_Quote);
			break;
		case '(':
			emit(s, token_LeftParen);
			break;
		case ')':
			emit(s, token_RightParen);
			break;
		case ',':
			emit(s, token_Comma);
			break;
		case ';':
			emit(s, token_Semicolon);
			break;
		default:
			emit(s, token_Invalid);
	}
	return (state) {state_between};
}


state state_number(Lexer *s) {
	while (true) {
		char r = next(s);

		if (is_digit(r)) {
			continue;
		}

		backtrack(s);
		emit(s, token_Number);
		return (state) {state_between};
	}
}


state state_invalid(Lexer *s) {
	while (true) {
		char r = next(s);

		if (r == '\0' || r == '\n') {
			backtrack(s);
		}
		emit(s, token_Invalid);
		return (state){state_between};
	}
}


// UTILS

bool is_white_space(char r) {
	return r == ' ' || r == '\t';
}


bool is_letter(char r) {
	return (r >= 'A' && r <= 'Z')
		|| (r >= 'a' && r <= 'z')
		|| r == '_';
}


bool is_digit(char r) {
	return r >= '0' && r <= '9';
}


bool is_delimiter(char r) {
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


bool is_symbol(char r) {
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
