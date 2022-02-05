# Grammar

## Keywords

    module use
    public forall
    unique struct trait alias
    const func where
    match case if then else

    and or not

## Operators

    -> =>
    = :=
    |
    + - * /


## PEG Grammar

(Out of date)

    ID = [a-z][a-z0-9-]*
    TYPEID = [A-Z][A-Za-z0-9-]*
    TYPEVARID = [A-Z][A-Z0-9-]*
    SOURCEVARID = [&][a-z0-9-]*
    TRAITID = [#][a-z][a-z0-9-]*

    Module <- TopLevelDef*
    TopLevelDef <- FuncDef / ConstDef
    FuncDef <- (LET / DEF) ID LPAREN Parameter (COMMA Parameter)* RPAREN RARROW TypeExpr EQUAL ExprSequence END
    Parameter <- MUT? ID COLON TypeExpr

    Expr <- ControlExpr / SimpleExpr
    ExprSequence <- ((SeqOnlyExpr / ControlExpr / SimpleExpr) SEMICOLON?)+

    SeqOnlyExpr <- LocalDef / ReturnExpr
    LocalDef <- MUT? ID EQUAL Expr
    ReturnExpr <- RETURN Expr

    ControlExpr <- IfExpr / WhileExpr / DoExpr
    IfExpr <- IF SimpleExpr THEN ExprSequence (ELSE ExprSequence)? END
    WhileExpr <- WHILE SimpleExpr DoExpr
    DoExpr <- DO ExprSequence END

    SimpleExpr <- AtomExpr (FuncCallTail / DotAccessTail)*
    FuncCallTail <- TupleExpr
    DotAccessTail <- DOT ID
    AtomExpr <- Identifier / Literal / TupleExpr
    TupleExpr <- LPAREN Expr (COMMA Expr)* RPAREN
    Identifier <- ID
    Literal <- NUMBER


    TypeExpr <- FuncType / TupleType / NamedType
    FuncType <- TypeExpr RARROW TypeExpr
    TupleType <- LPAREN TypeExpr (COMMA TypeExpr)* COMMA? RPAREN
    NamedType <- TypeName TypeParams? TypeTraits?
    TypeTraits <- TraitIdentifier+
    TypeParams <- LBRACKET TypeExpr (COMMA TypeExpr)* COMMA? RBRACKET
    TypeName <- TYPEID / TYPEVARID
    TraitIdentifier <- TRAITID



---
[Back to index](index.md)
