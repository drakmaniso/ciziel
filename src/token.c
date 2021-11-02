#include <stdio.h>
#include <stdlib.h>
#include "token.h"


Token token_new(USize pos, String value, Token_Tag tag) {
	return (Token) {
		.pos = pos,
		.value = value,
		.tag = tag
	};
}

void token_print(Token self) {
	switch (self.tag) {
		case token_Let: printf("Let"); break;
		case token_If: printf("If"); break;
		case token_Then: printf("Then"); break;
		case token_Else: printf("Else"); break;
		case token_While: printf("While"); break;
		case token_Do: printf("Do"); break;
		case token_End: printf("End"); break;

		case token_Identifier: printf("Id"); break;
		case token_Number: printf("Num"); break;

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
			printf("UNKNOWN");
	}
	if (self.tag == token_Identifier || self.tag == token_Number) {
		printf("<");
		str_print(self.value);
		printf(">");
	}
	if (self.tag == token_End || self.tag == token_Semicolon) {
		printf("\n");
	} else {
		printf(" ");
	}
}


Token_Array token_new_array(int32_t capacity) {
	return (Token_Array) {
		.items = calloc(capacity, sizeof(Token)),
		.length = 0,
		.capacity = capacity
	};
}


int32_t token_len(Token_Array a) {
	return a.length;
}


Token token_at(Token_Array a, int32_t index) {
	if (index >= a.length) {
		printf("PANIC: out-of-bound Token_Array index\n");
		exit(1);
	}
	return a.items[index];
}


Token_Array token_push(Token_Array a, Token t) {
	if (a.length >= a.capacity) {
		printf("NOT YET IMPLEMENTED: Token_Array growth");
		exit(1);
	}
	a.items[a.length] = t;
	return (Token_Array) {
		.items = a.items,
		.length = a.length + 1,
		.capacity = a.capacity
	};
}

