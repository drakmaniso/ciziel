#include <stdio.h>
#include "global.h"
#include "lexer.h"
#include "token.h"


// LEXER


void lexer_new(Lexer *self, char *filepath, String input) {
	*self = (Lexer) {
		.name = filepath,
		.input = input,
		.start = 0,
		.pos = 0,
	};
}


TokenArray lexer_tokenize(Lexer *self) {
	TokenArray tokens = array_new(Token, 8);
	self->start = 0;
	self->pos = 0;

	TokenTag tag = scan(self);
	while(tag != token_EOF) {
		String value = str_slice(self->input, self->start, self->pos);
		Token token = token_new(self->start, value, tag);
		self->start = self->pos;
		array_push(tokens, token);
		tag = scan(self);
	}
	return tokens;
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
			return token_EOF;
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

		if (is_lowercase(r)) {
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

		String text = str_slice(self->input, self->start, self->pos);
		if (str_is(text, "let")) {
			return token_Let;
		} else if (str_is(text, "def")) {
			return token_Def;
		} else if (str_is(text, "mut")) {
			return token_Mut;
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

		return token_Id;
	}
}


TokenTag scan_type_id(Lexer *self) {
	while (true) {
		char r = next(self);

		if (is_valid_for_names(r)) {
			continue;
		}

		backtrack(self);
		return token_TypeId;
	}
}


TokenTag scan_operator(Lexer *self) {
	while (is_symbol(peek(self))) {
		next(self);
	}

	if (str_is(str_slice(self->input, self->start, self->pos), "=")) {
		return token_Equal;
	} else if (str_is(str_slice(self->input, self->start, self->pos), "->")) {
		return token_RightArrow;
	} else if (str_is(str_slice(self->input, self->start, self->pos), "<-")) {
		return token_LeftArrow;
	}

	return token_Invalid;
}


TokenTag scan_delimiter(Lexer *self) {
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


TokenTag scan_number(Lexer *self) {
	while (true) {
		char r = next(self);

		if (is_digit(r)) {
			continue;
		}

		backtrack(self);
		return token_Number;
	}
}


TokenTag scan_invalid(Lexer *self) {
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
