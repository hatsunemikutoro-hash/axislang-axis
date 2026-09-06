#include <stdio.h>
#include "parser.h"
#include <string.h>
#include "ast.h"
#include "openfile.h"

#define MAX_MEM 256

typedef struct Machine
{
    int memory[MAX_MEM];
    int cursor;
} Machine;

void execute(ASTnode *node, Machine *machine)
{
    if (node == NULL)
    {
        return;
    }

    switch (node->type)
    {
    case AST_PRINT:
        if (node->left == NULL)
        {
            printf("%d", machine->memory[machine->cursor]);
        }

        if (node->left != NULL && node->left->type == AST_INT)
        {
            printf("%d\n", node->left->value);
        }
        break;

    case AST_ADD:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->memory[machine->cursor] += node->left->value;
        }

        break;

    case AST_SUB:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->memory[machine->cursor] -= node->left->value;
        }
        break;

    case AST_GOTO:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->cursor = node->left->value;
        }
        break;

    case AST_SET:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->memory[machine->cursor] = node->left->value;
        }
        break;

    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        Lexer lexer;
        lexer.size = 0;
        lexer.line = 0;
        lexer.c = read_file(argv[1]);

        Parser parser;
        parser.lexer = &lexer;

        Machine machine;

        memset(machine.memory, 0, sizeof(machine.memory));
        machine.cursor = 0;
        advance(&parser);

        while (parser.current.type != END)
        {

            if (parser.current.type == NEWLINE)
            {
                advance(&parser);
                continue;
            }

            ASTnode *root = parse_instruction(&parser);

            if (root != NULL)
            {
                execute(root, &machine);
                free_ast(root);
            }
            else
            {
                advance(&parser);
            }
        }
    }
    else
    {
        fprintf(stderr, "./axis (filename)");
    }

    return 0;
}