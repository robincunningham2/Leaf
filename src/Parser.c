#include <stdio.h>
#include "../h/Helper.h"
#include "../h/Parser.h"

int tokenHandler(token_t token)
{
    printf("Type: %d, lineno: %d, text: %s, name: %s\n", token.type, token.lineno, token.text, getTokenName(token));
    return 0;
}
