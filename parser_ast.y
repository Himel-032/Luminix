/* bison -d parser_ast.y; flex lexer.l; gcc parser_ast.tab.c lex.yy.c -o luminix_ast; ./luminix_ast input.txt */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SWITCH_STACK_MAX 64
#define SWITCH_EPSILON 1e-9
#define MAX_NODES 10000

/* ==================== AST NODE TYPES ==================== */

typedef enum {
    NODE_PROGRAM,
    NODE_STATEMENT_LIST,
    NODE_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_ARRAY_ASSIGNMENT,
    NODE_PRINT,
    NODE_SCAN,
    NODE_IF,
    NODE_SWITCH,
    NODE_CASE,
    NODE_DEFAULT,
    NODE_BREAK,
    NODE_LOOP_WHILE,
    NODE_LOOP_FOR,
    NODE_RETURN,
    NODE_EXPRESSION,
    NODE_CONDITION,
    NODE_FUNCTION_CALL,
    NODE_ARRAY_ACCESS,
    NODE_IDENTIFIER,
    NODE_LITERAL_INT,
    NODE_LITERAL_FLOAT,
    NODE_LITERAL_CHAR,
    NODE_LITERAL_STRING,
    NODE_LITERAL_BOOL,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_ARRAY_DECL_1D,
    NODE_ARRAY_DECL_2D,
    NODE_CASE_RANGE
} NodeType;

typedef enum {
    OP_PLUS, OP_MINUS, OP_MUL, OP_DIV, OP_MOD,
    OP_EQ, OP_NEQ, OP_GT, OP_LT, OP_GE, OP_LE,
    OP_AND, OP_OR,
    OP_BIT_AND, OP_BIT_OR, OP_BIT_XOR, OP_SHL, OP_SHR,
    OP_ASSIGN,
    OP_INC, OP_DEC, OP_NOT, OP_NEG
} OperatorType;

typedef enum {
    FUNC_POW, FUNC_SQRT, FUNC_ABS, FUNC_FLOOR, FUNC_CEIL
} FunctionType;

/* ==================== AST NODE STRUCTURE ==================== */

typedef struct ASTNode {
    NodeType type;
    int line_number;
    
    /* For literals */
    union {
        int int_val;
        double double_val;
        char char_val;
        char *string_val;
    } value;
    
    /* Identifier/type information */
    char identifier[50];
    int data_type;  /* 0: numeric, 1: char */
    
    /* For collections */
    struct ASTNode **children;
    int child_count;
    int child_capacity;
    
    /* For binary/unary operations */
    OperatorType operator;
    
    /* For function calls */
    FunctionType function;
    int arg_count;
    
    /* For array declarations */
    int array_size;
    int array_rows;
    int array_cols;
    int array_dimensions;
    
} ASTNode;

/* ==================== AST UTILITIES ==================== */

ASTNode *node_pool[MAX_NODES];
int node_count = 0;

extern int yylineno;

ASTNode* create_node(NodeType type) {
    if (node_count >= MAX_NODES) {
        fprintf(stderr, "Error: Maximum AST nodes exceeded\n");
        return NULL;
    }
    
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    memset(node, 0, sizeof(ASTNode));
    
    node->type = type;
    node->child_capacity = 10;
    node->children = (ASTNode**)malloc(sizeof(ASTNode*) * node->child_capacity);
    
    node_pool[node_count++] = node;
    return node;
}

void add_child(ASTNode *parent, ASTNode *child) {
    if (!parent || !child) return;
    
    if (parent->child_count >= parent->child_capacity) {
        parent->child_capacity *= 2;
        parent->children = (ASTNode**)realloc(parent->children, 
                                              sizeof(ASTNode*) * parent->child_capacity);
    }
    
    parent->children[parent->child_count++] = child;
}

void free_ast(ASTNode *node) {
    if (!node) return;
    
    for (int i = 0; i < node->child_count; i++) {
        free_ast(node->children[i]);
    }
    
    if (node->value.string_val && (node->type == NODE_LITERAL_STRING || node->type == NODE_IDENTIFIER)) {
        free(node->value.string_val);
    }
    
    free(node->children);
    free(node);
}

void print_ast(ASTNode *node, int depth);
void execute_ast(ASTNode *node);

/* ==================== SYMBOL TABLE ==================== */

typedef struct {
    char name[50];
    double value;
    int type; /* 0: numeric, 1: char */
    int is_array;
    int dimensions; /* 1= 1D, 2 = 2D */
    int rows;
    int cols;
    double array_values[100];
    int array_size;
    double array2d[50][50];
} Symbol;

Symbol symtab[1000];
int symcount = 0;
int execute_flag = 1;
int loop_flag = 0;
int current_decl_type = 0;

typedef struct {
    double value;
    int matched;
    int done;
    int outer_exec;
} SwitchFrame;

SwitchFrame switch_stack[SWITCH_STACK_MAX];
int switch_top = -1;
int break_flag = 0;

void switch_push(double val, int outer_exec) {
    if (switch_top + 1 >= SWITCH_STACK_MAX) {
        fprintf(stderr, "Runtime error: switch nesting too deep\n");
        return;
    }
    switch_top++;
    switch_stack[switch_top].value = val;
    switch_stack[switch_top].matched = 0;
    switch_stack[switch_top].done = 0;
    switch_stack[switch_top].outer_exec = outer_exec;
}

void switch_pop(void) {
    if (switch_top < 0) {
        fprintf(stderr, "Runtime error: switch stack underflow\n");
        return;
    }
    switch_top--;
}

SwitchFrame *switch_cur(void) {
    if (switch_top < 0) return NULL;
    return &switch_stack[switch_top];
}

int sw_match(double a, double b) {
    return fabs(a - b) < SWITCH_EPSILON;
}

void yyerror(const char *s);
int yylex(void);
extern int yylineno;

void set_symbol(char *name, double value){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){
            symtab[i].value=value;
            return;
        }
    }
    strcpy(symtab[symcount].name,name);
    symtab[symcount].value=value;
    symtab[symcount].type=current_decl_type;
    symtab[symcount].is_array=0;
    symtab[symcount].array_size=0;
    symcount++;
}

int get_symbol_type(char *name){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0)
            return symtab[i].type;
    }
    return 0;
}

double get_symbol(char *name){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0)
            return symtab[i].value;
    }
    printf("Runtime error: variable %s not declared\n",name);
    return 0;
}

void declare_array(char *name, int size){
    strcpy(symtab[symcount].name,name);
    symtab[symcount].is_array=1;
    symtab[symcount].dimensions=1;
    symtab[symcount].array_size=size;
    symtab[symcount].type = current_decl_type;
    for(int i=0;i<size;i++){
        symtab[symcount].array_values[i]=0;
    }
    symcount++;
}

void set_array_element(char *name, int index, double value){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){
            if(symtab[i].is_array && index >= 0 && index < symtab[i].array_size){
                symtab[i].array_values[index]=value;
            }
            return;
        }
    }
}

double get_array_element(char *name, int index){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){
            if(symtab[i].is_array && index >= 0 && index < symtab[i].array_size){
                return symtab[i].array_values[index];
            }
        }
    }
    printf("Runtime error: array access error\n");
    return 0;
}

void declare_2d_array(char *name,int r,int c){
    strcpy(symtab[symcount].name,name);
    symtab[symcount].is_array = 1;
    symtab[symcount].dimensions = 2;
    symtab[symcount].rows = r;
    symtab[symcount].cols = c;
    symtab[symcount].type = current_decl_type;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            symtab[symcount].array2d[i][j] = 0;
    symcount++;
}

void set_array2d_element(char *name,int r,int c,double value){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){
            if(symtab[i].dimensions == 2 &&
               r < symtab[i].rows &&
               c < symtab[i].cols){
                symtab[i].array2d[r][c] = value;
            }
            return;
        }
    }
}

double get_array2d_element(char *name,int r,int c){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){
            if(symtab[i].dimensions == 2 &&
               r < symtab[i].rows &&
               c < symtab[i].cols){
                return symtab[i].array2d[r][c];
            }
        }
    }
    printf("Runtime error: 2D array access error\n");
    return 0;
}

%}

%union{
    int ival;
    float fval;
    char cval;
    char *sval;
    double dval;
    struct ASTNode *node;
}

/* tokens */

%token INCLUDE DEFINE HEADER

%token INT_TYPE FLOAT_TYPE DOUBLE_TYPE CHAR_TYPE BOOL_TYPE
%token VOID_TYPE LONG_TYPE SHORT_TYPE UNSIGNED_TYPE CONST

%token STRUCT UNION TYPEDEF ENUM

%token IF ELSE ELSEIF SWITCH CASE DEFAULT
%token FOR WHILE DO BREAK CONTINUE RETURN

%token MAIN PRINT SCAN

%token TRUE_LITERAL FALSE_LITERAL

%token POW SQRT ABS FLOOR CEIL

%token EQ NEQ GE LE GT LT
%token AND OR NOT
%token INC DEC
%token PLUS MINUS MUL DIV MOD
%token ASSIGN

%token BIT_AND BIT_OR BIT_XOR BIT_NOT SHL SHR

%token SEMI COMMA COLON
%token LPAREN RPAREN
%token LBRACE RBRACE
%token LBRACKET RBRACKET
%token RANGE

%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <sval> STRING_LITERAL
%token <cval> CHAR_LITERAL
%token <sval> IDENTIFIER

%type <node> program preprocessor_list preprocessor main_function statement_list statement
%type <node> declaration type identifier_list assignment array_assignment
%type <node> print_stmt scan_stmt if_stmt switch_stmt loop_stmt return_stmt
%type <node> expression term factor primary condition function_call array_access
%type <node> else_if_part case_list case_item default_item case_expr

%type <ival> array_size

%left OR
%left AND
%left EQ NEQ
%left GT LT GE LE
%left PLUS MINUS
%left MUL DIV MOD
%right UNARY

%start program

%%

program
    : preprocessor_list main_function
        {
            ASTNode *prog = create_node(NODE_PROGRAM);
            if ($1) add_child(prog, $1);
            if ($2) add_child(prog, $2);
            $$ = prog;
        }
    ;

preprocessor_list
    : preprocessor_list preprocessor
        {
            ASTNode *list = $1;
            if (!list) {
                list = create_node(NODE_STATEMENT_LIST);
            }
            if ($2) add_child(list, $2);
            $$ = list;
        }
    |
        {
            $$ = NULL;
        }
    ;

preprocessor
    : INCLUDE HEADER { $$ = NULL; }
    | DEFINE IDENTIFIER INT_LITERAL { $$ = NULL; }
    ;

main_function
    : MAIN LPAREN RPAREN LBRACE statement_list RBRACE
        {
            ASTNode *main_node = create_node(NODE_STATEMENT_LIST);
            if ($5) {
                main_node = $5;
            }
            $$ = main_node;
        }
    ;

statement_list
    : statement_list statement
        {
            ASTNode *list = $1;
            if (!list) {
                list = create_node(NODE_STATEMENT_LIST);
            }
            if ($2) add_child(list, $2);
            $$ = list;
        }
    |
        {
            $$ = NULL;
        }
    ;

statement
    : declaration
        { $$ = $1; }
    | assignment SEMI
        { $$ = $1; }
    | array_assignment SEMI
        { $$ = $1; }
    | print_stmt
        { $$ = $1; }
    | scan_stmt
        { $$ = $1; }
    | if_stmt
        { $$ = $1; }
    | switch_stmt
        { $$ = $1; }
    | BREAK SEMI
        {
            if(execute_flag) break_flag = 1;
            ASTNode *brk = create_node(NODE_BREAK);
            $$ = brk;
        }
    | loop_stmt
        { $$ = $1; }
    | return_stmt SEMI
        { $$ = $1; }
    ;

declaration
    : type identifier_list SEMI
        { $$ = $2; }
    | type IDENTIFIER LBRACKET array_size RBRACKET SEMI
        {
            if(execute_flag) declare_array($2,$4);
            ASTNode *decl = create_node(NODE_ARRAY_DECL_1D);
            strcpy(decl->identifier, $2);
            decl->array_size = $4;
            decl->data_type = current_decl_type;
            $$ = decl;
        }
    | type IDENTIFIER LBRACKET array_size RBRACKET LBRACKET array_size RBRACKET SEMI
        {
            if(execute_flag) declare_2d_array($2,$4,$7);
            ASTNode *decl = create_node(NODE_ARRAY_DECL_2D);
            strcpy(decl->identifier, $2);
            decl->array_rows = $4;
            decl->array_cols = $7;
            decl->data_type = current_decl_type;
            $$ = decl;
        }
    ;

array_size
    : INT_LITERAL { $$=$1; }
    ;

type
    : INT_TYPE          { current_decl_type = 0; }
    | FLOAT_TYPE        { current_decl_type = 0; }
    | DOUBLE_TYPE       { current_decl_type = 0; }
    | CHAR_TYPE         { current_decl_type = 1; }
    | BOOL_TYPE         { current_decl_type = 0; }
    | VOID_TYPE         { current_decl_type = 0; }
    | LONG_TYPE         { current_decl_type = 0; }
    | SHORT_TYPE        { current_decl_type = 0; }
    | UNSIGNED_TYPE     { current_decl_type = 0; }
    ;

identifier_list
    : IDENTIFIER
        {
            if(execute_flag) set_symbol($1,0);
            ASTNode *decl = create_node(NODE_DECLARATION);
            strcpy(decl->identifier, $1);
            decl->value.double_val = 0;
            decl->data_type = current_decl_type;
            $$ = decl;
        }
    | IDENTIFIER ASSIGN expression
        {
            if(execute_flag) set_symbol($1,$3->value.double_val);
            ASTNode *decl = create_node(NODE_DECLARATION);
            strcpy(decl->identifier, $1);
            add_child(decl, $3);
            decl->data_type = current_decl_type;
            $$ = decl;
        }
    | IDENTIFIER COMMA identifier_list
        {
            if(execute_flag) set_symbol($1,0);
            ASTNode *decl = create_node(NODE_DECLARATION);
            strcpy(decl->identifier, $1);
            decl->value.double_val = 0;
            decl->data_type = current_decl_type;
            add_child(decl, $3);
            $$ = decl;
        }
    | IDENTIFIER ASSIGN expression COMMA identifier_list
        {
            if(execute_flag) set_symbol($1,$3->value.double_val);
            ASTNode *decl = create_node(NODE_DECLARATION);
            strcpy(decl->identifier, $1);
            add_child(decl, $3);
            add_child(decl, $5);
            decl->data_type = current_decl_type;
            $$ = decl;
        }
    ;

assignment
    : IDENTIFIER ASSIGN expression
        {
            if(execute_flag) set_symbol($1,$3->value.double_val);
            ASTNode *assign = create_node(NODE_ASSIGNMENT);
            strcpy(assign->identifier, $1);
            add_child(assign, $3);
            $$ = assign;
        }
    ;

array_assignment
    : IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression
        {
            if(execute_flag) set_array_element($1,(int)$3->value.double_val,$6->value.double_val);
            ASTNode *assign = create_node(NODE_ARRAY_ASSIGNMENT);
            strcpy(assign->identifier, $1);
            add_child(assign, $3);
            add_child(assign, $6);
            assign->array_dimensions = 1;
            $$ = assign;
        }
    | IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET ASSIGN expression
        {
            if(execute_flag) set_array2d_element($1,(int)$3->value.double_val,(int)$6->value.double_val,$9->value.double_val);
            ASTNode *assign = create_node(NODE_ARRAY_ASSIGNMENT);
            strcpy(assign->identifier, $1);
            add_child(assign, $3);
            add_child(assign, $6);
            add_child(assign, $9);
            assign->array_dimensions = 2;
            $$ = assign;
        }
    ;

/* ==================== EXPRESSIONS ==================== */

expression
    : expression PLUS term
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_PLUS;
            add_child(expr, $1);
            add_child(expr, $3);
            expr->value.double_val = $1->value.double_val + $3->value.double_val;
            $$ = expr;
        }
    | expression MINUS term
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_MINUS;
            add_child(expr, $1);
            add_child(expr, $3);
            expr->value.double_val = $1->value.double_val - $3->value.double_val;
            $$ = expr;
        }
    | MINUS term %prec UNARY
        {
            ASTNode *expr = create_node(NODE_UNARY_OP);
            expr->operator = OP_NEG;
            add_child(expr, $2);
            expr->value.double_val = -$2->value.double_val;
            $$ = expr;
        }
    | term
        { $$ = $1; }
    ;

term
    : term MUL factor
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_MUL;
            add_child(expr, $1);
            add_child(expr, $3);
            expr->value.double_val = $1->value.double_val * $3->value.double_val;
            $$ = expr;
        }
    | term DIV factor
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_DIV;
            add_child(expr, $1);
            add_child(expr, $3);
            if($3->value.double_val!=0) {
                expr->value.double_val = $1->value.double_val / $3->value.double_val;
            } else {
                yyerror("Division by zero");
                expr->value.double_val = 0;
            }
            $$ = expr;
        }
    | term MOD factor
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_MOD;
            add_child(expr, $1);
            add_child(expr, $3);
            if((int)$3->value.double_val!=0) {
                expr->value.double_val = (int)$1->value.double_val % (int)$3->value.double_val;
            } else {
                yyerror("Modulo by zero");
                expr->value.double_val = 0;
            }
            $$ = expr;
        }
    | factor
        { $$ = $1; }
    ;

factor
    : primary
        { $$ = $1; }
    ;

primary
    : IDENTIFIER
        {
            ASTNode *id = create_node(NODE_IDENTIFIER);
            strcpy(id->identifier, $1);
            id->value.double_val = get_symbol($1);
            $$ = id;
        }
    | INT_LITERAL
        {
            ASTNode *lit = create_node(NODE_LITERAL_INT);
            lit->value.int_val = $1;
            lit->value.double_val = $1;
            $$ = lit;
        }
    | FLOAT_LITERAL
        {
            ASTNode *lit = create_node(NODE_LITERAL_FLOAT);
            lit->value.double_val = $1;
            $$ = lit;
        }
    | TRUE_LITERAL
        {
            ASTNode *lit = create_node(NODE_LITERAL_BOOL);
            lit->value.double_val = 1;
            $$ = lit;
        }
    | FALSE_LITERAL
        {
            ASTNode *lit = create_node(NODE_LITERAL_BOOL);
            lit->value.double_val = 0;
            $$ = lit;
        }
    | CHAR_LITERAL
        {
            ASTNode *lit = create_node(NODE_LITERAL_CHAR);
            lit->value.char_val = $1;
            lit->value.double_val = $1;
            $$ = lit;
        }
    | LPAREN expression RPAREN
        { $$ = $2; }
    | function_call
        { $$ = $1; }
    | array_access
        { $$ = $1; }
    ;

array_access
    : IDENTIFIER LBRACKET expression RBRACKET
        {
            ASTNode *access = create_node(NODE_ARRAY_ACCESS);
            strcpy(access->identifier, $1);
            add_child(access, $3);
            access->value.double_val = get_array_element($1,(int)$3->value.double_val);
            access->array_dimensions = 1;
            $$ = access;
        }
    | IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET
        {
            ASTNode *access = create_node(NODE_ARRAY_ACCESS);
            strcpy(access->identifier, $1);
            add_child(access, $3);
            add_child(access, $6);
            access->value.double_val = get_array2d_element($1,(int)$3->value.double_val,(int)$6->value.double_val);
            access->array_dimensions = 2;
            $$ = access;
        }
    ;

/* ==================== FUNCTIONS ==================== */

function_call
    : POW LPAREN expression COMMA expression RPAREN
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_POW;
            add_child(func, $3);
            add_child(func, $5);
            func->arg_count = 2;
            func->value.double_val = pow($3->value.double_val, $5->value.double_val);
            $$ = func;
        }
    | SQRT LPAREN expression RPAREN
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_SQRT;
            add_child(func, $3);
            func->arg_count = 1;
            func->value.double_val = sqrt($3->value.double_val);
            $$ = func;
        }
    | ABS LPAREN expression RPAREN
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_ABS;
            add_child(func, $3);
            func->arg_count = 1;
            func->value.double_val = fabs($3->value.double_val);
            $$ = func;
        }
    | FLOOR LPAREN expression RPAREN
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_FLOOR;
            add_child(func, $3);
            func->arg_count = 1;
            func->value.double_val = floor($3->value.double_val);
            $$ = func;
        }
    | CEIL LPAREN expression RPAREN
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_CEIL;
            add_child(func, $3);
            func->arg_count = 1;
            func->value.double_val = ceil($3->value.double_val);
            $$ = func;
        }
    ;

/* ==================== PRINT ==================== */

print_stmt
    : PRINT LPAREN STRING_LITERAL RPAREN SEMI
        {
            if(execute_flag) {
                char *s = $3;
                if(s[0]=='"') s++;
                int len = strlen(s);
                if(len>0 && s[len-1]=='"') s[len-1]='\0';
                printf("%s\n",s);
            }
            ASTNode *print = create_node(NODE_PRINT);
            ASTNode *lit = create_node(NODE_LITERAL_STRING);
            lit->value.string_val = (char*)malloc(strlen($3) + 1);
            strcpy(lit->value.string_val, $3);
            add_child(print, lit);
            $$ = print;
        }
    | PRINT LPAREN IDENTIFIER RPAREN SEMI
        {
            if(execute_flag) {
                int t = get_symbol_type($3);
                double v = get_symbol($3);
                if(t == 1) printf("%c\n", (int)v);
                else printf("%g\n", v);
            }
            ASTNode *print = create_node(NODE_PRINT);
            ASTNode *id = create_node(NODE_IDENTIFIER);
            strcpy(id->identifier, $3);
            id->value.double_val = get_symbol($3);
            add_child(print, id);
            $$ = print;
        }
    | PRINT LPAREN expression RPAREN SEMI
        {
            if(execute_flag) printf("%g\n",$3->value.double_val);
            ASTNode *print = create_node(NODE_PRINT);
            add_child(print, $3);
            $$ = print;
        }
    ;

/* ==================== INPUT ==================== */

scan_stmt
    : SCAN LPAREN IDENTIFIER RPAREN SEMI
        {
            if(execute_flag) {
                int t = get_symbol_type($3);
                if(t == 1) {
                    char v;
                    scanf(" %c", &v);
                    set_symbol($3, (double)v);
                } else {
                    double v;
                    scanf("%lf",&v);
                    set_symbol($3,v);
                }
            }
            ASTNode *scan = create_node(NODE_SCAN);
            ASTNode *id = create_node(NODE_IDENTIFIER);
            strcpy(id->identifier, $3);
            add_child(scan, id);
            $$ = scan;
        }
    | SCAN LPAREN IDENTIFIER LBRACKET expression RBRACKET RPAREN SEMI
        {
            if(execute_flag) {
                double v;
                scanf("%lf",&v);
                set_array_element($3,(int)$5->value.double_val,v);
            }
            ASTNode *scan = create_node(NODE_SCAN);
            ASTNode *id = create_node(NODE_IDENTIFIER);
            strcpy(id->identifier, $3);
            add_child(scan, id);
            add_child(scan, $5);
            $$ = scan;
        }
    ;

/* ==================== IF ==================== */

if_stmt
    : IF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part
        {
            /* Save the original execute state before this if block */
            int saved_exec = execute_flag;
            int cond_val = $3->value.double_val;
            
            /* Execute the if block logic */
            if (saved_exec) {
                if (cond_val) {
                    execute_flag = 0;  /* block ran, skip rest */
                } else {
                    execute_flag = 1;  /* block didn't run, check next */
                }
            } else {
                execute_flag = 0;  /* already skipping */
            }
            
            /* Create AST node */
            ASTNode *if_node = create_node(NODE_IF);
            add_child(if_node, $3);      /* condition */
            if ($6) add_child(if_node, $6);    /* statement_list */
            if ($8) add_child(if_node, $8);    /* else_if_part */
            
            /* Restore original state for next statement */
            execute_flag = saved_exec;
            $$ = if_node;
        }
    ;

else_if_part
    : ELSEIF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part
        {
            int saved_exec = execute_flag;
            int cond_val = $3->value.double_val;
            
            if (saved_exec) {
                if (cond_val) {
                    execute_flag = 0;
                } else {
                    execute_flag = 1;
                }
            } else {
                execute_flag = 0;
            }
            
            ASTNode *elseif = create_node(NODE_IF);
            add_child(elseif, $3);       /* condition */
            if ($6) add_child(elseif, $6);     /* statement_list */
            if ($8) add_child(elseif, $8);     /* else_if_part */
            
            execute_flag = saved_exec;
            $$ = elseif;
        }
    | ELSE LBRACE statement_list RBRACE
        {
            $$ = $3;
        }
    | /* empty */
        {
            $$ = NULL;
        }
    ;

/* ==================== SWITCH-CASE ==================== */

switch_stmt
    : SWITCH LPAREN expression RPAREN
        {
            switch_push($3->value.double_val, execute_flag);
            if (execute_flag) {
                execute_flag = 0;
            } else {
                switch_cur()->done = 1;
            }
        }
      LBRACE case_list RBRACE
        {
            ASTNode *switch_node = create_node(NODE_SWITCH);
            add_child(switch_node, $3);
            if ($7) add_child(switch_node, $7);
            
            execute_flag = switch_cur()->outer_exec;
            switch_pop();
            break_flag = 0;
            $$ = switch_node;
        }
    ;

case_list
    : case_list case_item
        {
            ASTNode *list = $1;
            if (!list) {
                list = create_node(NODE_STATEMENT_LIST);
            }
            if ($2) add_child(list, $2);
            $$ = list;
        }
    | case_list default_item
        {
            ASTNode *list = $1;
            if (!list) {
                list = create_node(NODE_STATEMENT_LIST);
            }
            if ($2) add_child(list, $2);
            $$ = list;
        }
    | /* empty */
        {
            $$ = NULL;
        }
    ;

case_item
    : CASE case_expr COLON
        {
            /* case_expr already set execute_flag appropriately */
        }
      statement_list
        {
            SwitchFrame *f = switch_cur();
            if (f && break_flag && execute_flag) {
                f->done = 1;
                execute_flag = 0;
                break_flag = 0;
            }
            ASTNode *case_node = create_node(NODE_CASE);
            add_child(case_node, $2);
            if ($5) add_child(case_node, $5);
            $$ = case_node;
        }
    ;

case_expr
    : expression
        {
            SwitchFrame *f = switch_cur();
            if (f == NULL) {
                yyerror("case outside switch");
                execute_flag = 0;
            } else if (f->done) {
                execute_flag = 0;
            } else if (f->matched) {
                execute_flag = 1;
            } else if (fabs(f->value - $1->value.double_val) < SWITCH_EPSILON) {
                f->matched = 1;
                execute_flag = 1;
            } else {
                execute_flag = 0;
            }
            $$ = $1;
        }
    | expression RANGE expression
        {
            SwitchFrame *f = switch_cur();
            if (f == NULL) {
                yyerror("case outside switch");
                execute_flag = 0;
            } else if (f->done) {
                execute_flag = 0;
            } else if (f->matched) {
                execute_flag = 1;
            } else {
                int start = (int)$1->value.double_val;
                int end = (int)$3->value.double_val;
                int val = (int)f->value;
                
                if (val >= start && val <= end) {
                    f->matched = 1;
                    execute_flag = 1;
                } else {
                    execute_flag = 0;
                }
            }
            ASTNode *range = create_node(NODE_CASE_RANGE);
            add_child(range, $1);
            add_child(range, $3);
            $$ = range;
        }
    ;

default_item
    : DEFAULT COLON
        {
            SwitchFrame *f = switch_cur();
            if (f == NULL) {
                yyerror("default outside switch");
                execute_flag = 0;
            } else if (f->done) {
                execute_flag = 0;
            } else if (f->matched) {
                execute_flag = 1;
            } else {
                execute_flag = 1;
            }
        }
      statement_list
        {
            SwitchFrame *f = switch_cur();
            if (f && break_flag && execute_flag) {
                f->done = 1;
                execute_flag = 0;
                break_flag = 0;
            }
            ASTNode *default_node = create_node(NODE_DEFAULT);
            if ($4) add_child(default_node, $4);
            $$ = default_node;
        }
    ;

/* ==================== CONDITION ==================== */

condition
    : expression EQ expression
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_EQ;
            add_child(cond, $1);
            add_child(cond, $3);
            cond->value.double_val = ($1->value.double_val == $3->value.double_val);
            $$ = cond;
        }
    | expression NEQ expression
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_NEQ;
            add_child(cond, $1);
            add_child(cond, $3);
            cond->value.double_val = ($1->value.double_val != $3->value.double_val);
            $$ = cond;
        }
    | expression GT expression
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_GT;
            add_child(cond, $1);
            add_child(cond, $3);
            cond->value.double_val = ($1->value.double_val > $3->value.double_val);
            $$ = cond;
        }
    | expression LT expression
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_LT;
            add_child(cond, $1);
            add_child(cond, $3);
            cond->value.double_val = ($1->value.double_val < $3->value.double_val);
            $$ = cond;
        }
    | expression GE expression
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_GE;
            add_child(cond, $1);
            add_child(cond, $3);
            cond->value.double_val = ($1->value.double_val >= $3->value.double_val);
            $$ = cond;
        }
    | expression LE expression
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_LE;
            add_child(cond, $1);
            add_child(cond, $3);
            cond->value.double_val = ($1->value.double_val <= $3->value.double_val);
            $$ = cond;
        }
    ;

/* ==================== LOOPS ==================== */

loop_stmt
    : WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE
        {
            ASTNode *loop = create_node(NODE_LOOP_WHILE);
            add_child(loop, $3);
            if ($6) add_child(loop, $6);
            $$ = loop;
        }
    | FOR LPAREN assignment SEMI condition SEMI assignment RPAREN
      LBRACE statement_list RBRACE
        {
            ASTNode *loop = create_node(NODE_LOOP_FOR);
            if ($3) add_child(loop, $3);
            if ($5) add_child(loop, $5);
            if ($7) add_child(loop, $7);
            if ($10) add_child(loop, $10);
            $$ = loop;
        }
    ;

return_stmt
    : RETURN expression
        {
            if(execute_flag) printf("Program returned: %g\n",$2->value.double_val);
            ASTNode *ret = create_node(NODE_RETURN);
            add_child(ret, $2);
            $$ = ret;
        }
    ;

%%

/* ==================== AST UTILITIES IMPLEMENTATION ==================== */

const char* node_type_to_string(NodeType type) {
    switch(type) {
        case NODE_PROGRAM: return "PROGRAM";
        case NODE_STATEMENT_LIST: return "STATEMENT_LIST";
        case NODE_DECLARATION: return "DECLARATION";
        case NODE_ASSIGNMENT: return "ASSIGNMENT";
        case NODE_ARRAY_ASSIGNMENT: return "ARRAY_ASSIGNMENT";
        case NODE_PRINT: return "PRINT";
        case NODE_SCAN: return "SCAN";
        case NODE_IF: return "IF";
        case NODE_SWITCH: return "SWITCH";
        case NODE_CASE: return "CASE";
        case NODE_DEFAULT: return "DEFAULT";
        case NODE_BREAK: return "BREAK";
        case NODE_LOOP_WHILE: return "WHILE";
        case NODE_LOOP_FOR: return "FOR";
        case NODE_RETURN: return "RETURN";
        case NODE_EXPRESSION: return "EXPRESSION";
        case NODE_CONDITION: return "CONDITION";
        case NODE_FUNCTION_CALL: return "FUNCTION_CALL";
        case NODE_ARRAY_ACCESS: return "ARRAY_ACCESS";
        case NODE_IDENTIFIER: return "IDENTIFIER";
        case NODE_LITERAL_INT: return "INT_LITERAL";
        case NODE_LITERAL_FLOAT: return "FLOAT_LITERAL";
        case NODE_LITERAL_CHAR: return "CHAR_LITERAL";
        case NODE_LITERAL_STRING: return "STRING_LITERAL";
        case NODE_LITERAL_BOOL: return "BOOL_LITERAL";
        case NODE_BINARY_OP: return "BINARY_OP";
        case NODE_UNARY_OP: return "UNARY_OP";
        case NODE_ARRAY_DECL_1D: return "ARRAY_DECL_1D";
        case NODE_ARRAY_DECL_2D: return "ARRAY_DECL_2D";
        case NODE_CASE_RANGE: return "CASE_RANGE";
        default: return "UNKNOWN";
    }
}

const char* op_to_string(OperatorType op) {
    switch(op) {
        case OP_PLUS: return "+";
        case OP_MINUS: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "/";
        case OP_MOD: return "%";
        case OP_EQ: return "==";
        case OP_NEQ: return "!=";
        case OP_GT: return ">";
        case OP_LT: return "<";
        case OP_GE: return ">=";
        case OP_LE: return "<=";
        case OP_AND: return "&&";
        case OP_OR: return "||";
        case OP_BIT_AND: return "&";
        case OP_BIT_OR: return "|";
        case OP_BIT_XOR: return "^";
        case OP_SHL: return "<<";
        case OP_SHR: return ">>";
        case OP_NEG: return "-(unary)";
        case OP_NOT: return "!";
        default: return "?";
    }
}

const char* func_to_string(FunctionType func) {
    switch(func) {
        case FUNC_POW: return "pow";
        case FUNC_SQRT: return "sqrt";
        case FUNC_ABS: return "abs";
        case FUNC_FLOOR: return "floor";
        case FUNC_CEIL: return "ceil";
        default: return "?";
    }
}

void print_ast(ASTNode *node, int depth) {
    if (!node) return;
    
    for (int i = 0; i < depth; i++) printf("  ");
    
    printf("[%s]", node_type_to_string(node->type));
    
    switch(node->type) {
        case NODE_IDENTIFIER:
            printf(" name=%s", node->identifier);
            break;
        case NODE_LITERAL_INT:
            printf(" value=%d", node->value.int_val);
            break;
        case NODE_LITERAL_FLOAT:
        case NODE_LITERAL_BOOL:
            printf(" value=%g", node->value.double_val);
            break;
        case NODE_LITERAL_CHAR:
            printf(" value='%c'", node->value.char_val);
            break;
        case NODE_LITERAL_STRING:
            printf(" value=\"%s\"", node->value.string_val);
            break;
        case NODE_DECLARATION:
            printf(" name=%s", node->identifier);
            break;
        case NODE_ASSIGNMENT:
            printf(" id=%s", node->identifier);
            break;
        case NODE_ARRAY_ACCESS:
            printf(" id=%s dims=%d", node->identifier, node->array_dimensions);
            break;
        case NODE_ARRAY_DECL_1D:
            printf(" id=%s size=%d", node->identifier, node->array_size);
            break;
        case NODE_ARRAY_DECL_2D:
            printf(" id=%s rows=%d cols=%d", node->identifier, node->array_rows, node->array_cols);
            break;
        case NODE_BINARY_OP:
            printf(" op=%s", op_to_string(node->operator));
            break;
        case NODE_UNARY_OP:
            printf(" op=%s", op_to_string(node->operator));
            break;
        case NODE_CONDITION:
            printf(" op=%s", op_to_string(node->operator));
            break;
        case NODE_FUNCTION_CALL:
            printf(" func=%s args=%d", func_to_string(node->function), node->arg_count);
            break;
        default:
            break;
    }
    
    printf("\n");
    
    for (int i = 0; i < node->child_count; i++) {
        print_ast(node->children[i], depth + 1);
    }
}

void yyerror(const char *s){
    printf("Syntax Error at line %d: %s\n",yylineno,s);
}

extern FILE *yyin;

int main(int argc, char *argv[]){
    char *filename = (argc > 1) ? argv[1] : "input.txt";
    FILE *fp = fopen(filename, "r");

    if(!fp){
        printf("Cannot open input file: %s\n", filename);
        return 1;
    }

    yyin = fp;

    printf("Running Luminix Program (AST Version)...\n\n");

    ASTNode *ast = NULL;
    int parse_result = yyparse();
    
    if (parse_result == 0 && node_count > 0) {
        printf("\n====== AST STRUCTURE ======\n");
        print_ast(node_pool[node_count - 1], 0);
        printf("\n====== END AST ======\n\n");
    }

    printf("\nProgram finished.\n");
    
    /* Clean up */
    for (int i = 0; i < node_count; i++) {
        if (node_pool[i]) {
            free(node_pool[i]->children);
            if (node_pool[i]->value.string_val) {
                free(node_pool[i]->value.string_val);
            }
            free(node_pool[i]);
        }
    }

    return parse_result;
}
