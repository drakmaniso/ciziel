#ifndef AST_H
#define AST_H


#include "global.h"


typedef enum {
    ast_Literal,
} ASTTag;


typedef struct {
    Token number;
} Literal;


typedef struct {
    Literal *root;
} AST;


#endif // AST_H