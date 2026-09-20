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
    machine->ip = 0;
    machine->died = 0;
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
        // BUILD-IN FUNCTIONS

    case AST_PRINT:
        if (node->left == NULL)
        {
            printf("%d", machine->memory[machine->cursor]);
        }

        if (node->left != NULL && node->left->type == AST_INT)
        {
            printf("%d\n", node->left->value.ival);
        }
        break;

    case AST_PRINTC:
        if (node->left == NULL)
        {
            printf("%c", machine->memory[machine->cursor]);
        }

        if (node->left != NULL && node->left->type == AST_INT)
        {
            printf("%c", node->left->value.ival);
        }

        if (node->left != NULL && node->left->type == AST_STRING)
        {
            printf("%s\n", node->left->value.sval);
        }
        break;

    case AST_MOVE:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->cursor = node->left->value.ival;
        }
        break;

    case AST_JUMP:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->ip = node->left->value.ival;
        }
        break;

        // MATH UFNCTIONs

    case AST_SET:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->memory[machine->cursor] = node->left->value.ival;
        }
        break;

    case AST_ADD:
        if (node->left != NULL && node->left->type == AST_DEREF) {
            // AST_ADD->AST_DEREF->AST_INT->VAL
            
            machine->memory[machine->cursor] += machine->memory[node->left->left->value.ival];
        }


        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->memory[machine->cursor] += node->left->value.ival;
        }

        break;

    case AST_SUB:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->memory[machine->cursor] -= node->left->value.ival;
        }
        break;

    case AST_MULT:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->memory[machine->cursor] *= node->left->value.ival;
        }
        break;

    case AST_DIV:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->memory[machine->cursor] /= node->left->value.ival;
        }
        break;
    
    case AST_EXIT:
        machine->died = 1;
        break;
    default:
        break;
    }
}

void vm_run(Machine *machine, Program *program)
{
    while (!machine->died && machine->ip < program->count)
    {
        ASTnode *node = program->instructions[machine->ip];
        machine->ip++;

        vm_execute(machine, node);
    }
}
