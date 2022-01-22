#ifndef AST_H
#define AST_H


#include "global.h"


array_def(TopLevelDef);


typedef enum ASTTag {
    ast_Module,
    ast_TopLevelDef,
    ast_FuncDef,
    ast_TypeName,
    ast_Literal,
};


typedef struct {
    TopLevelDefArray definitions;
} Module;


typedef struct {
    ASTTag tag;
    union {
        FuncDef func_def;
    };
} TopLevelDef;


typedef struct {
    Token name;
    TypeName return_type;
    Literal body;
} FuncDef;


typedef struct {
    Token name;
} TypeName;


typedef struct {
    Token number;
} Literal;


#endif // AST_H