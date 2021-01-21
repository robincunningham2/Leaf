
#define TRUE                1
#define FALSE               0

#define TYPE_INT            1
#define TYPE_FLOAT          2
#define TYPE_STRING         3
#define TYPE_BOOL           4

#define ACTION_VALUE_CREATE 1

typedef struct Token {
    int token;
    int lineno;
    char * str;
    char * name;
} Token;

typedef struct Value {
    int statusCode;
    int type;
    int intValue;
    float floatValue;
    char * stringValue;
    int boolValue;
} Value;

typedef struct Process {
    char * version;
    char * module;
    char ** argv;
    int argc;
    char * filepath;
    char * absolute;
} Process;
