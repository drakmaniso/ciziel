#include "global.h"
#include "parser.h"
#include "ast.h"


Parser Parser_new(char *filepath, ArrayToken tokens) {
    return (Parser) {
        .filename = filepath,
        .tokens = tokens,
        .ast = Array_new(Module, 8),
        .ast = NULL,
        .start = 0,
        .pos = 0,
    };
}


