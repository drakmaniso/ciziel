#ifndef PARSER_H
#define PARSER_H


#include "global.h"


typedef struct {
    char *filename;
    TokenArray tokens;
    size_t start;
    size_t pos;
} Parser;


#endif // PARSER_H