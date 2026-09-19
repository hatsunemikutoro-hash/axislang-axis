#include "program.h"
#include <stdlib.h>
#include "parser.h"

#define INITIAL_CAPACITY 16
Program *create_program(void) {
    Program  *program = malloc(sizeof(*program));
    if (program == NULL) {
        return NULL;
    }
    program->instructions = malloc(INITIAL_CAPACITY * sizeof(*program->instructions));

    if (program->instructions == NULL) {
        free(program);
        return NULL;    
    }

    program->capacity = INITIAL_CAPACITY;
    program->count = 0;

    return program;
}

int program_add(Program *program, ASTnode *node) {
    if (program == NULL || node == NULL) {
        return 0;
    }

    if (program->count == program->capacity) {
        size_t new_capacity = program->capacity * 2;
        ASTnode **new_instructions = realloc(program->instructions, new_capacity * sizeof(*new_instructions));

        if (new_instructions == NULL) {
            return 0;
        }

        program->instructions = new_instructions;
        program->capacity = new_capacity;
    }

    program->instructions[program->count] = node;
    program->count++;

    return 1;
}

void program_destroy(Program *program) {
    if (program == NULL) {
        return;
    }

    for (size_t i = 0; i < program->count; i++)
    {
        free_ast(program->instructions[i]);
    }

    free(program->instructions);
    free(program);
    
}