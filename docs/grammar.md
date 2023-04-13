# Grammar

This document present the grammar of the language (currently, only part of the
core language).

## Keywords

    module use
    forall
    val fun type alias dispatch
    require ensure
    match if then else
    not and or

## Delimiters

    ( ) { } [ ]
    . ...
    : ::
    ,
    | ;

## Operators

    ->
    =
    == != < <= > >=
    + - * /
    not and or

## Identifiers

    ID <- [a-z_][A-Za-z0-9_-]*[']*

    TYPE-ID <- [A-Z][A-Za-z0-9_-]*[']*

    OPERATOR-ID <- [<][a-z][A-Za-z0-9_-]*[']*[>]

## PEG Grammar

    program <- declaration*

    declaration <- "val" ID ":" type "=" expr

    type <- "Int" / "Bool" / "\" "(" type ("," type)* ")" "->" type

    expr <- comparison

    comparison <- binary (("==" / "!=" / "<" / "<=" / ">" / ">=") binary)?

    binary <- unary binary-tail

    binary-tail <- (("+" / "-") unary)* / ("*" unary)* / ("/" unary)*
                    / ("and" unary)* / ("or" unary)*

    unary <- "-" call / "not" call / call

    call <- primary arguments*

    primary <- if-expr / lambda / atom

    if-expr <- "if" expr block "else" block

    lambda <- "\" "(" IDENTIFIER ("," IDENTIFIER)* ")" block

    block <- "{" (statement ";"?)* "}"

    statement <- declaration / expr

    arguments <- ~"(" (expr ("," expr)*)? ")"

    atom <- IDENTIFIER / LITERAL / paren-expr

    paren-expr <- "(" expr ")"

---
[Back to index](index.md)
