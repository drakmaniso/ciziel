# Grammar

## Keywords

    module
    let def
    mut
    if then else while do
    end

## Operators

    ->

## PEG Grammar

    ID = [a-z][A-Za-z0-9!-]*
    TYPEID = [A-Z][A-Za-z0-9!-]*

    Program <- TopLevelDefinition*
    TopLevelDefinition <- FuncDef / ConstDef
    FuncDef <- (LET / DEF) ID LPAREN Parameter (COMMA Parameter)* RPAREN RARROW Type EQUAL ExprSequence END
    Parameter <- MUT? ID COLON Type

    ExprSequence <- (OpenExpr SEMICOLON / ClosedExpr)* OpenExpr?

    Expr <- OpenExpr / ClosedExpr
    OpenExpr <- LocalDef / CallChain / TupleExpr
    ClosedExpr <- IfExpr / WhileExpr / DoExpr

    LocalDef <- MUT? ID EQUAL Expr
    CallChain <- ID (DOT ID)* TupleExpr*
    TupleExpr <- LPAREN Label? Expr (COMMA Expr)* RPAREN

    IfExpr <- IF ExprSequence THEN ExprSequence (ELSE ExprSequence)? END
    WhileExpr <- WHILE ExprSequence DoExpr
    DoExpr <- DO ExprSequence END