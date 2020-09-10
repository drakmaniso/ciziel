#ifndef STRINGS_H
#define STRINGS_H


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef int32_t String_Pos;


typedef struct {
	char *start;
	String_Pos length;
} String;


typedef char Rune;


String String_new (size_t length);
void String_free (String *s);
String String_slice (String s, String_Pos start, String_Pos end);
void String_print (String s);
String String_read_from (char *filepath);
bool String_is (String s, char *cs);
String_Pos String_length (String s);
Rune String_at (String s, String_Pos index);


#endif // STRINGS_H
