#include <stdio.h>
#include "tokens.h"

extern int yylex();

int main(void)
{
    int token = yylex();

    while (token)
    {
        printf("%d\n", token);
        token = yylex();
    }

    return 0;
}
