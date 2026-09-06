#ifndef AST_H
#define AST_H

typedef enum {
    AST_PRINT,
    AST_ADD,
    AST_SUB,
    AST_GOTO,
    AST_SET,

    AST_INT,
    AST_IDENT,
    AST_MUL,
    AST_DIV
} ASTType;

typedef struct ASTnode
{
    ASTType type;
    int value;

    struct ASTnode *left;
    struct ASTnode *right;
}ASTnode;


#endif