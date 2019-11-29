#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    if (argc != 2) {
        printf ("Usage: %s <filepath>", argv[0]);
        return 1;
    }

    char *filepath = argv[1];

    FILE *stream = fopen (filepath, "r");
    if (stream == NULL) {
        printf ("unable to open input file\n");
    }

    fseek (stream, 0, SEEK_END);
    size_t size = ftell (stream);
    rewind (stream);

    char *source;
    source = (char *)calloc (size + 1, sizeof (char));
    fread (source, sizeof(char), size, stream);
    source[size] = '\0';
    fclose (stream);

    printf ("Source:\n%s", source);

    free (source);
    return 0;
}        
