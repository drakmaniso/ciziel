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

    Program <- Definition*
    Definition <- FuncDef / ConstDef
    FuncDef <- ('let' / 'def') Name '(' Parameter (',' Parameter)* ')' '->' Type '=' ExprSequence 'end'
    Parameter <- 'mut'? Name ':' Type