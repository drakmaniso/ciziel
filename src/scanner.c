#include <stdio.h>
#include "global.h"
#include "scanner.h"
#include "token.h"


// LEXER


TokenTag detect_token(Scanner *self);


Scanner Scanner_new(String input) {
	return (Scanner) {
		.input = input,
		.start = 0,
		.pos = 0,
		.at_line_start = true,
	};
}


Token Scanner_scan(Scanner *self) {
	TokenTag tag = detect_token(self);
	String value = String_slice(self->input, self->start, self->pos);
	Token token = Token_new(self->start, value, tag, self->at_line_start);
	self->start = self->pos;
	self->at_line_start = false;
	return token;
}


char next(Scanner *self) {
	if (self->pos >= String_length(self->input)) {
		self->pos++;
		return '\0';
	}
	char result = String_at(self->input, self->pos);
	self->pos++;
	return result;
}


void ignore(Scanner *self) {
	self->start = self->pos;
}


void backtrack(Scanner *self) {
	self->pos--;
}


char peek(Scanner *self) {
	char r = next(self);
	backtrack(self);
	return r;
}


// SCANNER


TokenTag scan_white_space(Scanner *self);
TokenTag scan_id(Scanner *self);
TokenTag scan_type_id(Scanner *self);
TokenTag scan_delimiter(Scanner *self);
TokenTag scan_operator(Scanner *self);
TokenTag scan_number(Scanner *self);
TokenTag scan_invalid(Scanner *self);

bool is_new_line(char r);
bool is_white_space(char r);
bool is_uppercase(char r);
bool is_lowercase(char r);
bool is_letter(char r);
bool is_digit(char r);
bool is_valid_for_names(char r);
bool is_delimiter(char r);
bool is_symbol(char r);


TokenTag detect_token(Scanner *self) {
	while (true) {
		char r = next(self);

		if (r == '\0') {
			return Token_EOF;
		}

		if (is_new_line(r)) {
			self->at_line_start = true;
			ignore(self);
			continue;
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


TokenTag scan_id(Scanner *self) {
	while (true) {
		char r = next(self);

		if (is_valid_for_names(r)) {
			continue;
		}

		backtrack(self);

		String text = String_slice(self->input, self->start, self->pos);
		if (String_is(text, "let")) {
			return Token_Let;
		} else if (String_is(text, "if")) {
			return Token_If;
		} else if (String_is(text, "else")) {
			return Token_Else;
		} else if (String_is(text, "fun")) {
			return Token_Fun;
		}

		return Token_Id;
	}
}


TokenTag scan_type_id(Scanner *self) {
	while (true) {
		char r = next(self);

		if (is_valid_for_names(r)) {
			continue;
		}

		backtrack(self);
		return Token_TypeId;
	}
}


TokenTag scan_operator(Scanner *self) {
	while (is_symbol(peek(self))) {
		next(self);
	}

	String slice = String_slice(self->input, self->start, self->pos);
	if (String_is(slice, "->")) {
		return Token_Arrow;
	} else if (String_is(slice, "+")) {
		return Token_Plus;
	}

	return Token_Invalid;
}


TokenTag scan_delimiter(Scanner *self) {
	switch(String_at(self->input, self->start)) {
		case '{':
			return Token_LBrace;
			break;
		case '}':
			return Token_RBrace;
			break;
		case '(':
			return Token_LParen;
			break;
		case ')':
			return Token_RParen;
			break;
		case ':':
			return Token_Colon;
			break;
		case '=':
			return Token_Colon;
			break;
		case ',':
			return Token_Comma;
			break;
		case ';':
			return Token_Semicolon;
			break;
		default:
			return Token_Invalid;
	}
}


TokenTag scan_number(Scanner *self) {
	while (true) {
		char r = next(self);

		if (is_digit(r)) {
			continue;
		}

		backtrack(self);
		return Token_Number;
	}
}


TokenTag scan_invalid(Scanner *self) {
	while (true) {
		char r = next(self);

		if (r == '\0' || r == '\n') {
			backtrack(self);
		}
		return Token_Invalid;
	}
}


// CHARACTER CLASSES


bool is_new_line(char r) {
	return r == '\n' || r == '\r';
}


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
		|| r == '_' || r == '\'' || r == '-';
}


bool is_delimiter(char r) {
	return r == ':'
		|| r == '='
		|| r == ';'
		|| r == ','
		|| r == '.'
		|| r == '('
		|| r == ')'
		|| r == '['
		|| r == ']'
		|| r == '{'
		|| r == '}'
		|| r == '\\';
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
		|| r == '|'
		|| r == '/'
		|| r == '<'
		|| r == '>'
		|| r == '?'
		|| r == '@'
		|| r == '^'
		|| r == '~';
}
