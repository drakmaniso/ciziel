#ifndef TOKEN_H
#define TOKEN_H


#include "global.h"


typedef enum TokenTag {
	Token_None,

	// Keywords
	Token_Const,
	Token_Lambda,
	Token_If,
	Token_Then,
	Token_Else,
	
	// Delimiters
	Token_Colon,
	Token_Semicolon,
	Token_LeftParen,
	Token_RightParen,
	Token_Comma,
	Token_Quote,

	// Operators
	Token_Equal,
	Token_DoubleArrow,
	Token_RightArrow,
	Token_LeftArrow,

	// Literals and identifiers
	Token_Number,
	Token_Id,
	Token_TypeId,

	Token_EOF,
	Token_Invalid
} TokenTag;


typedef struct {
	size_t pos;
	String value;
	TokenTag tag;
} Token;

Array_typedef(Token);


Token Token_new(size_t pos, String value, TokenTag tag);
void Token_print(Token self);


#endif // TOKEN_H
