#include <stdio.h>
#include "string.h"
#include "scanner.h"


int main (int argc, char **argv)
{
	if (argc != 2) {
		printf ("Usage: %s <filepath>", argv[0]);
		return 1;
	}

	String source = String_read_from (argv[1]);

	Scanner scanner;
	Scanner_make (&scanner, argv[1], source);
	Scanner_run (&scanner);

	String_free (&source);
	return 0;
}
