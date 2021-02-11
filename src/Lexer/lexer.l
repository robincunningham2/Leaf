%{
    #include <stdio.h>
    #include "../../h/Helper.h"

    token_t yytoken;

    token_t createToken(int token)
    {
        token_t result;
        result._isempty = FALSE;
        if (token == error)
        {
            result._failed = TRUE;
        }

        result.type = token;
        result.lineno = yylineno;
        result.text = yytext;
        
        return result;
    }

    int err(char * type, char * msg)
    {
        yytoken._failed = TRUE;
        yytoken.type = error;
        yytoken.lineno = yylineno;
        yytoken.text = yytext;

        thrw(yytoken, type, msg);
        return error;
    }
%}

str     \"(\\\\|\\\"|[^\\"])*
float   (\.[0-9]+|[0-9]+\.[0-9]*)([eE][+-]?[[0-9]+)?
keyword module|func|val|if|else|while|for

comment \/\*(.|\n)*\*\/|\/\/(.)*
w       [:space:]

%%

{comment}               { /* Ignore comments */ }
[[:space:]]+            { /* Ignore whitespaces */ }

{float}                 { yytoken = createToken(token_float); return 1; }
0[0-9]                  { return err("Syntax Error", "0 starting integer"); }
0|[1-9][0-9]*           { yytoken = createToken(token_int); return 1; }
true|false              { yytoken = createToken(token_bool); return 1; }
{str}\"                 { yytoken = createToken(token_string); return 1; }
{str}[^\"]              { return err("Syntax Error", "Unterminated string literal"); }

{keyword}               { yytoken = createToken(token_keyword); return 1; }
[A-Za-z_][A-Za-z_0-9]*  { yytoken = createToken(token_id); return 1; }

"("                     { yytoken = createToken(token_lpar); return 1; }
")"                     { yytoken = createToken(token_rpar); return 1; }
"["                     { yytoken = createToken(token_lsqb); return 1; }
"]"                     { yytoken = createToken(token_rsqb); return 1; }

"+"                     { yytoken = createToken(token_plus); return 1; }
"-"                     { yytoken = createToken(token_minus); return 1; }
"*"                     { yytoken = createToken(token_multi); return 1; }
"/"                     { yytoken = createToken(token_slash); return 1; }

"|"                     { yytoken = createToken(token_vbar); return 1; }
"&"                     { yytoken = createToken(token_and); return 1; }
"."                     { yytoken = createToken(token_dot); return 1; }
","                     { yytoken = createToken(token_comma); return 1; }
":"                     { yytoken = createToken(token_colon); return 1; }
";"                     { yytoken = createToken(token_semicolon); return 1; }

"="                     { yytoken = createToken(token_equal); return 1; }
"=="                    { yytoken = createToken(token_isequal); return 1; }
"!="                    { yytoken = createToken(token_notequal); return 1; }
"<"                     { yytoken = createToken(token_less); return 1; }
">"                     { yytoken = createToken(token_greater); return 1; }

[^(){}[]|&.,:;!=<>{w}]+ { return err("Syntax Error", "Unexpected or invalid token"); }

%%

token_t yytoken;

int yywrap(void)
{
    return 1;
}
