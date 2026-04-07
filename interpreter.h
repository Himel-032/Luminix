#ifndef INTERPRETER_H
#define INTERPRETER_H



#include "ast.h"


void interpret(ASTNode *root);


double eval_expr(ASTNode *n);


void   exec_stmt(ASTNode *n);


double call_function(const char *name, ASTNode *arg_list);

#endif 
