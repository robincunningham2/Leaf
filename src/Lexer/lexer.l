%{
    #include <stdio.h>
    #include "../../h/Helper.h"

    token_t createToken(int token)
    {
        token_t result;
        result._success = TRUE;
        if (token == error)
            result._success = FALSE;
        
        result.token = token;
        result.lineno = yylineno;
        result.text = yytext;

        return result;
    }
%}

str     \"(\\\\|\\\"|[^\\"])*
float   (\.[0-9]+|[0-9]+\.[0-9]*)([eE][+-]?[[0-9]+)?
i       0-9
id      A-Za-z_
keyword module|func|val|if|else|while|for

comment \/\*(.|\n)*\*\/|\/\/(.)*
error   [^\(\)\{\}\[\]\.\,\:\;\=\<\>[:space:]]+

%%

{comment}           { /* Ignore comments */ }
[[:space:]]+        { /* Ignore whitespaces */ }

{float}             { return createToken(token_float); }
0|[1-9][{i}]*       { return createToken(token_int); }
true|false          { return createToken(token_bool); }
{str}\"             { return createToken(token_string); }
{str}*              {
                        error("Syntax Error");
                        printf("Unterminated string literal\n");
                        exitProcess(1);
                        return ERROR;
                    }

{keyword}           { return createToken(token_keyword); }
[{id}][{id}{i}]*    { return createToken(token_id); }

"("                 { return createToken(token_lpar); }
")"                 { return createToken(token_rpar); }
"["                 { return createToken(token_lsqb); }
"]"                 { return createToken(token_rsqb); }

"+"                 { return createToken(token_plus); }
"-"                 { return createToken(token_minus); }
"*"                 { return createToken(token_multi); }
"/"                 { return createToken(token_slash); }

"|"                 { return createToken(token_vbar); }
"&"                 { return createToken(token_and); }
"."                 { return createToken(token_dot); }
","                 { return createToken(token_comma); }
":"                 { return createToken(token_colon); }
";"                 { return createToken(token_semicolon; }

"="                 { return createToken(token_equal); }
"=="                { return createToken(token_isequal); }
"!="                { return createToken(token_notequal); }
"<"                 { return createToken(token_less); }
">"                 { return createToken(token_greater); }

{error}             {
                        error("Syntax Error");
                        printf("Unexpected or invalid token: '%s'\n", yytext);
                        return ERROR;
                    }

%%

int yywrap(void)
{
    return 1;
}
