#include "vm.h"
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Machine *vm_create(void)
{
    Machine *machine = malloc(sizeof(Machine));
    memset(machine->memory, 0, sizeof(machine->memory));
    machine->cursor = 0;
    return machine;
}

void vm_destroy(Machine *machine)
{
    free(machine);
}

void vm_execute(Machine *machine, ASTnode *node)
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

    case AST_MULT:
        if (node->left != NULL && node->left->type == AST_INT) {
            machine->memory[machine->cursor] *= node->left->value;
        }
        break;

    case AST_DIV:
        if (node->left != NULL && node->left->type == AST_INT) {
            machine->memory[machine->cursor] /= node->left->value;
        }
        break;

    default:
        break;
    }
}