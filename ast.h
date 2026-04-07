#ifndef AST_H
#define AST_H

#include <stdio.h>




typedef enum {
    
    NODE_INT_LIT,
    NODE_FLOAT_LIT,
    NODE_CHAR_LIT,
    NODE_STRING_LIT,
    NODE_BOOL_LIT,

    
    NODE_IDENT,

    
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_MOD,
    NODE_NEGATE,

    
    NODE_EQ,
    NODE_NEQ,
    NODE_GT,
    NODE_LT,
    NODE_GE,
    NODE_LE,

    
    NODE_AND,    
    NODE_OR,     
    NODE_NOT,   

    
    NODE_BIT_AND,    
    NODE_BIT_OR,     
    NODE_BIT_XOR,    
    NODE_BIT_NOT,    
    NODE_SHL,        
    NODE_SHR,        


    
    NODE_POW,
    NODE_SQRT,
    NODE_ABS,
    NODE_FLOOR,
    NODE_CEIL,

    
    NODE_ARRAY_ACCESS,   
    NODE_ARRAY_ACCESS_2D, 

    
    NODE_STMT_LIST,      
    NODE_DECL,            
    NODE_DECL_ARRAY,      
    NODE_DECL_ARRAY_2D,   
    NODE_ASSIGN,          
    NODE_ARRAY_ASSIGN,    
    NODE_ARRAY_ASSIGN_2D, 
    NODE_PRINT,
    NODE_SCAN,
    NODE_SCAN_ARRAY,

   
    NODE_IF,              
    NODE_ELSEIF,         
    NODE_ELSE,
    NODE_SWITCH,
    NODE_CASE,
    NODE_CASE_RANGE,
    NODE_DEFAULT,
    NODE_BREAK,
    NODE_CONTINUE,

    /* loops */
    NODE_WHILE,
    NODE_DO_WHILE,
    NODE_FOR,
    NODE_FOR_RANGE,       
    NODE_FOR_RANGE_STEP,  
    NODE_INCREMENT,          
    NODE_DECREMENT,          

    
    NODE_PROGRAM,
    NODE_RETURN,

    /* user-defined functions */
    NODE_FUNC_DEF,
    NODE_FUNC_CALL,       
    NODE_PARAM,          
    NODE_PARAM_LIST,      
    NODE_ARG_LIST,        
    NODE_RETURN_VOID,     
} NodeType;


typedef struct ASTNode ASTNode;


struct ASTNode {
    NodeType type;

    
    union {
        int    ival;
        double dval;
        char   cval;
        char  *sval;   
    };

    
    ASTNode *left;
    ASTNode *right;
    ASTNode *extra;   

    
    ASTNode *next;

    
    int decl_type;  /* 0 = numeric, 1 = char */
    int rows, cols; /*  2-D array */

    int ret_type;   /* return type: 0=numeric, 1=char, 2=void */
    int line;       /* source line number  */
};


ASTNode *make_node(NodeType type);
ASTNode *make_int_lit(int v);
ASTNode *make_float_lit(double v);
ASTNode *make_char_lit(char v);
ASTNode *make_string_lit(const char *s);
ASTNode *make_bool_lit(int v);
ASTNode *make_ident(const char *name);
ASTNode *make_binop(NodeType op, ASTNode *l, ASTNode *r);
ASTNode *make_unary(NodeType op, ASTNode *operand);
ASTNode *make_func1(NodeType fn, ASTNode *arg);
ASTNode *make_func2(NodeType fn, ASTNode *a, ASTNode *b);
ASTNode *make_array_access(const char *name, ASTNode *idx);
ASTNode *make_array_access_2d(const char *name, ASTNode *row, ASTNode *col);
ASTNode *make_stmt_list(ASTNode *stmt, ASTNode *rest);


ASTNode *make_param(const char *name, int type);
ASTNode *make_func_def(const char *name, int ret_type, ASTNode *params, ASTNode *body);
ASTNode *make_func_call(const char *name, ASTNode *args);
ASTNode *make_arg_list(ASTNode *expr, ASTNode *next);
ASTNode *make_return_void(void);


void    free_ast(ASTNode *n);


void    print_ast(ASTNode *n, int indent);
void    print_ast_file(ASTNode *n, int indent, FILE *out);

#endif 
