#ifndef SCANNER_H
#define SCANNER_H


#include "global.h"
#include "token.h"


typedef struct {
	char *name;
	String input;
	USize start;
	USize pos;
} Lexer;


void lexer_new(Lexer *self, char *filepath, String input);
void lexer_tokenize(Lexer *self);


#endif // SCANNER_H
