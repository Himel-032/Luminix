/* =========================================================
 *  symtab.c  –  Symbol table implementation
 * ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#include "ast.h"

Symbol symtab[SYMTAB_MAX];
int    symcount = 0;


FuncEntry functab[FUNC_MAX];
int funccount = 0;

/* ------------------------------------------------------------------ */
/* Scope / frame stack                                                  */
/* ------------------------------------------------------------------ */
#define FRAME_STACK_MAX 64
static int frame_stack[FRAME_STACK_MAX];
static int frame_top = 0;

/* ------------------------------------------------------------------ */
/* Function table                                                       */
/* ------------------------------------------------------------------ */
void func_define(const char *name, int ret_type,
                 ASTNode *params, ASTNode *body) {
    /* Overwrite if already defined (redefinition allowed like C) */
    for (int i = 0; i < funccount; i++) {
        if (strcmp(functab[i].name, name) == 0) {
            functab[i].ret_type = ret_type;
            functab[i].body     = body;
            
            functab[i].params = params;  /* for semantic use */;
            /* re-parse params */
            functab[i].param_count = 0;
            ASTNode *p = params;
            while (p && functab[i].param_count < PARAM_MAX) {
                strncpy(functab[i].param_names[functab[i].param_count],
                        p->sval, 63);
                functab[i].param_types[functab[i].param_count] = p->decl_type;
                functab[i].param_count++;
                p = p->next;
            }
            return;
        }
    }
    if (funccount >= FUNC_MAX) {
        fprintf(stderr, "Runtime error: function table full\n");
        return;
    }
    FuncEntry *f = &functab[funccount++];
    strncpy(f->name, name, 63);
    f->ret_type    = ret_type;
    f->body        = body;
    f->param_count = 0;
    f->params   = params;  /* for semantic use */;
    ASTNode *p = params;
    while (p && f->param_count < PARAM_MAX) {
        strncpy(f->param_names[f->param_count], p->sval, 63);
        f->param_types[f->param_count] = p->decl_type;
        f->param_count++;
        p = p->next;
    }
}

FuncEntry *func_lookup(const char *name) {
    for (int i = 0; i < funccount; i++)
        if (strcmp(functab[i].name, name) == 0)
            return &functab[i];
    return NULL;
}

void sym_push_frame(void) {
    if (frame_top >= FRAME_STACK_MAX) {
        fprintf(stderr, "Runtime error: call stack overflow\n");
        return;
    }
    frame_stack[frame_top++] = symcount;
}

void sym_pop_frame(void) {
    if (frame_top <= 0) return;
    symcount = frame_stack[--frame_top];
    /* Symbols above new symcount are simply dropped.
       If any held heap-allocated arrays they would need freeing —
       a production implementation would call free(); for this
       interpreter the Symbol struct holds everything inline so
       dropping the count is sufficient. */
}
/* ------------------------------------------------------------------ */
/* Internal helper: find an existing entry or return -1               */
/* ------------------------------------------------------------------ */
static int sym_find(const char *name) {
    for (int i = 0; i < symcount; i++)
        if (strcmp(symtab[i].name, name) == 0)
            return i;
    return -1;
}

/* Frame-aware find: searches only in the CURRENT frame */
static int sym_find_in_frame(const char *name) {
    int frame_start = (frame_top > 0) ? frame_stack[frame_top - 1] : 0;
    for (int i = frame_start; i < symcount; i++)
        if (strcmp(symtab[i].name, name) == 0)
            return i;
    return -1;
}

/* ------------------------------------------------------------------ */
/* Scalar                                                              */
/* ------------------------------------------------------------------ */
void sym_set(const char *name, double value, int decl_type) {
    /* When in a function frame, use frame-aware lookup */
    int i = (frame_top > 0) ? sym_find_in_frame(name) : sym_find(name);
    if (i >= 0) {  
        symtab[i].value = value;
        return;
    }
    if (symcount >= SYMTAB_MAX) {
        fprintf(stderr, "Runtime error: symbol table full\n");
        return;
    }
    strncpy(symtab[symcount].name, name, sizeof(symtab[symcount].name) - 1);
    symtab[symcount].value    = value;
    symtab[symcount].type     = decl_type;
    symtab[symcount].is_array = 0;
    symtab[symcount].array_size = 0;
    symcount++;
}

double sym_get(const char *name) {
    /* When in a function frame, prefer frame-aware lookup */
    int i = (frame_top > 0) ? sym_find_in_frame(name) : -1;
    if (i < 0) {
        /* Not in current frame, try global scope */
        i = sym_find(name);
    }
    if (i < 0) {
        fprintf(stderr, "Runtime error: variable '%s' not declared\n", name);
        return 0;
    }
    return symtab[i].value;
}

int sym_get_type(const char *name) {
    int i = sym_find(name);
    if (i < 0) return 0;
    return symtab[i].type;
}

/* ------------------------------------------------------------------ */
/* 1-D array                                                           */
/* ------------------------------------------------------------------ */
void sym_declare_array(const char *name, int size, int decl_type) {
    if (symcount >= SYMTAB_MAX) {
        fprintf(stderr, "Runtime error: symbol table full\n");
        return;
    }
    strncpy(symtab[symcount].name, name, sizeof(symtab[symcount].name) - 1);
    symtab[symcount].is_array   = 1;
    symtab[symcount].dimensions = 1;
    symtab[symcount].array_size = size;
    symtab[symcount].type       = decl_type;
    for (int i = 0; i < size && i < ARRAY_MAX; i++)
        symtab[symcount].array_values[i] = 0;
    symcount++;
}

void sym_set_array(const char *name, int idx, double value) {
    int i = sym_find(name);
    if (i < 0) { fprintf(stderr, "Runtime error: array '%s' not declared\n", name); return; }
    if (!symtab[i].is_array || idx < 0 || idx >= symtab[i].array_size) {
        fprintf(stderr, "Runtime error: array '%s' index %d out of bounds\n", name, idx);
        return;
    }
    symtab[i].array_values[idx] = value;
}

double sym_get_array(const char *name, int idx) {
    int i = sym_find(name);
    if (i < 0) { fprintf(stderr, "Runtime error: array '%s' not declared\n", name); return 0; }
    if (!symtab[i].is_array || idx < 0 || idx >= symtab[i].array_size) {
        fprintf(stderr, "Runtime error: array '%s' index %d out of bounds\n", name, idx);
        return 0;
    }
    return symtab[i].array_values[idx];
}

/* ------------------------------------------------------------------ */
/* 2-D array                                                           */
/* ------------------------------------------------------------------ */
void sym_declare_array2d(const char *name, int r, int c, int decl_type) {
    if (symcount >= SYMTAB_MAX) {
        fprintf(stderr, "Runtime error: symbol table full\n");
        return;
    }
    strncpy(symtab[symcount].name, name, sizeof(symtab[symcount].name) - 1);
    symtab[symcount].is_array   = 1;
    symtab[symcount].dimensions = 2;
    symtab[symcount].rows       = r;
    symtab[symcount].cols       = c;
    symtab[symcount].type       = decl_type;
    for (int i = 0; i < r && i < ARRAY2D_MAX; i++)
        for (int j = 0; j < c && j < ARRAY2D_MAX; j++)
            symtab[symcount].array2d[i][j] = 0;
    symcount++;
}

void sym_set_array2d(const char *name, int r, int c, double value) {
    int i = sym_find(name);
    if (i < 0) { fprintf(stderr, "Runtime error: array '%s' not declared\n", name); return; }
    if (symtab[i].dimensions != 2 || r < 0 || r >= symtab[i].rows || c < 0 || c >= symtab[i].cols) {
        fprintf(stderr, "Runtime error: 2D array '%s' index [%d][%d] out of bounds\n", name, r, c);
        return;
    }
    symtab[i].array2d[r][c] = value;
}

double sym_get_array2d(const char *name, int r, int c) {
    int i = sym_find(name);
    if (i < 0) { fprintf(stderr, "Runtime error: array '%s' not declared\n", name); return 0; }
    if (symtab[i].dimensions != 2 || r < 0 || r >= symtab[i].rows || c < 0 || c >= symtab[i].cols) {
        fprintf(stderr, "Runtime error: 2D array '%s' index [%d][%d] out of bounds\n", name, r, c);
        return 0;
    }
    return symtab[i].array2d[r][c];
}
