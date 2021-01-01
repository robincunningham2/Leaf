%{
    #include <stdlib.h>
    #include "tokens.h"
%}

%%

[+-]?([1-9]*\.[0-9]+)([eE][+-]?[0-9])?  return FLOAT;
[+-]?[1-9]([eE][+-]?[0-9])?             return INTEGER;
\"(\\\\|\\\"|[^\"])*\"                  return STRING;
(true|false)                            return BOOLEAN;

(func|val|if|else|while|for)*           return KEYWORD;
[_A-Za-z][_A-Za-z0-9]*                  return IDENTIFIER;

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
.                                       printf("Error.\n");

%%

int yywrap(void)
{
    return 1;
}
