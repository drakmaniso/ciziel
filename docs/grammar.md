# Grammar

## Keywords

    module

Definitions:

    let

Signatures:

    mut ->

Control-flow:

    if then else
    while do

End:

    end

## PEG Grammar

    Program <- Definition*
    Definition <- FuncDef / ConstDef
    FuncDef <- 'let' FuncName '(' Parameter (',' Parameter)* ')' '->' Type '=' ExpressionSeq 'end'
    Parameter <- 'mut'? ParamName ':' Type