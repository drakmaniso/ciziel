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
} Scanner;


void scan_make(Scanner *s, char *filepath, String input);
void scan_run(Scanner *s);
void scan_print(Token t);


#endif // SCANNER_H
