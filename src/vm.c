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

int resolve_operand(Machine *machine, ASTnode *operand, int *result)
{
    if (operand == NULL || result == NULL)
    {
        return 0;
    }

    if (operand->type == AST_INT)
    {
        *result = operand->value.ival;
        return 1;
    }

    if (operand->type == AST_DEREF && operand->left != NULL && operand->left->type == AST_INT)
    {

        int address = operand->left->value.ival;

        if (address < 0 || address >= MAX_MEM)
        {
            return 0;
        }

        *result = machine->memory[address];
        return 1;
    }

    return 0;
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
    {
        int operand;
        if (resolve_operand(machine, node->left, &operand))
        {
            machine->memory[machine->cursor] = operand;
        }
        break;
    }

    case AST_JUMP:
        if (node->left != NULL && node->left->type == AST_INT)
        {
            machine->ip = node->left->value.ival;
        }
        break;

        // MATH UFNCTIONs

    case AST_SET:
    {
        int operand;
        if (resolve_operand(machine, node->left, &operand))
        {
            machine->memory[machine->cursor] = operand;
        }
        break;
    }

    case AST_ADD:
    {
        int operand;
        if (resolve_operand(machine, node->left, &operand))
        {
            machine->memory[machine->cursor] += operand;
        }
        break;
    }

    case AST_SUB:
    {
        int operand;
        if (resolve_operand(machine, node->left, &operand))
        {
            machine->memory[machine->cursor] -= operand;
        }
        break;
    }

    case AST_MULT:
    {
        int operand;
        if (resolve_operand(machine, node->left, &operand))
        {
            machine->memory[machine->cursor] *= operand;
        }
        break;
    }

    case AST_DIV:
    {
        int operand;
        if (resolve_operand(machine, node->left, &operand))
        {
            if (operand == 0)
            {
                fprintf(stderr, "Axis error: CANNOT DIVIDE BY ZERO\n");
                break;
            }

            machine->memory[machine->cursor] /= operand;
        }
        break;
    }

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
