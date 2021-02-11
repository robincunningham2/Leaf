#include <stdio.h>
#include "../h/Helper.h"
#include "../h/Memory.h"
#include "../h/Lexer.h"

int main(int argc, char * argv[])
{
    prcss.argc = argc;
    prcss.argv = argv;

    prcss.path = "test.lf";
    prcss.abspath = "/Users/robin/Documents/GitHub/Leaf/test.lf";

    memory_t memory;
    prcss.memory = memory;

    initMemory(&prcss.memory, 256);

    int code = startLexer("module \"main\"; val test68 = \"Lmao.\"; 0");
    return ext(code);
}
