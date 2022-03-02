#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "token.h"


Token Token_new(size_t pos, String value, TokenTag tag) {
	return (Token) {
		.pos = pos,
		.value = value,
		.tag = tag
	};
}

void Token_print(Token self) {
	switch (self.tag) {
		case Token_Const: printf("CONST"); break;
		case Token_Lambda: printf("LAMBDA"); break;
		case Token_If: printf("IF"); break;
		case Token_Then: printf("THEN"); break;
		case Token_Else: printf("ELSE"); break;

		case Token_Number: printf("NUM"); break;
		case Token_Id: printf("ID"); break;
		case Token_TypeId: printf("TYPEID"); break;

		// Operators

		case Token_Equal: printf("EQUAL"); break;
		case Token_DoubleArrow: printf("DBARROW"); break;
		case Token_RightArrow: printf("RARROW"); break;
		case Token_LeftArrow: printf("LARROW"); break;

		// Delimiters

		case Token_Colon: printf("COLON"); break;
		case Token_Semicolon: printf("SEMICOLON"); break;
		case Token_LeftParen: printf("LPAREN"); break;
		case Token_RightParen: printf("RPAREN"); break;
		case Token_Comma: printf("COMMA"); break;
		case Token_Quote: printf("QUOTE"); break;

		case Token_Invalid: printf("INVALID"); break;

		default:
			printf("***UNKNOWN***");
	}
	if (self.tag == Token_Invalid || self.tag == Token_Number 
			|| self.tag == Token_Id || self.tag == Token_TypeId) {
		printf("(");
		String_print(self.value);
		printf(")");
	}
	if (self.tag == Token_Semicolon || self.tag == Token_Equal) {
		printf("\n");
	} else {
		printf(" ");
	}
}
