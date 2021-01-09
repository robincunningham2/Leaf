%{
    #include <stdlib.h>
    #include "tokens.h"

    char * process = "test.lf";
    int lno = -1;

    void asdhjkasd(char * name)
    {
        printf("\033[1m"); // Bold
        if (lno > 0)
        {
            printf("%s:%d: ", process, lno);
        } else printf("%s: ", process);

        printf("\033[0;31m"); // Red
        printf("\033[1m"); // Bold
        printf("%s: ", name);
        printf("\033[0m"); // Reset
    }
%}

%%

"/*"(.|\n)*"*/"                         ;

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

\n                                      return NEWLINE;
[ \t]                                   ;

.                                       {
                                            asdhjkasd("syntax error");
                                            printf("Invalid token '%s'", yytext);
                                        }

%%

int yywrap(void)
{
    return 1;
}