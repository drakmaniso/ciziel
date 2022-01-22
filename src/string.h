#ifndef STRINGS_H
#define STRINGS_H


#include "global.h"


typedef struct {
	char *start;
	size_t length;
} String;


String str_new(size_t length);
void str_free(String *s);
String str_slice(String s, size_t start, size_t end);
void str_print(String s);
String str_read_from(char *filepath);
bool str_is(String s, char *cs);
size_t str_length(String s);
char str_at(String s, size_t index);


#endif // STRINGS_H
