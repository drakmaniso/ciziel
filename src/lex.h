#ifndef LEX_H
#define LEX_H


#include <stdint.h>

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


typedef struct {
    char *name;
    String input;
    int32_t start;
    int32_t pos;
} Lexer;


void lexPrint (Token t);


#endif // LEX_H
