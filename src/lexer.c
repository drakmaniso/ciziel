#include <stdio.h>
#include "global.h"
#include "lexer.h"
#include "token.h"


// LEXER


void Lexer_new(Lexer *self, char *filepath, String input) {
	*self = (Lexer) {
		.name = filepath,
		.input = input,
		.start = 0,
		.pos = 0,
	};
}


ArrayToken Lexer_tokenize(Lexer *self) {
	ArrayToken tokens = Array_new(Token, 8);
	self->start = 0;
	self->pos = 0;

	TokenTag tag = scan(self);
	while(tag != Token_EOF) {
		String value = String_slice(self->input, self->start, self->pos);
		Token token = Token_new(self->start, value, tag);
		self->start = self->pos;
		Array_push(tokens, token);
		tag = scan(self);
	}
	return tokens;
}


char next(Lexer *self) {
	if (self->pos >= String_length(self->input)) {
		return '\0';
	}
	char result = String_at(self->input, self->pos);
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


TokenTag scan_between(Lexer *self);
TokenTag scan_id(Lexer *self);
TokenTag scan_type_id(Lexer *self);
TokenTag scan_delimiter(Lexer *self);
TokenTag scan_operator(Lexer *self);
TokenTag scan_number(Lexer *self);
TokenTag scan_invalid(Lexer *self);

bool is_white_space(char r);
bool is_uppercase(char r);
bool is_lowercase(char r);
bool is_letter(char r);
bool is_digit(char r);
bool is_valid_for_names(char r);
bool is_delimiter(char r);
bool is_symbol(char r);


TokenTag scan(Lexer *self) {
	while (true) {
		char r = next(self);

		if (r == '\0') {
			return Token_EOF;
		}

		if (r == '\n') {
			ignore(self);
			continue;
			//return (TokenTag) {lexNewLine};
		}

		if (is_white_space(r)) {
			ignore(self);
			continue;
		}

		if (is_delimiter(r)) {
			return scan_delimiter(self);
		}

		if (is_uppercase(r)) {
			return scan_type_id(self);
		}

		if (is_lowercase(r) || r == '_') {
			return scan_id(self);
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


TokenTag scan_id(Lexer *self) {
	while (true) {
		char r = next(self);

		if (is_valid_for_names(r)) {
			continue;
		}

		backtrack(self);

		String text = String_slice(self->input, self->start, self->pos);
		if (String_is(text, "const")) {
			return Token_Const;
		} else if (String_is(text, "if")) {
			return Token_If;
		} else if (String_is(text, "then")) {
			return Token_Then;
		} else if (String_is(text, "else")) {
			return Token_Else;
		}

		return Token_Id;
	}
}


TokenTag scan_type_id(Lexer *self) {
	while (true) {
		char r = next(self);

		if (is_valid_for_names(r)) {
			continue;
		}

		backtrack(self);
		return Token_TypeId;
	}
}


TokenTag scan_operator(Lexer *self) {
	while (is_symbol(peek(self))) {
		next(self);
	}

	String slice = String_slice(self->input, self->start, self->pos);
	if (String_is(slice, "=")) {
		return Token_Equal;
	} else if (String_is(slice, "\\")) {
		return Token_Lambda;
	} else if (String_is(slice, "=>")) {
		return Token_DoubleArrow;
	} else if (String_is(slice, "->")) {
		return Token_RightArrow;
	} else if (String_is(slice, "<-")) {
		return Token_LeftArrow;
	}

	return Token_Invalid;
}


TokenTag scan_delimiter(Lexer *self) {
	switch(String_at(self->input, self->start)) {
		case '\'':
			return Token_Quote;
			break;
		case '(':
			return Token_LeftParen;
			break;
		case ')':
			return Token_RightParen;
			break;
		case ',':
			return Token_Comma;
			break;
		case ':':
			return Token_Colon;
			break;
		case ';':
			return Token_Semicolon;
			break;
		default:
			return Token_Invalid;
	}
}


TokenTag scan_number(Lexer *self) {
	while (true) {
		char r = next(self);

		if (is_digit(r)) {
			continue;
		}

		backtrack(self);
		return Token_Number;
	}
}


TokenTag scan_invalid(Lexer *self) {
	while (true) {
		char r = next(self);

		if (r == '\0' || r == '\n') {
			backtrack(self);
		}
		return Token_Invalid;
	}
}


// CHARACTER CLASSES

bool is_white_space(char r) {
	return r == ' ' || r == '\t';
}


bool is_lowercase(char r) {
	return (r >= 'a' && r <= 'z');
}


bool is_uppercase(char r) {
	return (r >= 'A' && r <= 'Z');
}


bool is_letter(char r) {
	return is_uppercase(r) || is_lowercase(r);
}


bool is_digit(char r) {
	return r >= '0' && r <= '9';
}

bool is_valid_for_names(char r) {
	return is_letter(r) || is_digit(r)
		|| r == '_' || r == '!' || r == '-';
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
