#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

void free_ast(ASTnode *node)
{
    if (node == NULL)
        return;

    free_ast(node->left);
    free_ast(node->right);

    free(node);
}

void advance(Parser *parser)
{
    parser->current = next_token(parser->lexer);
}

ASTnode *create_node(ASTType type, int val)
{
    ASTnode *node = malloc(sizeof(ASTnode));

    if (node == NULL)
    {
        return NULL;
    }

    node->type = type;
    node->value = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}

ASTnode *parse_int_arg(Parser *parser)
{
    if (parser->current.type != INT)
    {
        return NULL;
    }

    ASTnode *arg1 = create_node(AST_INT, parser->current.val.ival);

    if (arg1 == NULL) {
        return NULL;
    }

    advance(parser);

    return arg1;
}

ASTnode *parse_single_instruction(Parser *parser, ASTType type)
{
    ASTnode *node = create_node(type, 0);

    if (node == NULL)
    {
        return NULL;
    }
    advance(parser);

    node->left = parse_int_arg(parser);

    return node;
}

ASTnode *parse_add(Parser *parser) {
        ASTnode *node = parse_single_instruction(parser, AST_ADD);

        if (node == NULL)
        {
            return NULL;
        }

        if (node->left == NULL)
        {
            fprintf(stderr, "ADD EXPECTS 1 ARGUMENT: Line %d\n", parser->current.line);

            free_ast(node);
            return NULL;
        }
        return node;
    }

ASTnode *parse_sub(Parser *parser) {
        ASTnode *node = parse_single_instruction(parser, AST_SUB);

        if (node == NULL)
        {
            return NULL;
        }

        if (node->left == NULL)
        {
            fprintf(stderr, "SUB EXPECTS 1 ARGUMENT: Line %d\n", parser->current.line);

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

    case KW_ADD:
        return parse_add(parser);

    case KW_SUB:
        return parse_sub(parser);

    default:
        return NULL;;
    }

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