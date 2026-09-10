#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum {
    INT,
    IDENTIFIER,
    NEWLINE,

    KW_PRINT,
    KW_ADD,
    KW_SUB,
    KW_GOTO,
    KW_SET,
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
    {"PRINT", KW_PRINT},
    {"ADD", KW_ADD},
    {"SUB", KW_SUB},
    {"GOTO", KW_GOTO},
    {"SET", KW_SET},
    {"MULT", KW_MULT},
    {"DIV", KW_DIV}
};

Token next_token(Lexer *lexer);

#endif
