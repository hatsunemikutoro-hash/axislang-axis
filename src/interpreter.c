#include <stdlib.h>
#include <stdio.h>

#include "interpreter.h"
#include "program.h"
#include "openfile.h"

Interpreter *interpreter_create(const char *filename)
{
    Interpreter *interpret = malloc(sizeof(Interpreter));

    Lexer *lexer = malloc(sizeof(Lexer));
    lexer->size = 0;
    lexer->line = 1;
    lexer->c = read_file(filename);

    Parser *parser = malloc(sizeof(Parser));
    parser->lexer = lexer;
    advance(parser);

    interpret->parser = parser;
    interpret->vm = vm_create();

    interpret->program = parse_program(parser);

    return interpret;
}

void interpreter_destroy(Interpreter* interp) {
    if  (interp == NULL) {
        return;
    }
    program_destroy(interp->program);

    free(interp->parser->lexer->c);
    free(interp->parser->lexer);
    free(interp->parser);

    vm_destroy(interp->vm);
    free(interp);
}

void interpreter_run(Interpreter* interp) {
    vm_run(interp->vm, interp->program);
    
}