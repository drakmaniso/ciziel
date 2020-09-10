#ifndef STRINGS_H
#define STRINGS_H


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef int32_t stringPos;


typedef struct {
	char *start;
	stringPos length;
} String;


typedef char Rune;


String stringNew (size_t length);
void stringFree (String *s);
String stringSlice (String s, stringPos start, stringPos end);
void stringPrint (String s);
String stringReadFrom (char *filepath);
bool stringIs (String s, char *cs);
stringPos stringLength (String s);
Rune stringAt (String s, stringPos index);


#endif // STRINGS_H
