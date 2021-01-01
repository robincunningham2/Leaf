#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TYPE_INT    1
#define TYPE_FLOAT  2
#define TYPE_STRING 3
#define TYPE_BOOL   4

typedef struct Object
{
    int builtIn;
    char * name;
    int type;

    int valid;

    int intValue;
    float floatValue;
    char * stringValue;
    int boolValue;
} Object;

typedef struct Memory
{
    int size;
    Object memory[1028];
} Memory;

struct Memory mem;

void init()
{
    mem.size = 0;
}

void createInt(char * name, int value, int builtIn)
{
    struct Object obj;

    obj.valid = 1;
    obj.type = TYPE_INT;

    char * str = malloc(strlen(name) + 1);
    strcpy(str, name);
    obj.name = str;

    obj.builtIn = builtIn;
    obj.intValue = value;

    mem.size++;
    mem.memory[mem.size] = obj;
}

int getInt(char * name)
{
    int result;

    for (int i = 0; i < mem.size; i++)
    {
        struct Object obj = mem.memory[i];
        if (obj.name == name)
        {
            result = obj.intValue;
        }
    }

    return result;
}

void createFloat(char * name, float value, int builtIn)
{
    struct Object obj;

    obj.valid = 1;
    obj.type = TYPE_FLOAT;

    char * str = malloc(strlen(name) + 1);
    strcpy(str, name);
    obj.name = str;

    obj.builtIn = builtIn;
    obj.floatValue = value;

    mem.size++;
    mem.memory[mem.size] = obj;
}

float getFloat(char * name)
{
    float result;

    for (int i = 0; i < mem.size; i++)
    {
        struct Object obj = mem.memory[i];
        if (obj.name == name)
        {
            result = obj.floatValue;
        }
    }

    return result;
}

void createString(char * name, char * value, int builtIn)
{
    struct Object obj;

    obj.valid = 1;
    obj.type = TYPE_STRING;

    char * str = malloc(strlen(name) + 1);
    strcpy(str, name);
    obj.name = str;

    obj.builtIn = builtIn;

    char * str2 = malloc(strlen(value) + 1);
    strcpy(str2, value);
    obj.stringValue = str2;

    mem.size++;
    mem.memory[mem.size] = obj;
}

char * getString(char * name)
{
    char * result;

    for (int i = 0; i < mem.size; i++)
    {
        struct Object obj = mem.memory[i];
        if (obj.name == name)
        {
            result = obj.stringValue;
        }
    }

    return result;
}

void createBool(char * name, int value, int builtIn)
{
    struct Object obj;

    obj.valid = 1;
    obj.type = TYPE_BOOL;

    char * str = malloc(strlen(name) + 1);
    strcpy(str, name);
    obj.name = str;

    obj.builtIn = builtIn;
    obj.boolValue = value;

    mem.size++;
    mem.memory[mem.size] = obj;
}

int getBool(char * name)
{
    int result;

    for (int i = 0; i < mem.size; i++)
    {
        struct Object obj = mem.memory[i];
        if (obj.name == name)
        {
            result = obj.boolValue;
        }
    }

    return result;
}
