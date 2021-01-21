%{
    #include <stdlib.h>
    #include "../../h/Tokens.h"

    extern void error(char * name);
    extern void warn(char * content);
    extern int exitProcess(int code);
%}

%option yylineno

%%

\/\*(.|\n)*\*\/|\/\/(.)*                    { /* Ignore comments */ }
[[:space:]]+                                { /* Ignore whitespaces */ }

(\.[0-9]+|[0-9]+\.[0-9]*)([eE][+-]?[0-9]+)? { return FLOAT; }
0|[1-9][0-9]*                               { return INTEGER; }
\"(\\\\|\\\"|[^\\"])*\"                     { return STRING; }
\"(\\\\|\\\"|[^\\"])*                       {
                                                error("Syntax Error");
                                                printf("Unterminated string literal\n");
                                                exitProcess(1);
                                                return ERROR;
                                            }

true|false                                  { return BOOLEAN; }

module|func|val|if|else|while|for           { return KEYWORD; }
[A-Za-z_][A-Za-z_0-9]*                      { return IDENTIFIER; }

"("                                         { return LPAR; }
")"                                         { return RPAR; }
"{"                                         { return LBR; }
"}"                                         { return RBR; }
"["                                         { return LSQB; }
"]"                                         { return RSQB; }

"+"                                         { return PLUS; }
"-"                                         { return MINUS; }
"*"                                         { return MULTI; }
"/"                                         { return SLASH; }
"|"                                         { return VBAR; }
"&"                                         { return AND; }
"."                                         { return DOT; }
","                                         { return COMMA; }
":"                                         { return COLON; }
";"                                         { return SEMICOLON; }
"="                                         { return EQUAL; }
"=="                                        { return ISEQUAL; }
"!="                                        { return NOTEQUAL; }
"<"                                         { return LESS; }
">"                                         { return GREATER; }

[^\(\)\{\}\[\]\.\,\:\;\=\<\>[:space:]]+     {
                                                error("Syntax Error");
                                                printf("Unexpected or invalid token: '%s'\n", yytext);
                                                exitProcess(1);
                                                return ERROR;
                                            }

%%

int yywrap(void)
{
    return 1;
}
