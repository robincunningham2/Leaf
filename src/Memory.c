#include <stdio.h>
#include <stdlib.h>
#include "../h/Helper.h"
#include "../h/Memory.h"

void initMemory(memory_t * a, size_t initialSize) {
    a -> values = malloc(initialSize * sizeof(char *));
    a -> used = 0;
    a -> size = initialSize;
}

void insertToMemory(memory_t * a, char * element) {
    if (a -> used == a -> size) {
        a -> size *= 2;
        a -> values = realloc(
            a -> values,
            a -> size * sizeof(char *)
        );
    }

    a -> values[a -> used++] = * element;
}

void freeMemory(memory_t * a) {
    free(a -> values);
    a -> values = NULL;
    a -> used = a -> size = 0;
}
