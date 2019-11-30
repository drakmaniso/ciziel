```

Module = Definitions+

Definition = VariableName '=' << Expression >>

Expression = Function / FunctionCall / SubExpression

Function = 'func' VariableName+ '->' << Expression >>

FunctionCall = SubExpression << SubExpression+ >>

SubExpression = VariableName / Number / '(' Expression ')'



VariableName = letter (letter / digit)*

Number = digit+

```
