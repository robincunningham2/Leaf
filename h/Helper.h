
#define TRUE    1
#define FALSE   0

#define none    0
#define error   -1

#define token_float     1
#define token_int       2
#define token_bool      3
#define token_string    4

#define token_keyword   5
#define token_id        6

#define token_lpar      7
#define token_rpar      8
#define token_lsqb      9
#define token_rsqb      10

#define token_plus      11
#define token_minus     12
#define token_multi     13
#define token_slash     14

#define token_vbar      15
#define token_and       16
#define token_dot       17
#define token_comma     18
#define token_colon     19
#define token_semicolon 20

#define token_equal     21
#define token_isequal   22
#define token_notequal  23
#define token_less      24
#define token_greater   25

typedef struct {
    int _success;
    int type;
    int lineno;
    char * text;
} token_t;

char * getTokenName(token_t token);
char * concat(char * s1, char * s2, char * s3);

int error(char * type, char * content);
void warn(char * content);
