#include <stdio.h>
#include <stdlib.h>

#include "string.h"


String stringNew (size_t length)
{
    return (String) {
        .start = calloc (length + 1, sizeof (char)),
        .length = length
    };
}

void stringFree (String *s)
{
    free (s->start);
    *s = (String) {
        .start = NULL,
        .length = 0
    };
}

void stringPrint (String s)
{
    printf ("%s", s.start);
}

String stringReadFrom (char *filepath) {
    FILE *stream = fopen (filepath, "r");
    if (stream == NULL) {
        printf ("unable to open input file\n");
    }

    fseek (stream, 0, SEEK_END);
    size_t size = ftell (stream);
    rewind (stream);

    String s = stringNew (size);
    fread (s.start, sizeof(char), size, stream);
    s.start[size] = '\0';
    fclose (stream);

    return s;
}
