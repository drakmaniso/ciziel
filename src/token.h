#ifndef TOKEN_H
#define TOKEN_H

#include "global.h"


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
	token_FwdArrow,
	token_BackArrow,

	// Literals and identifiers
	token_Number,
	token_Name,
	token_TypeName,

	token_EOF,
	token_Invalid
} TokenTag;


typedef struct {
	USize pos;
	String value;
	TokenTag tag;
} Token;


typedef struct {
	Token *items;
	int32_t length;
	int32_t capacity;
} TokenArray;


Token token_new(USize pos, String value, TokenTag tag);
void token_print(Token self);
TokenArray token_new_array(int32_t capacity);
int32_t token_len(TokenArray a);
Token token_at(TokenArray a, int32_t index);
TokenArray token_push(TokenArray a, Token t);


#endif // TOKEN_H
