#ifndef TOKENS_H
#define TOKENS_H


#include "string.h"


typedef enum TokenType {
	tokNone,
	tokKeyword,
	tokIdentifier,
	tokOperator,
	tokNumber,
	tokEqual,
	tokArrow,
	tokSemicolon,
	tokEOF,
	tokInvalid
} TokenType;


typedef struct {
	String value;
	TokenType type;
} Token;


#endif // TOKENS_H
