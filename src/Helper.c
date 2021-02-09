#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "../h/Helper.h"

char * concat(char * s1, char * s2, char * s3)
{
    char s[strlen(s1) + strlen(s2) + strlen(s3) + 1];
    snprintf(s, sizeof(s), "%s%s%s", s1, s2, s3);

    return s;
}

char * getTokenName(token_t token)
{
    if (token.type == token_int)            return "integer";
    else if (token.type == token_float)     return "float";
    else if (token.type == token_string)    return "string";
    else if (token.type == token_bool)      return "boolean";
    else if (token.type == token_keyword)   return "keyword";
    else if (token.type == token_id)        return "identifier";
    else return concat("'", token.text, "'");
}

int error(char * type, char * content)
{
    time_t t = time(NULL);
    struct tm * tm = localtime(&t);

    char date[64];
    assert(strftime(date, sizeof(date), "%c", tm));

    printf("Uncaught ");
    printf("\033[1m"); // Bold
    printf("%s: ", name);
    printf("\033[0m"); // Reset
    printf("%s\n", content);
    printf("\nProcess exited with code 1 at %s\n", date);

    return 1;
}

void warn(char * content)
{
    printf("\033[1m"); // Bold
    printf("Warning: ");
    printf("\033[0m"); // Reset
    printf("%s\n", content);
}
