#ifndef SCANNER_H
#define SCANNER_H


#include <stdint.h>
#include "string.h"
#include "token.h"


typedef struct {
	char *name;
	String input;
	USize start;
	USize pos;
} Lexer;


void lexer_new(Lexer *self, char *filepath, String input);
void lexer_run(Lexer *self);


#endif // SCANNER_H
