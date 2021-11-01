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


void lexer_make(Lexer *s, char *filepath, String input);
void lexer_run(Lexer *s);
void lexer_print(Token t);


#endif // SCANNER_H
