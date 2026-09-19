#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "tokenizer.h"
#include "program.h"

typedef struct Parser
{
    Lexer *lexer;
    Token current;
}Parser;

void advance(Parser *parser);
void free_ast(ASTnode *node);
ASTnode *parse_instruction(Parser *parser);
Program *parse_program(Parser *parser);

#endif