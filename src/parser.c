#include "global.h"
#include "scanner.h"
#include "parser.h"
#include "ast.h"


AST Parser_parse(char *filepath) {
	String source = String_read_from(filepath);
	
    Scanner scanner = Scanner_new(source);

    Parser parser = (Parser){
        .filename = filepath,
        .current = Token_new(0, String_slice(source, 0, 0), Token_None, true),
        .ast = (AST) { .root = NULL },
        .start = 0,
        .pos = 0,
    };

	while (true) {
		Token token = Scanner_scan(&scanner);
		Token_print(token);
		if (token.tag == Token_EOF) {
			break;
		}
	}

	String_free(&source);
    return parser.ast;
}