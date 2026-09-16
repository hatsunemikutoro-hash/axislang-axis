#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum TokenType{
    INT,
    IDENTIFIER,
    STRING,
    NEWLINE,

    // BuildIn functions

    KW_PRINT,
    KW_GOTO,
    KW_SET,
    KW_PRINTC,

    // math shit

    KW_ADD,
    KW_SUB,
    KW_MULT,
    KW_DIV,

    END,
    UNKNOWN
} TokenType;

typedef struct Keyword
{
    const char *name;
    TokenType type;
}Keyword;

typedef struct Token
{
    union
    {
        int ival;
        char *sval;
    } val;
    TokenType type;
    int line;
} Token;

typedef struct Lexer
{
    int size;
    char *c;
    int line;
} Lexer;

static const Keyword keywords[] = {
    // buiiçldin fuction

    {"PRINT", KW_PRINT},
    {"GOTO", KW_GOTO},
    {"SET", KW_SET},
    {"PRINTC", KW_PRINTC},

    // math shit

    {"ADD", KW_ADD},
    {"SUB", KW_SUB},
    {"MULT", KW_MULT},
    {"DIV", KW_DIV}
};

Token next_token(Lexer *lexer);

#endif
