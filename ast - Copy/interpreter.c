/* =========================================================
 *  interpreter.c  –  Tree-walking interpreter for Luminix
 * ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ast.h"
#include "symtab.h"
#include "interpreter.h"

/* ------------------------------------------------------------------ */
/* Control-flow signals (propagated up the call stack)                */
/* ------------------------------------------------------------------ */
static int g_break    = 0;   /* set when BREAK is hit   */
static int g_return   = 0;   /* set when RETURN is hit  */
static double g_retval = 0;  /* value from RETURN       */

/* ================================================================== */
/*  eval_expr  –  evaluate an expression node, return double          */
/* ================================================================== */
double eval_expr(ASTNode *n) {
    if (!n) return 0;

    switch (n->type) {

        /* ---- literals ---- */
        case NODE_INT_LIT:    return (double)n->ival;
        case NODE_FLOAT_LIT:  return n->dval;
        case NODE_CHAR_LIT:   return (double)n->cval;
        case NODE_BOOL_LIT:   return (double)n->ival;
        case NODE_STRING_LIT:
            fprintf(stderr, "Runtime error: cannot use string literal in numeric expression\n");
            return 0;

        /* ---- identifier lookup ---- */
        case NODE_IDENT:
            return sym_get(n->sval);

        /* ---- arithmetic ---- */
        case NODE_ADD:    return eval_expr(n->left) + eval_expr(n->right);
        case NODE_SUB:    return eval_expr(n->left) - eval_expr(n->right);
        case NODE_MUL:    return eval_expr(n->left) * eval_expr(n->right);
        case NODE_DIV: {
            double rhs = eval_expr(n->right);
            if (rhs == 0) { fprintf(stderr, "Runtime error: division by zero\n"); return 0; }
            return eval_expr(n->left) / rhs;
        }
        case NODE_MOD: {
            int rhs = (int)eval_expr(n->right);
            if (rhs == 0) { fprintf(stderr, "Runtime error: modulo by zero\n"); return 0; }
            return (double)((int)eval_expr(n->left) % rhs);
        }
        case NODE_NEGATE:
            return -eval_expr(n->left);

        /* ---- comparisons (return 0 or 1) ---- */
        case NODE_EQ:  return eval_expr(n->left) == eval_expr(n->right);
        case NODE_NEQ: return eval_expr(n->left) != eval_expr(n->right);
        case NODE_GT:  return eval_expr(n->left) >  eval_expr(n->right);
        case NODE_LT:  return eval_expr(n->left) <  eval_expr(n->right);
        case NODE_GE:  return eval_expr(n->left) >= eval_expr(n->right);
        case NODE_LE:  return eval_expr(n->left) <= eval_expr(n->right);

        /* ---- built-in math ---- */
        case NODE_POW:   return pow(eval_expr(n->left), eval_expr(n->right));
        case NODE_SQRT:  return sqrt(eval_expr(n->left));
        case NODE_ABS:   return fabs(eval_expr(n->left));
        case NODE_FLOOR: return floor(eval_expr(n->left));
        case NODE_CEIL:  return ceil(eval_expr(n->left));

        /* ---- array access ---- */
        case NODE_ARRAY_ACCESS: {
            int idx = (int)eval_expr(n->left);
            return sym_get_array(n->sval, idx);
        }
        case NODE_ARRAY_ACCESS_2D: {
            int r = (int)eval_expr(n->left);
            int c = (int)eval_expr(n->right);
            return sym_get_array2d(n->sval, r, c);
        }

        default:
            fprintf(stderr, "Runtime error: unknown expression node type %d\n", n->type);
            return 0;
    }
}

/* ================================================================== */
/*  exec_if  –  handle if / elseif* / else chain                      */
/* ================================================================== */

/*
 * Node layout for an if statement:
 *
 *   NODE_IF
 *     left   = condition expression
 *     right  = then-body (NODE_STMT_LIST or single stmt)
 *     extra  = next clause (NODE_ELSEIF | NODE_ELSE | NULL)
 *
 *   NODE_ELSEIF
 *     left   = condition expression
 *     right  = body
 *     extra  = next clause
 *
 *   NODE_ELSE
 *     left   = body
 */
static void exec_if(ASTNode *n, int already_matched) {
    if (!n) return;

    if (n->type == NODE_IF || n->type == NODE_ELSEIF) {
        if (!already_matched) {
            double cond = eval_expr(n->left);
            if (cond) {
                exec_stmt(n->right);
                already_matched = 1;
            }
        }
        exec_if(n->extra, already_matched);
    } else if (n->type == NODE_ELSE) {
        if (!already_matched) {
            exec_stmt(n->left);
        }
    }
}

/* ================================================================== */
/*  exec_switch – handle switch / case / case-range / default         */
/* ================================================================== */

/*
 * NODE_SWITCH
 *   left  = expression being switched on
 *   right = linked list of case/default nodes via ->next
 *
 * NODE_CASE
 *   left  = case expression
 *   right = body (NODE_STMT_LIST)
 *
 * NODE_CASE_RANGE
 *   left  = start expr
 *   right = end expr
 *   extra = body
 *
 * NODE_DEFAULT
 *   left  = body
 */
static void exec_switch(ASTNode *n) {
    double val  = eval_expr(n->left);
    int matched = 0;

    ASTNode *clause = n->right;
    while (clause) {
        if (g_break) { g_break = 0; break; }

        if (clause->type == NODE_CASE) {
            double case_val = eval_expr(clause->left);
            if (!matched && fabs(val - case_val) < 1e-9) matched = 1;
            if (matched) {
                exec_stmt(clause->right);
                if (g_break) { g_break = 0; break; }
            }

        } else if (clause->type == NODE_CASE_RANGE) {
            int start = (int)eval_expr(clause->left);
            int end   = (int)eval_expr(clause->right);
            int ival  = (int)val;
            if (!matched && ival >= start && ival <= end) matched = 1;
            if (matched) {
                exec_stmt(clause->extra);
                if (g_break) { g_break = 0; break; }
            }

        } else if (clause->type == NODE_DEFAULT) {
            if (!matched) matched = 1;
            if (matched) {
                exec_stmt(clause->left);
                if (g_break) { g_break = 0; break; }
            }
        }

        clause = clause->next;
    }
    g_break = 0; /* consume any leftover break */
}

/* ================================================================== */
/*  exec_stmt  –  execute a statement node                            */
/* ================================================================== */
void exec_stmt(ASTNode *n) {
    if (!n || g_return) return;

    switch (n->type) {

        /* ---- statement list ---- */
        case NODE_STMT_LIST:
            exec_stmt(n->left);
            if (!g_break && !g_return)
                exec_stmt(n->next);
            break;

        /* ---- declarations ---- */
        case NODE_DECL:
            /* left = optional init expression (may be NULL → 0) */
            sym_set(n->sval,
                    n->left ? eval_expr(n->left) : 0,
                    n->decl_type);
            break;

        case NODE_DECL_ARRAY:
            /* cols field re-purposed to store 1-D size */
            sym_declare_array(n->sval, n->cols, n->decl_type);
            break;

        case NODE_DECL_ARRAY_2D:
            sym_declare_array2d(n->sval, n->rows, n->cols, n->decl_type);
            break;

        /* ---- assignment ---- */
        case NODE_ASSIGN:
            sym_set(n->sval, eval_expr(n->left), n->decl_type);
            break;

        case NODE_ARRAY_ASSIGN: {
            int idx = (int)eval_expr(n->left);
            sym_set_array(n->sval, idx, eval_expr(n->right));
            break;
        }

        case NODE_ARRAY_ASSIGN_2D: {
            int r = (int)eval_expr(n->left);
            int c = (int)eval_expr(n->right);
            sym_set_array2d(n->sval, r, c, eval_expr(n->extra));
            break;
        }

        /* ---- print ---- */
        case NODE_PRINT:
            if (n->sval) {
                /* print a string literal or identifier */
                if (n->left) {
                    /* identifier: n->sval holds name, check type */
                    int t = sym_get_type(n->sval);
                    double v = sym_get(n->sval);
                    if (t == 1) printf("%c\n", (int)v);
                    else        printf("%g\n", v);
                } else {
                    /* string literal */
                    char *s = n->sval;
                    /* strip surrounding quotes if present */
                    if (s[0] == '"') s++;
                    int len = (int)strlen(s);
                    if (len > 0 && s[len-1] == '"') s[len-1] = '\0';
                    printf("%s\n", s);
                    /* restore quote for freeing later */
                    /* (we don't, because sval is heap-owned and was strdup'd) */
                }
            } else {
                /* numeric expression */
                printf("%g\n", eval_expr(n->left));
            }
            break;

        /* ---- scan ---- */
        case NODE_SCAN: {
            int t = sym_get_type(n->sval);
            if (t == 1) {
                char c; scanf(" %c", &c);
                sym_set(n->sval, (double)c, t);
            } else {
                double v; scanf("%lf", &v);
                sym_set(n->sval, v, t);
            }
            break;
        }

        case NODE_SCAN_ARRAY: {
            int idx = (int)eval_expr(n->left);
            double v; scanf("%lf", &v);
            sym_set_array(n->sval, idx, v);
            break;
        }

        /* ---- control flow ---- */
        case NODE_IF:
            exec_if(n, 0);
            break;

        case NODE_SWITCH:
            exec_switch(n);
            break;

        case NODE_BREAK:
            g_break = 1;
            break;

        /* ---- while loop ---- */
        case NODE_WHILE: {
            /*
             * left  = condition expr
             * right = body
             */
            while (eval_expr(n->left)) {
                exec_stmt(n->right);
                if (g_break)  { g_break  = 0; break; }
                if (g_return) break;
            }
            break;
        }

        /* ---- for loop ---- */
        case NODE_FOR: {
            /*
             * left  = init assignment node
             * right = body
             * extra = NODE_FOR_PARTS (condition=left, update=right)
             *         stored directly: extra->left = cond, extra->right = update
             */
            exec_stmt(n->left);               /* init           */
            while (eval_expr(n->extra->left)) {  /* condition   */
                exec_stmt(n->right);             /* body         */
                if (g_break)  { g_break  = 0; break; }
                if (g_return) break;
                exec_stmt(n->extra->right);      /* update       */
            }
            break;
        }

        /* ---- return ---- */
        case NODE_RETURN:
            g_retval = eval_expr(n->left);
            printf("Program returned: %g\n", g_retval);
            g_return = 1;
            break;

        default:
            fprintf(stderr, "Runtime error: unknown statement node type %d\n", n->type);
            break;
    }
    
    /* After executing this statement, execute the next one in the list */
    if (!g_break && !g_return && n->next) {
        exec_stmt(n->next);
    }
}

/* ================================================================== */
/*  interpret  –  entry point                                         */
/* ================================================================== */
void interpret(ASTNode *root) {
    if (!root) return;
    /* The root is NODE_PROGRAM whose left child is the statement list */
    exec_stmt(root->left);
}
