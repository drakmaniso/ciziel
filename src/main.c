#include <stdio.h>

#include "string.h"
#include "lex.h"


int main (int argc, char **argv)
{
    if (argc != 2) {
        printf ("Usage: %s <filepath>", argv[0]);
        return 1;
    }

    String source = stringReadFrom (argv[1]);

    //printf ("Source:\n");
    //stringPrint (source);

    Lexer lexer;
    lexMake (&lexer, argv[1], source);
    lexRun (lexer);

    stringFree (&source);
    return 0;
}        
