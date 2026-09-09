#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "tokenizer.h"
#include "parser.h"
#include "vm.h"


typedef struct Interpreter
{
    Parser *parser;
    Machine *vm;
} Interpreter;

Interpreter* interpreter_create(const char* filename);
void interpreter_run(Interpreter* interp);
void interpreter_destroy(Interpreter* interp);

#endif
