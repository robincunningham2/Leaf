#include <stdio.h>
#include "tokens.h"

extern int yylex();
extern void init();
extern int getInt(char * name);
extern void createInt(char * name, int builtIn, int value);

int main (int argc, char * argv[])
{
    init();

    if (argc < 2)
    {
        return 1;
    }
    
    FILE * fp;
    char * filename;
    long size;
    char * buffer;

    filename = argv[1];

    fp = fopen(filename, "rb");
    if (!fp) return 1;

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    buffer = malloc((size + 1) * sizeof(* buffer));
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';

    int token = yylex();

    while (token)
    {
        printf("%d\n", token);
        token = yylex();
    }

    return 0;
}
