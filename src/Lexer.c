#include <stdio.h>
#include "../h/Helper.h"

typedef struct yy_buffer_state * YY_BUFFER_STATE;

extern int yylex();
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern token_t yytoken;

token_t lex() {
    int token = yylex();
    if (token == error)
    {
        yytoken._failed = TRUE;
    }

    if (token == none)
    {
        yytoken._isempty = TRUE;
    }

    return yytoken;
}

int startLexer(char * buff) {
    YY_BUFFER_STATE buffer = yy_scan_string(buff);

    token_t token;
    token = lex();

    while (token._isempty == FALSE)
    {
        if (token._failed == TRUE) return 1;
        printf("Type: %d, lineno: %d, text: %s, name: %s\n", token.type, token.lineno, token.text, getTokenName(token));
        token = lex();
    }

    yy_delete_buffer(buffer);
    return 0;
}
