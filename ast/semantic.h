#ifndef SEMANTIC_H
#define SEMANTIC_H



#include "ast.h"
#include "symtab.h"

// semantic type tags 
#define SEM_TYPE_NUMERIC  0   // int / float / double / bool  
#define SEM_TYPE_CHAR     1   // char                         
#define SEM_TYPE_VOID     2   // void (functions only)        
#define SEM_TYPE_ARRAY    3   // 1-D array                   
#define SEM_TYPE_ARRAY2D  4   // 2-D array                   
#define SEM_TYPE_UNKNOWN  -1  // unresolved / error         

/* one entry in the semantic symbol table */
typedef struct {
    char name[64];
    int  sem_type;      
    int  is_array;      /* 1 if 1-D or 2-D array             */
    int  dimensions;    /* 1 or 2                            */
    int  array_size;    /* for 1-D                           */
    int  rows, cols;    /* for 2-D                           */
} SemSymbol;


typedef struct {
    char name[64];
    int  ret_type;                  /* SEM_TYPE_*            */
    int  param_count;
    int  param_types[PARAM_MAX];    /* SEM_TYPE_* per param  */
} SemFunc;


extern int sem_error_count;
extern int sem_warning_count;


int sem_analyse(ASTNode *root);

#endif /* SEMANTIC_H */