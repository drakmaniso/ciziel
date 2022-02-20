# Grammar

## Keywords

    module use
    public forall
    unique struct trait alias
    const func where
    require ensure
    match case if then else

    and or not

## Operators

    \ -> =>
    = :=
    |
    + - * /


## PEG Grammar (for the core language only)


    ID = [a-z][A-Za-z0-9-]*

    Module <- TopLevelDef*
    TopLevelDef <- ConstDef

    ConstDef <- CONST ID EQUAL LocalDef* Expr

    Expr <- ControlExpr / SimpleExpr

    LocalDef <- ID EQUAL Expr

    ControlExpr <- MatchExpr / LambdaExpr

    LambdaExpr <- LAMBDA ID (LAMBDA ID)* DOUBLEARROW LocalDef* Expr

    SimpleExpr <- Atom (FuncCallTail / DotAccessTail)*
    FuncCallTail <- Tuple
    DotAccess <- DOT ID

    Atom <- Identifier / Literal / Tuple
    Identifier <- ID
    Literal <- NUMBER
    Tuple <- LPAREN Expr (COMMA Expr)* RPAREN



---
[Back to index](index.md)
