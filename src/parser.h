#ifndef PARSER_H
#define PARSER_H


#include "global.h"
#include "token.h"
#include "ast.h"


typedef struct {
    char *filename;
    TokenArray tokens;
    ConstDef *ast;
    size_t start;
    size_t pos;
} Parser;


Parser parser_new(char *filepath, TokenArray tokens);


#endif // PARSER_H