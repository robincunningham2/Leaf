#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/Tokens.h"

#define TRUE  1
#define FALSE 0

#define yy_size_t size_t

typedef struct yy_buffer_state * YY_BUFFER_STATE;

extern int yylineno;
extern int yylex();
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void init();
extern void handleToken(int token);
extern char * yyprocess;

int active = FALSE;

void errorr(char * name)
{
    printf("\033[1m"); // Bold
    if (active == TRUE)
    {
        printf("%s:%d: ", yyprocess, yylineno);
    }

    printf("\033[0m"); // Reset
    printf("Uncaught ");
    printf("\033[0;31m"); // Red
    printf("\033[1m"); // Bold
    printf("%s: ", name);
    printf("\033[0m"); // Reset
}

void warn(char * content)
{
    printf("\033[1m"); // Bold
    if (active == TRUE)
    {
        printf("%s:%d: ", yyprocess, yylineno);
    }

    printf("\033[0;35m"); // Purple
    printf("\033[1m"); // Bold
    printf("Warning: ");
    printf("\033[0m"); // Reset
    printf("%s\n", content);
}

int main(int argc, char * argv[])
{
    init();
    yyprocess = argv[0];

    if (argc < 2)
    {
        warn("a file name must be included.\n    Usage:\n    $ leaf [file|command] [options]");
    }
    
    FILE * fp;
    char * filename;
    long size;
    char * buffer;

    filename = argv[1];

    fp = fopen(filename, "rb");
    if (!fp)
    {
        errorr("Module Error");
        printf("module was not found.\n");
        return 1;
    }

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    buffer = malloc((size) * sizeof(* buffer));
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';

    YY_BUFFER_STATE buff = yy_scan_string(buffer);
    yyprocess = argv[1];
    active = TRUE;

    int token;
    token = yylex();
    while (token)
    {
        if (token == ERROR)
        {
            yy_delete_buffer(buff);
            return 1;
        }
        
        handleToken(token);
        token = yylex();
    }

    yy_delete_buffer(buff);

    return 0;
}
