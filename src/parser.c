#include "global.h"
#include "parser.h"
#include "ast.h"


Parser parser_new(char *filepath, TokenArray tokens) {
    return (Parser) {
        .filename = filepath,
        .tokens = tokens,
        .ast = NULL,
        .start = 0,
        .pos = 0,
    };
}


