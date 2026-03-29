/* =========================================================
 *  semantic.c  –  Semantic Analysis implementation
 *
 *  Single-pass AST walk that checks:
 *    1. Variable declared before use
 *    2. No redeclaration in the same scope
 *    3. Function declared before call
 *    4. Argument count matches parameter count
 *    5. Type compatibility (numeric vs char assignments)
 *    6. Return value present/absent matches function ret_type
 *    7. break / continue only inside a loop or switch
 *    8. Array vs scalar access consistency
 *    9. Division by zero (literal-level only)
 *   10. Void function result used in an expression
 * ========================================================= */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "semantic.h"
#include "ast.h"
#include "symtab.h"

/* =========================================================
 *  Internal state
 * ========================================================= */

/* ---------- scoped symbol table ---------- */
#define SEM_SYM_MAX   1024
#define SEM_SCOPE_MAX   64

static SemSymbol sem_syms[SEM_SYM_MAX];
static int       sem_sym_count = 0;

/* scope stack: each entry stores the symcount at scope entry */
static int sem_scope_stack[SEM_SCOPE_MAX];
static int sem_scope_top = 0;

/* ---------- function table ---------- */
#define SEM_FUNC_MAX 200
static SemFunc sem_funcs[SEM_FUNC_MAX];
static int     sem_func_count = 0;

/* ---------- context flags ---------- */
static int inside_loop   = 0;   /* depth counter for loops   */
static int inside_switch = 0;   /* depth counter for switch  */

/* current function being analysed (NULL at top level) */
static SemFunc *current_func = NULL;

/* ---------- public counters ---------- */
int sem_error_count   = 0;
int sem_warning_count = 0;

/* =========================================================
 *  Helpers: error / warning reporters
 * ========================================================= */

static void sem_error(int line, const char *fmt, ...)
{
    va_list ap;
    if(line > 0)
        fprintf(stderr, "[Semantic Error] (line %d) ", line);
    else
        fprintf(stderr, "[Semantic Error] ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    sem_error_count++;
}

static void sem_warning(int line, const char *fmt, ...)
{
    va_list ap;
    if(line > 0)
        fprintf(stderr, "[Semantic Warning] (line %d) ", line);
    else
        fprintf(stderr, "[Semantic Warning] ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    sem_warning_count++;
}

/* =========================================================
 *  Scope management
 * ========================================================= */

static void scope_push(void)
{
    if (sem_scope_top >= SEM_SCOPE_MAX) {
        sem_error(0, "scope stack overflow (too many nested blocks)");
        return;
    }
    sem_scope_stack[sem_scope_top++] = sem_sym_count;
}

static void scope_pop(void)
{
    if (sem_scope_top <= 0) return;
    sem_sym_count = sem_scope_stack[--sem_scope_top];
}

/* =========================================================
 *  Symbol-table helpers
 * ========================================================= */

/* Look up a symbol in ALL visible scopes (top-down). */
static SemSymbol *sym_find_visible(const char *name)
{
    for (int i = sem_sym_count - 1; i >= 0; i--)
        if (strcmp(sem_syms[i].name, name) == 0)
            return &sem_syms[i];
    return NULL;
}

/* Look up only in the CURRENT (innermost) scope. */
static SemSymbol *sym_find_current_scope(const char *name)
{
    int scope_start = (sem_scope_top > 0)
                      ? sem_scope_stack[sem_scope_top - 1]
                      : 0;
    for (int i = sem_sym_count - 1; i >= scope_start; i--)
        if (strcmp(sem_syms[i].name, name) == 0)
            return &sem_syms[i];
    return NULL;
}

/* Declare a new symbol in the current scope. */
static void sym_declare(const char *name, int sem_type,
                        int is_array, int dimensions,
                        int size, int rows, int cols, int line)
{
    /* Redeclaration check within the same scope */
    if (sym_find_current_scope(name)) {
        sem_error(line, "redeclaration of '%s' in the same scope", name);
        return;
    }
    if (sem_sym_count >= SEM_SYM_MAX) {
        sem_error(line, "internal: semantic symbol table full");
        return;
    }
    SemSymbol *s = &sem_syms[sem_sym_count++];
    strncpy(s->name, name, 63);
    s->sem_type   = sem_type;
    s->is_array   = is_array;
    s->dimensions = dimensions;
    s->array_size = size;
    s->rows       = rows;
    s->cols       = cols;
}

/* =========================================================
 *  Function-table helpers
 * ========================================================= */

static SemFunc *func_find(const char *name)
{
    for (int i = 0; i < sem_func_count; i++)
        if (strcmp(sem_funcs[i].name, name) == 0)
            return &sem_funcs[i];
    return NULL;
}

/* Register function signature (first pass). */
static void func_register(ASTNode *n)
{
    /* n->type == NODE_FUNC_DEF
       n->sval  = name
       n->ret_type = return type (0=numeric,1=char,2=void)
       n->left  = param list (NODE_PARAM linked via ->next)
       n->right = body  */

    const char *name = n->sval;

    /* Allow redefinition (warn) */
    SemFunc *existing = func_find(name);
    if (existing) {
        sem_warning(n->line, "redefinition of function '%s'", name);
        /* overwrite */
    } else {
        if (sem_func_count >= SEM_FUNC_MAX) {
            sem_error(0, "too many functions");
            return;
        }
        existing = &sem_funcs[sem_func_count++];
    }

    strncpy(existing->name, name, 63);
    existing->ret_type    = n->ret_type;  /* 0/1/2 */
    existing->param_count = 0;

    ASTNode *p = n->left;   /* param list */
    while (p && existing->param_count < PARAM_MAX) {
        if (p->type == NODE_PARAM) {
            existing->param_types[existing->param_count++] = p->decl_type;
        }
        p = p->next;
    }
}

/* =========================================================
 *  Forward declarations for mutual recursion
 * ========================================================= */
static int  check_expr (ASTNode *n);   /* returns SEM_TYPE_* */
static void check_stmt (ASTNode *n);
static void check_stmts(ASTNode *n);
static int check_expr_nonvoid(ASTNode *n, int line, const char *ctx)
{
    int t = check_expr(n);
    if (t == SEM_TYPE_VOID) {
        sem_error(line, "void function result used in %s", ctx);
        return SEM_TYPE_UNKNOWN;
    }
    return t;
}
/* =========================================================
 *  Expression checker
 *  Returns the semantic type of the expression, or
 *  SEM_TYPE_UNKNOWN on error (so callers can continue).
 * ========================================================= */
static int check_expr(ASTNode *n)
{
    if (!n) return SEM_TYPE_UNKNOWN;

    switch (n->type) {

    /* ---- literals ---- */
    case NODE_INT_LIT:
    case NODE_FLOAT_LIT:
    case NODE_BOOL_LIT:
        return SEM_TYPE_NUMERIC;

    case NODE_CHAR_LIT:
        return SEM_TYPE_CHAR;

    case NODE_STRING_LIT:
        return SEM_TYPE_CHAR;   /* treat as char sequence */

    /* ---- identifier ---- */
    case NODE_IDENT: {
        SemSymbol *s = sym_find_visible(n->sval);
        if (!s) {
            sem_error(n->line, "use of undeclared variable '%s'", n->sval);
            return SEM_TYPE_UNKNOWN;
        }
        if (s->is_array) {
            sem_warning(n->line, "array '%s' used without index (treating as pointer)", n->sval);
        }
        return s->sem_type;
    }

    /* ---- 1-D array access ---- */
    case NODE_ARRAY_ACCESS: {
        SemSymbol *s = sym_find_visible(n->sval);
        if (!s) {
            sem_error(n->line, "use of undeclared array '%s'", n->sval);
            return SEM_TYPE_UNKNOWN;
        }
        if (!s->is_array) {
            sem_error(n->line, "'%s' is not an array", n->sval);
        }
        if (s->dimensions == 2) {
            sem_error(n->line, "2-D array '%s' accessed with a single index", n->sval);
        }
        int idx_type = check_expr(n->left);
        if (idx_type == SEM_TYPE_CHAR) {
            sem_warning(n->line, "char used as array index for '%s'", n->sval);
        }
        return s->sem_type;
    }

    /* ---- 2-D array access ---- */
    case NODE_ARRAY_ACCESS_2D: {
        SemSymbol *s = sym_find_visible(n->sval);
        if (!s) {
            sem_error(n->line, "use of undeclared 2-D array '%s'", n->sval);
            return SEM_TYPE_UNKNOWN;
        }
        if (!s->is_array || s->dimensions != 2) {
            sem_error(n->line, "'%s' is not a 2-D array", n->sval);
        }
        check_expr(n->left);
        check_expr(n->right);
        return s->sem_type;
    }

    /* ---- arithmetic binary ops ---- */
    case NODE_ADD:
    case NODE_SUB:
    case NODE_MUL:
    case NODE_MOD: {
        // int lt = check_expr(n->left);
        // int rt = check_expr(n->right);
        int lt = check_expr_nonvoid(n->left,  n->line, "arithmetic expression");
        int rt = check_expr_nonvoid(n->right, n->line, "arithmetic expression");
        if (lt == SEM_TYPE_CHAR || rt == SEM_TYPE_CHAR) {
            sem_warning(n->line, "arithmetic on char value (implicit numeric promotion)");
        }
        return SEM_TYPE_NUMERIC;
    }

    case NODE_DIV: {
        // int lt = check_expr(n->left);
        // int rt = check_expr(n->right);
        int lt = check_expr_nonvoid(n->left,  n->line, "arithmetic expression");
        int rt = check_expr_nonvoid(n->right, n->line, "arithmetic expression");
        (void)lt;
        /* Literal zero divisor */
        if (n->right &&
            (n->right->type == NODE_INT_LIT   && n->right->ival == 0) ||
            (n->right->type == NODE_FLOAT_LIT  && n->right->dval == 0.0)) {
            sem_error(n->line, "division by zero (literal)");
        }
        if (rt == SEM_TYPE_CHAR) {
            sem_warning(n->line, "char used as divisor (implicit numeric promotion)");
        }
        return SEM_TYPE_NUMERIC;
    }

    /* ---- unary arithmetic ---- */
    case NODE_NEGATE:
        check_expr(n->left);
        return SEM_TYPE_NUMERIC;

    /* ---- comparison ops → always produce numeric (boolean) ---- */
    case NODE_EQ:
    case NODE_NEQ:
    case NODE_GT:
    case NODE_LT:
    case NODE_GE:
    case NODE_LE: {
        // int lt = check_expr(n->left);
        // int rt = check_expr(n->right);
        int lt = check_expr_nonvoid(n->left,  n->line, "comparison");
        int rt = check_expr_nonvoid(n->right, n->line, "comparison");
        if ((lt == SEM_TYPE_CHAR) != (rt == SEM_TYPE_CHAR)) {
            sem_warning(n->line, "comparison between numeric and char");
        }
        return SEM_TYPE_NUMERIC;
    }

    /* ---- logical ops ---- */
    case NODE_AND:
    case NODE_OR:
        check_expr(n->left);
        check_expr(n->right);
        return SEM_TYPE_NUMERIC;

    case NODE_NOT:
        check_expr(n->left);
        return SEM_TYPE_NUMERIC;

    /* ---- bitwise ops ---- */
    case NODE_BIT_AND:
    case NODE_BIT_OR:
    case NODE_BIT_XOR:
    case NODE_SHL:
    case NODE_SHR:
        check_expr(n->left);
        check_expr(n->right);
        return SEM_TYPE_NUMERIC;

    case NODE_BIT_NOT:
        check_expr(n->left);
        return SEM_TYPE_NUMERIC;

    /* ---- built-in math functions ---- */
    case NODE_SQRT:
    case NODE_ABS:
    case NODE_FLOOR:
    case NODE_CEIL:
        check_expr(n->left);
        return SEM_TYPE_NUMERIC;

    case NODE_POW:
        check_expr(n->left);
        check_expr(n->right);
        return SEM_TYPE_NUMERIC;

    /* ---- user-defined function call ---- */
    case NODE_FUNC_CALL: {
        SemFunc *f = func_find(n->sval);
        if (!f) {
            sem_error(n->line, "call to undeclared function '%s'", n->sval);
            return SEM_TYPE_UNKNOWN;
        }

        /* Count and type-check arguments */
        int argc = 0;
        ASTNode *arg = n->left;   /* arg list */
        while (arg) {
            int arg_type = check_expr(
                (arg->type == NODE_ARG_LIST) ? arg->left : arg);

            if (argc < f->param_count) {
                int expected = f->param_types[argc];
                if (expected == SEM_TYPE_CHAR &&
                    arg_type  == SEM_TYPE_NUMERIC) {
                    sem_warning(n->line, "passing numeric value for char parameter %d of '%s'",
                                argc + 1, n->sval);
                } else if (expected == SEM_TYPE_NUMERIC &&
                           arg_type  == SEM_TYPE_CHAR) {
                    sem_warning(n->line, "passing char value for numeric parameter %d of '%s'",
                                argc + 1, n->sval);
                }
            }
            argc++;
            arg = (arg->type == NODE_ARG_LIST) ? arg->next : NULL;
        }

        if (argc != f->param_count) {
            sem_error(n->line, "function '%s' expects %d argument(s), got %d",
                      n->sval, f->param_count, argc);
        }

        /* Return type of the call expression */
        if (f->ret_type == 2 /* void */) {
            /* Caller may be ignoring the void — that is fine as a stmt.
               If used inside an expression it will be caught by the
               parent context (e.g. assignment to numeric). */
            return SEM_TYPE_VOID;
        }
        return (f->ret_type == 1) ? SEM_TYPE_CHAR : SEM_TYPE_NUMERIC;
    }

    default:
        /* Unknown / unhandled expression node — silently ignore */
        return SEM_TYPE_UNKNOWN;
    }
}

/* =========================================================
 *  Statement checker
 * ========================================================= */

static void check_stmt(ASTNode *n)
{
    if (!n) return;

    switch (n->type) {

    /* ---- statement list ---- */
    case NODE_STMT_LIST:
        check_stmts(n);
        return;

    /* ---- scalar declaration ---- */
    case NODE_DECL: {
        int sem_type = (n->decl_type == 1) ? SEM_TYPE_CHAR : SEM_TYPE_NUMERIC;
        sym_declare(n->sval, sem_type, 0, 0, 0, 0, 0, n->line);

        /* Check initialiser expression, if any */
        if (n->left) {
            int expr_type = check_expr(n->left);
            if (sem_type == SEM_TYPE_CHAR && expr_type == SEM_TYPE_NUMERIC) {
                sem_warning(n->line, "initialising char variable '%s' with numeric value", n->sval);
            } else if (sem_type == SEM_TYPE_NUMERIC && expr_type == SEM_TYPE_CHAR) {
                sem_warning(n->line, "initialising numeric variable '%s' with char value", n->sval);
            } else if (expr_type == SEM_TYPE_VOID) {
                sem_error(n->line, "cannot initialise '%s' with result of void function", n->sval);
            }
        }
        return;
    }

    /* ---- 1-D array declaration ---- */
    case NODE_DECL_ARRAY: {
        int sem_type = (n->decl_type == 1) ? SEM_TYPE_CHAR : SEM_TYPE_NUMERIC;
        int size     = n->cols;   /* parser stores size in cols */
        if (size <= 0) {
            sem_error(n->line, "array '%s' declared with non-positive size %d", n->sval, size);
        }
        sym_declare(n->sval, sem_type, 1, 1, size, 0, 0, n->line);
        return;
    }

    /* ---- 2-D array declaration ---- */
    case NODE_DECL_ARRAY_2D: {
        int sem_type = (n->decl_type == 1) ? SEM_TYPE_CHAR : SEM_TYPE_NUMERIC;
        if (n->rows <= 0 || n->cols <= 0) {
            sem_error(n->line, "2-D array '%s' declared with non-positive dimension(s) [%d][%d]",
                      n->sval, n->rows, n->cols);
        }
        sym_declare(n->sval, sem_type, 1, 2, 0, n->rows, n->cols, n->line);
        return;
    }

    /* ---- scalar assignment ---- */
    case NODE_ASSIGN: {
        SemSymbol *s = sym_find_visible(n->sval);
        if (!s) {
            sem_error(n->line, "assignment to undeclared variable '%s'", n->sval);
        } else if (s->is_array) {
            sem_error(n->line, "'%s' is an array; use indexed assignment", n->sval);
        } else {
            int expr_type = check_expr(n->left);
            if (expr_type == SEM_TYPE_VOID) {
                sem_error(n->line, "cannot assign result of void function to '%s'", n->sval);
            } else if (s->sem_type == SEM_TYPE_CHAR &&
                       expr_type  == SEM_TYPE_NUMERIC) {
                sem_warning(n->line, "assigning numeric value to char variable '%s'", n->sval);
            } else if (s->sem_type == SEM_TYPE_NUMERIC &&
                       expr_type  == SEM_TYPE_CHAR) {
                sem_warning(n->line, "assigning char value to numeric variable '%s'", n->sval);
            }
        }
        return;
    }

    /* ---- 1-D array assignment ---- */
    case NODE_ARRAY_ASSIGN: {
        SemSymbol *s = sym_find_visible(n->sval);
        if (!s) {
            sem_error(n->line, "assignment to undeclared array '%s'", n->sval);
        } else if (!s->is_array) {
            sem_error(n->line, "'%s' is not an array", n->sval);
        } else if (s->dimensions == 2) {
            sem_error(n->line, "2-D array '%s' requires two indices for assignment", n->sval);
        }
        check_expr(n->left);   /* index */
        check_expr(n->right);  /* value */
        return;
    }

    /* ---- 2-D array assignment ---- */
    case NODE_ARRAY_ASSIGN_2D: {
        SemSymbol *s = sym_find_visible(n->sval);
        if (!s) {
            sem_error(n->line, "assignment to undeclared 2-D array '%s'", n->sval);
        } else if (!s->is_array || s->dimensions != 2) {
            sem_error(n->line, "'%s' is not a 2-D array", n->sval);
        }
        check_expr(n->left);   /* row index */
        check_expr(n->right);  /* col index */
        check_expr(n->extra);  /* value     */
        return;
    }

    /* ---- print ---- */
    case NODE_PRINT:
        if (n->left)  check_expr(n->left);
        if (n->right) check_expr(n->right);
        return;

    /* ---- scan ---- */
    case NODE_SCAN: {
        SemSymbol *s = sym_find_visible(n->sval);
        if (!s) {
            sem_error(n->line, "scan into undeclared variable '%s'", n->sval);
        } else if (s->is_array) {
            sem_error(n->line, "scan into array '%s' requires an index", n->sval);
        }
        return;
    }

    case NODE_SCAN_ARRAY: {
        SemSymbol *s = sym_find_visible(n->sval);
        if (!s) {
            sem_error(n->line, "scan into undeclared array '%s'", n->sval);
        } else if (!s->is_array) {
            sem_error(n->line, "'%s' is not an array (scan)", n->sval);
        }
        check_expr(n->left);   /* index */
        return;
    }

    /* ---- if / elseif / else ---- */
    case NODE_IF:
    case NODE_ELSEIF: {
        check_expr(n->left);          /* condition */
        scope_push();
        check_stmts(n->right);        /* then-branch */
        scope_pop();
        if (n->extra) {
            check_stmt(n->extra);     /* elseif / else chain */
        }
        return;
    }

    case NODE_ELSE:
        scope_push();
        check_stmts(n->left);
        scope_pop();
        return;

    /* ---- switch ---- */
    case NODE_SWITCH: {
        int expr_type = check_expr(n->left);
        if (expr_type == SEM_TYPE_CHAR) {
            sem_warning(n->line, "switch on char expression (numeric value will be used)");
        }
        inside_switch++;
        check_stmts(n->right);   /* case list */
        inside_switch--;
        return;
    }

    case NODE_CASE:
    case NODE_CASE_RANGE:
    case NODE_DEFAULT:
        scope_push();
        check_stmts(n->left);
        if (n->right) check_stmts(n->right);  /* range second body */
        scope_pop();
        return;

    /* ---- break / continue ---- */
    case NODE_BREAK:
        if (inside_loop == 0 && inside_switch == 0) {
            sem_error(n->line, "'break' used outside of loop or switch");
        }
        return;

    case NODE_CONTINUE:
        if (inside_loop == 0) {
            sem_error(n->line, "'continue' used outside of loop");
        }
        return;

    /* ---- while ---- */
    case NODE_WHILE: {
        check_expr(n->left);    /* condition */
        inside_loop++;
        scope_push();
        check_stmts(n->right);  /* body */
        scope_pop();
        inside_loop--;
        return;
    }

    /* ---- do-while ---- */
    case NODE_DO_WHILE: {
        inside_loop++;
        scope_push();
        check_stmts(n->left);   /* body */
        scope_pop();
        inside_loop--;
        check_expr(n->right);   /* condition */
        return;
    }

    /* ---- for ---- */
    case NODE_FOR: {
        /* n->left  = init (declaration or assignment or NULL)
           n->right = condition expression
           n->extra = update (assignment or NULL)
           body is stored as n->extra->next — or if extra is NULL,
           the parser hangs the body somewhere; inspect carefully.

           In your parser.y the for layout appears to be:
             n->left  = for_init
             n->right = condition
             n->extra = for_update
             body     = n->extra ? n->extra->next : separate child

           We open a scope so that a for-init declaration is local. */
        scope_push();
        if (n->left)  check_stmt(n->left);    /* init */
        if (n->right) check_expr(n->right);   /* condition */

        inside_loop++;
        /* body: interpreter.c walks n->extra->next or similar —
           use the same node the interpreter uses (left of extra?) */
        if (n->extra) {
            /* update expression */
            if (n->extra->type == NODE_ASSIGN ||
                n->extra->type == NODE_ARRAY_ASSIGN) {
                check_stmt(n->extra);
            } else {
                check_expr(n->extra);
            }
        }
        /* The body in your AST is the fourth child; the parser stores
           it as statement list attached via n->extra->next or as a
           separate extra2.  Because ast.h has only left/right/extra,
           the for body is passed as n->left of a wrapper when needed.
           Conservatively walk every remaining child. */
        if (n->extra && n->extra->next) {
            check_stmts(n->extra->next);
        }
        inside_loop--;
        scope_pop();
        return;
    }

    /* ---- return ---- */
    case NODE_RETURN: {
        if (!current_func) {
            sem_error(n->line, "'return' with value outside of function");
            check_expr(n->left);
            return;
        }
        if (current_func->ret_type == 2 /* void */) {
            sem_error(n->line, "returning a value from void function '%s'",
                      current_func->name);
            return;
        }
        int expr_type = check_expr(n->left);
        if (current_func->ret_type == 1 /* char */ &&
            expr_type == SEM_TYPE_NUMERIC) {
            sem_warning(n->line, "returning numeric value from char function '%s'",
                        current_func->name);
        } else if (current_func->ret_type == 0 /* numeric */ &&
                   expr_type == SEM_TYPE_CHAR) {
            sem_warning(n->line, "returning char value from numeric function '%s'",
                        current_func->name);
        }
        return;
    }

    case NODE_RETURN_VOID: {
        if (!current_func) {
            sem_error(n->line, "'return' outside of function");
            return;
        }
        if (current_func->ret_type != 2 /* void */) {
            sem_error(n->line, "missing return value in non-void function '%s'",
                      current_func->name);
        }
        return;
    }

    /* ---- function definition ---- */
    case NODE_FUNC_DEF: {
        SemFunc *saved_func = current_func;
        current_func = func_find(n->sval);

        scope_push();
        /* Declare parameters as local variables */
        ASTNode *p = n->left;
        while (p) {
            if (p->type == NODE_PARAM) {
                int ptype = (p->decl_type == 1) ? SEM_TYPE_CHAR : SEM_TYPE_NUMERIC;
                sym_declare(p->sval, ptype, 0, 0, 0, 0, 0, p->line);
            }
            p = p->next;
        }
        /* Analyse function body */
        check_stmts(n->right);
        scope_pop();

        current_func = saved_func;
        return;
    }

    /* ---- function call as statement (discarded return value) ---- */
    case NODE_FUNC_CALL:
        check_expr(n);   /* reuse expr checker */
        return;

    /* ---- program root ---- */
    case NODE_PROGRAM:
        check_stmts(n->left);
        return;

    default:
        /* Could be an expression used as a statement */
        check_expr(n);
        return;
    }
}

/* Walk a linked statement list (via ->next). */
static void check_stmts(ASTNode *n)
{
    while (n) {
        if (n->type == NODE_STMT_LIST) {
            check_stmt(n->left);
            n = n->right;
        } else {
            check_stmt(n);
            n = n->next;
        }
    }
}

/* =========================================================
 *  First pass: collect all top-level function signatures
 *  so that forward-calls (calling a function defined later
 *  in the source) are valid.
 * ========================================================= */
static void collect_functions(ASTNode *n)
{
    if (!n) return;

    if (n->type == NODE_FUNC_DEF) {
        func_register(n);
        return;   /* don't recurse into body during collection */
    }

    /* Recurse over statement lists */
    if (n->type == NODE_STMT_LIST) {
        collect_functions(n->left);
        collect_functions(n->right);
        return;
    }

    if (n->type == NODE_PROGRAM) {
        collect_functions(n->left);
        return;
    }

    /* Walk ->next chain for top-level lists */
    collect_functions(n->next);
}

/* =========================================================
 *  Public entry point
 * ========================================================= */
int sem_analyse(ASTNode *root)
{
    /* Reset state */
    sem_sym_count    = 0;
    sem_scope_top    = 0;
    sem_func_count   = 0;
    inside_loop      = 0;
    inside_switch    = 0;
    current_func     = NULL;
    sem_error_count  = 0;
    sem_warning_count= 0;
 
    if (!root) {
        sem_error(0, "empty program (null AST root)");
        return -1;
    }
 
    /* ---- Pass 1: seed semantic function table from the runtime functab ----
     *
     * The parser calls func_define() for every function it encounters, so
     * by the time sem_analyse() is called ALL functions (even those defined
     * after main in the source) are already in functab.
     * We mirror that into sem_funcs so that forward calls are always valid.
     */
    for (int fi = 0; fi < funccount; fi++) {
        FuncEntry *fe = &functab[fi];
        if (sem_func_count >= SEM_FUNC_MAX) break;
        SemFunc *sf = &sem_funcs[sem_func_count++];
        strncpy(sf->name, fe->name, 63);
        sf->ret_type    = fe->ret_type;
        sf->param_count = fe->param_count;
        for (int pi = 0; pi < fe->param_count && pi < PARAM_MAX; pi++)
            sf->param_types[pi] = fe->param_types[pi];
    }
    /* Also walk AST for any definitions the above may have missed. */
    collect_functions(root);
 
    // /* ---- Pass 2: full semantic walk ---- */
 
    // /* Set up a synthetic "main" context so that Return inside
    //  * StartExam() / main is not flagged as "outside a function".
    //  * ret_type = 0 (numeric) matches  Return 0;               */
    // static SemFunc main_func;
    // strncpy(main_func.name, "main", 63);
    // main_func.ret_type    = 0;   /* numeric — Return 0 is valid */
    // main_func.param_count = 0;
    // current_func = &main_func;
 
    // scope_push();   /* global scope */
    // check_stmt(root);
    // scope_pop();
 
    // current_func = NULL;
    // AFTER:

    /* ---- Pass 2: walk every user-defined function body ---- */
    for (int fi = 0; fi < funccount; fi++) {
        FuncEntry *fe = &functab[fi];
        if (!fe->body) continue;

        /* Set current_func so return-type checks know which function
           they are inside */
        // current_func = &sem_funcs[fi];   /* sem_funcs mirrors functab order */
        current_func = func_find(fe->name);  /* safer lookup by name */
        if (!current_func) {
            continue;
        }

        scope_push();
        /* Declare parameters as local variables for this function */
        // ASTNode *p = fe->params;   /* need to store params — see note below */
        // while (p) {
        //     if (p->type == NODE_PARAM) {
        //         int ptype = (p->decl_type == 1) ? SEM_TYPE_CHAR : SEM_TYPE_NUMERIC;
        //         sym_declare(p->sval, ptype, 0, 0, 0, 0, 0, p->line);
        //     }
        //     p = p->next;
        // }
          for (int pi = 0; pi < fe->param_count; pi++) {
            int ptype = (fe->param_types[pi] == 1) ? SEM_TYPE_CHAR : SEM_TYPE_NUMERIC;
            sym_declare(fe->param_names[pi], ptype, 0, 0, 0, 0, 0, 0);
        }
        check_stmts(fe->body);
        scope_pop();

        current_func = NULL;
    }

    /* ---- Pass 3: walk StartExam / main body ---- */
    static SemFunc main_func;
    strncpy(main_func.name, "main", 63);
    main_func.ret_type    = 0;
    main_func.param_count = 0;
    current_func = &main_func;

    scope_push();
    check_stmt(root);
    scope_pop();

    current_func = NULL;
 
    /* Summary */
    if (sem_error_count > 0 || sem_warning_count > 0) {
        fprintf(stderr,
                "\n[Semantic Analysis] %d error(s), %d warning(s) found.\n",
                sem_error_count, sem_warning_count);
    } else {
        fprintf(stderr,
                "[Semantic Analysis] No errors found.\n");
    }
 
    return (sem_error_count > 0) ? -1 : 0;
}