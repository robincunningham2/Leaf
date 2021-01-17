#include <stdio.h>
#include "../h/Tokens.h"

extern char * yyprocess;
extern int yylineno;
extern char * yytext;
extern void error(char * name);
extern void warn(char * content);

typedef struct Token {
    int token;
    int lineno;
    char * str;
} Token;

int expected = STRING;

int handleToken(int token)
{
    Token t;
    t.token = token;
    t.lineno = yylineno;
    t.str = yytext;

    if (expected != NONE && t.token != expected)
    {
        error("Unexpected Error");
        printf("Expected '%d', got '%d'\n", expected, t.token);
        return 1;
    }

    // Do something
}
