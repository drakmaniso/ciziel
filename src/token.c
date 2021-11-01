#include <stdio.h>
#include <stdlib.h>
#include "token.h"


Token tok_make(tok_Tag c, int32_t line, int32_t column, String value) {
	return (Token) {
		.value = value,
		.tag = c,
		.line = line,
		.column = column
	};
}


tok_Array tok_new_array(int32_t capacity) {
	return (tok_Array) {
		.items = calloc(capacity, sizeof(Token)),
		.length = 0,
		.capacity = capacity
	};
}


int32_t tok_len(tok_Array a) {
	return a.length;
}


Token tok_at(tok_Array a, int32_t index) {
	if (index >= a.length) {
		printf("PANIC: out-of-bound tok_Array index\n");
		exit(1);
	}
	return a.items[index];
}


tok_Array tok_push(tok_Array a, Token t) {
	if (a.length >= a.capacity) {
		printf("NOT YET IMPLEMENTED: tok_Array growth");
		exit(1);
	}
	a.items[a.length] = t;
	return (tok_Array) {
		.items = a.items,
		.length = a.length + 1,
		.capacity = a.capacity
	};
}

