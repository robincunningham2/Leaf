%{
    #include <stdlib.h>
    #include "../../h/Tokens.h"

    char * yyprocess;

    void err(char * name)
    {
        printf("\033[1m"); // Bold
        if (yylineno > 0)
        {
            printf("%s:%d: ", yyprocess, yylineno);
        } else printf("%s: ", yyprocess);

        printf("\033[0m"); // Reset
        printf("Uncaught ");
        printf("\033[0;31m"); // Red
        printf("\033[1m"); // Bold
        printf("%s: ", name);
        printf("\033[0m"); // Reset
    }
%}

%option yylineno

%%

\/\*(.|\n)*\*\/                         ;
\/\/(.)*                                ;

[+-]?([1-9]*\.[0-9]+)([eE][+-]?[0-9])?  return FLOAT;
[+-]?[1-9]([eE][+-]?[0-9])?             return INTEGER;
\"(\\\\|\\\"|[^\"])*\"                  return STRING;
(true|false)                            return BOOLEAN;

(func|val|if|else|while|for)*           return KEYWORD;
[A-Za-z_][A-Za-z_0-9]*                  return IDENTIFIER;

"("                                     return LPAR;
")"                                     return RPAR;
"{"                                     return LBR;
"}"                                     return RBR;
"["                                     return LSQB;
"]"                                     return RSQB;

"+"                                     return PLUS;
"-"                                     return MINUS;
"*"                                     return MULTI;
"/"                                     return SLASH;
"|"                                     return VBAR;
"&"                                     return AND;
"."                                     return DOT;
","                                     return COMMA;
":"                                     return COLON;
";"                                     return SEMICOLON;
"="                                     return EQUAL;
"=="                                    return ISEQUAL;
"!="                                    return NOTEQUAL;
"<"                                     return LESS;
">"                                     return GREATER;

[ \n\t]                                 ;

.                                       {
                                            err("Syntax Error");
                                            printf("Unexpected or invalid token: '%s'\n", yytext);
                                            return ERROR;
                                        }

%%

int yywrap(void)
{
    return 1;
}

char * yyprocess;
