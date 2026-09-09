#include <stdlib.h>
#include <stdio.h>

#include "interpreter.h"
#include "openfile.h"

Interpreter *interpreter_create(const char *filename)
{
    Interpreter *interpret = malloc(sizeof(Interpreter));

    Lexer *lexer = malloc(sizeof(Lexer));
    lexer->size = 0;
    lexer->line = 0;
    lexer->c = read_file(filename);

    Parser *parser = malloc(sizeof(Lexer));
    parser->lexer = lexer;
    advance(parser);

    interpret->parser = parser;
    interpret->vm = vm_create();

    return interpret;
}

void interpreter_destroy(Interpreter* interp) {
    free(interp->parser->lexer->c);
    free(interp->parser->lexer);
    free(interp->parser);

    vm_destroy(interp->vm);
    free(interp);
}

void interpreter_run(Interpreter* interp) {
    while (interp->parser->current.type != END) 
    {
        if (interp->parser->current.type == NEWLINE) {
            advance(interp->parser);
            continue;
        }

        ASTnode *node = parse_instruction(interp->parser);
        if(node) {
            vm_execute(interp->vm, node);
            free_ast(node);
        } else {
            advance(interp->parser);
        }
        
    }
    
}