#ifndef VM_H
#define VM_H

#define MAX_MEM 256

#include "ast.h"
#include "program.h"

typedef struct Machine
{
    int memory[MAX_MEM];
    int cursor;

    size_t ip;
    int died;
} Machine;

Machine* vm_create(void);
void vm_destroy(Machine* machine);
void vm_execute(Machine* machine, ASTnode* node);
void vm_run(Machine* machine, Program *program);

#endif