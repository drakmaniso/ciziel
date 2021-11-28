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

    ID = [a-z][A-Za-z0-9!-]*
    TYPEID = [A-Z][A-Za-z0-9!-]*

    Program <- TopLevelDef*
    TopLevelDef <- FuncDef / ConstDef
    FuncDef <- (LET / DEF) ID LPAREN Parameter (COMMA Parameter)* RPAREN RARROW Type EQUAL ExprSequence END
    Parameter <- MUT? ID COLON Type

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
    AtomExpr <- ID / NUMBER / TupleExpr
    TupleExpr <- LPAREN Expr (COMMA Expr)* RPAREN

