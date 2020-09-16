# Grammar

This is a tentative grammar for the inital subset of the language.

## Precedence

                      Operators:                 Associates:
    Arrow             ->                         Right
    Application       (none)                     Left
	Quote             '                          Right



    a b c             <-->       (a b) c
	a -> b -> c       <-->       a -> (b -> c)
	a -> b c          <-->       a -> (b c)
	a b -> c          <-->       ERROR: (a b) -> c


## EBNF


    delimiter = "'" | ";" | "," | "(" | ")"
    operator = "=" | "->"
    keyword = "public" | "do" | "end" | "if" | "then" | "else"
    number = digit { digit }
	variable_name = lowercase { lowercase | digit | underscore }
	type_name = uppercase lowercase { lowercase | digit | underscore }
	type_variable_name = uppercase
	concept_name = uppercase { uppercase | digit | underscore }

    Source_file = "module" module_name { Top_definition } "private" { Top_level_definition }

	Top_level_definition = Definition | Type_definition | Concept_definition
	Definition = identifier "=" Expression ";"
	
	Expression = Lambda
	Lambda = Application "->" Lambda | Application
	Application = Primary { Primary }
	Primary = Do_block | If_block | Tuple | variable_identifier | number
	Tuple = "(" Expression { "," Expression } [","] ")"

	Do_block = "do" { Definition } Expression "end"
	If_block = "if" Expression "then" { Definition } Expression "else" { Definition } Expression "end"
