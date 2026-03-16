#ifndef SYMTAB_H
#define SYMTAB_H

/* =========================================================
 *  symtab.h  –  Symbol table interface
 * ========================================================= */

#define SYMTAB_MAX   1000
#define ARRAY_MAX    100
#define ARRAY2D_MAX   50

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
