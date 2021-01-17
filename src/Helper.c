#include <stdio.h>
#include "../h/Tokens.h"
#define TRUE  1
#define FALSE 0

extern char * yyprocess;
extern int yylineno;
extern char * yytext;
extern int active;

char * getTokenName(int token)
{
    if (token == INTEGER)       return "integer";
    if (token == FLOAT)         return "float";
    if (token == STRING)        return "string";
    if (token == BOOLEAN)       return "boolean";
    if (token == KEYWORD)       return "keyword";
    if (token == IDENTIFIER)    return "identifier";
    if (token == LPAR)          return "'('";
    if (token == RPAR)          return "')'";
    if (token == LBR)           return "'{'";
    if (token == RBR)           return "'}'";
    if (token == LSQB)          return "'['";
    if (token == RSQB)          return "']'";
    if (token == PLUS)          return "'+'";
    if (token == MINUS)         return "'-'";
    if (token == MULTI)         return "'*'";
    if (token == SLASH)         return "'/'";
    if (token == VBAR)          return "'|'";
    if (token == AND)           return "'&'";
    if (token == DOT)           return "'.'";
    if (token == COMMA)         return "','";
    if (token == COLON)         return "':'";
    if (token == SEMICOLON)     return "';'";
    if (token == EQUAL)         return "'='";
    if (token == ISEQUAL)       return "'=='";
    if (token == NOTEQUAL)      return "'!='";
    if (token == LESS)          return "'<'";
    if (token == GREATER)       return "'>'";
    if (token == ERROR)         return "error";
    if (token == NONE)          return "none";
}

void error(char * name)
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
