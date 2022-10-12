#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "token.h"


Token Token_new(size_t pos, String value, TokenTag tag, bool at_line_start) {
	return (Token) {
		.pos = pos,
		.value = value,
		.tag = tag,
		.at_line_start = at_line_start
	};
}


void print_value(Token self) {
	printf("(");
	String_print(self.value);
	printf(")");
}


void Token_print(Token self) {
	if (self.at_line_start) {
		printf("\n");
	}

	switch (self.tag) {
		case Token_Let: printf("LET"); break;
		case Token_If: printf("IF"); break;
		case Token_Else: printf("ELSE"); break;
		case Token_Fun: printf("FUN"); break;

		case Token_Number: printf("NUM"); print_value(self); break;
		case Token_Id: printf("ID"); print_value(self); break;
		case Token_TypeId: printf("TYPEID"); print_value(self); break;

		// Operators

		case Token_Arrow: printf("ARROW"); break;
		case Token_Plus: printf("PLUS"); break;

		// Delimiters

		case Token_LBrace: printf("LBRACE"); break;
		case Token_RBrace: printf("RBRACE"); break;
		case Token_LParen: printf("LPAREN"); break;
		case Token_RParen: printf("RPAREN"); break;
		case Token_Colon: printf("COLON"); break;
		case Token_Equal: printf("EQUAL"); break;
		case Token_Semicolon: printf("SEMICOLON"); break;
		case Token_Comma: printf("COMMA"); break;

		case Token_Invalid: printf("INVALID"); print_value(self); break;

		case Token_EOF: printf("EOF"); break;

		default:
			printf("***UNKNOWN-TOKEN***");
	}

	printf(" ");
}
