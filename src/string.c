#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"


String String_new(size_t length)
{
	return (String) {
		.start = calloc(length + 1, sizeof(char)),
		.length = length
	};
}


void String_free(String *s)
{
	free(s->start);
	*s = (String) {
		.start = NULL,
		.length = 0
	};
}


String String_slice(String s, String_Pos start, String_Pos end) {
	return (String) {
		.start = s.start + start,
		.length = end - start
	};
}


Rune String_at(String s, String_Pos index) {
	return s.start[index];
}


String_Pos String_length(String s) {
	return s.length;
}


void String_print(String s)
{
	fwrite(s.start, sizeof(char), s.length, stdout);
}


String String_read_from(char *filepath) {
	FILE *stream = fopen(filepath, "r");
	if (stream == NULL) {
		printf("unable to open input file\n");
	}

	fseek(stream, 0, SEEK_END);
	size_t size = ftell(stream);
	rewind(stream);

	String s = String_new(size);
	fread(s.start, sizeof(char), size, stream);
	s.start[size] = '\0';
	fclose(stream);

	return s;
}


bool String_is(String s, char *cs) {
	size_t len = strlen(cs);
	if (String_length(s) == len && strncmp(s.start, cs, len) == 0) {
		return true;
	}
	return false;
}
