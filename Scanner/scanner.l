%{
    #include <stdlib.h>
%}

%%

.   return 0;

%%

int yywrap(void)
{
    return 1;
}
