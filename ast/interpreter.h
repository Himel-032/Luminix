#ifndef INTERPRETER_H
#define INTERPRETER_H

/* =========================================================
 *  interpreter.h  –  AST evaluator interface
 * ========================================================= */

#include "ast.h"

/* Entry point: walk and execute the whole program tree */
void interpret(ASTNode *root);

/* Evaluate an expression node → double */
double eval_expr(ASTNode *n);

/* Execute a statement (or statement list) node */
void   exec_stmt(ASTNode *n);

/* Call a user-defined function with an evaluated argument list.
   Returns the function's return value (0.0 for void functions). */
double call_function(const char *name, ASTNode *arg_list);

#endif /* INTERPRETER_H */
