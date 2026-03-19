#ifndef AST_H
#define AST_H

/* =========================================================
 *  ast.h  –  Abstract Syntax Tree node types & structures
 * ========================================================= */

/* ---- node-type tags ---- */
typedef enum {
    /* literals */
    NODE_INT_LIT,
    NODE_FLOAT_LIT,
    NODE_CHAR_LIT,
    NODE_STRING_LIT,
    NODE_BOOL_LIT,

    /* identifiers */
    NODE_IDENT,

    /* arithmetic */
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_MOD,
    NODE_NEGATE,

    /* comparison */
    NODE_EQ,
    NODE_NEQ,
    NODE_GT,
    NODE_LT,
    NODE_GE,
    NODE_LE,

    /* logical operators */
    NODE_AND,    /* && */
    NODE_OR,     /* || */
    NODE_NOT,    /* ! */


    /* built-in math functions */
    NODE_POW,
    NODE_SQRT,
    NODE_ABS,
    NODE_FLOOR,
    NODE_CEIL,

    /* array access */
    NODE_ARRAY_ACCESS,    /* id[expr]          */
    NODE_ARRAY_ACCESS_2D, /* id[expr][expr]    */

    /* statements */
    NODE_STMT_LIST,       /* linked list of statements        */
    NODE_DECL,            /* variable declaration             */
    NODE_DECL_ARRAY,      /* 1-D array declaration            */
    NODE_DECL_ARRAY_2D,   /* 2-D array declaration            */
    NODE_ASSIGN,          /* variable = expr                  */
    NODE_ARRAY_ASSIGN,    /* id[expr] = expr                  */
    NODE_ARRAY_ASSIGN_2D, /* id[expr][expr] = expr            */
    NODE_PRINT,
    NODE_SCAN,
    NODE_SCAN_ARRAY,

    /* control flow */
    NODE_IF,              /* if / elseif* / else chain        */
    NODE_ELSEIF,          /* single elseif clause             */
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

    /* program */
    NODE_PROGRAM,
    NODE_RETURN,

    /* user-defined functions */
    NODE_FUNC_DEF,        /* function definition          */
    NODE_FUNC_CALL,       /* function call expression      */
    NODE_PARAM,           /* single parameter              */
    NODE_PARAM_LIST,      /* linked list of params         */
    NODE_ARG_LIST,        /* linked list of call arguments */
    NODE_RETURN_VOID,     /* return;  (no value)           */
} NodeType;

/* ---- forward declaration ---- */
typedef struct ASTNode ASTNode;

/* ---- the node itself ---- */
struct ASTNode {
    NodeType type;

    /* literal payload */
    union {
        int    ival;
        double dval;
        char   cval;
        char  *sval;   /* heap-allocated string (name or string literal) */
    };

    /* generic child pointers (meaning depends on node type) */
    ASTNode *left;
    ASTNode *right;
    ASTNode *extra;   /* third child where needed (e.g. else branch)    */

    /* for statement lists: intrusive linked list */
    ASTNode *next;

    /* declaration metadata */
    int decl_type;  /* 0 = numeric, 1 = char */
    int rows, cols; /* for 2-D arrays */

    int ret_type;   /* return type: 0=numeric, 1=char, 2=void */
};

/* ---- constructors (implemented in ast.c) ---- */
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

/* user-defined function nodes */
ASTNode *make_param(const char *name, int type);
ASTNode *make_func_def(const char *name, int ret_type, ASTNode *params, ASTNode *body);
ASTNode *make_func_call(const char *name, ASTNode *args);
ASTNode *make_arg_list(ASTNode *expr, ASTNode *next);
ASTNode *make_return_void(void);

/* free the whole tree */
void    free_ast(ASTNode *n);

/* pretty-print the tree (for debugging) */
void    print_ast(ASTNode *n, int indent);

#endif /* AST_H */
