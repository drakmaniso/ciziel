#include <stdio.h>
#include "global.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"


int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s <filepath>", argv[0]);
		return 1;
	}

	String source = String_read_from(argv[1]);

	Lexer lexer;
	Lexer_new(&lexer, argv[1], source);
	ArrayToken tokens = Lexer_tokenize(&lexer);

	for(size_t i = 0; i < Array_length(tokens); i++) {
		Token tok = Array_at(tokens, i);
		Token_print(tok);
	}

	Parser parser = Parser_new(argv[1], tokens);

	String_free(&source);
	return 0;
}
