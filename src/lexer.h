#ifndef SCANNER_H
#define SCANNER_H


#include "global.h"
#include "token.h"


typedef struct {
	char *name;
	String input;
	size_t start;
	size_t pos;
	bool at_line_start;
} Lexer;


void Lexer_new(Lexer *self, char *filepath, String input);
ArrayToken Lexer_tokenize(Lexer *self);


#endif // SCANNER_H
