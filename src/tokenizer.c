#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// funcao pra skipa whitespace pode pa
void sskip(Lexer *lexer)
{
    while (lexer->c[lexer->size] == ' ')
    {
        lexer->size++;
    }
}

const char *debug_type(TokenType type)
{
    switch (type)
    {
    case INT:
        return "INT";
        break;

    case IDENTIFIER:
        return "IDENTIFIER";
        break;

    case KW_PRINT:
        return "KW_PRINT";
        break;

    case KW_ADD:
        return "KW_ADD";
        break;

    case NEWLINE:
        return "NEWLINE";
        break;

    case END:
        return "END";
        break;
    
    default:
        return "UNKNOWN";
        break;
    }
}

int isAlpha(char c) {

    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

int isNum(char c)
{
    return c >= '0' && c <= '9';
}

int isAlnum(char c)
{
    return isAlpha(c) || isNum(c);
}


TokenType KW_find(const char *str) {

    for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
    {
        if (strcmp(str, keywords[i].name) == 0)
        {
            return keywords[i].type;
        }
        
    }
    
    return IDENTIFIER;
}

Token next_token(Lexer *lexer)
{
    Token n_token;
    n_token.line = lexer->line;
    sskip(lexer);
    int start = lexer->size;

    char c = lexer->c[lexer->size];

    if (c == '\0') {
        n_token.type = END;
        return n_token;
    }

    if (c == '\n') {
        n_token.type = NEWLINE;
        lexer->line++;
        lexer->size++;
        return n_token;
    }

    if (isNum(lexer->c[lexer->size]))
    {
        int number = 0;
        while (isNum(lexer->c[lexer->size]))
        {

            number = number * 10 + (lexer->c[lexer->size] - '0');

            lexer->size++;
        }

        n_token.type = INT;
        n_token.val.ival = number;
        return n_token;
    }

    if (isAlpha(c)) {
       while (isAlnum(lexer->c[lexer->size]))
       {
            lexer->size++;
       }
       int len = lexer->size - start;
       char *str = malloc(len + 1);

       if (str == NULL) {
            n_token.type = UNKNOWN;
            return n_token;
       }

       memcpy(str, &lexer->c[start], len);
       str[len] = '\0';

       n_token.type = KW_find(str);
       n_token.val.sval = str;

       return n_token;
       
    }

    n_token.type = UNKNOWN;
    lexer->size++;
    return n_token;
    
}

// int main() {
//     Lexer lexer;
//     lexer.c = "ADD 10";
//     lexer.size = 0;
    
//     printf("%s\n", debug_type(next_token(&lexer).type));
//     printf("%s\n", debug_type(next_token(&lexer).type));
//     printf("%s\n", debug_type(next_token(&lexer).type));
//     return 0;
// }