#include <stdio.h>
#define TRUE  1
#define FALSE 0

extern char * yyprocess;
extern int yylineno;
extern char * yytext;
extern int active;

void error(char * name)
{
    printf("\033[1m"); // Bold
    if (active == TRUE)
    {
        printf("%s:%d: ", yyprocess, yylineno);
    }

    printf("\033[0m"); // Reset
    printf("Uncaught ");
    printf("\033[0;31m"); // Red
    printf("\033[1m"); // Bold
    printf("%s: ", name);
    printf("\033[0m"); // Reset
}

void warn(char * content)
{
    printf("\033[1m"); // Bold
    if (active == TRUE)
    {
        printf("%s:%d: ", yyprocess, yylineno);
    }

    printf("\033[0;35m"); // Purple
    printf("\033[1m"); // Bold
    printf("Warning: ");
    printf("\033[0m"); // Reset
    printf("%s\n", content);
}
