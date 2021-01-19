#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/Tokens.h"
#include "../h/Helper.h"
#include "../h/Version.h"

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
extern int startsWith(const char * pre, const char * str);

const char * help = "Usage: leaf [options] [ script.lf ] [argv] \n\
       leaf [options] \n\
\n\
Examples: \n\
    leaf test.lf \n\
    leaf test.lf -d \n\
    leaf -v \n\
\n\
Options: \n\
    -h      --help          shows this message \n\
    -v      --version       gets Leaf version \n\
    -d      --debug         sets System.debug variable to true";

int active = FALSE, debug = FALSE;

int main(int argc, char * argv[])
{
    init();
    yyprocess = argv[0];

    if (argc < 2)
    {
        printf("%s\n", help);
        return 0;
    }

    FILE * fp;
    char * filename;
    long size;
    char * buffer;
    YY_BUFFER_STATE buff;

    for (int i = 1; i < argc; i++)
    {
        char * arg = argv[i];
        if (arg[0] == '-')
        {
            if (strcmp(arg, "-h") == 0
                || strcmp(arg, "--help") == 0)
            {
                printf("%s\n", help);
                return 0;
            } else if (strcmp(arg, "-v") == 0
                || strcmp(arg, "--version") == 0)
            {
                printf("v%s\n", versionString);
                return 0;
            } else if (strcmp(arg, "-d") == 0
                || strcmp(arg, "--debug") == 0)
            {
                debug = TRUE;
                printf("\033[37;2m");
                printf("* Debug mode is enabled!\n");
                printf("\033[0m");
            } else warn("Option not found");

            if (i == argc - 1) return 0;
            continue;
        }

        if (active == TRUE)
        {
            continue;
        }

        filename = arg;

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

        buff = yy_scan_string(buffer);
        yyprocess = argv[1];
        active = TRUE;
    }

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
