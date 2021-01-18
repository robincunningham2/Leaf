#include <stdio.h>
#include <string.h>
#include "../h/Tokens.h"
#include "../h/Helper.h"

extern char * yyprocess;
extern int yylineno;
extern char * yytext;
extern int yylex();
extern void error(char * name);
extern void warn(char * content);
extern char * getTokenName(int token);
extern Token getToken(int token);
extern Value getValueFromToken(Token val);

typedef struct ActionValueCreate {
    char * name;
    Value val;
} ActionValueCreate;

typedef struct ActionNode {
    int action;
    ActionValueCreate actionValueCreate;
} ActionNode;

int i = 0;
ActionNode actionTree[16] = {};

int expected, i;

int valCallback(Token t)
{
    ActionNode node;
    node.action = ACTION_VALUE_CREATE;

    ActionValueCreate actionValueCreate;

    Token name = getToken(yylex());
    if (name.token != IDENTIFIER)
    {
        error("Syntax Error");
        printf("Expected %s, found %s\n", getTokenName(IDENTIFIER), name.name);
        return 1;
    }

    Token equals = getToken(yylex());
    if (equals.token != EQUAL)
    {
        error("Syntax Error");
        printf("Expected %s, found %s\n", getTokenName(EQUAL), equals.name);
        return 1;
    }

    Token value = getToken(yylex());
    if (value.token != INTEGER
        && value.token != FLOAT
        && value.token != STRING
        && value.token != BOOLEAN
        && value.token != IDENTIFIER)
    {
        error("Syntax Error");
        printf("Expected %s, found %s\n", "value type", value.name);
        return 1;
    }

    name.str = strtok(name.str, "=");

    actionValueCreate.name = name.str;
    actionValueCreate.val = getValueFromToken(value);

    node.actionValueCreate = actionValueCreate;

    actionTree[i] = node;
    i++;

    return 0;
}

int handleToken(int token)
{
    Token t = getToken(token);

    if (expected && t.token != expected)
    {
        error("Syntax Error");
        printf("Expected %s, found %s\n", getTokenName(expected), t.name);
        return 1;
    }

    if (t.token == KEYWORD)
    {
        if (strcmp(t.str, "func") == 0) warn("func.");
        if (strcmp(t.str, "val") == 0) return valCallback(t);
        if (strcmp(t.str, "if") == 0) warn("if.");
        if (strcmp(t.str, "else") == 0)  warn("else.");
        if (strcmp(t.str, "while") == 0) warn("while.");
        if (strcmp(t.str, "for") == 0) warn("for.");
    }

    return 0;
}
