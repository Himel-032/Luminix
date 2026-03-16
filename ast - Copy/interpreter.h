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

#endif /* INTERPRETER_H */
