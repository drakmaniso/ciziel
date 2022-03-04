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
	printf("\"");
	String_print(self.value);
	printf("\"");
}


void Token_print(Token self) {
	if (self.at_line_start) {
		printf("\n");
	}

	switch (self.tag) {
		case Token_Const: printf("CONST"); break;
		case Token_If: printf("IF"); break;
		case Token_Then: printf("THEN"); break;
		case Token_Else: printf("ELSE"); break;

		case Token_Number: printf("NUMBER"); print_value(self); break;
		case Token_Id: printf("ID"); print_value(self); break;
		case Token_TypeId: printf("TYPEID"); print_value(self); break;

		// Operators

		case Token_Equal: printf("EQUAL"); break;
		case Token_Lambda: printf("LAMBDA"); break;
		case Token_SArrow: printf("SARROW"); break;
		case Token_DArrow: printf("DARROW"); break;

		// Delimiters

		case Token_Colon: printf("COLON"); break;
		case Token_Semicolon: printf("SEMICOLON"); break;
		case Token_LParen: printf("LPAREN"); break;
		case Token_RParen: printf("RPAREN"); break;
		case Token_Comma: printf("COMMA"); break;
		case Token_Quote: printf("QUOTE"); break;

		case Token_Invalid: printf("INVALID"); print_value(self); break;

		default:
			printf("***UNKNOWN-TOKEN***");
	}

	printf(" ");
}
