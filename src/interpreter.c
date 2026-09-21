#include <stdlib.h>
#include <stdio.h>

#include "interpreter.h"
#include "program.h"
#include "openfile.h"

Interpreter *interpreter_create(const char *filename)
{
    Interpreter *interpret = malloc(sizeof(Interpreter));

    if (interpret == NULL)
    {
        fprintf(stderr, "Internal Error: Failed to allocate interpreter\n");
        free(interpret);
        return NULL;
    }

    Lexer *lexer = malloc(sizeof(Lexer));

    if (lexer == NULL)
    {
        fprintf(stderr, "Internal Error: Failed to allocate lexer\n");
        free(interpret);
        return NULL;
    }
    lexer->size = 0;
    lexer->line = 1;
    lexer->c = read_file(filename);

    if (lexer->c == NULL)
    {
        free(lexer);
        free(interpret);
        return NULL;
    }

    Parser *parser = malloc(sizeof(Parser));

    if (parser == NULL)
    {
        fprintf(stderr, "Internal Error: Failed to allocate parser\n");
        free(lexer->c);
        free(lexer);
        free(interpret);
        return NULL;
    }
    parser->lexer = lexer;
    advance(parser);

    interpret->parser = parser;
    interpret->vm = vm_create();

    if (interpret->vm == NULL)
    {
        fprintf(stderr, "Axis error: failed to allocate virtual machine\n");
        free(parser);
        free(lexer->c);
        free(lexer);
        free(interpret);
        return NULL;
    }

    interpret->program = parse_program(parser);

    if (interpret->program == NULL)
    {
        fprintf(stderr, "Axis error: failed to parse program\n");
        vm_destroy(interpret->vm);
        free(parser);
        free(lexer->c);
        free(lexer);
        free(interpret);
        return NULL;
    }

    return interpret;
}

void interpreter_destroy(Interpreter *interp)
{
    if (interp == NULL)
    {
        return;
    }
    program_destroy(interp->program);

    free(interp->parser->lexer->c);
    free(interp->parser->lexer);
    free(interp->parser);

    vm_destroy(interp->vm);
    free(interp);
}

void interpreter_run(Interpreter *interp)
{
    vm_run(interp->vm, interp->program);
}