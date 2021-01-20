#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "../h/Tokens.h"
#include "../h/Helper.h"

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
    char * filename = realpath(yyprocess, NULL);

    if (active == TRUE) printf("\n%s:%d:\n", filename, yylineno);
    printf("Uncaught ");
    printf("\033[1m"); // Bold
    printf("%s: ", name);
    printf("\033[0m"); // Reset

    free(filename);
}

void warn(char * content)
{
    printf("\033[1m"); // Bold
    printf("Warning: ");
    printf("\033[0m"); // Reset
    printf("%s\n", content);
}

int exitProcess(int code)
{
    time_t t = time(NULL);
    struct tm * tm = localtime(&t);

    char date[64];
    assert(strftime(date, sizeof(date), "%c", tm));

    printf("\nProcess exited with code %d at %s\n", code, date);

    return code;
}

char * parseString(char * str)
{
    str[strlen(str) - 2] = '\0';
    str++;

    return str;
}

Token getToken(int token)
{
    Token result;
    result.token = token;
    result.lineno = yylineno;
    result.str = yytext;
    result.name = getTokenName(token);

    return result;
}

Value getValueFromToken(Token val)
{
    Value result;
    switch (val.token)
    {
        default:
        case INTEGER:
            result.type = TYPE_INT;
            result.intValue = atoi(val.str);
            break;
        case FLOAT:
            result.type = TYPE_FLOAT;
            result.floatValue = atof(val.str);
        case STRING:
            result.type = TYPE_STRING;
            result.stringValue = val.str;
        case BOOLEAN:
            result.type = TYPE_BOOL;
            if (strcmp(val.str, "true") == 0) result.boolValue = 1;
            else result.boolValue = 0;
    }

    return result;
}
