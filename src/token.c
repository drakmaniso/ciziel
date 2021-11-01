#include <stdio.h>
#include <stdlib.h>
#include "token.h"


Token token_make(Token_Tag c, int32_t line, int32_t column, String value) {
	return (Token) {
		.value = value,
		.tag = c,
		.line = line,
		.column = column
	};
}


Token_Array token_new_array(int32_t capacity) {
	return (Token_Array) {
		.items = calloc(capacity, sizeof(Token)),
		.length = 0,
		.capacity = capacity
	};
}


int32_t token_len(Token_Array a) {
	return a.length;
}


Token token_at(Token_Array a, int32_t index) {
	if (index >= a.length) {
		printf("PANIC: out-of-bound Token_Array index\n");
		exit(1);
	}
	return a.items[index];
}


Token_Array token_push(Token_Array a, Token t) {
	if (a.length >= a.capacity) {
		printf("NOT YET IMPLEMENTED: Token_Array growth");
		exit(1);
	}
	a.items[a.length] = t;
	return (Token_Array) {
		.items = a.items,
		.length = a.length + 1,
		.capacity = a.capacity
	};
}

