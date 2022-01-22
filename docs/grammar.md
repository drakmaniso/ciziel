# Grammar

## Keywords

    module
    let def
    mut
    if then else while do
    return
    end

## Operators

    -> = <-

## PEG Grammar

    ID = [a-z][a-z0-9!_-]*
    TYPEID = [A-Z][A-Za-z0-9!_-]*
    TYPEVARID = [A-Z][A-Z0-9!_-]*
    TRAITID = [#][a-z][a-z0-9_-]*

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