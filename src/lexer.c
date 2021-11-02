#include <stdbool.h>
#include <stdio.h>
#include "lexer.h"


// LEXER


void lexer_new(Lexer *self, char *filepath, String input) {
	*self = (Lexer) {
		.name = filepath,
		.input = input,
		.start = 0,
		.pos = 0,
	};
}


void lexer_run(Lexer *self) {
	self->start = 0;
	self->pos = 0;

	Token_Tag tag = scan(self);
	while(tag != token_EOF) {
		String value = str_slice(self->input, self->start, self->pos);
		Token token = token_new(self->start, value, tag);
		self->start = self->pos;
		token_print(token);
		tag = scan(self);
	}
}


char next(Lexer *self) {
	if (self->pos >= str_length(self->input)) {
		return '\0';
	}
	char result = str_at(self->input, self->pos);
	self->pos++;
	return result;
}


void ignore(Lexer *self) {
	self->start = self->pos;
}


void backtrack(Lexer *self) {
	self->pos--;
}


char peek(Lexer *self) {
	char r = next(self);
	backtrack(self);
	return r;
}


// SCANNER


Token_Tag scan_between(Lexer *self);
Token_Tag scan_identifier(Lexer *self);
Token_Tag scan_delimiter(Lexer *self);
Token_Tag scan_operator(Lexer *self);
Token_Tag scan_number(Lexer *self);
Token_Tag scan_invalid(Lexer *self);

bool is_white_space(char r);
bool is_letter(char r);
bool is_digit(char r);
bool is_delimiter(char r);
bool is_symbol(char r);


Token_Tag scan(Lexer *self) {
	while (true) {
		char r = next(self);

		if (r == '\0') {
			return token_EOF;
		}

		if (r == '\n') {
			ignore(self);
			continue;
			//return (Token_Tag) {lexNewLine};
		}

		if (is_white_space(r)) {
			ignore(self);
			continue;
		}

		if (is_delimiter(r)) {
			return scan_delimiter(self);
		}

		if (is_letter(r)) {
			return scan_identifier(self);
		}

		if (is_digit(r)) {
			return scan_number(self);
		}

		if (r == '-' && peek(self) == '-') {
			while (peek(self) != '\n' && peek(self) != '\0') {
				next(self);
			}
			ignore(self);
			continue;
		}

		if (is_symbol(r)) {
			return scan_operator(self);
		}

		// Invalid rune in input
		return scan_invalid(self);
	}
}


Token_Tag scan_identifier(Lexer *self) {
	while (true) {
		char r = next(self);

		if (is_letter(r) || is_digit(r)) {
			continue;
		}

		backtrack(self);

		String text = str_slice(self->input, self->start, self->pos);
		if (str_is(text, "let")) {
			return token_Let;
		} else if (str_is(text, "if")) {
			return token_If;
		} else if (str_is(text, "then")) {
			return token_Then;
		} else if (str_is(text, "else")) {
			return token_Else;
		} else if (str_is(text, "while")) {
			return token_Do;
		} else if (str_is(text, "do")) {
			return token_Do;
		} else if (str_is(text, "end")) {
			return token_End;
		}

		return token_Identifier;
	}
}


Token_Tag scan_operator(Lexer *self) {
	while (is_symbol(peek(self))) {
		next(self);
	}

	if (str_is(str_slice(self->input, self->start, self->pos), "=")) {
		return token_Equal;
	} else if (str_is(str_slice(self->input, self->start, self->pos), "->")) {
		return token_FwdArrow;
	} else if (str_is(str_slice(self->input, self->start, self->pos), "<-")) {
		return token_BackArrow;
	}

	return token_Invalid;
}


Token_Tag scan_delimiter(Lexer *self) {
	switch(str_at(self->input, self->start)) {
		case '\'':
			return token_Quote;
			break;
		case '(':
			return token_LeftParen;
			break;
		case ')':
			return token_RightParen;
			break;
		case ',':
			return token_Comma;
			break;
		case ':':
			return token_Colon;
			break;
		case ';':
			return token_Semicolon;
			break;
		default:
			return token_Invalid;
	}
}


Token_Tag scan_number(Lexer *self) {
	while (true) {
		char r = next(self);

		if (is_digit(r)) {
			continue;
		}

		backtrack(self);
		return token_Number;
	}
}


Token_Tag scan_invalid(Lexer *self) {
	while (true) {
		char r = next(self);

		if (r == '\0' || r == '\n') {
			backtrack(self);
		}
		return token_Invalid;
	}
}


// CHARACTER CLASSES

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
		|| r == ':'
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
