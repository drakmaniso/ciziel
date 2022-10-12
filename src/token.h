#ifndef TOKEN_H
#define TOKEN_H


#include "global.h"


typedef enum TokenTag {
	Token_None,

	// Keywords
	Token_Let,
	Token_If,
	Token_Else,
	Token_Fun,
	
	// Delimiters
	Token_LBrace,
	Token_RBrace,
	Token_LParen,
	Token_RParen,
	Token_Colon,
	Token_Equal,
	Token_Semicolon,
	Token_Comma,

	// Operators
	Token_Arrow,
	Token_Plus,

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
	bool at_line_start;
} Token;

Array_typedef(Token);


Token Token_new(size_t pos, String value, TokenTag tag, bool at_line_start);
void Token_print(Token self);


#endif // TOKEN_H
