#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/Helper.h"
#include "../h/Version.h"

Process Main;

extern int lexer(char * buffer);
extern void error(char * name);
extern void warn(char * content);

const char * help = "Usage: leaf [options] [ script.lf ] [argv] \n\
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
    -d      --debug         sets System.debug variable to true";

int debug, active;

int main(int argc, char * argv[])
{
    Main.argv = argv;
    Main.argc = argc;
    Main.filepath = argv[0];

    if (argc < 2)
    {
        printf("%s\n", help);
        return 0;
    }

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
                printf("v%s\n", versionString);
                return 0;
            } else if (strcmp(arg, "-d") == 0
                || strcmp(arg, "--debug") == 0)
            {
                debug = TRUE;
                printf("\033[37;2m");
                printf("* Debug mode is enabled!\n");
                printf("\033[0m");
            } else if (active == FALSE)
            {
                printf("%s: bad option: %s\n", argv[0], arg);
                return 1;
            }

            if (i == argc - 1 && active == FALSE) return 0;
            continue;
        }

        if (active == TRUE)
        {
            continue;
        }

        Main.filepath = arg;
        Main.absolute = realpath(arg, NULL);

        fp = fopen(Main.filepath, "rb");
        if (!fp)
        {
            error("Module Error");
            printf("module was not found.\n");
            return 1;
        }

        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        rewind(fp);

        buffer = malloc((size) * sizeof(* buffer));
        fread(buffer, size, 1, fp);
        buffer[size] = '\0';
        active = TRUE;
    }

    return lexer(buffer);
}
