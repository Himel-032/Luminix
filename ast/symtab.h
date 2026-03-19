#ifndef SYMTAB_H
#define SYMTAB_H

/* =========================================================
 *  symtab.h  –  Symbol table interface
 * ========================================================= */
#include "ast.h"   /* for ASTNode* — put this near top of symtab.h */

#define SYMTAB_MAX   1000
#define ARRAY_MAX    100
#define ARRAY2D_MAX   50

/* ---- function table ---- */
#define FUNC_MAX      200
#define PARAM_MAX      32

typedef struct {
    char     name[64];
    int      ret_type;          /* 0=numeric, 1=char, 2=void */
    int      param_count;
    char     param_names[PARAM_MAX][64];
    int      param_types[PARAM_MAX];  /* 0=numeric, 1=char */
    ASTNode *body;              /* NOT owned — owned by the AST */
} FuncEntry;



extern FuncEntry functab[FUNC_MAX];
extern int       funccount;

/* function table API */
void func_define(const char *name, int ret_type, ASTNode *params, ASTNode *body);
FuncEntry *func_lookup(const char *name);

/* scoped symbol-table frames (for local variables) */
void sym_push_frame(void);   /* save current symcount         */
void sym_pop_frame(void);    /* restore symcount (drop locals) */

typedef struct {
    char   name[64];
    double value;
    int    type;       /* 0 = numeric, 1 = char */
    int    is_array;
    int    dimensions; /* 1 = 1-D, 2 = 2-D     */
    int    rows, cols;
    double array_values[ARRAY_MAX];
    int    array_size;
    double array2d[ARRAY2D_MAX][ARRAY2D_MAX];
} Symbol;

extern Symbol symtab[SYMTAB_MAX];
extern int    symcount;

/* scalar */
void   sym_set(const char *name, double value, int decl_type);
double sym_get(const char *name);
int    sym_get_type(const char *name);

/* 1-D array */
void   sym_declare_array(const char *name, int size, int decl_type);
void   sym_set_array(const char *name, int idx, double value);
double sym_get_array(const char *name, int idx);

/* 2-D array */
void   sym_declare_array2d(const char *name, int r, int c, int decl_type);
void   sym_set_array2d(const char *name, int r, int c, double value);
double sym_get_array2d(const char *name, int r, int c);

#endif /* SYMTAB_H */
