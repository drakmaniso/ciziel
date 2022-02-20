#ifndef AST_H
#define AST_H


#include "global.h"


typedef enum {
    ast_TopLevelDef,
    ast_ConstDef,
    ast_Literal,
} ASTTag;


typedef struct {
    Token number;
} Literal;


typedef struct {
    Token name;
    Literal *body;
} ConstDef;


typedef struct {
    ASTTag tag;
    union {
        ConstDef *const_def;
    };
} TopLevelDef;


#endif // AST_H