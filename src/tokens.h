#ifndef TOKENS_H
#define TOKENS_H


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
	Token_Tag tag;
} Token;


#endif // TOKENS_H
