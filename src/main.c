#include <stdio.h>
#include "string.h"
#include "lexer.h"


int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s <filepath>", argv[0]);
		return 1;
	}

	String source = str_read_from(argv[1]);

	Lexer lexer;
	lexer_new(&lexer, argv[1], source);
	lexer_run(&lexer);

	str_free(&source);
	return 0;
}
