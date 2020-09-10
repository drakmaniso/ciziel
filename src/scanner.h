#ifndef SCANNER_H
#define SCANNER_H


#include <stdint.h>
#include "string.h"
#include "token.h"


typedef struct {
	char *name;
	String input;
	String_Pos start;
	String_Pos pos;
} Scanner;


void Scanner_make (Scanner *s, char *filepath, String input);
void Scanner_run (Scanner *s);
void Scanner_print (Token t);


#endif // SCANNER_H
