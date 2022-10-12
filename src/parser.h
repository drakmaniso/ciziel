#ifndef PARSER_H
#define PARSER_H


#include "global.h"
#include "token.h"
#include "ast.h"


typedef struct {
    char *filename;
    Token current;
    AST ast;
    size_t start;
    size_t pos;
} Parser;


AST Parser_parse(char *filepath);


#endif // PARSER_H