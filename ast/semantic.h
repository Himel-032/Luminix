#ifndef SEMANTIC_H
#define SEMANTIC_H

/* =========================================================
 *  semantic.h  –  Semantic Analysis interface
 *
 *  Performs a pass over the AST (after parsing, before
 *  interpretation) and reports semantic errors such as:
 *  $  - use of undeclared variables / functions
 *    - redeclaration of variables in the same scope
 *    - type mismatches (numeric vs char)
            [Semantic Warning] (line 13) initialising numeric variable 'd' with char value
            [Semantic Warning] (line 14) initialising char variable 'l' with numeric value
 *    - wrong number of arguments in function calls
 *  $  - return-type violations (value returned from void, etc.)
 *    - break / continue used outside a loop
 *    - array index used on a non-array, and vice-versa
 * ========================================================= */

#include "ast.h"
#include "symtab.h"

/* ---- semantic type tags (mirrors decl_type + extras) ---- */
#define SEM_TYPE_NUMERIC  0   /* int / float / double / bool  */
#define SEM_TYPE_CHAR     1   /* char                         */
#define SEM_TYPE_VOID     2   /* void (functions only)        */
#define SEM_TYPE_ARRAY    3   /* 1-D array                    */
#define SEM_TYPE_ARRAY2D  4   /* 2-D array                    */
#define SEM_TYPE_UNKNOWN  -1  /* unresolved / error           */

/* ---- one entry in the semantic symbol table ---- */
typedef struct {
    char name[64];
    int  sem_type;      /* SEM_TYPE_* above                  */
    int  is_array;      /* 1 if 1-D or 2-D array             */
    int  dimensions;    /* 1 or 2                            */
    int  array_size;    /* for 1-D                           */
    int  rows, cols;    /* for 2-D                           */
} SemSymbol;

/* ---- one entry in the semantic function table ---- */
typedef struct {
    char name[64];
    int  ret_type;                  /* SEM_TYPE_*            */
    int  param_count;
    int  param_types[PARAM_MAX];    /* SEM_TYPE_* per param  */
} SemFunc;

/* ---- counters exposed for caller diagnostics ---- */
extern int sem_error_count;
extern int sem_warning_count;

/* =========================================================
 *  Public API
 * ========================================================= */

/*
 * sem_analyse(root)
 *   Walk the entire AST rooted at `root` and report all
 *   semantic errors / warnings to stderr.
 *   Returns 0 if no errors were found, -1 otherwise.
 *   (Warnings do not affect the return value.)
 */
int sem_analyse(ASTNode *root);

#endif /* SEMANTIC_H */