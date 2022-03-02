#ifndef AST_H
#define AST_H


#include "global.h"


typedef enum {
    ast_Module,
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


array_typedef(TopLevelDef);


typedef struct {
    ArrayTopLevelDef definitions;
} Module;


array_typedef(Module);


#endif // AST_H