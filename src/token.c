#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "token.h"


Token token_new(USize pos, String value, TokenTag tag) {
	return (Token) {
		.pos = pos,
		.value = value,
		.tag = tag
	};
}

void token_print(Token self) {
	switch (self.tag) {
		case token_Let: printf("LET"); break;
		case token_Def: printf("DEF"); break;
		case token_Mut: printf("MUT"); break;
		case token_If: printf("IF"); break;
		case token_Then: printf("THEN"); break;
		case token_Else: printf("ELSE"); break;
		case token_While: printf("WHILE"); break;
		case token_Do: printf("DO"); break;
		case token_End: printf("END"); break;

		case token_Number: printf("NUM"); break;
		case token_Id: printf("ID"); break;
		case token_TypeId: printf("TYPEID"); break;

		// Operators

		case token_Equal: printf("EQUAL"); break;
		case token_RightArrow: printf("RARROW"); break;
		case token_LeftArrow: printf("LARROW"); break;

		// Delimiters

		case token_Colon: printf("COLON"); break;
		case token_Semicolon: printf("SEMICOLON"); break;
		case token_LeftParen: printf("LPAREN"); break;
		case token_RightParen: printf("RPAREN"); break;
		case token_Comma: printf("COMMA"); break;
		case token_Quote: printf("QUOTE"); break;

		case token_Invalid: printf("INVALID"); break;

		default:
			printf("***UNKNOWN***");
	}
	if (self.tag == token_Invalid || self.tag == token_Number 
			|| self.tag == token_Id || self.tag == token_TypeId) {
		printf("(");
		str_print(self.value);
		printf(")");
	}
	if (self.tag == token_End || self.tag == token_Semicolon || self.tag == token_Equal) {
		printf("\n");
	} else {
		printf(" ");
	}
}


TokenArray token_new_array(int32_t capacity) {
	return (TokenArray) {
		.items = calloc(capacity, sizeof(Token)),
		.length = 0,
		.capacity = capacity
	};
}


int32_t token_len(TokenArray a) {
	return a.length;
}


Token token_at(TokenArray a, int32_t index) {
	if (index >= a.length) {
		printf("PANIC: out-of-bound TokenArray index\n");
		exit(1);
	}
	return a.items[index];
}


TokenArray token_push(TokenArray a, Token t) {
	if (a.length >= a.capacity) {
		printf("NOT YET IMPLEMENTED: TokenArray growth");
		exit(1);
	}
	a.items[a.length] = t;
	return (TokenArray) {
		.items = a.items,
		.length = a.length + 1,
		.capacity = a.capacity
	};
}

