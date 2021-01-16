#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

#define yy_size_t size_t

typedef struct yy_buffer_state * YY_BUFFER_STATE;

extern int yylineno;
extern int yylex();
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void init();
extern void handleToken(int token);

char * process;

int error(char * name, char * content)
{
    printf("\033[1m"); // Bold
    if (yylineno > 0)
    {
        printf("%s:%d: ", process, yylineno);
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
    if (yylineno > 0)
    {
        printf("%s:%d: ", process, yylineno);
    } else printf("%s: ", process);

    printf("\033[0;35m"); // Purple
    printf("\033[1m"); // Bold
    printf("warning: ");
    printf("\033[0m"); // Reset
    printf("%s\n", content);
}

int main(int argc, char * argv[])
{
    init();
    process = argv[0];

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
    if (!fp) {
        return error("module error", "module was not found.");
    }

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    buffer = malloc((size) * sizeof(* buffer));
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';

    printf("%s\n", buffer);

    YY_BUFFER_STATE buff = yy_scan_string(buffer);
    process = argv[1];

    int token;
    token = yylex();
    while (token)
    {
        handleToken(token);
        token = yylex();
    }

    yy_delete_buffer(buff);

    return 0;
}
