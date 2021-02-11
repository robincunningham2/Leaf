
#ifndef MEMORY_H
#define MEMORY_H

#include "../h/Helper.h"

typedef struct
{
    char ** values;
    size_t used;
    size_t size;
} memory_t;

typedef struct
{
    int type;
    char * value;
} value_t;

void initMemory(memory_t * a, size_t initialSize);
void insertToMemory(char * element);
void freeMemory();

char * valueToString(value_t value);
value_t stringToValue(char * string);

#endif
