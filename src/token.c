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
		case token_Let: printf("Let"); break;
		case token_Def: printf("Def"); break;
		case token_Mut: printf("Mut"); break;
		case token_If: printf("If"); break;
		case token_Then: printf("Then"); break;
		case token_Else: printf("Else"); break;
		case token_While: printf("While"); break;
		case token_Do: printf("Do"); break;
		case token_End: printf("End"); break;

		case token_Number: printf("Num"); break;
		case token_Name: printf("Name"); break;
		case token_TypeName: printf("TypeName"); break;

		// Operators

		case token_Equal: printf("Equal"); break;
		case token_FwdArrow: printf("FwdArrow"); break;
		case token_BackArrow: printf("BackArrow"); break;

		// Delimiters

		case token_Colon: printf("Colon"); break;
		case token_Semicolon: printf("Semicolon"); break;
		case token_LeftParen: printf("LeftParen"); break;
		case token_RightParen: printf("RightParen"); break;
		case token_Comma: printf("Comma"); break;
		case token_Quote: printf("Quote"); break;

		case token_Invalid: printf("INVALID"); break;

		default:
			printf("***UNKNOWN***");
	}
	if (self.tag == token_Invalid || self.tag == token_Number 
			|| self.tag == token_Name || self.tag == token_TypeName) {
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

