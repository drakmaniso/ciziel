#ifndef STRINGS_H
#define STRINGS_H


#include "global.h"


typedef struct {
	char *start;
	size_t length;
} String;


String String_new(size_t length);
void String_free(String *s);
String String_slice(String s, size_t start, size_t end);
void String_print(String s);
String String_read_from(char *filepath);
bool String_is(String s, char *cs);
size_t String_length(String s);
char String_at(String s, size_t index);


#endif // STRINGS_H
