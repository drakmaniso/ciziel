#ifndef STRINGS_H
#define STRINGS_H


#include <stdint.h>


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


#endif // STRINGS_H
