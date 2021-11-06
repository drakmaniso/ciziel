#ifndef ARRAY
#define ARRAY

#include <stdlib.h>
#include "global.h"


typedef struct {
	void *items;
	size_t length;
	size_t capacity;
} Array;


#define array_new(itemType, cap)                  \
    (Array) {                                     \
        .items = calloc((cap), sizeof(itemType)), \
        .length = 0,                              \
        .capacity = (cap)                         \
    }

#define array_length(array) ((array).length)

#define array_push(itemType, array, item)                                            \
    if((array).length >= (array).capacity) {                                         \
        (array).capacity *= 2;                                                       \
        (array).items = realloc((array).items, (array).capacity * sizeof(itemType)); \
    }                                                                                \
    ((itemType*)(array).items)[(array).length] = item;                               \
    (array).length++;

#define array_at(itemType, array, index) ((index) >= 0 && (index) < (array).length ? ((itemType*)(array).items)[index] : (panic("*** Array: index out of bounds ***"), ((itemType*)0)[0]))


#endif ARRAY