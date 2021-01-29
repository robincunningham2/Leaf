#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <json-c/json.h>
#include "../h/Helper.h"

extern Process Main;
extern void error(char * name);

char * repeat(int n, const char * s)
{
    size_t slen = strlen(s);
    char * dest = malloc(n * slen + 1);
 
    int i; char * p;
    for (i = 0, p = dest; i < n; ++i, p += slen)
    {
        memcpy(p, s, slen);
    }

    * p = '\0';
    return dest;
}

char * concat(char * s1, char * s2)
{
    char s[strlen(s1) + strlen(s2) + 1];
    snprintf(s, sizeof(s), "%s%s", s1, s2);

    return s;
}

int checkDir(int i)
{
    char * dir = dirname(strdup(Main.absolute));

    char * filepath;
    char * abs;
    FILE * fp;
    char * suffix;

    suffix = repeat(i, "/..");
    filepath = concat(
        dir,
        concat(suffix, "/module.json")
    );

    abs = realpath(filepath, NULL);

    fp = fopen(abs, "rb");
    if (!fp) return 0;
    else return 1;
}

int invalidType(const char * filepath, char * field, char * expected)
{
    printf("%s: Invalid type for field '%s'. Expected %s\n", filepath, field, expected);
    return 1;
}

int parseModuleFile()
{
    // find module.json file

    char * dir = dirname(strdup(Main.absolute));
    char * filepath;
    char * final;

    FILE * fp;
    long size;
    char * buffer;

    char * suffix;
    int i = 0;

    while (!fp)
    {
        suffix = repeat(i, "../");
        if (strlen(suffix) == 0) suffix = repeat(1, "./");
        filepath = concat(suffix, "module.json");

        char * abs = realpath(filepath, NULL);
        fp = fopen(abs, "rb");

        if (fp)
        {
            final = malloc(strlen(abs) + 1);
            strcpy(final, abs);
        }

        if (
            abs == "C:/"
            || abs == "/"
        ) break;

        i++;
    }

    if (!fp)
    {
        error("Module Error");
        printf("Cannot find module.json file\n");
        return 1;
    }

    // read json file

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    buffer = malloc((size) * sizeof(* buffer));
    fread(buffer, size, 1, fp);
    fclose(fp);
    buffer[size] = '\0';

    struct json_object * object;
    struct json_object * name;
    struct json_object * version;
    struct json_object * description;
    struct json_object * author;
    struct json_object * license;

    object = json_tokener_parse(buffer);

    json_object_object_get_ex(object, "name", &name);
    json_object_object_get_ex(object, "version", &version);
    json_object_object_get_ex(object, "description", &description);
    json_object_object_get_ex(object, "author", &author);
    json_object_object_get_ex(object, "license", &license);

    if (json_object_get_type(name) != json_type_string)
        return invalidType(final, "name", "string");
    if (json_object_get_type(version) != json_type_string)
        return invalidType(final, "version", "string");
    if (json_object_get_type(description) != json_type_string)
        return invalidType(final, "description", "string");
    if (json_object_get_type(author) != json_type_string)
        return invalidType(final, "author", "string");
    if (json_object_get_type(author) != json_type_string && json_object_get_type(author) != json_type_null)
        return invalidType(final, "license", "string or null");
    
    return 0;
}
