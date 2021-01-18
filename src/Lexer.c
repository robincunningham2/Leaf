#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/Tokens.h"
#include "../h/Helper.h"

#define yy_size_t size_t

typedef struct yy_buffer_state * YY_BUFFER_STATE;

extern int yylex();
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void init();
extern int handleToken(int token);
extern char * yyprocess;
extern int yylineno;
extern char * yytext;
extern void error(char * name);
extern void warn(char * content);
extern int exitProcess(int code);

int active = FALSE;

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
        error("Module Error");
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

    int token, code;
    token = yylex();
    while (token)
    {
        if (token == ERROR)
        {
            yy_delete_buffer(buff);
            return 1;
        }
        
        code = handleToken(token);
        if (code != 0)
        {
            yy_delete_buffer(buff);
            return exitProcess(code);
        }

        token = yylex();
    }

    yy_delete_buffer(buff);
    return exitProcess(0);
}
