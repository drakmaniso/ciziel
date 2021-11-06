#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "token.h"


Token token_new(size_t pos, String value, TokenTag tag) {
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
