#include <stdio.h>

#include "string.h"


int main (int argc, char **argv)
{
    if (argc != 2) {
        printf ("Usage: %s <filepath>", argv[0]);
        return 1;
    }

    String source = stringReadFrom (argv[1]);

    printf ("Source:\n");
    stringPrint (source);

    stringFree (&source);
    return 0;
}        
