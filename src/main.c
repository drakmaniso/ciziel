#include <stdio.h>
#include "string.h"
#include "scanner.h"


int main (int argc, char **argv)
{
    if (argc != 2) {
        printf ("Usage: %s <filepath>", argv[0]);
        return 1;
    }

    String source = stringReadFrom (argv[1]);

    Scanner scanner;
    scanMake (&scanner, argv[1], source);
    scanRun (&scanner);

    stringFree (&source);
    return 0;
}        
