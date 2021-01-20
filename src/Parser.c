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
extern char * parseString(char * str);
extern Token getToken(int token);

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

int expected, i, c;
char * module;

int moduleCallback(Token t)
{
    Token moduleName = getToken(yylex());
    if (moduleName.token != IDENTIFIER && moduleName.token != STRING)
    {
        error("Syntax Error");
        printf("Expected %s or %s, found %s\n", getTokenName(IDENTIFIER),
            getTokenName(STRING), moduleName.name);
        return 1;
    }

    Token next = getToken(yylex());
    if (next.token != SEMICOLON)
    {
        error("Syntax Error");
        printf("Expected %s, found %s\n", getTokenName(SEMICOLON), next.name);
        return 1;
    }

    if (moduleName.str[0] == '"')
    {
        module = parseString(moduleName.str);
    } else module = moduleName.str;

    c++;
    return 0;
}

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

    if (yylex() != SEMICOLON)
    {
        error("Syntax Error");
        printf("Expected %s, found %s\n", getTokenName(SEMICOLON), value.name);
        return 1;
    }

    name.str = strtok(name.str, "=");

    actionValueCreate.name = name.str;
    actionValueCreate.val = getValueFromToken(value);

    if (actionValueCreate.val.statusCode)
    {
        return actionValueCreate.val.statusCode;
    }

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

    if (c == 0 && (t.token != KEYWORD || strcmp(t.str, "module") != 0))
    {
        error("Syntax Error");
        printf("Expected '%s' at start of file, found '%s'\n", "module", t.str);
        return 1;
    }

    if (t.token == KEYWORD)
    {
        if (strcmp(t.str, "module") == 0) return moduleCallback(t);
        if (strcmp(t.str, "func") == 0) warn("func.");
        if (strcmp(t.str, "val") == 0) return valCallback(t);
        if (strcmp(t.str, "if") == 0) warn("if.");
        if (strcmp(t.str, "else") == 0)  warn("else.");
        if (strcmp(t.str, "while") == 0) warn("while.");
        if (strcmp(t.str, "for") == 0) warn("for.");
    }

    c++;
    return 0;
}
