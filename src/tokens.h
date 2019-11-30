#ifndef TOKENS_H
#define TOKENS_H


#include "string.h"


typedef enum TokenType {
	tokNone,
	tokIndent,
	tokKeyword,
	tokIdentifier,
	tokNumber,
	tokDefine,
	tokEOF,
	tokInvalid
} TokenType;


typedef struct {
	String value;
	TokenType type;
} Token;


#endif // TOKENS_H
