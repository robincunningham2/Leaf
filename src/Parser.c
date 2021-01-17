#include <stdio.h>
#include "../h/Tokens.h"

typedef struct Token {
    int token;
    int lineno;
    char * str;
} Token;

void handleToken(int token, int yylineno, char * yytext)
{
    Token t;
    t.token = token;
    t.lineno = yylineno;
    t.str = yytext;

    // Do something
}
