%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"
#include "interpreter.h"

void yyerror(const char *s);
int  yylex(void);
extern int yylineno;

/* tracks declaration type for declarations */
static int current_decl_type = 0;   /* 0 = numeric, 1 = char */
%}

/* ---- value types ---- */
%union {
    int      ival;
    float    fval;
    char     cval;
    char    *sval;
    double   dval;
    ASTNode *node;   /* <-- NEW: AST node pointer */
}

/* -----tokens------- */

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

/* ---- non-terminal types ---- */
%type <node> expression term factor primary condition
%type <node> function_call array_access
%type <node> statement statement_list
%type <node> declaration declaration_no_semi assignment array_assignment
%type <node> print_stmt scan_stmt
%type <node> if_stmt else_if_part
%type <node> switch_stmt case_list case_item case_expr default_item
%type <node> loop_stmt return_stmt
%type <node> identifier_list_decls
%type <node> for_init for_update

%type <node> func_def func_call_expr
%type <node> param_list param arg_list_opt arg_list
%type <ival> ret_type

%type <ival> array_size

/* ---- precedence ---- */
%left  OR
%left  AND
%left  EQ NEQ
%left  GT LT GE LE
%left  PLUS MINUS
%left  MUL DIV MOD
%right UNARY

%start program

%%

/* ================================================================== */
/*  Top-level                                                          */
/* ================================================================== */

program
    : preprocessor_list top_level_list
    ;

top_level_list
    : top_level_list func_def
    | top_level_list main_function
    | /* empty */
    ;

func_def
    : ret_type IDENTIFIER LPAREN param_list RPAREN LBRACE statement_list RBRACE
        {
            /* Register function into the function table at parse time.
               The body AST is stored by reference — do NOT free it. */
            ASTNode *def = make_func_def($2, $1, $4, $7);
            func_define($2, $1, $4, $7);
            /* def itself is not added to the program tree —
               the function table holds the body reference */
            (void)def;   /* suppress unused-variable warning */
        }
    ;

ret_type
    : INT_TYPE      { $$ = 0; current_decl_type = 0; }
    | FLOAT_TYPE    { $$ = 0; current_decl_type = 0; }
    | DOUBLE_TYPE   { $$ = 0; current_decl_type = 0; }
    | CHAR_TYPE     { $$ = 1; current_decl_type = 1; }
    | BOOL_TYPE     { $$ = 0; current_decl_type = 0; }
    | VOID_TYPE     { $$ = 2; current_decl_type = 0; }
    | LONG_TYPE     { $$ = 0; current_decl_type = 0; }
    | SHORT_TYPE    { $$ = 0; current_decl_type = 0; }
    | UNSIGNED_TYPE { $$ = 0; current_decl_type = 0; }
    ;
param_list
    : param_list COMMA param
        {
            /* append $3 to end of $1 */
            if ($1 == NULL) { $$ = $3; }
            else {
                ASTNode *t = $1;
                while (t->next) t = t->next;
                t->next = $3;
                $$ = $1;
            }
        }
    | param         { $$ = $1; }
    | /* empty */   { $$ = NULL; }
    ;

param
    : type IDENTIFIER
        {
            $$ = make_param($2, current_decl_type);
        }
    ;


preprocessor_list
    : preprocessor_list preprocessor
    | /* empty */
    ;

preprocessor
    : INCLUDE HEADER
    | DEFINE IDENTIFIER INT_LITERAL
    ;

main_function
    : MAIN LPAREN RPAREN LBRACE statement_list RBRACE
        {
            /* Build program root and immediately interpret it */
            ASTNode *prog = make_node(NODE_PROGRAM);
            prog->left = $5;
            interpret(prog);
            free_ast(prog);
        }
    ;

/* ================================================================== */
/*  Statements                                                         */
/* ================================================================== */

statement_list
    : statement_list statement
        {
            /* Append $2 to the end of the $1 list.
               We use a right-growing list: walk to the tail and link. */
            if ($1 == NULL) {
                $$ = $2;
            } else if ($2 == NULL) {
                $$ = $1;
            } else {
                /* find tail of $1 */
                ASTNode *tail = $1;
                while (tail->next) tail = tail->next;
                tail->next = $2;
                $$ = $1;
            }
        }
    | /* empty */ { $$ = NULL; }
    ;

statement
    : declaration          { $$ = $1; }
    | assignment SEMI      { $$ = $1; }
    | array_assignment SEMI { $$ = $1; }
    | print_stmt           { $$ = $1; }
    | scan_stmt            { $$ = $1; }
    | if_stmt              { $$ = $1; }
    | switch_stmt          { $$ = $1; }
    | BREAK SEMI
        {
            $$ = make_node(NODE_BREAK);
        }
    | CONTINUE SEMI
        {
            $$ = make_node(NODE_CONTINUE);
        }
    | loop_stmt            { $$ = $1; }
    | return_stmt SEMI     { $$ = $1; }
    | func_call_expr SEMI    { $$ = $1; }
    | RETURN SEMI    { $$ = make_return_void(); }
    ;

/* ================================================================== */
/*  Declarations                                                       */
/* ================================================================== */

declaration
    : type identifier_list_decls SEMI
        { $$ = $2; }
    | type IDENTIFIER LBRACKET array_size RBRACKET SEMI
        {
            ASTNode *n = make_node(NODE_DECL_ARRAY);
            n->sval      = strdup($2);
            n->cols      = $4;   /* size stored in cols */
            n->decl_type = current_decl_type;
            $$ = n;
        }
    | type IDENTIFIER LBRACKET array_size RBRACKET LBRACKET array_size RBRACKET SEMI
        {
            ASTNode *n = make_node(NODE_DECL_ARRAY_2D);
            n->sval      = strdup($2);
            n->rows      = $4;
            n->cols      = $7;
            n->decl_type = current_decl_type;
            $$ = n;
        }
    ;

/* for loop declarations (without trailing semicolon) */
declaration_no_semi
    : type IDENTIFIER
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup($2);
            n->left      = NULL;
            n->decl_type = current_decl_type;
            $$ = n;
        }
    | type IDENTIFIER ASSIGN expression
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup($2);
            n->left      = $4;
            n->decl_type = current_decl_type;
            $$ = n;
        }
    ;

array_size
    : INT_LITERAL { $$ = $1; }
    ;

type
    : INT_TYPE      { current_decl_type = 0; }
    | FLOAT_TYPE    { current_decl_type = 0; }
    | DOUBLE_TYPE   { current_decl_type = 0; }
    | CHAR_TYPE     { current_decl_type = 1; }
    | BOOL_TYPE     { current_decl_type = 0; }
    | VOID_TYPE     { current_decl_type = 0; }
    | LONG_TYPE     { current_decl_type = 0; }
    | SHORT_TYPE    { current_decl_type = 0; }
    | UNSIGNED_TYPE { current_decl_type = 0; }
    ;

/*
 * A comma-separated list of declarators:
 *   x, y = 5, z
 * Each declarator becomes a NODE_DECL; they are linked via ->next.
 */
identifier_list_decls
    : IDENTIFIER
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup($1);
            n->left      = NULL;   /* no initialiser */
            n->decl_type = current_decl_type;
            $$ = n;
        }
    | IDENTIFIER ASSIGN expression
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup($1);
            n->left      = $3;
            n->decl_type = current_decl_type;
            $$ = n;
        }
    | IDENTIFIER COMMA identifier_list_decls
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup($1);
            n->left      = NULL;
            n->decl_type = current_decl_type;
            n->next      = $3;
            $$ = n;
        }
    | IDENTIFIER ASSIGN expression COMMA identifier_list_decls
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup($1);
            n->left      = $3;
            n->decl_type = current_decl_type;
            n->next      = $5;
            $$ = n;
        }
    ;

/* ================================================================== */
/*  Assignment                                                         */
/* ================================================================== */

assignment
    : IDENTIFIER ASSIGN expression
        {
            ASTNode *n = make_node(NODE_ASSIGN);
            n->sval = strdup($1);
            n->left = $3;
            $$ = n;
        }
    ;

array_assignment
    : IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression
        {
            ASTNode *n = make_node(NODE_ARRAY_ASSIGN);
            n->sval  = strdup($1);
            n->left  = $3;   /* index  */
            n->right = $6;   /* value  */
            $$ = n;
        }
    | IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET ASSIGN expression
        {
            ASTNode *n = make_node(NODE_ARRAY_ASSIGN_2D);
            n->sval  = strdup($1);
            n->left  = $3;   /* row   */
            n->right = $6;   /* col   */
            n->extra = $9;   /* value */
            $$ = n;
        }
    ;

/* ================================================================== */
/*  Expressions                                                        */
/* ================================================================== */

expression
    : expression PLUS term   { $$ = make_binop(NODE_ADD, $1, $3); }
    | expression MINUS term  { $$ = make_binop(NODE_SUB, $1, $3); }
    | expression AND term         { $$ = make_binop(NODE_AND, $1, $3); }
    | expression OR term          { $$ = make_binop(NODE_OR, $1, $3); }
    | MINUS term %prec UNARY { $$ = make_unary(NODE_NEGATE, $2); }
    | NOT term %prec UNARY        { $$ = make_unary(NODE_NOT, $2); }
    | term                   { $$ = $1; }
    ;

term
    : term MUL factor   { $$ = make_binop(NODE_MUL, $1, $3); }
    | term DIV factor   { $$ = make_binop(NODE_DIV, $1, $3); }
    | term MOD factor   { $$ = make_binop(NODE_MOD, $1, $3); }
    | factor            { $$ = $1; }
    ;

factor
    : primary { $$ = $1; }
    ;

primary
    : IDENTIFIER        { $$ = make_ident($1); }
    | INT_LITERAL       { $$ = make_int_lit($1); }
    | FLOAT_LITERAL     { $$ = make_float_lit((double)$1); }
    | TRUE_LITERAL      { $$ = make_bool_lit(1); }
    | FALSE_LITERAL     { $$ = make_bool_lit(0); }
    | CHAR_LITERAL      { $$ = make_char_lit($1); }
    | LPAREN expression RPAREN { $$ = $2; }
    | function_call     { $$ = $1; }
    | array_access      { $$ = $1; }
    | func_call_expr    { $$ = $1; }
    ;

func_call_expr
    : IDENTIFIER LPAREN arg_list_opt RPAREN
        {
            $$ = make_func_call($1, $3);
        }
    ;

arg_list_opt
    : arg_list   { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

arg_list
    : arg_list COMMA expression
        {
            ASTNode *a = make_arg_list($3, NULL);
            /* append to end */
            if ($1 == NULL) { $$ = a; }
            else {
                ASTNode *t = $1;
                while (t->next) t = t->next;
                t->next = a;
                $$ = $1;
            }
        }
    | expression
        {
            $$ = make_arg_list($1, NULL);
        }
    ;

array_access
    : IDENTIFIER LBRACKET expression RBRACKET
        { $$ = make_array_access($1, $3); }
    | IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET
        { $$ = make_array_access_2d($1, $3, $6); }
    ;

/* ================================================================== */
/*  Built-in functions                                                 */
/* ================================================================== */

function_call
    : POW LPAREN expression COMMA expression RPAREN
        { $$ = make_func2(NODE_POW, $3, $5); }
    | SQRT LPAREN expression RPAREN
        { $$ = make_func1(NODE_SQRT, $3); }
    | ABS LPAREN expression RPAREN
        { $$ = make_func1(NODE_ABS, $3); }
    | FLOOR LPAREN expression RPAREN
        { $$ = make_func1(NODE_FLOOR, $3); }
    | CEIL LPAREN expression RPAREN
        { $$ = make_func1(NODE_CEIL, $3); }
    ;

/* ================================================================== */
/*  Print & Scan                                                       */
/* ================================================================== */

print_stmt
    : PRINT LPAREN STRING_LITERAL RPAREN SEMI
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = strdup($3);   /* string literal */
            n->left = NULL;         /* marks this as a string-literal print */
            $$ = n;
        }
    | PRINT LPAREN IDENTIFIER RPAREN SEMI
        {
            /* print a variable — left != NULL signals identifier mode */
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = strdup($3);
            n->left = make_ident($3);   /* non-NULL → identifier print */
            $$ = n;
        }
    | PRINT LPAREN expression RPAREN SEMI
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = NULL;   /* NULL → expression print */
            n->left = $3;
            $$ = n;
        }
    ;

scan_stmt
    : SCAN LPAREN IDENTIFIER RPAREN SEMI
        {
            ASTNode *n = make_node(NODE_SCAN);
            n->sval = strdup($3);
            $$ = n;
        }
    | SCAN LPAREN IDENTIFIER LBRACKET expression RBRACKET RPAREN SEMI
        {
            ASTNode *n = make_node(NODE_SCAN_ARRAY);
            n->sval = strdup($3);
            n->left = $5;   /* index expression */
            $$ = n;
        }
    ;

/* ================================================================== */
/*  Condition                                                          */
/* ================================================================== */

condition
    : expression EQ  expression { $$ = make_binop(NODE_EQ,  $1, $3); }
    | expression NEQ expression { $$ = make_binop(NODE_NEQ, $1, $3); }
    | expression GT  expression { $$ = make_binop(NODE_GT,  $1, $3); }
    | expression LT  expression { $$ = make_binop(NODE_LT,  $1, $3); }
    | expression GE  expression { $$ = make_binop(NODE_GE,  $1, $3); }
    | expression LE  expression { $$ = make_binop(NODE_LE,  $1, $3); }
    ;

/* ================================================================== */
/*  If / Elseif / Else                                                 */
/* ================================================================== */

/*
 * if_stmt builds:
 *
 *   NODE_IF
 *     left  = condition
 *     right = then-body
 *     extra = else_if_part (chain of NODE_ELSEIF / NODE_ELSE / NULL)
 */
if_stmt
    : IF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part
        {
            ASTNode *n = make_node(NODE_IF);
            n->left  = $3;   /* condition  */
            n->right = $6;   /* then body  */
            n->extra = $8;   /* else chain */
            $$ = n;
        }
    ;

else_if_part
    : ELSEIF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part
        {
            ASTNode *n = make_node(NODE_ELSEIF);
            n->left  = $3;
            n->right = $6;
            n->extra = $8;
            $$ = n;
        }
    | ELSE LBRACE statement_list RBRACE
        {
            ASTNode *n = make_node(NODE_ELSE);
            n->left = $3;
            $$ = n;
        }
    | /* empty */ { $$ = NULL; }
    ;

/* ================================================================== */
/*  Switch                                                             */
/* ================================================================== */

/*
 * NODE_SWITCH
 *   left  = switch expression
 *   right = head of case list (linked via ->next)
 */
switch_stmt
    : SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE
        {
            ASTNode *n = make_node(NODE_SWITCH);
            n->left  = $3;   /* switch expression */
            n->right = $6;   /* case list head    */
            $$ = n;
        }
    ;

case_list
    : case_list case_item
        {
            /* append case_item to end of case_list */
            if ($1 == NULL) { $$ = $2; }
            else {
                ASTNode *tail = $1;
                while (tail->next) tail = tail->next;
                tail->next = $2;
                $$ = $1;
            }
        }
    | case_list default_item
        {
            if ($1 == NULL) { $$ = $2; }
            else {
                ASTNode *tail = $1;
                while (tail->next) tail = tail->next;
                tail->next = $2;
                $$ = $1;
            }
        }
    | /* empty */ { $$ = NULL; }
    ;

case_item
    : CASE case_expr COLON statement_list
        {
            /*
             * case_expr is either NODE_CASE or NODE_CASE_RANGE.
             * We attach the body to whichever node was built.
             */
            ASTNode *c = $2;
            if (c->type == NODE_CASE) {
                /* left = value expr (already set), right = body */
                c->right = $4;
            } else {
                /* NODE_CASE_RANGE: left=start, right=end, extra=body */
                c->extra = $4;
            }
            $$ = c;
        }
    ;

case_expr
    : expression
        {
            ASTNode *n = make_node(NODE_CASE);
            n->left = $1;   /* case value expression */
            $$ = n;
        }
    | expression RANGE expression
        {
            ASTNode *n = make_node(NODE_CASE_RANGE);
            n->left  = $1;  /* range start */
            n->right = $3;  /* range end   */
            $$ = n;
        }
    ;

default_item
    : DEFAULT COLON statement_list
        {
            ASTNode *n = make_node(NODE_DEFAULT);
            n->left = $3;   /* body */
            $$ = n;
        }
    ;

/* ================================================================== */
/*  Loops                                                              */
/* ================================================================== */

/*
 * NODE_WHILE
 *   left  = condition
 *   right = body
 *
 * NODE_FOR
 *   left  = init (assignment or declaration node)
 *   right = body
 *   extra = NODE_FOR_PARTS
 *              left  = condition
 *              right = update (assignment node)
 *
 * We reuse NODE_STMT_LIST as a container for the for-parts.
 */

for_init
    : assignment { $$ = $1; }
    | declaration_no_semi { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

for_update
    : assignment { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

loop_stmt
    : WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE
        {
            ASTNode *n = make_node(NODE_WHILE);
            n->left  = $3;   /* condition */
            n->right = $6;   /* body      */
            $$ = n;
        }
     | DO LBRACE statement_list RBRACE WHILE LPAREN condition RPAREN SEMI
        {
            ASTNode *n = make_node(NODE_DO_WHILE);
            n->left  = $3;   /* body      */
            n->right = $7;   /* condition */
            $$ = n;
        }
    | FOR LPAREN for_init SEMI condition SEMI for_update RPAREN
      LBRACE statement_list RBRACE
        {
            /* pack condition + update into a helper node */
            ASTNode *parts = make_node(NODE_STMT_LIST);
            parts->left  = $5;   /* condition */
            parts->right = $7;   /* update    */

            ASTNode *n = make_node(NODE_FOR);
            n->left  = $3;      /* init  */
            n->right = $10;     /* body  */
            n->extra = parts;   /* parts */
            $$ = n;
        }
    ;

/* ================================================================== */
/*  Return                                                             */
/* ================================================================== */

return_stmt
    : RETURN expression
        {
            ASTNode *n = make_node(NODE_RETURN);
            n->left = $2;
            $$ = n;
        }
    ;

%%

/* ------------------------------------------------------------------ */
void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
}

extern FILE *yyin;

int main(int argc, char *argv[]) {
    const char *filename = (argc > 1) ? argv[1] : "input.txt";
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Cannot open input file: %s\n", filename);
        return 1;
    }
    yyin = fp;
    printf("Running Luminix Program...\n\n");
    yyparse();
    printf("\nProgram finished.\n");
    fclose(fp);
    return 0;
}