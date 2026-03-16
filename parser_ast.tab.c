/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser_ast.y"

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


#line 395 "parser_ast.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser_ast.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INCLUDE = 3,                    /* INCLUDE  */
  YYSYMBOL_DEFINE = 4,                     /* DEFINE  */
  YYSYMBOL_HEADER = 5,                     /* HEADER  */
  YYSYMBOL_INT_TYPE = 6,                   /* INT_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 7,                 /* FLOAT_TYPE  */
  YYSYMBOL_DOUBLE_TYPE = 8,                /* DOUBLE_TYPE  */
  YYSYMBOL_CHAR_TYPE = 9,                  /* CHAR_TYPE  */
  YYSYMBOL_BOOL_TYPE = 10,                 /* BOOL_TYPE  */
  YYSYMBOL_VOID_TYPE = 11,                 /* VOID_TYPE  */
  YYSYMBOL_LONG_TYPE = 12,                 /* LONG_TYPE  */
  YYSYMBOL_SHORT_TYPE = 13,                /* SHORT_TYPE  */
  YYSYMBOL_UNSIGNED_TYPE = 14,             /* UNSIGNED_TYPE  */
  YYSYMBOL_CONST = 15,                     /* CONST  */
  YYSYMBOL_STRUCT = 16,                    /* STRUCT  */
  YYSYMBOL_UNION = 17,                     /* UNION  */
  YYSYMBOL_TYPEDEF = 18,                   /* TYPEDEF  */
  YYSYMBOL_ENUM = 19,                      /* ENUM  */
  YYSYMBOL_IF = 20,                        /* IF  */
  YYSYMBOL_ELSE = 21,                      /* ELSE  */
  YYSYMBOL_ELSEIF = 22,                    /* ELSEIF  */
  YYSYMBOL_SWITCH = 23,                    /* SWITCH  */
  YYSYMBOL_CASE = 24,                      /* CASE  */
  YYSYMBOL_DEFAULT = 25,                   /* DEFAULT  */
  YYSYMBOL_FOR = 26,                       /* FOR  */
  YYSYMBOL_WHILE = 27,                     /* WHILE  */
  YYSYMBOL_DO = 28,                        /* DO  */
  YYSYMBOL_BREAK = 29,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 30,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 31,                    /* RETURN  */
  YYSYMBOL_MAIN = 32,                      /* MAIN  */
  YYSYMBOL_PRINT = 33,                     /* PRINT  */
  YYSYMBOL_SCAN = 34,                      /* SCAN  */
  YYSYMBOL_TRUE_LITERAL = 35,              /* TRUE_LITERAL  */
  YYSYMBOL_FALSE_LITERAL = 36,             /* FALSE_LITERAL  */
  YYSYMBOL_POW = 37,                       /* POW  */
  YYSYMBOL_SQRT = 38,                      /* SQRT  */
  YYSYMBOL_ABS = 39,                       /* ABS  */
  YYSYMBOL_FLOOR = 40,                     /* FLOOR  */
  YYSYMBOL_CEIL = 41,                      /* CEIL  */
  YYSYMBOL_EQ = 42,                        /* EQ  */
  YYSYMBOL_NEQ = 43,                       /* NEQ  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_LE = 45,                        /* LE  */
  YYSYMBOL_GT = 46,                        /* GT  */
  YYSYMBOL_LT = 47,                        /* LT  */
  YYSYMBOL_AND = 48,                       /* AND  */
  YYSYMBOL_OR = 49,                        /* OR  */
  YYSYMBOL_NOT = 50,                       /* NOT  */
  YYSYMBOL_INC = 51,                       /* INC  */
  YYSYMBOL_DEC = 52,                       /* DEC  */
  YYSYMBOL_PLUS = 53,                      /* PLUS  */
  YYSYMBOL_MINUS = 54,                     /* MINUS  */
  YYSYMBOL_MUL = 55,                       /* MUL  */
  YYSYMBOL_DIV = 56,                       /* DIV  */
  YYSYMBOL_MOD = 57,                       /* MOD  */
  YYSYMBOL_ASSIGN = 58,                    /* ASSIGN  */
  YYSYMBOL_BIT_AND = 59,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 60,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 61,                   /* BIT_XOR  */
  YYSYMBOL_BIT_NOT = 62,                   /* BIT_NOT  */
  YYSYMBOL_SHL = 63,                       /* SHL  */
  YYSYMBOL_SHR = 64,                       /* SHR  */
  YYSYMBOL_SEMI = 65,                      /* SEMI  */
  YYSYMBOL_COMMA = 66,                     /* COMMA  */
  YYSYMBOL_COLON = 67,                     /* COLON  */
  YYSYMBOL_LPAREN = 68,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 69,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 70,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 71,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 72,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 73,                  /* RBRACKET  */
  YYSYMBOL_RANGE = 74,                     /* RANGE  */
  YYSYMBOL_INT_LITERAL = 75,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 76,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 77,            /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 78,              /* CHAR_LITERAL  */
  YYSYMBOL_IDENTIFIER = 79,                /* IDENTIFIER  */
  YYSYMBOL_UNARY = 80,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_program = 82,                   /* program  */
  YYSYMBOL_preprocessor_list = 83,         /* preprocessor_list  */
  YYSYMBOL_preprocessor = 84,              /* preprocessor  */
  YYSYMBOL_main_function = 85,             /* main_function  */
  YYSYMBOL_statement_list = 86,            /* statement_list  */
  YYSYMBOL_statement = 87,                 /* statement  */
  YYSYMBOL_declaration = 88,               /* declaration  */
  YYSYMBOL_array_size = 89,                /* array_size  */
  YYSYMBOL_type = 90,                      /* type  */
  YYSYMBOL_identifier_list = 91,           /* identifier_list  */
  YYSYMBOL_assignment = 92,                /* assignment  */
  YYSYMBOL_array_assignment = 93,          /* array_assignment  */
  YYSYMBOL_expression = 94,                /* expression  */
  YYSYMBOL_term = 95,                      /* term  */
  YYSYMBOL_factor = 96,                    /* factor  */
  YYSYMBOL_primary = 97,                   /* primary  */
  YYSYMBOL_array_access = 98,              /* array_access  */
  YYSYMBOL_function_call = 99,             /* function_call  */
  YYSYMBOL_print_stmt = 100,               /* print_stmt  */
  YYSYMBOL_scan_stmt = 101,                /* scan_stmt  */
  YYSYMBOL_if_stmt = 102,                  /* if_stmt  */
  YYSYMBOL_else_if_part = 103,             /* else_if_part  */
  YYSYMBOL_switch_stmt = 104,              /* switch_stmt  */
  YYSYMBOL_105_1 = 105,                    /* $@1  */
  YYSYMBOL_case_list = 106,                /* case_list  */
  YYSYMBOL_case_item = 107,                /* case_item  */
  YYSYMBOL_108_2 = 108,                    /* $@2  */
  YYSYMBOL_case_expr = 109,                /* case_expr  */
  YYSYMBOL_default_item = 110,             /* default_item  */
  YYSYMBOL_111_3 = 111,                    /* $@3  */
  YYSYMBOL_condition = 112,                /* condition  */
  YYSYMBOL_loop_stmt = 113,                /* loop_stmt  */
  YYSYMBOL_return_stmt = 114               /* return_stmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   443

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  225

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   395,   395,   405,   415,   421,   422,   426,   437,   447,
     453,   455,   457,   459,   461,   463,   465,   467,   473,   475,
     480,   482,   491,   504,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   520,   529,   538,   548,   561,   572,   582,
     598,   607,   616,   624,   629,   638,   652,   666,   671,   676,
     683,   690,   696,   702,   708,   715,   717,   719,   724,   733,
     748,   758,   767,   776,   785,   799,   815,   830,   842,   862,
     881,   911,   934,   939,   948,   947,   970,   979,   989,   996,
     995,  1015,  1033,  1064,  1063,  1094,  1103,  1112,  1121,  1130,
    1139,  1153,  1160,  1173
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INCLUDE", "DEFINE",
  "HEADER", "INT_TYPE", "FLOAT_TYPE", "DOUBLE_TYPE", "CHAR_TYPE",
  "BOOL_TYPE", "VOID_TYPE", "LONG_TYPE", "SHORT_TYPE", "UNSIGNED_TYPE",
  "CONST", "STRUCT", "UNION", "TYPEDEF", "ENUM", "IF", "ELSE", "ELSEIF",
  "SWITCH", "CASE", "DEFAULT", "FOR", "WHILE", "DO", "BREAK", "CONTINUE",
  "RETURN", "MAIN", "PRINT", "SCAN", "TRUE_LITERAL", "FALSE_LITERAL",
  "POW", "SQRT", "ABS", "FLOOR", "CEIL", "EQ", "NEQ", "GE", "LE", "GT",
  "LT", "AND", "OR", "NOT", "INC", "DEC", "PLUS", "MINUS", "MUL", "DIV",
  "MOD", "ASSIGN", "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT", "SHL", "SHR",
  "SEMI", "COMMA", "COLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "RANGE", "INT_LITERAL", "FLOAT_LITERAL",
  "STRING_LITERAL", "CHAR_LITERAL", "IDENTIFIER", "UNARY", "$accept",
  "program", "preprocessor_list", "preprocessor", "main_function",
  "statement_list", "statement", "declaration", "array_size", "type",
  "identifier_list", "assignment", "array_assignment", "expression",
  "term", "factor", "primary", "array_access", "function_call",
  "print_stmt", "scan_stmt", "if_stmt", "else_if_part", "switch_stmt",
  "$@1", "case_list", "case_item", "$@2", "case_expr", "default_item",
  "$@3", "condition", "loop_stmt", "return_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-102)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -102,     3,     7,  -102,     9,   -60,    -8,  -102,  -102,  -102,
     -26,     8,  -102,    -4,  -102,    79,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,    26,    35,    39,    41,     6,
      -3,    50,    52,  -102,    12,  -102,  -102,    59,    77,    92,
    -102,  -102,  -102,  -102,  -102,   116,    -3,    -3,    65,    -3,
    -102,  -102,  -102,    84,    98,   114,   117,   119,   364,    -3,
    -102,  -102,  -102,   121,   125,   108,  -102,  -102,  -102,  -102,
     352,   105,    -3,    -3,   -50,   123,  -102,  -102,  -102,   185,
     122,   -41,   137,   145,   142,    -3,    -3,    -3,    -3,    -3,
     108,     0,    -3,   364,   364,   364,   364,   364,   144,    68,
      47,    87,   125,   -27,    -3,   135,   141,  -102,    -3,    -3,
      -3,    -3,    -3,    -3,   147,  -102,    -3,   150,    95,    70,
      74,    76,    82,  -102,   -23,   108,   108,  -102,  -102,  -102,
     157,   159,   168,   170,    -3,    53,   101,   -51,  -102,  -102,
     164,   125,   125,   125,   125,   125,   125,  -102,   166,   175,
    -102,    -3,  -102,  -102,  -102,  -102,   169,  -102,  -102,  -102,
    -102,    -6,    -3,    -3,   135,   -47,   163,  -102,    65,   192,
      93,    -3,   174,   125,    42,  -102,  -102,   141,     2,   -19,
     186,  -102,  -102,    44,   179,   196,   183,   187,   190,  -102,
      -3,   193,  -102,  -102,  -102,   191,  -102,  -102,    -3,   199,
    -102,    -3,   -33,   200,  -102,  -102,   125,  -102,   239,   214,
      -3,  -102,  -102,   268,  -102,   215,   125,  -102,   344,  -102,
    -102,   344,   315,     2,  -102
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,     3,     2,     5,
       0,     0,     6,     0,     9,     0,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     0,     8,    10,     0,     0,     0,
      13,    14,    15,    16,    18,     0,     0,     0,     0,     0,
      17,    52,    53,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    54,    49,    93,    43,    47,    48,    57,    56,
       0,     0,     0,     0,    33,     0,    11,    12,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,    37,     0,     0,     0,     0,    20,     0,     0,
       0,     0,     0,     0,     0,    74,     0,     0,     0,     0,
       0,     0,     0,    55,     0,    40,    41,    44,    45,    46,
       0,     0,     0,     0,     0,     0,    34,    33,    35,    23,
       0,    85,    86,    89,    90,    87,    88,     9,     0,     0,
       9,     0,    61,    62,    63,    64,    58,    65,    66,    67,
      68,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,    38,     0,    36,    21,     0,    73,     0,
       0,    91,    60,     0,     0,     0,     0,     0,     0,    70,
       0,     0,    75,    76,    77,     0,    59,    69,     0,     0,
       9,     0,    81,     0,    83,     9,    39,    22,     0,     0,
       0,    79,     9,     0,    72,     0,    82,     9,    84,    92,
       9,    80,     0,    73,    71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -102,  -102,  -102,  -102,  -102,   -86,  -102,  -102,   107,  -102,
    -101,   -46,  -102,   -30,   -49,   112,  -102,  -102,  -102,  -102,
    -102,  -102,    46,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,   -48,  -102,  -102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     7,     8,    15,    35,    36,   140,    37,
      75,    38,    39,    79,    65,    66,    67,    68,    69,    40,
      41,    42,   189,    43,   148,   179,   193,   217,   203,   194,
     212,    80,    44,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      64,    84,    83,     3,   138,   190,   191,   104,   104,    90,
       4,     5,    93,    94,     9,   105,   105,    81,   176,    10,
      93,    94,   106,   187,   188,   177,    93,    94,   115,    91,
      93,    94,    51,    52,    53,    54,    55,    56,    57,     6,
     100,   210,   102,   103,   125,   126,   135,    93,    94,    12,
     156,    58,   192,    93,    94,   118,   119,   120,   121,   122,
      11,   166,   124,   175,   169,    59,    14,   172,   149,   123,
      72,    50,    60,    61,   136,    62,    63,    13,   141,   142,
     143,   144,   145,   146,    73,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    46,    93,    94,    93,    94,    25,
      93,    94,    26,    47,   161,    27,    28,    48,    29,    49,
      30,   162,    31,    32,   208,   185,   132,   196,    70,   213,
      71,   170,   180,    93,    94,   163,   218,    93,    94,    93,
      94,   221,   173,   174,   222,    93,    94,   131,    74,   152,
      92,   183,    76,   153,    82,   154,    93,    94,    93,    94,
      33,   155,    85,   209,    93,    94,   133,    77,    34,   134,
     202,   151,   182,    95,    96,    97,    86,   164,   206,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    93,    94,
     216,    78,    87,    25,   101,    88,    26,    89,   107,    27,
      28,   114,    29,    92,    30,    72,    31,    32,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   127,   128,   129,
     116,   117,    25,   130,   137,    26,   139,   147,    27,    28,
     150,    29,   157,    30,   158,    31,    32,   108,   109,   110,
     111,   112,   113,   159,   178,   160,   167,   165,    93,    94,
     168,   171,    34,   184,   197,    16,    17,    18,    19,    20,
      21,    22,    23,    24,   198,   195,   199,   200,   201,    25,
     204,   205,    26,   181,   207,    27,    28,   211,    29,   224,
      30,    34,    31,    32,    16,    17,    18,    19,    20,    21,
      22,    23,    24,   215,   186,   220,     0,     0,    25,     0,
       0,    26,     0,     0,    27,    28,     0,    29,     0,    30,
       0,    31,    32,     0,     0,     0,     0,     0,     0,     0,
     214,     0,     0,     0,     0,     0,     0,     0,    34,     0,
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,     0,     0,     0,     0,    25,     0,     0,    26,   219,
       0,    27,    28,     0,    29,     0,    30,    34,    31,    32,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     0,
       0,     0,     0,     0,    25,     0,     0,    26,     0,     0,
      27,    28,     0,    29,     0,    30,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,   223,    51,    52,    53,
      54,    55,    56,    57,    34,     0,     0,     0,     0,    51,
      52,    53,    54,    55,    56,    57,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      59,     0,     0,    34,     0,     0,     0,    60,    61,    98,
      62,    99,    59,     0,     0,     0,     0,     0,     0,    60,
      61,     0,    62,    63
};

static const yytype_int16 yycheck[] =
{
      30,    49,    48,     0,   105,    24,    25,    58,    58,    58,
       3,     4,    53,    54,     5,    66,    66,    47,    65,    79,
      53,    54,    72,    21,    22,    72,    53,    54,    69,    59,
      53,    54,    35,    36,    37,    38,    39,    40,    41,    32,
      70,    74,    72,    73,    93,    94,    73,    53,    54,    75,
      73,    54,    71,    53,    54,    85,    86,    87,    88,    89,
      68,   147,    92,   164,   150,    68,    70,    73,   116,    69,
      58,    65,    75,    76,   104,    78,    79,    69,   108,   109,
     110,   111,   112,   113,    72,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    68,    53,    54,    53,    54,    20,
      53,    54,    23,    68,   134,    26,    27,    68,    29,    68,
      31,    58,    33,    34,   200,    73,    69,    73,    68,   205,
      68,   151,   168,    53,    54,    72,   212,    53,    54,    53,
      54,   217,   162,   163,   220,    53,    54,    69,    79,    69,
      72,   171,    65,    69,    79,    69,    53,    54,    53,    54,
      71,    69,    68,   201,    53,    54,    69,    65,    79,    72,
     190,    66,    69,    55,    56,    57,    68,    66,   198,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    53,    54,
     210,    65,    68,    20,    79,    68,    23,    68,    65,    26,
      27,    69,    29,    72,    31,    58,    33,    34,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    95,    96,    97,
      65,    69,    20,    69,    79,    23,    75,    70,    26,    27,
      70,    29,    65,    31,    65,    33,    34,    42,    43,    44,
      45,    46,    47,    65,    71,    65,    70,    73,    53,    54,
      65,    72,    79,    69,    65,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    58,    69,    73,    70,    68,    20,
      67,    70,    23,    71,    65,    26,    27,    67,    29,   223,
      31,    79,    33,    34,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    69,   177,    70,    -1,    -1,    20,    -1,
      -1,    23,    -1,    -1,    26,    27,    -1,    29,    -1,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    23,    71,
      -1,    26,    27,    -1,    29,    -1,    31,    79,    33,    34,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    23,    -1,    -1,
      26,    27,    -1,    29,    -1,    31,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    35,    36,    37,
      38,    39,    40,    41,    79,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    79,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    68,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    -1,    78,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    82,    83,     0,     3,     4,    32,    84,    85,     5,
      79,    68,    75,    69,    70,    86,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    20,    23,    26,    27,    29,
      31,    33,    34,    71,    79,    87,    88,    90,    92,    93,
     100,   101,   102,   104,   113,   114,    68,    68,    68,    68,
      65,    35,    36,    37,    38,    39,    40,    41,    54,    68,
      75,    76,    78,    79,    94,    95,    96,    97,    98,    99,
      68,    68,    58,    72,    79,    91,    65,    65,    65,    94,
     112,    94,    79,    92,   112,    68,    68,    68,    68,    68,
      95,    94,    72,    53,    54,    55,    56,    57,    77,    79,
      94,    79,    94,    94,    58,    66,    72,    65,    42,    43,
      44,    45,    46,    47,    69,    69,    65,    69,    94,    94,
      94,    94,    94,    69,    94,    95,    95,    96,    96,    96,
      69,    69,    69,    69,    72,    73,    94,    79,    91,    75,
      89,    94,    94,    94,    94,    94,    94,    70,   105,   112,
      70,    66,    69,    69,    69,    69,    73,    65,    65,    65,
      65,    94,    58,    72,    66,    73,    86,    70,    65,    86,
      94,    72,    73,    94,    94,    91,    65,    72,    71,   106,
      92,    71,    69,    94,    69,    73,    89,    21,    22,   103,
      24,    25,    71,   107,   110,    69,    73,    65,    58,    73,
      70,    68,    94,   109,    67,    70,    94,    65,    86,   112,
      74,    67,   111,    86,    71,    69,    94,   108,    86,    71,
      70,    86,    86,    71,   103
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      88,    88,    88,    89,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    92,    93,    93,
      94,    94,    94,    94,    95,    95,    95,    95,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    98,    98,
      99,    99,    99,    99,    99,   100,   100,   100,   101,   101,
     102,   103,   103,   103,   105,   104,   106,   106,   106,   108,
     107,   109,   109,   111,   110,   112,   112,   112,   112,   112,
     112,   113,   113,   114
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     3,     6,     2,     0,
       1,     2,     2,     1,     1,     1,     1,     2,     1,     2,
       3,     6,     9,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     5,     3,     6,     9,
       3,     3,     2,     1,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     4,     7,
       6,     4,     4,     4,     4,     5,     5,     5,     5,     8,
       8,     8,     4,     0,     0,     8,     2,     2,     0,     0,
       5,     1,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     7,    11,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: preprocessor_list main_function  */
#line 396 "parser_ast.y"
        {
            ASTNode *prog = create_node(NODE_PROGRAM);
            if ((yyvsp[-1].node)) add_child(prog, (yyvsp[-1].node));
            if ((yyvsp[0].node)) add_child(prog, (yyvsp[0].node));
            (yyval.node) = prog;
        }
#line 1699 "parser_ast.tab.c"
    break;

  case 3: /* preprocessor_list: preprocessor_list preprocessor  */
#line 406 "parser_ast.y"
        {
            ASTNode *list = (yyvsp[-1].node);
            if (!list) {
                list = create_node(NODE_STATEMENT_LIST);
            }
            if ((yyvsp[0].node)) add_child(list, (yyvsp[0].node));
            (yyval.node) = list;
        }
#line 1712 "parser_ast.tab.c"
    break;

  case 4: /* preprocessor_list: %empty  */
#line 415 "parser_ast.y"
        {
            (yyval.node) = NULL;
        }
#line 1720 "parser_ast.tab.c"
    break;

  case 5: /* preprocessor: INCLUDE HEADER  */
#line 421 "parser_ast.y"
                     { (yyval.node) = NULL; }
#line 1726 "parser_ast.tab.c"
    break;

  case 6: /* preprocessor: DEFINE IDENTIFIER INT_LITERAL  */
#line 422 "parser_ast.y"
                                    { (yyval.node) = NULL; }
#line 1732 "parser_ast.tab.c"
    break;

  case 7: /* main_function: MAIN LPAREN RPAREN LBRACE statement_list RBRACE  */
#line 427 "parser_ast.y"
        {
            ASTNode *main_node = create_node(NODE_STATEMENT_LIST);
            if ((yyvsp[-1].node)) {
                main_node = (yyvsp[-1].node);
            }
            (yyval.node) = main_node;
        }
#line 1744 "parser_ast.tab.c"
    break;

  case 8: /* statement_list: statement_list statement  */
#line 438 "parser_ast.y"
        {
            ASTNode *list = (yyvsp[-1].node);
            if (!list) {
                list = create_node(NODE_STATEMENT_LIST);
            }
            if ((yyvsp[0].node)) add_child(list, (yyvsp[0].node));
            (yyval.node) = list;
        }
#line 1757 "parser_ast.tab.c"
    break;

  case 9: /* statement_list: %empty  */
#line 447 "parser_ast.y"
        {
            (yyval.node) = NULL;
        }
#line 1765 "parser_ast.tab.c"
    break;

  case 10: /* statement: declaration  */
#line 454 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1771 "parser_ast.tab.c"
    break;

  case 11: /* statement: assignment SEMI  */
#line 456 "parser_ast.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1777 "parser_ast.tab.c"
    break;

  case 12: /* statement: array_assignment SEMI  */
#line 458 "parser_ast.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1783 "parser_ast.tab.c"
    break;

  case 13: /* statement: print_stmt  */
#line 460 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1789 "parser_ast.tab.c"
    break;

  case 14: /* statement: scan_stmt  */
#line 462 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1795 "parser_ast.tab.c"
    break;

  case 15: /* statement: if_stmt  */
#line 464 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1801 "parser_ast.tab.c"
    break;

  case 16: /* statement: switch_stmt  */
#line 466 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1807 "parser_ast.tab.c"
    break;

  case 17: /* statement: BREAK SEMI  */
#line 468 "parser_ast.y"
        {
            if(execute_flag) break_flag = 1;
            ASTNode *brk = create_node(NODE_BREAK);
            (yyval.node) = brk;
        }
#line 1817 "parser_ast.tab.c"
    break;

  case 18: /* statement: loop_stmt  */
#line 474 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1823 "parser_ast.tab.c"
    break;

  case 19: /* statement: return_stmt SEMI  */
#line 476 "parser_ast.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1829 "parser_ast.tab.c"
    break;

  case 20: /* declaration: type identifier_list SEMI  */
#line 481 "parser_ast.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1835 "parser_ast.tab.c"
    break;

  case 21: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET SEMI  */
#line 483 "parser_ast.y"
        {
            if(execute_flag) declare_array((yyvsp[-4].sval),(yyvsp[-2].ival));
            ASTNode *decl = create_node(NODE_ARRAY_DECL_1D);
            strcpy(decl->identifier, (yyvsp[-4].sval));
            decl->array_size = (yyvsp[-2].ival);
            decl->data_type = current_decl_type;
            (yyval.node) = decl;
        }
#line 1848 "parser_ast.tab.c"
    break;

  case 22: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET LBRACKET array_size RBRACKET SEMI  */
#line 492 "parser_ast.y"
        {
            if(execute_flag) declare_2d_array((yyvsp[-7].sval),(yyvsp[-5].ival),(yyvsp[-2].ival));
            ASTNode *decl = create_node(NODE_ARRAY_DECL_2D);
            strcpy(decl->identifier, (yyvsp[-7].sval));
            decl->array_rows = (yyvsp[-5].ival);
            decl->array_cols = (yyvsp[-2].ival);
            decl->data_type = current_decl_type;
            (yyval.node) = decl;
        }
#line 1862 "parser_ast.tab.c"
    break;

  case 23: /* array_size: INT_LITERAL  */
#line 504 "parser_ast.y"
                  { (yyval.ival)=(yyvsp[0].ival); }
#line 1868 "parser_ast.tab.c"
    break;

  case 24: /* type: INT_TYPE  */
#line 508 "parser_ast.y"
                        { current_decl_type = 0; }
#line 1874 "parser_ast.tab.c"
    break;

  case 25: /* type: FLOAT_TYPE  */
#line 509 "parser_ast.y"
                        { current_decl_type = 0; }
#line 1880 "parser_ast.tab.c"
    break;

  case 26: /* type: DOUBLE_TYPE  */
#line 510 "parser_ast.y"
                        { current_decl_type = 0; }
#line 1886 "parser_ast.tab.c"
    break;

  case 27: /* type: CHAR_TYPE  */
#line 511 "parser_ast.y"
                        { current_decl_type = 1; }
#line 1892 "parser_ast.tab.c"
    break;

  case 28: /* type: BOOL_TYPE  */
#line 512 "parser_ast.y"
                        { current_decl_type = 0; }
#line 1898 "parser_ast.tab.c"
    break;

  case 29: /* type: VOID_TYPE  */
#line 513 "parser_ast.y"
                        { current_decl_type = 0; }
#line 1904 "parser_ast.tab.c"
    break;

  case 30: /* type: LONG_TYPE  */
#line 514 "parser_ast.y"
                        { current_decl_type = 0; }
#line 1910 "parser_ast.tab.c"
    break;

  case 31: /* type: SHORT_TYPE  */
#line 515 "parser_ast.y"
                        { current_decl_type = 0; }
#line 1916 "parser_ast.tab.c"
    break;

  case 32: /* type: UNSIGNED_TYPE  */
#line 516 "parser_ast.y"
                        { current_decl_type = 0; }
#line 1922 "parser_ast.tab.c"
    break;

  case 33: /* identifier_list: IDENTIFIER  */
#line 521 "parser_ast.y"
        {
            if(execute_flag) set_symbol((yyvsp[0].sval),0);
            ASTNode *decl = create_node(NODE_DECLARATION);
            strcpy(decl->identifier, (yyvsp[0].sval));
            decl->value.double_val = 0;
            decl->data_type = current_decl_type;
            (yyval.node) = decl;
        }
#line 1935 "parser_ast.tab.c"
    break;

  case 34: /* identifier_list: IDENTIFIER ASSIGN expression  */
#line 530 "parser_ast.y"
        {
            if(execute_flag) set_symbol((yyvsp[-2].sval),(yyvsp[0].node)->value.double_val);
            ASTNode *decl = create_node(NODE_DECLARATION);
            strcpy(decl->identifier, (yyvsp[-2].sval));
            add_child(decl, (yyvsp[0].node));
            decl->data_type = current_decl_type;
            (yyval.node) = decl;
        }
#line 1948 "parser_ast.tab.c"
    break;

  case 35: /* identifier_list: IDENTIFIER COMMA identifier_list  */
#line 539 "parser_ast.y"
        {
            if(execute_flag) set_symbol((yyvsp[-2].sval),0);
            ASTNode *decl = create_node(NODE_DECLARATION);
            strcpy(decl->identifier, (yyvsp[-2].sval));
            decl->value.double_val = 0;
            decl->data_type = current_decl_type;
            add_child(decl, (yyvsp[0].node));
            (yyval.node) = decl;
        }
#line 1962 "parser_ast.tab.c"
    break;

  case 36: /* identifier_list: IDENTIFIER ASSIGN expression COMMA identifier_list  */
#line 549 "parser_ast.y"
        {
            if(execute_flag) set_symbol((yyvsp[-4].sval),(yyvsp[-2].node)->value.double_val);
            ASTNode *decl = create_node(NODE_DECLARATION);
            strcpy(decl->identifier, (yyvsp[-4].sval));
            add_child(decl, (yyvsp[-2].node));
            add_child(decl, (yyvsp[0].node));
            decl->data_type = current_decl_type;
            (yyval.node) = decl;
        }
#line 1976 "parser_ast.tab.c"
    break;

  case 37: /* assignment: IDENTIFIER ASSIGN expression  */
#line 562 "parser_ast.y"
        {
            if(execute_flag) set_symbol((yyvsp[-2].sval),(yyvsp[0].node)->value.double_val);
            ASTNode *assign = create_node(NODE_ASSIGNMENT);
            strcpy(assign->identifier, (yyvsp[-2].sval));
            add_child(assign, (yyvsp[0].node));
            (yyval.node) = assign;
        }
#line 1988 "parser_ast.tab.c"
    break;

  case 38: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression  */
#line 573 "parser_ast.y"
        {
            if(execute_flag) set_array_element((yyvsp[-5].sval),(int)(yyvsp[-3].node)->value.double_val,(yyvsp[0].node)->value.double_val);
            ASTNode *assign = create_node(NODE_ARRAY_ASSIGNMENT);
            strcpy(assign->identifier, (yyvsp[-5].sval));
            add_child(assign, (yyvsp[-3].node));
            add_child(assign, (yyvsp[0].node));
            assign->array_dimensions = 1;
            (yyval.node) = assign;
        }
#line 2002 "parser_ast.tab.c"
    break;

  case 39: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET ASSIGN expression  */
#line 583 "parser_ast.y"
        {
            if(execute_flag) set_array2d_element((yyvsp[-8].sval),(int)(yyvsp[-6].node)->value.double_val,(int)(yyvsp[-3].node)->value.double_val,(yyvsp[0].node)->value.double_val);
            ASTNode *assign = create_node(NODE_ARRAY_ASSIGNMENT);
            strcpy(assign->identifier, (yyvsp[-8].sval));
            add_child(assign, (yyvsp[-6].node));
            add_child(assign, (yyvsp[-3].node));
            add_child(assign, (yyvsp[0].node));
            assign->array_dimensions = 2;
            (yyval.node) = assign;
        }
#line 2017 "parser_ast.tab.c"
    break;

  case 40: /* expression: expression PLUS term  */
#line 599 "parser_ast.y"
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_PLUS;
            add_child(expr, (yyvsp[-2].node));
            add_child(expr, (yyvsp[0].node));
            expr->value.double_val = (yyvsp[-2].node)->value.double_val + (yyvsp[0].node)->value.double_val;
            (yyval.node) = expr;
        }
#line 2030 "parser_ast.tab.c"
    break;

  case 41: /* expression: expression MINUS term  */
#line 608 "parser_ast.y"
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_MINUS;
            add_child(expr, (yyvsp[-2].node));
            add_child(expr, (yyvsp[0].node));
            expr->value.double_val = (yyvsp[-2].node)->value.double_val - (yyvsp[0].node)->value.double_val;
            (yyval.node) = expr;
        }
#line 2043 "parser_ast.tab.c"
    break;

  case 42: /* expression: MINUS term  */
#line 617 "parser_ast.y"
        {
            ASTNode *expr = create_node(NODE_UNARY_OP);
            expr->operator = OP_NEG;
            add_child(expr, (yyvsp[0].node));
            expr->value.double_val = -(yyvsp[0].node)->value.double_val;
            (yyval.node) = expr;
        }
#line 2055 "parser_ast.tab.c"
    break;

  case 43: /* expression: term  */
#line 625 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2061 "parser_ast.tab.c"
    break;

  case 44: /* term: term MUL factor  */
#line 630 "parser_ast.y"
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_MUL;
            add_child(expr, (yyvsp[-2].node));
            add_child(expr, (yyvsp[0].node));
            expr->value.double_val = (yyvsp[-2].node)->value.double_val * (yyvsp[0].node)->value.double_val;
            (yyval.node) = expr;
        }
#line 2074 "parser_ast.tab.c"
    break;

  case 45: /* term: term DIV factor  */
#line 639 "parser_ast.y"
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_DIV;
            add_child(expr, (yyvsp[-2].node));
            add_child(expr, (yyvsp[0].node));
            if((yyvsp[0].node)->value.double_val!=0) {
                expr->value.double_val = (yyvsp[-2].node)->value.double_val / (yyvsp[0].node)->value.double_val;
            } else {
                yyerror("Division by zero");
                expr->value.double_val = 0;
            }
            (yyval.node) = expr;
        }
#line 2092 "parser_ast.tab.c"
    break;

  case 46: /* term: term MOD factor  */
#line 653 "parser_ast.y"
        {
            ASTNode *expr = create_node(NODE_BINARY_OP);
            expr->operator = OP_MOD;
            add_child(expr, (yyvsp[-2].node));
            add_child(expr, (yyvsp[0].node));
            if((int)(yyvsp[0].node)->value.double_val!=0) {
                expr->value.double_val = (int)(yyvsp[-2].node)->value.double_val % (int)(yyvsp[0].node)->value.double_val;
            } else {
                yyerror("Modulo by zero");
                expr->value.double_val = 0;
            }
            (yyval.node) = expr;
        }
#line 2110 "parser_ast.tab.c"
    break;

  case 47: /* term: factor  */
#line 667 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2116 "parser_ast.tab.c"
    break;

  case 48: /* factor: primary  */
#line 672 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2122 "parser_ast.tab.c"
    break;

  case 49: /* primary: IDENTIFIER  */
#line 677 "parser_ast.y"
        {
            ASTNode *id = create_node(NODE_IDENTIFIER);
            strcpy(id->identifier, (yyvsp[0].sval));
            id->value.double_val = get_symbol((yyvsp[0].sval));
            (yyval.node) = id;
        }
#line 2133 "parser_ast.tab.c"
    break;

  case 50: /* primary: INT_LITERAL  */
#line 684 "parser_ast.y"
        {
            ASTNode *lit = create_node(NODE_LITERAL_INT);
            lit->value.int_val = (yyvsp[0].ival);
            lit->value.double_val = (yyvsp[0].ival);
            (yyval.node) = lit;
        }
#line 2144 "parser_ast.tab.c"
    break;

  case 51: /* primary: FLOAT_LITERAL  */
#line 691 "parser_ast.y"
        {
            ASTNode *lit = create_node(NODE_LITERAL_FLOAT);
            lit->value.double_val = (yyvsp[0].fval);
            (yyval.node) = lit;
        }
#line 2154 "parser_ast.tab.c"
    break;

  case 52: /* primary: TRUE_LITERAL  */
#line 697 "parser_ast.y"
        {
            ASTNode *lit = create_node(NODE_LITERAL_BOOL);
            lit->value.double_val = 1;
            (yyval.node) = lit;
        }
#line 2164 "parser_ast.tab.c"
    break;

  case 53: /* primary: FALSE_LITERAL  */
#line 703 "parser_ast.y"
        {
            ASTNode *lit = create_node(NODE_LITERAL_BOOL);
            lit->value.double_val = 0;
            (yyval.node) = lit;
        }
#line 2174 "parser_ast.tab.c"
    break;

  case 54: /* primary: CHAR_LITERAL  */
#line 709 "parser_ast.y"
        {
            ASTNode *lit = create_node(NODE_LITERAL_CHAR);
            lit->value.char_val = (yyvsp[0].cval);
            lit->value.double_val = (yyvsp[0].cval);
            (yyval.node) = lit;
        }
#line 2185 "parser_ast.tab.c"
    break;

  case 55: /* primary: LPAREN expression RPAREN  */
#line 716 "parser_ast.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 2191 "parser_ast.tab.c"
    break;

  case 56: /* primary: function_call  */
#line 718 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2197 "parser_ast.tab.c"
    break;

  case 57: /* primary: array_access  */
#line 720 "parser_ast.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2203 "parser_ast.tab.c"
    break;

  case 58: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 725 "parser_ast.y"
        {
            ASTNode *access = create_node(NODE_ARRAY_ACCESS);
            strcpy(access->identifier, (yyvsp[-3].sval));
            add_child(access, (yyvsp[-1].node));
            access->value.double_val = get_array_element((yyvsp[-3].sval),(int)(yyvsp[-1].node)->value.double_val);
            access->array_dimensions = 1;
            (yyval.node) = access;
        }
#line 2216 "parser_ast.tab.c"
    break;

  case 59: /* array_access: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET  */
#line 734 "parser_ast.y"
        {
            ASTNode *access = create_node(NODE_ARRAY_ACCESS);
            strcpy(access->identifier, (yyvsp[-6].sval));
            add_child(access, (yyvsp[-4].node));
            add_child(access, (yyvsp[-1].node));
            access->value.double_val = get_array2d_element((yyvsp[-6].sval),(int)(yyvsp[-4].node)->value.double_val,(int)(yyvsp[-1].node)->value.double_val);
            access->array_dimensions = 2;
            (yyval.node) = access;
        }
#line 2230 "parser_ast.tab.c"
    break;

  case 60: /* function_call: POW LPAREN expression COMMA expression RPAREN  */
#line 749 "parser_ast.y"
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_POW;
            add_child(func, (yyvsp[-3].node));
            add_child(func, (yyvsp[-1].node));
            func->arg_count = 2;
            func->value.double_val = pow((yyvsp[-3].node)->value.double_val, (yyvsp[-1].node)->value.double_val);
            (yyval.node) = func;
        }
#line 2244 "parser_ast.tab.c"
    break;

  case 61: /* function_call: SQRT LPAREN expression RPAREN  */
#line 759 "parser_ast.y"
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_SQRT;
            add_child(func, (yyvsp[-1].node));
            func->arg_count = 1;
            func->value.double_val = sqrt((yyvsp[-1].node)->value.double_val);
            (yyval.node) = func;
        }
#line 2257 "parser_ast.tab.c"
    break;

  case 62: /* function_call: ABS LPAREN expression RPAREN  */
#line 768 "parser_ast.y"
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_ABS;
            add_child(func, (yyvsp[-1].node));
            func->arg_count = 1;
            func->value.double_val = fabs((yyvsp[-1].node)->value.double_val);
            (yyval.node) = func;
        }
#line 2270 "parser_ast.tab.c"
    break;

  case 63: /* function_call: FLOOR LPAREN expression RPAREN  */
#line 777 "parser_ast.y"
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_FLOOR;
            add_child(func, (yyvsp[-1].node));
            func->arg_count = 1;
            func->value.double_val = floor((yyvsp[-1].node)->value.double_val);
            (yyval.node) = func;
        }
#line 2283 "parser_ast.tab.c"
    break;

  case 64: /* function_call: CEIL LPAREN expression RPAREN  */
#line 786 "parser_ast.y"
        {
            ASTNode *func = create_node(NODE_FUNCTION_CALL);
            func->function = FUNC_CEIL;
            add_child(func, (yyvsp[-1].node));
            func->arg_count = 1;
            func->value.double_val = ceil((yyvsp[-1].node)->value.double_val);
            (yyval.node) = func;
        }
#line 2296 "parser_ast.tab.c"
    break;

  case 65: /* print_stmt: PRINT LPAREN STRING_LITERAL RPAREN SEMI  */
#line 800 "parser_ast.y"
        {
            if(execute_flag) {
                char *s = (yyvsp[-2].sval);
                if(s[0]=='"') s++;
                int len = strlen(s);
                if(len>0 && s[len-1]=='"') s[len-1]='\0';
                printf("%s\n",s);
            }
            ASTNode *print = create_node(NODE_PRINT);
            ASTNode *lit = create_node(NODE_LITERAL_STRING);
            lit->value.string_val = (char*)malloc(strlen((yyvsp[-2].sval)) + 1);
            strcpy(lit->value.string_val, (yyvsp[-2].sval));
            add_child(print, lit);
            (yyval.node) = print;
        }
#line 2316 "parser_ast.tab.c"
    break;

  case 66: /* print_stmt: PRINT LPAREN IDENTIFIER RPAREN SEMI  */
#line 816 "parser_ast.y"
        {
            if(execute_flag) {
                int t = get_symbol_type((yyvsp[-2].sval));
                double v = get_symbol((yyvsp[-2].sval));
                if(t == 1) printf("%c\n", (int)v);
                else printf("%g\n", v);
            }
            ASTNode *print = create_node(NODE_PRINT);
            ASTNode *id = create_node(NODE_IDENTIFIER);
            strcpy(id->identifier, (yyvsp[-2].sval));
            id->value.double_val = get_symbol((yyvsp[-2].sval));
            add_child(print, id);
            (yyval.node) = print;
        }
#line 2335 "parser_ast.tab.c"
    break;

  case 67: /* print_stmt: PRINT LPAREN expression RPAREN SEMI  */
#line 831 "parser_ast.y"
        {
            if(execute_flag) printf("%g\n",(yyvsp[-2].node)->value.double_val);
            ASTNode *print = create_node(NODE_PRINT);
            add_child(print, (yyvsp[-2].node));
            (yyval.node) = print;
        }
#line 2346 "parser_ast.tab.c"
    break;

  case 68: /* scan_stmt: SCAN LPAREN IDENTIFIER RPAREN SEMI  */
#line 843 "parser_ast.y"
        {
            if(execute_flag) {
                int t = get_symbol_type((yyvsp[-2].sval));
                if(t == 1) {
                    char v;
                    scanf(" %c", &v);
                    set_symbol((yyvsp[-2].sval), (double)v);
                } else {
                    double v;
                    scanf("%lf",&v);
                    set_symbol((yyvsp[-2].sval),v);
                }
            }
            ASTNode *scan = create_node(NODE_SCAN);
            ASTNode *id = create_node(NODE_IDENTIFIER);
            strcpy(id->identifier, (yyvsp[-2].sval));
            add_child(scan, id);
            (yyval.node) = scan;
        }
#line 2370 "parser_ast.tab.c"
    break;

  case 69: /* scan_stmt: SCAN LPAREN IDENTIFIER LBRACKET expression RBRACKET RPAREN SEMI  */
#line 863 "parser_ast.y"
        {
            if(execute_flag) {
                double v;
                scanf("%lf",&v);
                set_array_element((yyvsp[-5].sval),(int)(yyvsp[-3].node)->value.double_val,v);
            }
            ASTNode *scan = create_node(NODE_SCAN);
            ASTNode *id = create_node(NODE_IDENTIFIER);
            strcpy(id->identifier, (yyvsp[-5].sval));
            add_child(scan, id);
            add_child(scan, (yyvsp[-3].node));
            (yyval.node) = scan;
        }
#line 2388 "parser_ast.tab.c"
    break;

  case 70: /* if_stmt: IF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part  */
#line 882 "parser_ast.y"
        {
            /* Save the original execute state before this if block */
            int saved_exec = execute_flag;
            int cond_val = (yyvsp[-5].node)->value.double_val;
            
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
            add_child(if_node, (yyvsp[-5].node));      /* condition */
            if ((yyvsp[-2].node)) add_child(if_node, (yyvsp[-2].node));    /* statement_list */
            if ((yyvsp[0].node)) add_child(if_node, (yyvsp[0].node));    /* else_if_part */
            
            /* Restore original state for next statement */
            execute_flag = saved_exec;
            (yyval.node) = if_node;
        }
#line 2419 "parser_ast.tab.c"
    break;

  case 71: /* else_if_part: ELSEIF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part  */
#line 912 "parser_ast.y"
        {
            int saved_exec = execute_flag;
            int cond_val = (yyvsp[-5].node)->value.double_val;
            
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
            add_child(elseif, (yyvsp[-5].node));       /* condition */
            if ((yyvsp[-2].node)) add_child(elseif, (yyvsp[-2].node));     /* statement_list */
            if ((yyvsp[0].node)) add_child(elseif, (yyvsp[0].node));     /* else_if_part */
            
            execute_flag = saved_exec;
            (yyval.node) = elseif;
        }
#line 2446 "parser_ast.tab.c"
    break;

  case 72: /* else_if_part: ELSE LBRACE statement_list RBRACE  */
#line 935 "parser_ast.y"
        {
            (yyval.node) = (yyvsp[-1].node);
        }
#line 2454 "parser_ast.tab.c"
    break;

  case 73: /* else_if_part: %empty  */
#line 939 "parser_ast.y"
        {
            (yyval.node) = NULL;
        }
#line 2462 "parser_ast.tab.c"
    break;

  case 74: /* $@1: %empty  */
#line 948 "parser_ast.y"
        {
            switch_push((yyvsp[-1].node)->value.double_val, execute_flag);
            if (execute_flag) {
                execute_flag = 0;
            } else {
                switch_cur()->done = 1;
            }
        }
#line 2475 "parser_ast.tab.c"
    break;

  case 75: /* switch_stmt: SWITCH LPAREN expression RPAREN $@1 LBRACE case_list RBRACE  */
#line 957 "parser_ast.y"
        {
            ASTNode *switch_node = create_node(NODE_SWITCH);
            add_child(switch_node, (yyvsp[-5].node));
            if ((yyvsp[-1].node)) add_child(switch_node, (yyvsp[-1].node));
            
            execute_flag = switch_cur()->outer_exec;
            switch_pop();
            break_flag = 0;
            (yyval.node) = switch_node;
        }
#line 2490 "parser_ast.tab.c"
    break;

  case 76: /* case_list: case_list case_item  */
#line 971 "parser_ast.y"
        {
            ASTNode *list = (yyvsp[-1].node);
            if (!list) {
                list = create_node(NODE_STATEMENT_LIST);
            }
            if ((yyvsp[0].node)) add_child(list, (yyvsp[0].node));
            (yyval.node) = list;
        }
#line 2503 "parser_ast.tab.c"
    break;

  case 77: /* case_list: case_list default_item  */
#line 980 "parser_ast.y"
        {
            ASTNode *list = (yyvsp[-1].node);
            if (!list) {
                list = create_node(NODE_STATEMENT_LIST);
            }
            if ((yyvsp[0].node)) add_child(list, (yyvsp[0].node));
            (yyval.node) = list;
        }
#line 2516 "parser_ast.tab.c"
    break;

  case 78: /* case_list: %empty  */
#line 989 "parser_ast.y"
        {
            (yyval.node) = NULL;
        }
#line 2524 "parser_ast.tab.c"
    break;

  case 79: /* $@2: %empty  */
#line 996 "parser_ast.y"
        {
            /* case_expr already set execute_flag appropriately */
        }
#line 2532 "parser_ast.tab.c"
    break;

  case 80: /* case_item: CASE case_expr COLON $@2 statement_list  */
#line 1000 "parser_ast.y"
        {
            SwitchFrame *f = switch_cur();
            if (f && break_flag && execute_flag) {
                f->done = 1;
                execute_flag = 0;
                break_flag = 0;
            }
            ASTNode *case_node = create_node(NODE_CASE);
            add_child(case_node, (yyvsp[-3].node));
            if ((yyvsp[0].node)) add_child(case_node, (yyvsp[0].node));
            (yyval.node) = case_node;
        }
#line 2549 "parser_ast.tab.c"
    break;

  case 81: /* case_expr: expression  */
#line 1016 "parser_ast.y"
        {
            SwitchFrame *f = switch_cur();
            if (f == NULL) {
                yyerror("case outside switch");
                execute_flag = 0;
            } else if (f->done) {
                execute_flag = 0;
            } else if (f->matched) {
                execute_flag = 1;
            } else if (fabs(f->value - (yyvsp[0].node)->value.double_val) < SWITCH_EPSILON) {
                f->matched = 1;
                execute_flag = 1;
            } else {
                execute_flag = 0;
            }
            (yyval.node) = (yyvsp[0].node);
        }
#line 2571 "parser_ast.tab.c"
    break;

  case 82: /* case_expr: expression RANGE expression  */
#line 1034 "parser_ast.y"
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
                int start = (int)(yyvsp[-2].node)->value.double_val;
                int end = (int)(yyvsp[0].node)->value.double_val;
                int val = (int)f->value;
                
                if (val >= start && val <= end) {
                    f->matched = 1;
                    execute_flag = 1;
                } else {
                    execute_flag = 0;
                }
            }
            ASTNode *range = create_node(NODE_CASE_RANGE);
            add_child(range, (yyvsp[-2].node));
            add_child(range, (yyvsp[0].node));
            (yyval.node) = range;
        }
#line 2602 "parser_ast.tab.c"
    break;

  case 83: /* $@3: %empty  */
#line 1064 "parser_ast.y"
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
#line 2620 "parser_ast.tab.c"
    break;

  case 84: /* default_item: DEFAULT COLON $@3 statement_list  */
#line 1078 "parser_ast.y"
        {
            SwitchFrame *f = switch_cur();
            if (f && break_flag && execute_flag) {
                f->done = 1;
                execute_flag = 0;
                break_flag = 0;
            }
            ASTNode *default_node = create_node(NODE_DEFAULT);
            if ((yyvsp[0].node)) add_child(default_node, (yyvsp[0].node));
            (yyval.node) = default_node;
        }
#line 2636 "parser_ast.tab.c"
    break;

  case 85: /* condition: expression EQ expression  */
#line 1095 "parser_ast.y"
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_EQ;
            add_child(cond, (yyvsp[-2].node));
            add_child(cond, (yyvsp[0].node));
            cond->value.double_val = ((yyvsp[-2].node)->value.double_val == (yyvsp[0].node)->value.double_val);
            (yyval.node) = cond;
        }
#line 2649 "parser_ast.tab.c"
    break;

  case 86: /* condition: expression NEQ expression  */
#line 1104 "parser_ast.y"
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_NEQ;
            add_child(cond, (yyvsp[-2].node));
            add_child(cond, (yyvsp[0].node));
            cond->value.double_val = ((yyvsp[-2].node)->value.double_val != (yyvsp[0].node)->value.double_val);
            (yyval.node) = cond;
        }
#line 2662 "parser_ast.tab.c"
    break;

  case 87: /* condition: expression GT expression  */
#line 1113 "parser_ast.y"
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_GT;
            add_child(cond, (yyvsp[-2].node));
            add_child(cond, (yyvsp[0].node));
            cond->value.double_val = ((yyvsp[-2].node)->value.double_val > (yyvsp[0].node)->value.double_val);
            (yyval.node) = cond;
        }
#line 2675 "parser_ast.tab.c"
    break;

  case 88: /* condition: expression LT expression  */
#line 1122 "parser_ast.y"
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_LT;
            add_child(cond, (yyvsp[-2].node));
            add_child(cond, (yyvsp[0].node));
            cond->value.double_val = ((yyvsp[-2].node)->value.double_val < (yyvsp[0].node)->value.double_val);
            (yyval.node) = cond;
        }
#line 2688 "parser_ast.tab.c"
    break;

  case 89: /* condition: expression GE expression  */
#line 1131 "parser_ast.y"
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_GE;
            add_child(cond, (yyvsp[-2].node));
            add_child(cond, (yyvsp[0].node));
            cond->value.double_val = ((yyvsp[-2].node)->value.double_val >= (yyvsp[0].node)->value.double_val);
            (yyval.node) = cond;
        }
#line 2701 "parser_ast.tab.c"
    break;

  case 90: /* condition: expression LE expression  */
#line 1140 "parser_ast.y"
        {
            ASTNode *cond = create_node(NODE_CONDITION);
            cond->operator = OP_LE;
            add_child(cond, (yyvsp[-2].node));
            add_child(cond, (yyvsp[0].node));
            cond->value.double_val = ((yyvsp[-2].node)->value.double_val <= (yyvsp[0].node)->value.double_val);
            (yyval.node) = cond;
        }
#line 2714 "parser_ast.tab.c"
    break;

  case 91: /* loop_stmt: WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE  */
#line 1154 "parser_ast.y"
        {
            ASTNode *loop = create_node(NODE_LOOP_WHILE);
            add_child(loop, (yyvsp[-4].node));
            if ((yyvsp[-1].node)) add_child(loop, (yyvsp[-1].node));
            (yyval.node) = loop;
        }
#line 2725 "parser_ast.tab.c"
    break;

  case 92: /* loop_stmt: FOR LPAREN assignment SEMI condition SEMI assignment RPAREN LBRACE statement_list RBRACE  */
#line 1162 "parser_ast.y"
        {
            ASTNode *loop = create_node(NODE_LOOP_FOR);
            if ((yyvsp[-8].node)) add_child(loop, (yyvsp[-8].node));
            if ((yyvsp[-6].node)) add_child(loop, (yyvsp[-6].node));
            if ((yyvsp[-4].node)) add_child(loop, (yyvsp[-4].node));
            if ((yyvsp[-1].node)) add_child(loop, (yyvsp[-1].node));
            (yyval.node) = loop;
        }
#line 2738 "parser_ast.tab.c"
    break;

  case 93: /* return_stmt: RETURN expression  */
#line 1174 "parser_ast.y"
        {
            if(execute_flag) printf("Program returned: %g\n",(yyvsp[0].node)->value.double_val);
            ASTNode *ret = create_node(NODE_RETURN);
            add_child(ret, (yyvsp[0].node));
            (yyval.node) = ret;
        }
#line 2749 "parser_ast.tab.c"
    break;


#line 2753 "parser_ast.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1182 "parser_ast.y"


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
