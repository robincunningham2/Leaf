#include "../h/Helper.h"

typedef struct
{
    char * values;
    size_t used;
    size_t size;
} memory_t;

void initMemory(memory_t * a, size_t initialSize);
void insertToMemory(memory_t * a, char * element);
void freeMemory(memory_t * a);
