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
	variable_identifier = lowercase { lowercase | digit | underscore }
	type_identifier = uppercase lowercase { lowercase | digit | underscore }
	type_variable_identifier = uppercase
	concept_identifier = uppercase { uppercase | digit | underscore }

    Source_file = Section { Section }
	Section = Public_section
	Public_section = "public" ";" { Top_level_definition }

	Top_level_definition = Constant_definition
	Constant_definition = identifier "=" Expression
	
	Expression = Lambda [";"]
	Lambda = Application "->" Lambda | Application
	Application = Primary { Primary }
	Primary = Do_block | If_block | Tuple | variable_identifier | number
	Tuple = "(" Expression { "," Expression } [","] ")"

