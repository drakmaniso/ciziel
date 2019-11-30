#ifndef SCANNER_H
#define SCANNER_H


#include <stdint.h>
#include "string.h"
#include "tokens.h"


typedef struct {
	char *name;
	String input;
	stringPos start;
	stringPos pos;
} Scanner;


void scanMake (Scanner *s, char *filepath, String input);
void scanRun (Scanner *s);
void scanPrint (Token t);


#endif // SCANNER_H
