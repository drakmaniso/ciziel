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

Keyword operators:

    =
    \ =>

Type operators:

    | ->

Logic and comparison:

    and or == /= < <= > >=

Term:

    + -

Factor:

    * /

Unary:

    not -


## PEG Grammar (for the core language only)


    ID = [a-z][A-Za-z0-9-]*

    Module <- TopLevelDef*
    TopLevelDef <- ConstDef

    ConstDef <- CONST ID EQUAL LocalDef* Expr

    LocalDef <- ID EQUAL Expr

    Expr <- MatchExpr / LambdaExpr / BinaryExpr

    LambdaExpr <- LAMBDA ID (LAMBDA ID)* DARROW LocalDef* Expr

    BinaryExpr <- UnaryExpr (
            (AND UnaryExpr)*
            / (OR UnaryExpr)*
            / (EQ UnaryExpr)*
            / (DIFF UnaryExpr)*
            / (LT UnaryExpr)*
            / (LTE UnaryExpr)*
            / (GT UnaryExpr)*
            / (GTE UnaryExpr)*
            / (MINUS UnaryExpr)*
            / (PLUS UnaryExpr)*
            / (SLASH UnaryExpr)*
            / (ASTERISK UnaryExpr)*
        )

    UnaryExpr <- (NOT / MINUS) UnaryExpr / Call

    Call <- Primary (LPAREN Arguments? RPAREN / DOT ID)*
    Arguments <- Expr (COMMA  Expr)*


    Primary <- Identifier / Literal / Tuple
    Identifier <- ID
    Literal <- NUMBER
    Tuple <- LPAREN Expr (COMMA Expr)* RPAREN


---
[Back to index](index.md)
