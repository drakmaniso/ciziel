# Grammar

This document present the grammar of the language (currently, only part of the
core language).

## Lexing

The language is whitespace insensitive, with one small exception: in a function call, the opening parenthesis must be on the same line as the function.

## Semicolon Insertion Rule

If a line starts with an opening parenthesis and the previous line does *not* end with an operator, then a semicolon is inserted before the parenthesis.

### Delimiters

    DELIMITERS <-
        | "(" | ")" | "{" | "}" | "[" | "]"
        | "." | "..."
        | ":" | "::"
        | "," | ";"

### Operators

    | ->
    =
    == != < <= > >=
    + - * /
    not and or

### Keywords

    KEYWORDS <-
        | "module" | "use" | "from"
        | "forall" | "extend" | "as" | "to" | "ref"
        | "val" | "fun" | "type" | "alias" | "dispatch"
        | "require" | "ensure"
        | "match" | "if" | "then" | "else"
        | "not" | "and" | "or"

### Identifiers

    IDENT <- [a-z_][A-Za-z0-9_-]*[']*

    OPERATOR-ID <- [<][a-z][A-Za-z0-9_-]*[']*[>]

## PEG Grammar

    program <- declaration*

    declaration <- "val" IDENT ":" type "=" expr

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

    lambda <- "\" "(" IDENT ("," IDENT)* ")" block

    block <- "{" (statement ";"?)* "}"

    statement <- declaration / expr

    arguments <- ~"(" (expr ("," expr)*)? ")"

    atom <- IDENT / LITERAL / paren-expr

    paren-expr <- "(" expr ")"

---
[Back to index](index.md)
