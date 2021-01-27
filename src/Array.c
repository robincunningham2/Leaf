#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char ** array;
  size_t used;
  size_t size;
} Array;

void createArray(Array * a, size_t initialSize) {
    a -> array = malloc(initialSize * sizeof(char *));
    a -> used = 0;
    a -> size = initialSize;
}

void insertToArray(Array * a, int element) {
    if (a -> used == a -> size) {
        a -> size *= 2;
        a -> array = realloc(a -> array,
        a -> size * sizeof(char *));
    }

    a -> array[a -> used++] = element;
}

void freeArray(Array * a) {
    free(a -> array);
    a -> array = NULL;
    a -> used = a -> size = 0;
}
