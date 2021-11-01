#ifndef TOKEN_H
#define TOKEN_H


#include <stddef.h>
#include "string.h"


typedef enum tok_Tag {
	tok_None,

	// Keywords
	tok_Public,
	tok_Do,
	tok_If,
	tok_Then,
	tok_Else,
	tok_End,
	
	// Delimiters
	tok_Semicolon,
	tok_LeftParen,
	tok_RightParen,
	tok_Comma,
	tok_Quote,

	// Operators
	tok_Equal,
	tok_Arrow,

	// Literals and identifiers
	tok_Number,
	tok_Identifier,

	tok_EOF,
	tok_Invalid
} tok_Tag;


typedef struct {
	String value;
	int32_t line;
	int32_t column;
	tok_Tag tag;
} Token;


typedef struct {
	Token *items;
	int32_t length;
	int32_t capacity;
} tok_Array;


Token tok_make(tok_Tag tag, int32_t line, int32_t column, String value);
tok_Array tok_new_array(int32_t capacity);
int32_t tok_len(tok_Array a);
Token tok_at(tok_Array a, int32_t index);
tok_Array tok_push(tok_Array a, Token t);


#endif // TOKEN_H
