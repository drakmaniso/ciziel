#ifndef TOKEN_H
#define TOKEN_H


#include <stddef.h>
#include "string.h"


typedef enum Token_Tag {
	Token_None,
	Token_Keyword,
	Token_Identifier,
	Token_Operator,
	Token_Number,
	Token_Equal,
	Token_Arrow,
	Token_Semicolon,
	Token_EOF,
	Token_Invalid
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


Token Token_make (Token_Tag tag, int32_t line, int32_t column, String value);
Token_Array Token_new_array (int32_t capacity);
int32_t Token_len (Token_Array a);
Token Token_at (Token_Array a, int32_t index);
Token_Array Token_push (Token_Array a, Token t);


#endif // TOKEN_H
