#include "global.h"
#include "parser.h"
#include "ast.h"


Parser Parser_new(char *filepath, Array_Token tokens) {
    return (Parser){
        .filename = filepath,
        .tokens = tokens,
        .ast = (AST) { .root = NULL },
        .start = 0,
        .pos = 0,
    };
}


AST Parser_parse(Parser *self) {
    // parse_number(self);
    return self->ast;
}