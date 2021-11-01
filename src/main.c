#include <stdio.h>
#include "string.h"
#include "scanner.h"


int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s <filepath>", argv[0]);
		return 1;
	}

	String source = str_read_from(argv[1]);

	Scanner scanner;
	scan_make(&scanner, argv[1], source);
	scan_run(&scanner);

	str_free(&source);
	return 0;
}
