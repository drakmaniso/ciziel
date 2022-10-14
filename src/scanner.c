#include <stdio.h>
#include "global.h"
#include "scanner.h"
#include "token.h"


///////////////////////////////////////////////////////////////////////////////


Scanner Scanner_new(String input) {
	return (Scanner) {
		.input = input,
		.start = 0,
		.pos = 0,
		.at_line_start = true,
	};
}


///////////////////////////////////////////////////////////////////////////////


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


bool is_valid_for_operators(char r) {
	return r == '!'
		|| r == '$' || r == '%' || r == '&'
		|| r == '*' || r == '+'
		|| r == '-'
		|| r == '/'
		|| r == '<' || r == '=' || r == '>'
		|| r == '^'
		|| r == '|'
		|| r == '~';
}

///////////////////////////////////////////////////////////////////////////////


char peek(Scanner *self) {
	if (self->pos >= String_length(self->input)) {
		return '\0';
	}
	return String_at(self->input, self->pos);
}


char peek_next(Scanner *self) {
	if (self->pos + 1 >= String_length(self->input)) {
		return '\0';
	}
	return String_at(self->input, self->pos + 1);
}


void advance(Scanner *self) {
	if (self->pos < String_length(self->input)) {
		self->pos++;
	}
}


///////////////////////////////////////////////////////////////////////////////


void skip_whitespace(Scanner *self) {
	while (true) {
		switch(peek(self)) {
			case ' ':
			case '\t':
				advance(self);
				break;
			
			case '\n':
			case '\r':
				self->at_line_start = true;
				advance(self);
				break;
			
			case '-':
				if (peek_next(self) != '-') {
					return;
				}
				advance(self);
				advance(self);
				while(peek(self) != '\n' && peek(self) != '\r' && peek(self) != '\0') {
					advance(self);
				}
				break;
			
			default:
				return;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////


TokenTag consume_keyword_or_id(Scanner *self) {
	while (is_valid_for_names(peek(self))) {
		advance(self);
	}

	String text = String_slice(self->input, self->start, self->pos);

	if (String_is(text, "let")) {
		return Token_Let;
	}
	
	if (String_is(text, "if")) {
		return Token_If;
	}
	
	if (String_is(text, "else")) {
		return Token_Else;
	}
 
	return Token_Id;
}


TokenTag consume_type_id(Scanner *self) {
	while (is_valid_for_names(peek(self))) {
		advance(self);
	}

	return Token_TypeId;
}


TokenTag consume_operator(Scanner *self) {
	while (is_valid_for_operators(peek(self))) {
		advance(self);
	}

	return Token_Operator;
}


TokenTag consume_number(Scanner *self) {
	while (true) {
		char c = peek(self);

		if (is_digit(c)) {
			advance(self);
			continue;
		}

		return Token_Number;
	}
}


///////////////////////////////////////////////////////////////////////////////


TokenTag detect_token(Scanner *self) {
	skip_whitespace(self);
	self->start = self->pos;
	
	char c = peek(self);
		
	if (is_lowercase(c)) {
		advance(self);
		return consume_keyword_or_id(self);
	}
	
	if (is_uppercase(c)) {
		advance(self);
		return consume_type_id(self);
	}
	
	if (is_digit(c)) {
		advance(self);
		return consume_number(self);
	}
	
	if (is_valid_for_operators(c)) {
		advance(self);
		return consume_operator(self);
	}

	switch(c) {
		case '\0':
			advance(self);
			return Token_EOF;
		
		case '"':
			advance(self);
			return Token_TODO;

		case '#':
			advance(self);
			return Token_TODO;

		// '$': operator

		// '%': operator

		// '&': operator

		case '\'':
			advance(self);
			return Token_TODO;

		case '(':
			advance(self);
			return Token_LParen;

		case ')':
			advance(self);
			return Token_RParen;
		
		// '*': operator
		
		// '+': operator

		case ',':
			advance(self);
			return Token_Comma;
		
		// '-': operator
		
		case '.':
			advance(self);
			return Token_Dot;
		
		// '/': operator

		case ':':
			advance(self);
			return Token_Colon;

		case ';':
			advance(self);
			return Token_Semicolon;
		
		// '<': operator
		
		// '=': operator
		
		// '>': operator
		
		case '?':
			advance(self);
			return Token_TODO;
		
		case '@':
			advance(self);
			return Token_TODO;

		case '[':
			advance(self);
			return Token_LBracket;

		case '\\':
			advance(self);
			return Token_Lambda;

		case ']':
			advance(self);
			return Token_RBracket;
		
		// '^': operator
		
		case '_':
			advance(self);
			return consume_keyword_or_id(self);
		
		case '`':
			advance(self);
			return Token_TODO;

		case '{':
			advance(self);
			return Token_LBrace;

		// '|': operator

		case '}':
			advance(self);
			return Token_RBrace;

		// '~': operator
	}

	// Invalid character in input
	advance(self);
	return Token_Invalid;
}


///////////////////////////////////////////////////////////////////////////////


Token Scanner_next_token(Scanner *self) {
	TokenTag tag = detect_token(self);

	String value = String_slice(self->input, self->start, self->pos);
	Token token = Token_new(self->start, value, tag, self->at_line_start);
	self->start = self->pos;
	self->at_line_start = false;
	return token;
}
