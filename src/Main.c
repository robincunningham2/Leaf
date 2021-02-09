#include <stdio.h>
#include "../h/Helper.h"
#include "../h/Memory.h"

int main(int argc, char * argv[])
{
    memory_t memory;
    initMemory(&memory, 256);

    value_t val;
    val.type = type_float;
    val.value = "3.6547";

    printf("%s\n", valueToString(val));
    insertToMemory(&memory, valueToString(val));

    return 0;
}
