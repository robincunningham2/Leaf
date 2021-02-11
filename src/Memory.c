#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/Helper.h"
#include "../h/Memory.h"

memory_t * def;

void initMemory(memory_t * a, size_t initialSize)
{
    a -> values = malloc(initialSize * sizeof(char *));
    a -> used = 0;
    a -> size = initialSize;

    def = a;
}

void insertToMemory(char * element)
{
    if (def -> used == def -> size) {
        def -> size *= 2;
        def -> values = realloc(
            def -> values,
            def -> size * sizeof(char *)
        );
    }

    def -> values[def -> used++] = element;
}

void freeMemory()
{
    free(def -> values);
    def -> values = NULL;
    def -> used = def -> size = 0;
}

char * valueToString(value_t value)
{
    char * s[strlen(value.value) + 2];
    char * prefix = "";
    if (value.type == type_float)   prefix = "f";
    if (value.type == type_int)     prefix = "i";
    if (value.type == type_string)  prefix = "s";
    if (value.type == type_bool)    prefix = "b";

    char * string;
    string = concat(prefix, value.value, "");

    return string;
}

value_t stringToValue(char * string)
{
    value_t value;
    value.value = string;
    value.value++;

    if (string[0] == 'f') value.type = type_float;
    if (string[0] == 'i') value.type = type_int;
    if (string[0] == 's') value.type = type_string;
    if (string[0] == 'b') value.type = type_bool;

    return value;
}
