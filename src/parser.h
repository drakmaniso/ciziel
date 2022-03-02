#ifndef PARSER_H
#define PARSER_H


#include "global.h"
#include "token.h"
#include "ast.h"


typedef struct {
    char *filename;
    ArrayToken tokens;
    ArrayModule ast;
    size_t start;
    size_t pos;
} Parser;


Parser parser_new(char *filepath, ArrayToken tokens);


#endif // PARSER_H