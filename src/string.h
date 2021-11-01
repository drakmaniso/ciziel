#ifndef STRINGS_H
#define STRINGS_H


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef uintptr_t USize;


typedef struct {
	char *start;
	USize length;
} String;


typedef char Rune;


String str_new(size_t length);
void str_free(String *s);
String str_slice(String s, USize start, USize end);
void str_print(String s);
String str_read_from(char *filepath);
bool str_is(String s, char *cs);
USize str_length(String s);
Rune str_at(String s, USize index);


#endif // STRINGS_H
