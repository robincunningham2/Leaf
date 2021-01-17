#include <stdio.h>
#include "../h/Tokens.h"

extern char * yyprocess;
extern int yylineno;
extern char * yytext;
extern void error(char * name);
extern void warn(char * content);
extern char * getTokenName(int token);

typedef struct Token {
    int token;
    int lineno;
    char * str;
    char * name;
} Token;

Token getToken(int token)
{
    Token result;
    result.token = token;
    result.lineno = yylineno;
    result.str = yytext;
    result.name = getTokenName(token);

    return result;
}

int expected = AND;

int handleToken(int token)
{
    Token t = getToken(token);

    if (expected != NONE && t.token != expected)
    {
        error("Syntax Error");
        printf("Expected %s, found %s\n", getTokenName(expected), t.name);
        return 1;
    }

    // Do something
}
