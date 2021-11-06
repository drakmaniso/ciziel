#ifndef SCANNER_H
#define SCANNER_H


#include "global.h"
#include "string.h"
#include "array.h"


typedef struct {
	char *name;
	String input;
	size_t start;
	size_t pos;
} Lexer;


void lexer_new(Lexer *self, char *filepath, String input);
Array lexer_tokenize(Lexer *self);


#endif // SCANNER_H
