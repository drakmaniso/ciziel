# Grammar

This document present the grammar of the language (currently, only part of the
core language).

## Keywords

    module use
    forall def let var
    require ensure
    match case if then else
    and or not
    fun
    ___ _

## Delimiters

    ( ) { } [ ]
    :: .
    : =
    , ;
    \

## Operators

    |
    ->
    not
    and or
    == != < <= > >=
    -
    + - * /

## Identifiers

    ID <- [a-z_][_A-Za-z0-9-]*[']*

    TYPE-ID <- [A-Z][_A-Za-z0-9-]*[']*

    OPERATOR-ID <- [<][a-z][_A-Za-z0-9-]*['][>]

## PEG Grammar (for the currently implemented part of the language)

    program <- declaration*

    declaration <- "let" ID ":" type "=" expr

    type <- "Int" / "Bool" / "\" "(" type ("," type)* ")" "->" type

    expr <- unary / binary / function-call

    unary <- "-" term / "not" term

    binary <- term binary-tail

    binary-tail <- (("+" / "-") term)* / ("*" term)* / ("/" term)*
                    / ("and" term)* / ("or" term)*
                    / "==" term / "<" term / "<=" term / ">". term / ">=" term

    function-call <- term arguments*

    term <- if-expr / lambda / function-call

    if-expr <- "if" expr block "else" block

    lambda <- "\" "(" IDENTIFIER ("," IDENTIFIER)* ")" block

    block <- "{" (statement ";"?)* "}"

    statement <- declaration / expr

    arguments <- ~"(" (expr ("," expr)*)? ")"

    atom <- IDENTIFIER / LITERAL / paren-expr

    paren-expr <- "(" expr ")"

---
[Back to index](index.md)
