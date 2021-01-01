%{
    #include <stdlib.h>
    #include "tokens.h"
%}

%%

[1-9][0-9]*                     return INTEGER;
[1-9][0-9].[0-9]*               return FLOAT;
\"(\\\\|\\\"|[^\"])*\"          return STRING;
(true|false)                    return BOOLEAN;

(func|val|if|else|while|for)    return KEYWORD;
[A-Za-z_][A-Za-z0-9_]           return IDENTIFIER;

.   return 0;

%%

int yywrap(void)
{
    return 1;
}
