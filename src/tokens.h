#ifndef TOKENS_H
#define TOKENS_H


#include "string.h"


typedef enum TokenType {
	tokNone,
	tokEOF,
	tokKeyword,
	tokIdentifier,
	tokNumber,
	tokDefine,
	tokInvalid
} TokenType;


typedef struct {
	String value;
	TokenType type;
} Token;


#endif // TOKENS_H
