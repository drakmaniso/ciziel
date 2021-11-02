#ifndef TOKEN_H
#define TOKEN_H


#include <stddef.h>
#include "string.h"


typedef enum Token_Tag {
	token_None,

	// Keywords
	token_Let,
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
	token_Identifier,

	token_EOF,
	token_Invalid
} Token_Tag;


typedef struct {
	String value;
	int32_t line;
	int32_t column;
	Token_Tag tag;
} Token;


typedef struct {
	Token *items;
	int32_t length;
	int32_t capacity;
} Token_Array;


Token token_make(Token_Tag tag, int32_t line, int32_t column, String value);
Token_Array token_new_array(int32_t capacity);
int32_t token_len(Token_Array a);
Token token_at(Token_Array a, int32_t index);
Token_Array token_push(Token_Array a, Token t);


#endif // TOKEN_H
