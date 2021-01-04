#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

typedef struct yy_buffer_state * YY_BUFFER_STATE;

extern int yylex();
extern YY_BUFFER_STATE yy_scan_buffer(char * base);
extern void init();
extern void handleToken(int token);

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

char * removeAll(char * str, const char toRemove)
{
    int i, j;
    int len = strlen(str);

    for (i = 0; i < len; i++)
    {
        if (str[i] == toRemove)
        {
            for (j = i; j < len; j++)
            {
                str[j] = str[j + 1];
            }

            len--;
            i--;
        }
    }

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
        return error("module error", "module was not found.");
    }

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    buffer = malloc((size + 2) * sizeof(* buffer));
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';
    buffer[size + 1] = '\0';

    buffer = removeAll(buffer, '\n');

    yy_scan_buffer(buffer);
    process = argv[1];
    lineno = 1;

    int token;
    token = 1;
    while (token)
    {
        printf("Called\n");
        token = yylex();
        printf("Token: %d\n", token);
        printf("Isnewline: %d\n", token == NEWLINE);

        if (token == NEWLINE)
        {
            printf("newline\n");
            lineno++;
            continue;
        }

        printf("Token: %d\n", token);
        handleToken(token);
    }

    printf("endded\n");

    return 0;
}
