#ifndef SCANNER_H
#define SCANNER_H


#include "global.h"
#include "token.h"


typedef struct {
	String input;
	size_t start;
	size_t pos;
	bool at_line_start;
} Scanner;


Scanner Scanner_new(String input);
Token Scanner_next_token(Scanner *self);


#endif // SCANNER_H
