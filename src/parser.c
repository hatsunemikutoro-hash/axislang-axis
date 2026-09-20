#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "program.h"

ASTnode *parse_deref(Parser *parser);
ASTnode *parse_single_instruction(Parser *parser, ASTType type);

static char *my_strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char *p = malloc(len);
    if (p != NULL)
    {
        memcpy(p, s, len);
    }
    return p;
}

void free_ast(ASTnode *node)
{
    if (node == NULL)
        return;

    free_ast(node->left);
    free_ast(node->right);
    if (node->type == AST_STRING || node->type == AST_IDENT)
    {
        free(node->value.sval);
    }
    free(node);
}

void advance(Parser *parser)
{
    parser->current = next_token(parser->lexer);
}

ASTnode *create_node(ASTType type, Token Tok)
{
    ASTnode *node = malloc(sizeof(ASTnode));

    if (node == NULL)
    {
        return NULL;
    }

    node->type = type;

    switch (type)
    {
    case AST_INT:
        node->value.ival = Tok.val.ival;
        break;

    // TODO fazer propia strdup pra evitar libc
    case AST_STRING:
        node->value.sval = my_strdup(Tok.val.sval);
        break;

    case AST_IDENT:
        node->value.sval = my_strdup(Tok.val.sval);
        break;

    default:
        break;
    }

    node->left = NULL;
    node->right = NULL;

    return node;
}

ASTnode *parse_arg(Parser *parser)
{
    ASTType arg_type;
    switch (parser->current.type)
    {
    case INT:
        arg_type = AST_INT;
        break;
    case STRING:
        arg_type = AST_STRING;
        break;
    case IDENTIFIER:
        arg_type = AST_IDENT;
        break;
    case STAR:
        return parse_deref(parser);

    default:
        return NULL;
        break;
    }
    ASTnode *arg1 = create_node(arg_type, parser->current);

    if (arg1 == NULL)
    {
        return NULL;
    }

    advance(parser);
    return arg1;
}

ASTnode *parse_instruction_without_arg(Parser *parser, ASTType type)
{
    ASTnode *node = create_node(type, parser->current);

    if (node == NULL) {
        return NULL;
    }

    advance(parser);

    return node;
}

ASTnode *parse_single_instruction(Parser *parser, ASTType type)
{
    ASTnode *node = create_node(type, parser->current);

    if (node == NULL)
    {
        return NULL;
    }
    advance(parser);

    node->left = parse_arg(parser);

    return node;
}

ASTnode *parse_single_instruction_arg(Parser *parser, ASTType type, const char *error_msg)
{
    ASTnode *node = parse_single_instruction(parser, type);

    if (node == NULL)
    {
        return NULL;
    }

    if (node->left == NULL)
    {
        fprintf(stderr, "%s EXPECTS 1 ARGUMENT: Line %d\n", error_msg, parser->current.line);

        free_ast(node);
        return NULL;
    }
    return node;
}

ASTnode *parse_div(Parser *parser)
{
    ASTnode *node = parse_single_instruction(parser, AST_DIV);

    if (node == NULL)
    {
        return NULL;
    }

    if (node->left == NULL)
    {
        fprintf(stderr, "DIV EXPECTS 1 ARGUMENT: Line %d\n", parser->current.line);

        free_ast(node);
        return NULL;
    }

    if (node->left->type == AST_INT && node->left->value.ival == 0)
    {
        fprintf(stderr, "CANNOT DIVIDE BY 0: Line %d\n", parser->current.line);

        free_ast(node);
        return NULL;
    }

    return node;
}

ASTnode *parse_deref(Parser *parser) {
    ASTnode *node = parse_single_instruction(parser, AST_DEREF);

    if (node == NULL) {
        return NULL;
    }

    if (node->left == NULL) {
        fprintf(stderr, "CANNOT MAKE A DEREFERENCE WITHOUT A ADDRESS: Line %d\n", parser->current.line);

        free_ast(node);
        return NULL;
    }

    return node;
}

ASTnode *parse_instruction(Parser *parser)
{
    switch (parser->current.type)
    {
    case KW_PRINT:
        return parse_single_instruction(parser, AST_PRINT);

    case KW_PRINTC:
        return parse_single_instruction(parser, AST_PRINTC);

    case KW_ADD:
        return parse_single_instruction_arg(parser, AST_ADD, "ADD");

    case KW_SUB:
        return parse_single_instruction_arg(parser, AST_SUB, "SUB");

    case KW_MOVE:
        return parse_single_instruction_arg(parser, AST_MOVE, "MOVE");

    case KW_JUMP:
        return parse_single_instruction_arg(parser, AST_JUMP, "JUMP");

    case KW_SET:
        return parse_single_instruction_arg(parser, AST_SET, "SET");

    case KW_MULT:
        return parse_single_instruction_arg(parser, AST_MULT, "MULT");

    case KW_EXIT:
        return parse_instruction_without_arg(parser, AST_EXIT);

    case KW_DIV:
        return parse_div(parser);

    default:
        return NULL;
        ;
    }
}

Program *parse_program(Parser *parser)
{
    Program *program = create_program();
    if (program == NULL)
    {
        return NULL;
    }

    while (parser->current.type != END)
    {
        if (parser->current.type == NEWLINE)
        {
            advance(parser);
            continue;
        }

        ASTnode *node = parse_instruction(parser);

        if (node == NULL)
        {
            advance(parser);
            continue;
        }

        if (!program_add(program, node)) {
            free_ast(node);
            program_destroy(program);
            return NULL;
        }
    }
    return program;
}

// int main()
// {
//     Lexer lexer;
//     lexer.c = "21 + 41";
//     lexer.size = 0;

//     Parser parser;
//     parser.lexer = &lexer; // é originalmente Lexer *lexer na struct do parser ent ta suave

//     return 0;
// }