#ifndef STRINGS_H
#define STRINGS_H


#include <stdint.h>


typedef struct {
    char *start;
    int32_t length;
} String;


String stringNew (size_t length);
void stringFree (String *s);
void stringPrint (String s);
String stringReadFrom (char *filepath);


#endif // STRINGS_H
