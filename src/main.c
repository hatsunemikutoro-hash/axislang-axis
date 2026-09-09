#include <stdio.h>
#include "parser.h"
#include <string.h>
#include "ast.h"
#include "openfile.h"
#include "interpreter.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "./axis filename\n");
        return 1;
    }

    Interpreter *interpreter = interpreter_create(argv[1]);
    if (!interpreter) {
        fprintf(stderr, "Failed to create the interpreter\n");
        return 1;
    }

    interpreter_run(interpreter);
    interpreter_destroy(interpreter);
    return 0;
}