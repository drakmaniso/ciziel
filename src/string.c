#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"


String str_new(size_t length)
{
	return (String) {
		.start = calloc(length + 1, sizeof(char)),
		.length = length
	};
}


void str_free(String *s)
{
	free(s->start);
	*s = (String) {
		.start = NULL,
		.length = 0
	};
}


String str_slice(String s, USize start, USize end) {
	return (String) {
		.start = s.start + start,
		.length = end - start
	};
}


Rune str_at(String s, USize index) {
	return s.start[index];
}


USize str_length(String s) {
	return s.length;
}


void str_print(String s)
{
	fwrite(s.start, sizeof(char), s.length, stdout);
}


String str_read_from(char *filepath) {
	FILE *stream = fopen(filepath, "r");
	if (stream == NULL) {
		printf("unable to open input file\n");
	}

	fseek(stream, 0, SEEK_END);
	size_t size = ftell(stream);
	rewind(stream);

	String s = str_new(size);
	fread(s.start, sizeof(char), size, stream);
	s.start[size] = '\0';
	fclose(stream);

	return s;
}


bool str_is(String s, char *cs) {
	size_t len = strlen(cs);
	if (str_length(s) == len && strncmp(s.start, cs, len) == 0) {
		return true;
	}
	return false;
}
