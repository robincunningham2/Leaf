#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/Helper.h"
#include "../h/Memory.h"
#include "../h/Lexer.h"

const char * help = "\n\
Usage: leaf [options] [ script.lf ] [argv] \n\
       leaf [options] \n\
\n\
Examples: \n\
    leaf test.lf \n\
    leaf test.lf -d \n\
    leaf -v \n\
\n\
Options: \n\
    -h      --help          shows this message \n\
    -v      --version       gets Leaf version \n\
";

int foundFile = FALSE;

int main(int argc, char * argv[])
{
    prcss.argc = argc;
    prcss.argv = argv;

    prcss.path = "test.lf";
    prcss.abspath = "/Users/robin/Documents/GitHub/Leaf/test.lf";

    if (argc < 2)
    {
        printf("%s\n", help);
        return 0;
    }

    memory_t memory;
    prcss.memory = memory;

    initMemory(&prcss.memory, 256);

    FILE * fp;
    long size;
    char * buffer;

    for (int i = 1; i < argc; i++)
    {
        char * arg = argv[i];
        if (arg[0] == '-')
        {
            if (strcmp(arg, "-h") == 0
                || strcmp(arg, "--help") == 0)
            {
                printf("%s\n", help);
                return 0;
            } else if (strcmp(arg, "-v") == 0
                || strcmp(arg, "--version") == 0)
            {
                printf("v%s\n", "1.0.0");
                return 0;
            } else if (foundFile == FALSE)
            {
               return thrwLeaf(concat("bad option: ", arg, ""));
            }

            if (i == argc - 1 && foundFile == FALSE) return 0;
            continue;
        }

        if (foundFile == TRUE)
        {
            continue;
        }

        prcss.path = arg;
        prcss.abspath = realpath(prcss.path, NULL);

        fp = fopen(prcss.path, "rb");
        if (!fp)
        {
            thrwLeaf(concat("module '", prcss.path, "' was not found"));
            return 1;
        }

        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        rewind(fp);

        buffer = malloc((size) * sizeof(* buffer));
        fread(buffer, size, 1, fp);
        buffer[size] = '\0';
        foundFile = TRUE;
    }

    int code = startLexer(buffer);
    return ext(code);
}
