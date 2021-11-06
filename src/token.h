#ifndef TOKEN_H
#define TOKEN_H

#include "global.h"
#include "string.h"


typedef enum TokenTag {
	token_None,

	// Keywords
	token_Let,
	token_Def,
	token_Mut,
	token_If,
	token_Then,
	token_Else,
	token_While,
	token_Do,
	token_End,
	
	// Delimiters
	token_Colon,
	token_Semicolon,
	token_LeftParen,
	token_RightParen,
	token_Comma,
	token_Quote,

	// Operators
	token_Equal,
	token_RightArrow,
	token_LeftArrow,

	// Literals and identifiers
	token_Number,
	token_Id,
	token_TypeId,

	token_EOF,
	token_Invalid
} TokenTag;


typedef struct {
	size_t pos;
	String value;
	TokenTag tag;
} Token;

array_def(Token);


Token token_new(size_t pos, String value, TokenTag tag);
void token_print(Token self);


#endif // TOKEN_H
