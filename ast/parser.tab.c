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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"
#include "interpreter.h"
#include "semantic.h"

void yyerror(const char *s);
int  yylex(void);
extern int yylineno;

/* tracks declaration type for declarations */
static int current_decl_type = 0;   /* 0 = numeric, 1 = char */

#line 88 "parser.tab.c"

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

#include "parser.tab.h"
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
  YYSYMBOL_END = 35,                       /* END  */
  YYSYMBOL_TRUE_LITERAL = 36,              /* TRUE_LITERAL  */
  YYSYMBOL_FALSE_LITERAL = 37,             /* FALSE_LITERAL  */
  YYSYMBOL_POW = 38,                       /* POW  */
  YYSYMBOL_SQRT = 39,                      /* SQRT  */
  YYSYMBOL_ABS = 40,                       /* ABS  */
  YYSYMBOL_FLOOR = 41,                     /* FLOOR  */
  YYSYMBOL_CEIL = 42,                      /* CEIL  */
  YYSYMBOL_EQ = 43,                        /* EQ  */
  YYSYMBOL_NEQ = 44,                       /* NEQ  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_LE = 46,                        /* LE  */
  YYSYMBOL_GT = 47,                        /* GT  */
  YYSYMBOL_LT = 48,                        /* LT  */
  YYSYMBOL_AND = 49,                       /* AND  */
  YYSYMBOL_OR = 50,                        /* OR  */
  YYSYMBOL_NOT = 51,                       /* NOT  */
  YYSYMBOL_INC = 52,                       /* INC  */
  YYSYMBOL_DEC = 53,                       /* DEC  */
  YYSYMBOL_PLUS = 54,                      /* PLUS  */
  YYSYMBOL_MINUS = 55,                     /* MINUS  */
  YYSYMBOL_MUL = 56,                       /* MUL  */
  YYSYMBOL_DIV = 57,                       /* DIV  */
  YYSYMBOL_MOD = 58,                       /* MOD  */
  YYSYMBOL_ASSIGN = 59,                    /* ASSIGN  */
  YYSYMBOL_BIT_AND = 60,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 61,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 62,                   /* BIT_XOR  */
  YYSYMBOL_BIT_NOT = 63,                   /* BIT_NOT  */
  YYSYMBOL_SHL = 64,                       /* SHL  */
  YYSYMBOL_SHR = 65,                       /* SHR  */
  YYSYMBOL_SEMI = 66,                      /* SEMI  */
  YYSYMBOL_COMMA = 67,                     /* COMMA  */
  YYSYMBOL_COLON = 68,                     /* COLON  */
  YYSYMBOL_LPAREN = 69,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 70,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 71,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 72,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 73,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 74,                  /* RBRACKET  */
  YYSYMBOL_RANGE = 75,                     /* RANGE  */
  YYSYMBOL_INT_LITERAL = 76,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 77,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 78,            /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 79,              /* CHAR_LITERAL  */
  YYSYMBOL_IDENTIFIER = 80,                /* IDENTIFIER  */
  YYSYMBOL_UNARY = 81,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_program = 83,                   /* program  */
  YYSYMBOL_top_level_list = 84,            /* top_level_list  */
  YYSYMBOL_func_def = 85,                  /* func_def  */
  YYSYMBOL_ret_type = 86,                  /* ret_type  */
  YYSYMBOL_param_list = 87,                /* param_list  */
  YYSYMBOL_param = 88,                     /* param  */
  YYSYMBOL_preprocessor_list = 89,         /* preprocessor_list  */
  YYSYMBOL_preprocessor = 90,              /* preprocessor  */
  YYSYMBOL_main_function = 91,             /* main_function  */
  YYSYMBOL_statement_list = 92,            /* statement_list  */
  YYSYMBOL_statement = 93,                 /* statement  */
  YYSYMBOL_declaration = 94,               /* declaration  */
  YYSYMBOL_declaration_no_semi = 95,       /* declaration_no_semi  */
  YYSYMBOL_array_size = 96,                /* array_size  */
  YYSYMBOL_type = 97,                      /* type  */
  YYSYMBOL_identifier_list_decls = 98,     /* identifier_list_decls  */
  YYSYMBOL_assignment = 99,                /* assignment  */
  YYSYMBOL_array_assignment = 100,         /* array_assignment  */
  YYSYMBOL_expression = 101,               /* expression  */
  YYSYMBOL_term = 102,                     /* term  */
  YYSYMBOL_factor = 103,                   /* factor  */
  YYSYMBOL_primary = 104,                  /* primary  */
  YYSYMBOL_func_call_expr = 105,           /* func_call_expr  */
  YYSYMBOL_arg_list_opt = 106,             /* arg_list_opt  */
  YYSYMBOL_arg_list = 107,                 /* arg_list  */
  YYSYMBOL_array_access = 108,             /* array_access  */
  YYSYMBOL_function_call = 109,            /* function_call  */
  YYSYMBOL_print_stmt = 110,               /* print_stmt  */
  YYSYMBOL_print_end_opt = 111,            /* print_end_opt  */
  YYSYMBOL_scan_stmt = 112,                /* scan_stmt  */
  YYSYMBOL_condition = 113,                /* condition  */
  YYSYMBOL_if_stmt = 114,                  /* if_stmt  */
  YYSYMBOL_else_if_part = 115,             /* else_if_part  */
  YYSYMBOL_switch_stmt = 116,              /* switch_stmt  */
  YYSYMBOL_case_list = 117,                /* case_list  */
  YYSYMBOL_case_item = 118,                /* case_item  */
  YYSYMBOL_case_expr = 119,                /* case_expr  */
  YYSYMBOL_default_item = 120,             /* default_item  */
  YYSYMBOL_for_init = 121,                 /* for_init  */
  YYSYMBOL_for_update = 122,               /* for_update  */
  YYSYMBOL_loop_stmt = 123,                /* loop_stmt  */
  YYSYMBOL_return_stmt = 124               /* return_stmt  */
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
typedef yytype_int16 yy_state_t;

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
#define YYLAST   907

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  135
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  299

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   336


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
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   107,   107,   111,   112,   113,   117,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   142,   153,   154,   158,
     166,   167,   171,   172,   176,   196,   212,   216,   217,   218,
     219,   220,   221,   222,   223,   227,   231,   232,   233,   234,
     242,   244,   252,   265,   273,   284,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   305,   313,   321,   330,   346,
     356,   364,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   396,   397,   398,   399,   403,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     420,   427,   428,   432,   444,   451,   453,   462,   464,   466,
     468,   470,   478,   486,   504,   515,   522,   527,   533,   547,
     548,   549,   550,   551,   552,   568,   579,   587,   593,   606,
     616,   627,   637,   641,   660,   666,   676,   704,   705,   706,
     710,   711,   715,   722,   729,   750
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
  "RETURN", "MAIN", "PRINT", "SCAN", "END", "TRUE_LITERAL",
  "FALSE_LITERAL", "POW", "SQRT", "ABS", "FLOOR", "CEIL", "EQ", "NEQ",
  "GE", "LE", "GT", "LT", "AND", "OR", "NOT", "INC", "DEC", "PLUS",
  "MINUS", "MUL", "DIV", "MOD", "ASSIGN", "BIT_AND", "BIT_OR", "BIT_XOR",
  "BIT_NOT", "SHL", "SHR", "SEMI", "COMMA", "COLON", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "RANGE", "INT_LITERAL",
  "FLOAT_LITERAL", "STRING_LITERAL", "CHAR_LITERAL", "IDENTIFIER", "UNARY",
  "$accept", "program", "top_level_list", "func_def", "ret_type",
  "param_list", "param", "preprocessor_list", "preprocessor",
  "main_function", "statement_list", "statement", "declaration",
  "declaration_no_semi", "array_size", "type", "identifier_list_decls",
  "assignment", "array_assignment", "expression", "term", "factor",
  "primary", "func_call_expr", "arg_list_opt", "arg_list", "array_access",
  "function_call", "print_stmt", "print_end_opt", "scan_stmt", "condition",
  "if_stmt", "else_if_part", "switch_stmt", "case_list", "case_item",
  "case_expr", "default_item", "for_init", "for_update", "loop_stmt",
  "return_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-154)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -154,    19,    97,  -154,    18,   -40,   176,  -154,  -154,   -24,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,     9,
    -154,     3,  -154,  -154,    39,    51,    35,   893,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,   -10,  -154,
      45,    36,   893,    55,  -154,    58,    59,    60,    70,    69,
      75,    76,   452,    74,    87,  -154,    48,  -154,  -154,    80,
      95,    96,    98,  -154,  -154,  -154,  -154,  -154,    99,  -154,
    -154,   497,   497,    79,   497,  -154,  -154,  -154,  -154,  -154,
     110,   123,   125,   129,   130,   517,   517,   517,  -154,   497,
    -154,  -154,  -154,   -44,   833,    41,  -154,  -154,  -154,  -154,
    -154,   432,    88,   497,   497,   497,   136,   134,  -154,  -154,
    -154,  -154,   124,   640,   131,   657,   148,  -154,   133,  -154,
     144,   141,   250,   497,   497,   497,   497,   497,    41,    41,
      41,   674,   497,   517,   517,   517,   517,   517,   517,   517,
     517,   517,   517,   517,   517,   179,   149,   776,   150,   -12,
     833,   833,   151,   152,   549,   497,   138,   155,  -154,  -154,
     497,   497,   497,   497,   497,   497,   153,   154,   177,   497,
     161,   212,   795,   691,   708,   725,   742,  -154,   566,    41,
      41,    41,    41,    41,    41,    41,    41,    41,  -154,  -154,
    -154,   181,   172,   174,   185,   186,   497,  -154,   497,    21,
     814,   -31,  -154,  -154,   169,   833,   833,   833,   833,   833,
     833,  -154,  -154,   497,   187,  -154,   178,   497,  -154,  -154,
    -154,  -154,   192,   167,   188,   200,  -154,  -154,   583,   833,
     497,   497,   138,    29,   279,    -4,   833,   189,   327,   497,
     759,   497,  -154,  -154,  -154,   197,   833,   600,  -154,  -154,
     155,    82,   497,   203,  -154,  -154,  -154,  -154,   198,  -154,
     202,  -154,   617,   208,   216,   220,   211,   226,  -154,   173,
     228,  -154,   227,   231,  -154,  -154,   497,   234,  -154,   497,
     497,  -154,     4,  -154,  -154,   833,  -154,   356,   233,   833,
       4,   404,  -154,   230,  -154,  -154,   433,    82,  -154
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      21,     0,     5,     1,     0,     0,     2,    20,    22,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,     0,
       3,     0,     4,    23,     0,     0,     0,    18,    26,    46,
      47,    48,    49,    50,    51,    52,    53,    54,     0,    17,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,     0,    25,    27,     0,
       0,     0,     0,    30,    31,    32,    33,    36,     0,    16,
      26,     0,     0,   129,     0,    26,    34,    35,    83,    84,
       0,     0,     0,     0,     0,     0,     0,     0,    39,     0,
      81,    82,    85,    80,   135,    74,    78,    79,    89,    88,
      87,   106,     0,     0,    92,     0,    55,     0,    28,    29,
      38,    37,     0,     0,     0,     0,     0,   128,     0,   127,
       0,     0,     0,     0,     0,     0,     0,     0,    72,    71,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,   106,     0,     0,
      59,    94,     0,    91,     0,     0,     0,     0,    40,     6,
       0,     0,     0,     0,     0,     0,     0,     0,    43,     0,
       0,     0,     0,     0,     0,     0,     0,    86,     0,    64,
      65,    62,    63,    68,    66,    67,    69,    70,    75,    76,
      77,     0,     0,     0,     0,     0,     0,    90,     0,     0,
      56,    55,    57,    45,     0,   109,   110,   113,   114,   111,
     112,    26,   122,     0,     0,    26,     0,     0,    98,    99,
     100,   101,    95,     0,     0,     0,   104,   107,     0,    93,
       0,     0,     0,     0,     0,     0,    44,   131,     0,     0,
       0,     0,   105,   102,   103,     0,    60,     0,    58,    41,
       0,   118,     0,     0,   119,   120,   121,   130,     0,   132,
       0,    97,     0,     0,     0,     0,     0,     0,   115,   124,
       0,    26,     0,     0,    96,   108,     0,     0,    26,     0,
       0,    26,   126,    26,   133,    61,    42,     0,     0,   125,
     123,     0,   117,     0,   134,    26,     0,   118,   116
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -154,  -154,  -154,  -154,  -154,  -154,   262,  -154,  -154,  -154,
     -66,  -154,  -154,  -154,    61,    -1,  -153,   -68,  -154,   -50,
      37,  -136,  -154,   -41,  -154,  -154,  -154,  -154,  -154,   -28,
    -154,   -73,  -154,    17,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     6,    20,    21,    38,    39,     2,     7,    22,
      41,    57,    58,   117,   204,    59,   107,    60,    61,   113,
      95,    96,    97,    98,   152,   153,    99,   100,    63,   148,
      64,   114,    65,   268,    66,   235,   255,   270,   256,   120,
     258,    67,    68
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,   121,    94,   202,   112,   119,   188,   189,   190,   122,
      29,    30,    31,    32,    33,    34,    35,    36,    37,     3,
     252,   253,   115,     8,    45,   104,    40,    46,   155,   132,
      47,    48,    49,    50,    51,    52,   156,    53,    54,   131,
       9,    40,    29,    30,    31,    32,    33,    34,    35,    36,
      37,   147,    23,   150,   151,   154,    45,    42,   195,    46,
      43,   196,    47,    48,    49,    50,    51,    52,   254,    53,
      54,    62,   118,   172,   173,   174,   175,   176,    24,   248,
     230,    62,   178,    25,    56,    29,    30,    31,    32,    33,
      34,    35,    36,    37,   231,   249,   214,   142,   143,   144,
       4,     5,   250,   266,   267,   200,    28,   103,    55,    26,
     205,   206,   207,   208,   209,   210,    56,   104,   192,   193,
      27,   105,   128,   129,   130,    44,    70,    71,    72,    73,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    74,
      75,    76,    77,   101,    45,   234,   228,    46,   229,   238,
      47,    48,    49,    50,    51,    52,   102,    53,    54,   116,
     106,   108,   109,   236,   110,   111,   260,   240,   149,   257,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   123,
     246,   247,    10,    11,    12,    13,    14,    15,    16,    17,
      18,   262,   124,    62,   125,   155,   159,    62,   126,   127,
     158,   166,   269,   156,    56,   282,   288,   103,    19,   157,
     169,   170,   287,   168,   191,   290,   145,   291,   201,   198,
     194,   197,   133,   134,   211,   212,   285,   135,   136,   296,
     289,   203,   215,   137,   138,   139,   213,   140,   141,   216,
     223,    62,   224,   233,   225,   242,    62,   239,   280,    62,
      62,   226,   227,   237,   243,    62,    29,    30,    31,    32,
      33,    34,    35,    36,    37,   241,   244,   263,   272,   116,
      45,   271,   273,    46,   275,   276,    47,    48,    49,    50,
      51,    52,   278,    53,    54,    29,    30,    31,    32,    33,
      34,    35,    36,    37,   277,   279,   281,   284,   283,    45,
     286,   295,    46,   293,    69,    47,    48,    49,    50,    51,
      52,   265,    53,    54,   298,     0,     0,     0,     0,     0,
       0,     0,   171,     0,     0,     0,     0,     0,     0,     0,
      56,     0,     0,    29,    30,    31,    32,    33,    34,    35,
      36,    37,     0,     0,     0,     0,     0,    45,     0,     0,
      46,   251,     0,    47,    48,    49,    50,    51,    52,    56,
      53,    54,    29,    30,    31,    32,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     0,    45,     0,     0,    46,
       0,     0,    47,    48,    49,    50,    51,    52,     0,    53,
      54,     0,     0,     0,     0,     0,     0,     0,     0,   259,
       0,     0,     0,     0,     0,     0,     0,    56,     0,     0,
      29,    30,    31,    32,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     0,    45,     0,     0,    46,   292,     0,
      47,    48,    49,    50,    51,    52,    56,    53,    54,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     0,     0,
       0,     0,     0,    45,     0,     0,    46,     0,     0,    47,
      48,    49,    50,    51,    52,     0,    53,    54,    78,    79,
      80,    81,    82,    83,    84,     0,   294,     0,     0,     0,
       0,     0,     0,    85,    56,     0,     0,    86,    78,    79,
      80,    81,    82,    83,    84,    87,     0,     0,     0,   145,
       0,    89,     0,    85,     0,   297,     0,    86,    90,    91,
     146,    92,    93,    56,     0,    87,     0,     0,    88,     0,
       0,    89,     0,     0,     0,     0,     0,     0,    90,    91,
       0,    92,    93,    78,    79,    80,    81,    82,    83,    84,
       0,     0,     0,     0,     0,     0,     0,     0,    85,     0,
       0,     0,    86,    78,    79,    80,    81,    82,    83,    84,
      87,     0,     0,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,    90,    91,     0,    92,    93,     0,     0,
       0,     0,     0,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,    90,    91,     0,    92,    93,   133,   134,
       0,     0,     0,   135,   136,     0,     0,     0,     0,   137,
     138,   139,     0,   140,   141,   133,   134,     0,     0,     0,
     135,   136,     0,   199,     0,     0,   137,   138,   139,     0,
     140,   141,   133,   134,     0,     0,     0,   135,   136,     0,
     222,     0,     0,   137,   138,   139,     0,   140,   141,   133,
     134,     0,     0,     0,   135,   136,     0,   245,     0,     0,
     137,   138,   139,     0,   140,   141,   133,   134,     0,     0,
       0,   135,   136,     0,   264,     0,     0,   137,   138,   139,
       0,   140,   141,   160,   161,   162,   163,   164,   165,   133,
     134,   274,     0,     0,   135,   136,     0,     0,     0,     0,
     137,   138,   139,     0,   140,   141,   133,   134,     0,     0,
       0,   135,   136,     0,     0,     0,     0,   137,   138,   139,
       0,   140,   141,   133,   134,     0,     0,   167,   135,   136,
       0,     0,     0,     0,   137,   138,   139,     0,   140,   141,
     133,   134,     0,     0,   177,   135,   136,     0,     0,     0,
       0,   137,   138,   139,     0,   140,   141,   133,   134,     0,
       0,   218,   135,   136,     0,     0,     0,     0,   137,   138,
     139,     0,   140,   141,   133,   134,     0,     0,   219,   135,
     136,     0,     0,     0,     0,   137,   138,   139,     0,   140,
     141,   133,   134,     0,     0,   220,   135,   136,     0,     0,
       0,     0,   137,   138,   139,     0,   140,   141,   133,   134,
       0,     0,   221,   135,   136,     0,     0,     0,     0,   137,
     138,   139,     0,   140,   141,   133,   134,     0,     0,   261,
     135,   136,     0,     0,     0,     0,   137,   138,   139,     0,
     140,   141,     0,   145,   133,   134,     0,     0,     0,   135,
     136,     0,     0,     0,     0,   137,   138,   139,     0,   140,
     141,     0,   217,   133,   134,     0,     0,     0,   135,   136,
       0,     0,     0,     0,   137,   138,   139,     0,   140,   141,
       0,   232,   133,   134,     0,     0,     0,   135,   136,     0,
       0,     0,     0,   137,   138,   139,     0,   140,   141,    29,
      30,    31,    32,    33,    34,    35,    36,    37
};

static const yytype_int16 yycheck[] =
{
      41,    74,    52,   156,    70,    73,   142,   143,   144,    75,
       6,     7,     8,     9,    10,    11,    12,    13,    14,     0,
      24,    25,    72,     5,    20,    69,    27,    23,    59,    73,
      26,    27,    28,    29,    30,    31,    67,    33,    34,    89,
      80,    42,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   101,    76,   103,   104,   105,    20,    67,    70,    23,
      70,    73,    26,    27,    28,    29,    30,    31,    72,    33,
      34,   112,    73,   123,   124,   125,   126,   127,    69,   232,
      59,   122,   132,    80,    80,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    73,    66,   169,    56,    57,    58,
       3,     4,    73,    21,    22,   155,    71,    59,    72,    70,
     160,   161,   162,   163,   164,   165,    80,    69,   146,   147,
      69,    73,    85,    86,    87,    80,    71,    69,    69,    69,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    69,
      71,    66,    66,    69,    20,   211,   196,    23,   198,   215,
      26,    27,    28,    29,    30,    31,    69,    33,    34,    80,
      80,    66,    66,   213,    66,    66,   239,   217,    80,   237,
     133,   134,   135,   136,   137,   138,   139,   140,   141,    69,
     230,   231,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   241,    69,   234,    69,    59,    72,   238,    69,    69,
      66,    70,   252,    67,    80,   271,   279,    59,    32,    73,
      66,    70,   278,    80,    35,   281,    67,   283,    80,    67,
      70,    70,    49,    50,    71,    71,   276,    54,    55,   295,
     280,    76,    71,    60,    61,    62,    59,    64,    65,    27,
      59,   282,    70,    74,    70,    78,   287,    69,    75,   290,
     291,    66,    66,    66,    66,   296,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    73,    66,    70,    70,    80,
      20,    68,    70,    23,    66,    59,    26,    27,    28,    29,
      30,    31,    71,    33,    34,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    74,    69,    68,    66,    71,    20,
      66,    71,    23,    70,    42,    26,    27,    28,    29,    30,
      31,   250,    33,    34,   297,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    -1,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      23,    72,    -1,    26,    27,    28,    29,    30,    31,    80,
      33,    34,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    23,
      -1,    -1,    26,    27,    28,    29,    30,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    23,    72,    -1,
      26,    27,    28,    29,    30,    31,    80,    33,    34,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    23,    -1,    -1,    26,
      27,    28,    29,    30,    31,    -1,    33,    34,    36,    37,
      38,    39,    40,    41,    42,    -1,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    80,    -1,    -1,    55,    36,    37,
      38,    39,    40,    41,    42,    63,    -1,    -1,    -1,    67,
      -1,    69,    -1,    51,    -1,    72,    -1,    55,    76,    77,
      78,    79,    80,    80,    -1,    63,    -1,    -1,    66,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      -1,    79,    80,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    55,    36,    37,    38,    39,    40,    41,    42,
      63,    -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    -1,    79,    80,    49,    50,
      -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    -1,    64,    65,    49,    50,    -1,    -1,    -1,
      54,    55,    -1,    74,    -1,    -1,    60,    61,    62,    -1,
      64,    65,    49,    50,    -1,    -1,    -1,    54,    55,    -1,
      74,    -1,    -1,    60,    61,    62,    -1,    64,    65,    49,
      50,    -1,    -1,    -1,    54,    55,    -1,    74,    -1,    -1,
      60,    61,    62,    -1,    64,    65,    49,    50,    -1,    -1,
      -1,    54,    55,    -1,    74,    -1,    -1,    60,    61,    62,
      -1,    64,    65,    43,    44,    45,    46,    47,    48,    49,
      50,    74,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,
      60,    61,    62,    -1,    64,    65,    49,    50,    -1,    -1,
      -1,    54,    55,    -1,    -1,    -1,    -1,    60,    61,    62,
      -1,    64,    65,    49,    50,    -1,    -1,    70,    54,    55,
      -1,    -1,    -1,    -1,    60,    61,    62,    -1,    64,    65,
      49,    50,    -1,    -1,    70,    54,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    -1,    64,    65,    49,    50,    -1,
      -1,    70,    54,    55,    -1,    -1,    -1,    -1,    60,    61,
      62,    -1,    64,    65,    49,    50,    -1,    -1,    70,    54,
      55,    -1,    -1,    -1,    -1,    60,    61,    62,    -1,    64,
      65,    49,    50,    -1,    -1,    70,    54,    55,    -1,    -1,
      -1,    -1,    60,    61,    62,    -1,    64,    65,    49,    50,
      -1,    -1,    70,    54,    55,    -1,    -1,    -1,    -1,    60,
      61,    62,    -1,    64,    65,    49,    50,    -1,    -1,    70,
      54,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    -1,
      64,    65,    -1,    67,    49,    50,    -1,    -1,    -1,    54,
      55,    -1,    -1,    -1,    -1,    60,    61,    62,    -1,    64,
      65,    -1,    67,    49,    50,    -1,    -1,    -1,    54,    55,
      -1,    -1,    -1,    -1,    60,    61,    62,    -1,    64,    65,
      -1,    67,    49,    50,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,    -1,    60,    61,    62,    -1,    64,    65,     6,
       7,     8,     9,    10,    11,    12,    13,    14
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    83,    89,     0,     3,     4,    84,    90,     5,    80,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    32,
      85,    86,    91,    76,    69,    80,    70,    69,    71,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    87,    88,
      97,    92,    67,    70,    80,    20,    23,    26,    27,    28,
      29,    30,    31,    33,    34,    72,    80,    93,    94,    97,
      99,   100,   105,   110,   112,   114,   116,   123,   124,    88,
      71,    69,    69,    69,    69,    71,    66,    66,    36,    37,
      38,    39,    40,    41,    42,    51,    55,    63,    66,    69,
      76,    77,    79,    80,   101,   102,   103,   104,   105,   108,
     109,    69,    69,    59,    69,    73,    80,    98,    66,    66,
      66,    66,    92,   101,   113,   101,    80,    95,    97,    99,
     121,   113,    92,    69,    69,    69,    69,    69,   102,   102,
     102,   101,    73,    49,    50,    54,    55,    60,    61,    62,
      64,    65,    56,    57,    58,    67,    78,   101,   111,    80,
     101,   101,   106,   107,   101,    59,    67,    73,    66,    72,
      43,    44,    45,    46,    47,    48,    70,    70,    80,    66,
      70,    72,   101,   101,   101,   101,   101,    70,   101,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   103,   103,
     103,    35,   111,   111,    70,    70,    73,    70,    67,    74,
     101,    80,    98,    76,    96,   101,   101,   101,   101,   101,
     101,    71,    71,    59,   113,    71,    27,    67,    70,    70,
      70,    70,    74,    59,    70,    70,    66,    66,   101,   101,
      59,    73,    67,    74,    92,   117,   101,    66,    92,    69,
     101,    73,    78,    66,    66,    74,   101,   101,    98,    66,
      73,    72,    24,    25,    72,   118,   120,    99,   122,    72,
     113,    70,   101,    70,    74,    96,    21,    22,   115,   101,
     119,    68,    70,    70,    74,    66,    59,    74,    71,    69,
      75,    68,    92,    71,    66,   101,    66,    92,   113,   101,
      92,    92,    72,    70,    72,    71,    92,    72,   115
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    87,    87,    87,    88,
      89,    89,    90,    90,    91,    92,    92,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      94,    94,    94,    95,    95,    96,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    98,    98,    98,    98,    99,
     100,   100,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   102,   102,   102,   102,   103,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     105,   106,   106,   107,   107,   108,   108,   109,   109,   109,
     109,   109,   110,   110,   110,   111,   111,   112,   112,   113,
     113,   113,   113,   113,   113,   114,   115,   115,   115,   116,
     117,   117,   117,   118,   119,   119,   120,   121,   121,   121,
     122,   122,   123,   123,   123,   124
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     8,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     2,
       2,     0,     2,     3,     6,     2,     0,     1,     2,     2,
       1,     1,     1,     1,     2,     2,     1,     2,     2,     2,
       3,     6,     9,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     5,     3,
       6,     9,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     1,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       4,     1,     0,     3,     1,     4,     7,     6,     4,     4,
       4,     4,     6,     6,     5,     4,     0,     5,     8,     3,
       3,     3,     3,     3,     3,     8,     8,     4,     0,     7,
       2,     2,     0,     4,     1,     3,     3,     1,     1,     0,
       1,     0,     7,     9,    11,     2
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
  case 6: /* func_def: ret_type IDENTIFIER LPAREN param_list RPAREN LBRACE statement_list RBRACE  */
#line 118 "parser.y"
        {
            /* Register function into the function table at parse time.
               The body AST is stored by reference — do NOT free it. */
            ASTNode *def = make_func_def((yyvsp[-6].sval), (yyvsp[-7].ival), (yyvsp[-4].node), (yyvsp[-1].node));
            func_define((yyvsp[-6].sval), (yyvsp[-7].ival), (yyvsp[-4].node), (yyvsp[-1].node));
            /* def itself is not added to the program tree —
               the function table holds the body reference */
           /* (void)def;    suppress unused-variable warning */
           (yyval.node) = def;
        }
#line 1536 "parser.tab.c"
    break;

  case 7: /* ret_type: INT_TYPE  */
#line 131 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1542 "parser.tab.c"
    break;

  case 8: /* ret_type: FLOAT_TYPE  */
#line 132 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1548 "parser.tab.c"
    break;

  case 9: /* ret_type: DOUBLE_TYPE  */
#line 133 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1554 "parser.tab.c"
    break;

  case 10: /* ret_type: CHAR_TYPE  */
#line 134 "parser.y"
                    { (yyval.ival) = 1; current_decl_type = 1; }
#line 1560 "parser.tab.c"
    break;

  case 11: /* ret_type: BOOL_TYPE  */
#line 135 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1566 "parser.tab.c"
    break;

  case 12: /* ret_type: VOID_TYPE  */
#line 136 "parser.y"
                    { (yyval.ival) = 2; current_decl_type = 0; }
#line 1572 "parser.tab.c"
    break;

  case 13: /* ret_type: LONG_TYPE  */
#line 137 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1578 "parser.tab.c"
    break;

  case 14: /* ret_type: SHORT_TYPE  */
#line 138 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1584 "parser.tab.c"
    break;

  case 15: /* ret_type: UNSIGNED_TYPE  */
#line 139 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1590 "parser.tab.c"
    break;

  case 16: /* param_list: param_list COMMA param  */
#line 143 "parser.y"
        {
            /* append $3 to end of $1 */
            if ((yyvsp[-2].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
            else {
                ASTNode *t = (yyvsp[-2].node);
                while (t->next) t = t->next;
                t->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-2].node);
            }
        }
#line 1605 "parser.tab.c"
    break;

  case 17: /* param_list: param  */
#line 153 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1611 "parser.tab.c"
    break;

  case 18: /* param_list: %empty  */
#line 154 "parser.y"
                    { (yyval.node) = NULL; }
#line 1617 "parser.tab.c"
    break;

  case 19: /* param: type IDENTIFIER  */
#line 159 "parser.y"
        {
            (yyval.node) = make_param((yyvsp[0].sval), current_decl_type);
        }
#line 1625 "parser.tab.c"
    break;

  case 24: /* main_function: MAIN LPAREN RPAREN LBRACE statement_list RBRACE  */
#line 177 "parser.y"
        {
            /* Build program root and immediately interpret it */
            ASTNode *prog = make_node(NODE_PROGRAM);
            prog->left = (yyvsp[-1].node);
            if(sem_analyse(prog) != 0){
                fprintf(stderr, "Aborting due to semantic error. \n");
                free_ast(prog);
                YYABORT;
            }
            interpret(prog);
            free_ast(prog);
        }
#line 1642 "parser.tab.c"
    break;

  case 25: /* statement_list: statement_list statement  */
#line 197 "parser.y"
        {
            /* Append $2 to the end of the $1 list.
               We use a right-growing list: walk to the tail and link. */
            if ((yyvsp[-1].node) == NULL) {
                (yyval.node) = (yyvsp[0].node);
            } else if ((yyvsp[0].node) == NULL) {
                (yyval.node) = (yyvsp[-1].node);
            } else {
                /* find tail of $1 */
                ASTNode *tail = (yyvsp[-1].node);
                while (tail->next) tail = tail->next;
                tail->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-1].node);
            }
        }
#line 1662 "parser.tab.c"
    break;

  case 26: /* statement_list: %empty  */
#line 212 "parser.y"
                  { (yyval.node) = NULL; }
#line 1668 "parser.tab.c"
    break;

  case 27: /* statement: declaration  */
#line 216 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1674 "parser.tab.c"
    break;

  case 28: /* statement: assignment SEMI  */
#line 217 "parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1680 "parser.tab.c"
    break;

  case 29: /* statement: array_assignment SEMI  */
#line 218 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1686 "parser.tab.c"
    break;

  case 30: /* statement: print_stmt  */
#line 219 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1692 "parser.tab.c"
    break;

  case 31: /* statement: scan_stmt  */
#line 220 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1698 "parser.tab.c"
    break;

  case 32: /* statement: if_stmt  */
#line 221 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1704 "parser.tab.c"
    break;

  case 33: /* statement: switch_stmt  */
#line 222 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1710 "parser.tab.c"
    break;

  case 34: /* statement: BREAK SEMI  */
#line 224 "parser.y"
        {
            (yyval.node) = make_node(NODE_BREAK);
        }
#line 1718 "parser.tab.c"
    break;

  case 35: /* statement: CONTINUE SEMI  */
#line 228 "parser.y"
        {
            (yyval.node) = make_node(NODE_CONTINUE);
        }
#line 1726 "parser.tab.c"
    break;

  case 36: /* statement: loop_stmt  */
#line 231 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1732 "parser.tab.c"
    break;

  case 37: /* statement: return_stmt SEMI  */
#line 232 "parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1738 "parser.tab.c"
    break;

  case 38: /* statement: func_call_expr SEMI  */
#line 233 "parser.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 1744 "parser.tab.c"
    break;

  case 39: /* statement: RETURN SEMI  */
#line 234 "parser.y"
                     { (yyval.node) = make_return_void(); }
#line 1750 "parser.tab.c"
    break;

  case 40: /* declaration: type identifier_list_decls SEMI  */
#line 243 "parser.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1756 "parser.tab.c"
    break;

  case 41: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET SEMI  */
#line 245 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL_ARRAY);
            n->sval      = strdup((yyvsp[-4].sval));
            n->cols      = (yyvsp[-2].ival);   /* size stored in cols */
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1768 "parser.tab.c"
    break;

  case 42: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET LBRACKET array_size RBRACKET SEMI  */
#line 253 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL_ARRAY_2D);
            n->sval      = strdup((yyvsp[-7].sval));
            n->rows      = (yyvsp[-5].ival);
            n->cols      = (yyvsp[-2].ival);
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1781 "parser.tab.c"
    break;

  case 43: /* declaration_no_semi: type IDENTIFIER  */
#line 266 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[0].sval));
            n->left      = NULL;
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1793 "parser.tab.c"
    break;

  case 44: /* declaration_no_semi: type IDENTIFIER ASSIGN expression  */
#line 274 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-2].sval));
            n->left      = (yyvsp[0].node);
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1805 "parser.tab.c"
    break;

  case 45: /* array_size: INT_LITERAL  */
#line 284 "parser.y"
                  { (yyval.ival) = (yyvsp[0].ival); }
#line 1811 "parser.tab.c"
    break;

  case 46: /* type: INT_TYPE  */
#line 288 "parser.y"
                    { current_decl_type = 0; }
#line 1817 "parser.tab.c"
    break;

  case 47: /* type: FLOAT_TYPE  */
#line 289 "parser.y"
                    { current_decl_type = 0; }
#line 1823 "parser.tab.c"
    break;

  case 48: /* type: DOUBLE_TYPE  */
#line 290 "parser.y"
                    { current_decl_type = 0; }
#line 1829 "parser.tab.c"
    break;

  case 49: /* type: CHAR_TYPE  */
#line 291 "parser.y"
                    { current_decl_type = 1; }
#line 1835 "parser.tab.c"
    break;

  case 50: /* type: BOOL_TYPE  */
#line 292 "parser.y"
                    { current_decl_type = 0; }
#line 1841 "parser.tab.c"
    break;

  case 51: /* type: VOID_TYPE  */
#line 293 "parser.y"
                    { current_decl_type = 0; }
#line 1847 "parser.tab.c"
    break;

  case 52: /* type: LONG_TYPE  */
#line 294 "parser.y"
                    { current_decl_type = 0; }
#line 1853 "parser.tab.c"
    break;

  case 53: /* type: SHORT_TYPE  */
#line 295 "parser.y"
                    { current_decl_type = 0; }
#line 1859 "parser.tab.c"
    break;

  case 54: /* type: UNSIGNED_TYPE  */
#line 296 "parser.y"
                    { current_decl_type = 0; }
#line 1865 "parser.tab.c"
    break;

  case 55: /* identifier_list_decls: IDENTIFIER  */
#line 306 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[0].sval));
            n->left      = NULL;   /* no initialiser */
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1877 "parser.tab.c"
    break;

  case 56: /* identifier_list_decls: IDENTIFIER ASSIGN expression  */
#line 314 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-2].sval));
            n->left      = (yyvsp[0].node);
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1889 "parser.tab.c"
    break;

  case 57: /* identifier_list_decls: IDENTIFIER COMMA identifier_list_decls  */
#line 322 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-2].sval));
            n->left      = NULL;
            n->decl_type = current_decl_type;
            n->next      = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1902 "parser.tab.c"
    break;

  case 58: /* identifier_list_decls: IDENTIFIER ASSIGN expression COMMA identifier_list_decls  */
#line 331 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-4].sval));
            n->left      = (yyvsp[-2].node);
            n->decl_type = current_decl_type;
            n->next      = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1915 "parser.tab.c"
    break;

  case 59: /* assignment: IDENTIFIER ASSIGN expression  */
#line 347 "parser.y"
        {
            ASTNode *n = make_node(NODE_ASSIGN);
            n->sval = strdup((yyvsp[-2].sval));
            n->left = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1926 "parser.tab.c"
    break;

  case 60: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression  */
#line 357 "parser.y"
        {
            ASTNode *n = make_node(NODE_ARRAY_ASSIGN);
            n->sval  = strdup((yyvsp[-5].sval));
            n->left  = (yyvsp[-3].node);   /* index  */
            n->right = (yyvsp[0].node);   /* value  */
            (yyval.node) = n;
        }
#line 1938 "parser.tab.c"
    break;

  case 61: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET ASSIGN expression  */
#line 365 "parser.y"
        {
            ASTNode *n = make_node(NODE_ARRAY_ASSIGN_2D);
            n->sval  = strdup((yyvsp[-8].sval));
            n->left  = (yyvsp[-6].node);   /* row   */
            n->right = (yyvsp[-3].node);   /* col   */
            n->extra = (yyvsp[0].node);   /* value */
            (yyval.node) = n;
        }
#line 1951 "parser.tab.c"
    break;

  case 62: /* expression: expression PLUS term  */
#line 380 "parser.y"
                             { (yyval.node) = make_binop(NODE_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1957 "parser.tab.c"
    break;

  case 63: /* expression: expression MINUS term  */
#line 381 "parser.y"
                             { (yyval.node) = make_binop(NODE_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1963 "parser.tab.c"
    break;

  case 64: /* expression: expression AND term  */
#line 382 "parser.y"
                                  { (yyval.node) = make_binop(NODE_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1969 "parser.tab.c"
    break;

  case 65: /* expression: expression OR term  */
#line 383 "parser.y"
                                  { (yyval.node) = make_binop(NODE_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1975 "parser.tab.c"
    break;

  case 66: /* expression: expression BIT_OR term  */
#line 384 "parser.y"
                                  { (yyval.node) = make_binop(NODE_BIT_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1981 "parser.tab.c"
    break;

  case 67: /* expression: expression BIT_XOR term  */
#line 385 "parser.y"
                                  { (yyval.node) = make_binop(NODE_BIT_XOR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1987 "parser.tab.c"
    break;

  case 68: /* expression: expression BIT_AND term  */
#line 386 "parser.y"
                                  { (yyval.node) = make_binop(NODE_BIT_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1993 "parser.tab.c"
    break;

  case 69: /* expression: expression SHL term  */
#line 387 "parser.y"
                                  { (yyval.node) = make_binop(NODE_SHL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1999 "parser.tab.c"
    break;

  case 70: /* expression: expression SHR term  */
#line 388 "parser.y"
                                  { (yyval.node) = make_binop(NODE_SHR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2005 "parser.tab.c"
    break;

  case 71: /* expression: MINUS term  */
#line 389 "parser.y"
                             { (yyval.node) = make_unary(NODE_NEGATE, (yyvsp[0].node)); }
#line 2011 "parser.tab.c"
    break;

  case 72: /* expression: NOT term  */
#line 390 "parser.y"
                                  { (yyval.node) = make_unary(NODE_NOT, (yyvsp[0].node)); }
#line 2017 "parser.tab.c"
    break;

  case 73: /* expression: BIT_NOT term  */
#line 391 "parser.y"
                                  { (yyval.node) = make_unary(NODE_BIT_NOT, (yyvsp[0].node)); }
#line 2023 "parser.tab.c"
    break;

  case 74: /* expression: term  */
#line 392 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2029 "parser.tab.c"
    break;

  case 75: /* term: term MUL factor  */
#line 396 "parser.y"
                        { (yyval.node) = make_binop(NODE_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2035 "parser.tab.c"
    break;

  case 76: /* term: term DIV factor  */
#line 397 "parser.y"
                        { (yyval.node) = make_binop(NODE_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2041 "parser.tab.c"
    break;

  case 77: /* term: term MOD factor  */
#line 398 "parser.y"
                        { (yyval.node) = make_binop(NODE_MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2047 "parser.tab.c"
    break;

  case 78: /* term: factor  */
#line 399 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2053 "parser.tab.c"
    break;

  case 79: /* factor: primary  */
#line 403 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2059 "parser.tab.c"
    break;

  case 80: /* primary: IDENTIFIER  */
#line 407 "parser.y"
                        { (yyval.node) = make_ident((yyvsp[0].sval)); }
#line 2065 "parser.tab.c"
    break;

  case 81: /* primary: INT_LITERAL  */
#line 408 "parser.y"
                        { (yyval.node) = make_int_lit((yyvsp[0].ival)); }
#line 2071 "parser.tab.c"
    break;

  case 82: /* primary: FLOAT_LITERAL  */
#line 409 "parser.y"
                        { (yyval.node) = make_float_lit((double)(yyvsp[0].fval)); }
#line 2077 "parser.tab.c"
    break;

  case 83: /* primary: TRUE_LITERAL  */
#line 410 "parser.y"
                        { (yyval.node) = make_bool_lit(1); }
#line 2083 "parser.tab.c"
    break;

  case 84: /* primary: FALSE_LITERAL  */
#line 411 "parser.y"
                        { (yyval.node) = make_bool_lit(0); }
#line 2089 "parser.tab.c"
    break;

  case 85: /* primary: CHAR_LITERAL  */
#line 412 "parser.y"
                        { (yyval.node) = make_char_lit((yyvsp[0].cval)); }
#line 2095 "parser.tab.c"
    break;

  case 86: /* primary: LPAREN expression RPAREN  */
#line 413 "parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2101 "parser.tab.c"
    break;

  case 87: /* primary: function_call  */
#line 414 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2107 "parser.tab.c"
    break;

  case 88: /* primary: array_access  */
#line 415 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2113 "parser.tab.c"
    break;

  case 89: /* primary: func_call_expr  */
#line 416 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2119 "parser.tab.c"
    break;

  case 90: /* func_call_expr: IDENTIFIER LPAREN arg_list_opt RPAREN  */
#line 421 "parser.y"
        {
            (yyval.node) = make_func_call((yyvsp[-3].sval), (yyvsp[-1].node));
        }
#line 2127 "parser.tab.c"
    break;

  case 91: /* arg_list_opt: arg_list  */
#line 427 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2133 "parser.tab.c"
    break;

  case 92: /* arg_list_opt: %empty  */
#line 428 "parser.y"
                  { (yyval.node) = NULL; }
#line 2139 "parser.tab.c"
    break;

  case 93: /* arg_list: arg_list COMMA expression  */
#line 433 "parser.y"
        {
            ASTNode *a = make_arg_list((yyvsp[0].node), NULL);
            /* append to end */
            if ((yyvsp[-2].node) == NULL) { (yyval.node) = a; }
            else {
                ASTNode *t = (yyvsp[-2].node);
                while (t->next) t = t->next;
                t->next = a;
                (yyval.node) = (yyvsp[-2].node);
            }
        }
#line 2155 "parser.tab.c"
    break;

  case 94: /* arg_list: expression  */
#line 445 "parser.y"
        {
            (yyval.node) = make_arg_list((yyvsp[0].node), NULL);
        }
#line 2163 "parser.tab.c"
    break;

  case 95: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 452 "parser.y"
        { (yyval.node) = make_array_access((yyvsp[-3].sval), (yyvsp[-1].node)); }
#line 2169 "parser.tab.c"
    break;

  case 96: /* array_access: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET  */
#line 454 "parser.y"
        { (yyval.node) = make_array_access_2d((yyvsp[-6].sval), (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2175 "parser.tab.c"
    break;

  case 97: /* function_call: POW LPAREN expression COMMA expression RPAREN  */
#line 463 "parser.y"
        { (yyval.node) = make_func2(NODE_POW, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2181 "parser.tab.c"
    break;

  case 98: /* function_call: SQRT LPAREN expression RPAREN  */
#line 465 "parser.y"
        { (yyval.node) = make_func1(NODE_SQRT, (yyvsp[-1].node)); }
#line 2187 "parser.tab.c"
    break;

  case 99: /* function_call: ABS LPAREN expression RPAREN  */
#line 467 "parser.y"
        { (yyval.node) = make_func1(NODE_ABS, (yyvsp[-1].node)); }
#line 2193 "parser.tab.c"
    break;

  case 100: /* function_call: FLOOR LPAREN expression RPAREN  */
#line 469 "parser.y"
        { (yyval.node) = make_func1(NODE_FLOOR, (yyvsp[-1].node)); }
#line 2199 "parser.tab.c"
    break;

  case 101: /* function_call: CEIL LPAREN expression RPAREN  */
#line 471 "parser.y"
        { (yyval.node) = make_func1(NODE_CEIL, (yyvsp[-1].node)); }
#line 2205 "parser.tab.c"
    break;

  case 102: /* print_stmt: PRINT LPAREN STRING_LITERAL print_end_opt RPAREN SEMI  */
#line 479 "parser.y"
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = strdup((yyvsp[-3].sval));   /* string literal */
            n->left = NULL;         /* marks this as a string-literal print */
            n->extra = (yyvsp[-2].node);
            (yyval.node) = n;
        }
#line 2217 "parser.tab.c"
    break;

  case 103: /* print_stmt: PRINT LPAREN expression print_end_opt RPAREN SEMI  */
#line 487 "parser.y"
        {
            /* Handle both identifier and expression cases */
            ASTNode *n = make_node(NODE_PRINT);
            
            /* Check if expression is just an identifier */
            if ((yyvsp[-3].node)->type == NODE_IDENT) {
                /* It's an identifier - print variable */
                n->sval = strdup((yyvsp[-3].node)->sval);
                n->left = (yyvsp[-3].node);  /* Keep the identifier node */
            } else {
                /* It's a complex expression */
                n->sval = NULL;
                n->left = (yyvsp[-3].node);
            }
            n->extra = (yyvsp[-2].node);
            (yyval.node) = n;
        }
#line 2239 "parser.tab.c"
    break;

  case 104: /* print_stmt: PRINT LPAREN print_end_opt RPAREN SEMI  */
#line 505 "parser.y"
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = NULL;
            n->left = NULL;
            n->extra = (yyvsp[-2].node);
            (yyval.node) = n;
        }
#line 2251 "parser.tab.c"
    break;

  case 105: /* print_end_opt: COMMA END ASSIGN STRING_LITERAL  */
#line 516 "parser.y"
        {
            ASTNode *n = make_node(NODE_STRING_LIT);
            n->sval = strdup((yyvsp[0].sval));
            (yyval.node) = n;
        }
#line 2261 "parser.tab.c"
    break;

  case 106: /* print_end_opt: %empty  */
#line 522 "parser.y"
        {
            (yyval.node) = NULL;
        }
#line 2269 "parser.tab.c"
    break;

  case 107: /* scan_stmt: SCAN LPAREN IDENTIFIER RPAREN SEMI  */
#line 528 "parser.y"
        {
            ASTNode *n = make_node(NODE_SCAN);
            n->sval = strdup((yyvsp[-2].sval));
            (yyval.node) = n;
        }
#line 2279 "parser.tab.c"
    break;

  case 108: /* scan_stmt: SCAN LPAREN IDENTIFIER LBRACKET expression RBRACKET RPAREN SEMI  */
#line 534 "parser.y"
        {
            ASTNode *n = make_node(NODE_SCAN_ARRAY);
            n->sval = strdup((yyvsp[-5].sval));
            n->left = (yyvsp[-3].node);   /* index expression */
            (yyval.node) = n;
        }
#line 2290 "parser.tab.c"
    break;

  case 109: /* condition: expression EQ expression  */
#line 547 "parser.y"
                                { (yyval.node) = make_binop(NODE_EQ,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2296 "parser.tab.c"
    break;

  case 110: /* condition: expression NEQ expression  */
#line 548 "parser.y"
                                { (yyval.node) = make_binop(NODE_NEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2302 "parser.tab.c"
    break;

  case 111: /* condition: expression GT expression  */
#line 549 "parser.y"
                                { (yyval.node) = make_binop(NODE_GT,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2308 "parser.tab.c"
    break;

  case 112: /* condition: expression LT expression  */
#line 550 "parser.y"
                                { (yyval.node) = make_binop(NODE_LT,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2314 "parser.tab.c"
    break;

  case 113: /* condition: expression GE expression  */
#line 551 "parser.y"
                                { (yyval.node) = make_binop(NODE_GE,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2320 "parser.tab.c"
    break;

  case 114: /* condition: expression LE expression  */
#line 552 "parser.y"
                                { (yyval.node) = make_binop(NODE_LE,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2326 "parser.tab.c"
    break;

  case 115: /* if_stmt: IF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part  */
#line 569 "parser.y"
        {
            ASTNode *n = make_node(NODE_IF);
            n->left  = (yyvsp[-5].node);   /* condition  */
            n->right = (yyvsp[-2].node);   /* then body  */
            n->extra = (yyvsp[0].node);   /* else chain */
            (yyval.node) = n;
        }
#line 2338 "parser.tab.c"
    break;

  case 116: /* else_if_part: ELSEIF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part  */
#line 580 "parser.y"
        {
            ASTNode *n = make_node(NODE_ELSEIF);
            n->left  = (yyvsp[-5].node);
            n->right = (yyvsp[-2].node);
            n->extra = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 2350 "parser.tab.c"
    break;

  case 117: /* else_if_part: ELSE LBRACE statement_list RBRACE  */
#line 588 "parser.y"
        {
            ASTNode *n = make_node(NODE_ELSE);
            n->left = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 2360 "parser.tab.c"
    break;

  case 118: /* else_if_part: %empty  */
#line 593 "parser.y"
                  { (yyval.node) = NULL; }
#line 2366 "parser.tab.c"
    break;

  case 119: /* switch_stmt: SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE  */
#line 607 "parser.y"
        {
            ASTNode *n = make_node(NODE_SWITCH);
            n->left  = (yyvsp[-4].node);   /* switch expression */
            n->right = (yyvsp[-1].node);   /* case list head    */
            (yyval.node) = n;
        }
#line 2377 "parser.tab.c"
    break;

  case 120: /* case_list: case_list case_item  */
#line 617 "parser.y"
        {
            /* append case_item to end of case_list */
            if ((yyvsp[-1].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
            else {
                ASTNode *tail = (yyvsp[-1].node);
                while (tail->next) tail = tail->next;
                tail->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-1].node);
            }
        }
#line 2392 "parser.tab.c"
    break;

  case 121: /* case_list: case_list default_item  */
#line 628 "parser.y"
        {
            if ((yyvsp[-1].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
            else {
                ASTNode *tail = (yyvsp[-1].node);
                while (tail->next) tail = tail->next;
                tail->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-1].node);
            }
        }
#line 2406 "parser.tab.c"
    break;

  case 122: /* case_list: %empty  */
#line 637 "parser.y"
                  { (yyval.node) = NULL; }
#line 2412 "parser.tab.c"
    break;

  case 123: /* case_item: CASE case_expr COLON statement_list  */
#line 642 "parser.y"
        {
            /*
             * case_expr is either NODE_CASE or NODE_CASE_RANGE.
             * We attach the body to whichever node was built.
             */
            ASTNode *c = (yyvsp[-2].node);
            if (c->type == NODE_CASE) {
                /* left = value expr (already set), right = body */
                c->right = (yyvsp[0].node);
            } else {
                /* NODE_CASE_RANGE: left=start, right=end, extra=body */
                c->extra = (yyvsp[0].node);
            }
            (yyval.node) = c;
        }
#line 2432 "parser.tab.c"
    break;

  case 124: /* case_expr: expression  */
#line 661 "parser.y"
        {
            ASTNode *n = make_node(NODE_CASE);
            n->left = (yyvsp[0].node);   /* case value expression */
            (yyval.node) = n;
        }
#line 2442 "parser.tab.c"
    break;

  case 125: /* case_expr: expression RANGE expression  */
#line 667 "parser.y"
        {
            ASTNode *n = make_node(NODE_CASE_RANGE);
            n->left  = (yyvsp[-2].node);  /* range start */
            n->right = (yyvsp[0].node);  /* range end   */
            (yyval.node) = n;
        }
#line 2453 "parser.tab.c"
    break;

  case 126: /* default_item: DEFAULT COLON statement_list  */
#line 677 "parser.y"
        {
            ASTNode *n = make_node(NODE_DEFAULT);
            n->left = (yyvsp[0].node);   /* body */
            (yyval.node) = n;
        }
#line 2463 "parser.tab.c"
    break;

  case 127: /* for_init: assignment  */
#line 704 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2469 "parser.tab.c"
    break;

  case 128: /* for_init: declaration_no_semi  */
#line 705 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2475 "parser.tab.c"
    break;

  case 129: /* for_init: %empty  */
#line 706 "parser.y"
                  { (yyval.node) = NULL; }
#line 2481 "parser.tab.c"
    break;

  case 130: /* for_update: assignment  */
#line 710 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2487 "parser.tab.c"
    break;

  case 131: /* for_update: %empty  */
#line 711 "parser.y"
                  { (yyval.node) = NULL; }
#line 2493 "parser.tab.c"
    break;

  case 132: /* loop_stmt: WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE  */
#line 716 "parser.y"
        {
            ASTNode *n = make_node(NODE_WHILE);
            n->left  = (yyvsp[-4].node);   /* condition */
            n->right = (yyvsp[-1].node);   /* body      */
            (yyval.node) = n;
        }
#line 2504 "parser.tab.c"
    break;

  case 133: /* loop_stmt: DO LBRACE statement_list RBRACE WHILE LPAREN condition RPAREN SEMI  */
#line 723 "parser.y"
        {
            ASTNode *n = make_node(NODE_DO_WHILE);
            n->left  = (yyvsp[-6].node);   /* body      */
            n->right = (yyvsp[-2].node);   /* condition */
            (yyval.node) = n;
        }
#line 2515 "parser.tab.c"
    break;

  case 134: /* loop_stmt: FOR LPAREN for_init SEMI condition SEMI for_update RPAREN LBRACE statement_list RBRACE  */
#line 731 "parser.y"
        {
            /* pack condition + update into a helper node */
            ASTNode *parts = make_node(NODE_STMT_LIST);
            parts->left  = (yyvsp[-6].node);   /* condition */
            parts->right = (yyvsp[-4].node);   /* update    */

            ASTNode *n = make_node(NODE_FOR);
            n->left  = (yyvsp[-8].node);      /* init  */
            n->right = (yyvsp[-1].node);     /* body  */
            n->extra = parts;   /* parts */
            (yyval.node) = n;
        }
#line 2532 "parser.tab.c"
    break;

  case 135: /* return_stmt: RETURN expression  */
#line 751 "parser.y"
        {
            ASTNode *n = make_node(NODE_RETURN);
            n->left = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 2542 "parser.tab.c"
    break;


#line 2546 "parser.tab.c"

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

#line 758 "parser.y"


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
