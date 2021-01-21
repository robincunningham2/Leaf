#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/Tokens.h"
#include "../h/Helper.h"

#define yy_size_t size_t

typedef struct yy_buffer_state * YY_BUFFER_STATE;

extern Process Main;

extern int yylex();
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern int handleToken(int token);
extern int exitProcess(int code);

int lexer(char * buffer)
{
    YY_BUFFER_STATE buff = yy_scan_string(buffer);

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
