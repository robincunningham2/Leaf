#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

typedef struct yy_buffer_state * YY_BUFFER_STATE;

extern int yylex();
extern YY_BUFFER_STATE yy_scan_buffer(char * base, int size);
extern void init();

char * process;
int lineno = -1;

int error(char * name, char * content)
{
    printf("\033[1m"); // Bold
    if (lineno > 0)
    {
        printf("%s:%d: ", process, lineno);
    } else printf("%s: ", process);

    printf("\033[0;31m"); // Red
    printf("\033[1m"); // Bold
    printf("%s: ", name);
    printf("\033[0m"); // Reset
    printf("%s\n", content);

    return 1;
}

void warn(char * content)
{
    printf("\033[1m"); // Bold
    if (lineno > 0)
    {
        printf("%s:%d: ", process, lineno);
    } else printf("%s: ", process);

    printf("\033[0;35m"); // Purple
    printf("\033[1m"); // Bold
    printf("warning: ");
    printf("\033[0m"); // Reset
    printf("%s\n", content);
}

char * concat(char * s1, char * s2, char * s3)
{
    char * str = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);
    strcpy(str, s1);
    strcat(str, s2);
    strcat(str, s3);

    return str;
}

int main(int argc, char * argv[])
{
    init();
    process = argv[0];

    if (argc < 2)
    {
        warn("a file name must be included.\n    Usage:\n    $ a [file|command] [options]");
    }
    
    FILE * fp;
    char * filename;
    long size;
    char * buffer;

    filename = argv[1];

    fp = fopen(filename, "rb");
    if (!fp) {
        return error("module error", concat("module '", filename, "' was not found."));
    }

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    buffer = malloc((size + 1) * sizeof(* buffer));
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';

    printf("%s\n", buffer);

    yy_scan_buffer(buffer, sizeof(buffer));
    process = argv[1];
    lineno = 1;

    printf("1\n");

    int token = yylex();

    printf("%d\n", token);

    while (token)
    {
        if (token == NEWLINE)
        {
            lineno++;
            continue;
        }

        printf("%d\n", token);
        token = yylex();
    }

    return 0;
}
