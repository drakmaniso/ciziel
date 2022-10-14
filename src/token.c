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
		case Token_Let: printf("let"); break;
		case Token_If: printf("if"); break;
		case Token_Else: printf("else"); break;

		case Token_Number: printf("num"); print_value(self); break;
		case Token_Id: printf("id"); print_value(self); break;
		case Token_TypeId: printf("tid"); print_value(self); break;
		case Token_Operator: printf("op"); print_value(self); break;

		// Delimiters

		case Token_LParen: printf("lparen"); break;
		case Token_RParen: printf("rparen"); break;
		case Token_Comma: printf("comma"); break;
		case Token_Dot: printf("dot"); break;
		case Token_Colon: printf("colon"); break;
		case Token_Semicolon: printf("semicolon"); break;
		case Token_LBracket: printf("lbracket"); break;
		case Token_RBracket: printf("rbracket"); break;
		case Token_LBrace: printf("lbrace"); break;
		case Token_RBrace: printf("rbrace"); break;
		case Token_Lambda: printf("lambda"); break;

		case Token_TODO: printf("todo"); break;
		case Token_Invalid:
			printf("***INVALID(");
			String_print(self.value);
			printf(")***");
			break;

		case Token_EOF: printf("EOF"); break;

		default:
			printf("***UNKNOWN-TOKEN***");
	}

	printf(" ");
}
