#include <stdio.h>
#include "global.h"
#include "parser.h"


int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s <filepath>", argv[0]);
		return 1;
	}

	AST ast = Parser_parse(argv[1]);

	return 0;
}
