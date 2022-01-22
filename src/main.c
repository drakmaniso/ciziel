#include <stdio.h>
#include "global.h"
#include "lexer.h"
#include "token.h"


int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s <filepath>", argv[0]);
		return 1;
	}

	String source = str_read_from(argv[1]);

	Lexer lexer;
	lexer_new(&lexer, argv[1], source);
	TokenArray tokens = lexer_tokenize(&lexer);

	for(size_t i = 0; i < array_length(tokens); i++) {
		Token tok = array_at(tokens, i);
		token_print(tok);
	}

	str_free(&source);
	return 0;
}
