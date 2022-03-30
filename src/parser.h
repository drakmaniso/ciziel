#ifndef PARSER_H
#define PARSER_H


#include "global.h"
#include "token.h"
#include "ast.h"


typedef struct {
    char *filename;
    Array_Token tokens;
    AST ast;
    size_t start;
    size_t pos;
} Parser;


Parser Parser_new(char *filepath, Array_Token tokens);


#endif // PARSER_H