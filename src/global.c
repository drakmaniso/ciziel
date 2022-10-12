#include <stdio.h>

#include "global.h"


void panic(char *msg) {
    printf("%s", msg);
    exit(1);
}