#ifndef PROGRAM_H
#define PROGRAM_H

#include <stddef.h>
#include "ast.h"

typedef struct Program 
{
    ASTnode **instructions;
    size_t count;
    size_t capacity;
}Program;

Program *create_program(void);
int program_add(Program *program, ASTnode  *node);
void program_destroy(Program *program);


#endif