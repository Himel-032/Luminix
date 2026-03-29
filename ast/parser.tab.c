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
  YYSYMBOL_IN = 54,                        /* IN  */
  YYSYMBOL_INCREMENT = 55,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 56,                 /* DECREMENT  */
  YYSYMBOL_PLUS = 57,                      /* PLUS  */
  YYSYMBOL_MINUS = 58,                     /* MINUS  */
  YYSYMBOL_MUL = 59,                       /* MUL  */
  YYSYMBOL_DIV = 60,                       /* DIV  */
  YYSYMBOL_MOD = 61,                       /* MOD  */
  YYSYMBOL_ASSIGN = 62,                    /* ASSIGN  */
  YYSYMBOL_BIT_AND = 63,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 64,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 65,                   /* BIT_XOR  */
  YYSYMBOL_BIT_NOT = 66,                   /* BIT_NOT  */
  YYSYMBOL_SHL = 67,                       /* SHL  */
  YYSYMBOL_SHR = 68,                       /* SHR  */
  YYSYMBOL_SEMI = 69,                      /* SEMI  */
  YYSYMBOL_COMMA = 70,                     /* COMMA  */
  YYSYMBOL_COLON = 71,                     /* COLON  */
  YYSYMBOL_LPAREN = 72,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 73,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 74,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 75,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 76,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 77,                  /* RBRACKET  */
  YYSYMBOL_RANGE = 78,                     /* RANGE  */
  YYSYMBOL_INT_LITERAL = 79,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 80,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 81,            /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 82,              /* CHAR_LITERAL  */
  YYSYMBOL_IDENTIFIER = 83,                /* IDENTIFIER  */
  YYSYMBOL_UNARY = 84,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 85,                  /* $accept  */
  YYSYMBOL_program = 86,                   /* program  */
  YYSYMBOL_top_level_list = 87,            /* top_level_list  */
  YYSYMBOL_func_def = 88,                  /* func_def  */
  YYSYMBOL_ret_type = 89,                  /* ret_type  */
  YYSYMBOL_param_list = 90,                /* param_list  */
  YYSYMBOL_param = 91,                     /* param  */
  YYSYMBOL_preprocessor_list = 92,         /* preprocessor_list  */
  YYSYMBOL_preprocessor = 93,              /* preprocessor  */
  YYSYMBOL_main_function = 94,             /* main_function  */
  YYSYMBOL_statement_list = 95,            /* statement_list  */
  YYSYMBOL_statement = 96,                 /* statement  */
  YYSYMBOL_declaration = 97,               /* declaration  */
  YYSYMBOL_declaration_no_semi = 98,       /* declaration_no_semi  */
  YYSYMBOL_array_size = 99,                /* array_size  */
  YYSYMBOL_type = 100,                     /* type  */
  YYSYMBOL_identifier_list_decls = 101,    /* identifier_list_decls  */
  YYSYMBOL_assignment = 102,               /* assignment  */
  YYSYMBOL_array_assignment = 103,         /* array_assignment  */
  YYSYMBOL_expression = 104,               /* expression  */
  YYSYMBOL_term = 105,                     /* term  */
  YYSYMBOL_factor = 106,                   /* factor  */
  YYSYMBOL_primary = 107,                  /* primary  */
  YYSYMBOL_func_call_expr = 108,           /* func_call_expr  */
  YYSYMBOL_arg_list_opt = 109,             /* arg_list_opt  */
  YYSYMBOL_arg_list = 110,                 /* arg_list  */
  YYSYMBOL_array_access = 111,             /* array_access  */
  YYSYMBOL_function_call = 112,            /* function_call  */
  YYSYMBOL_print_stmt = 113,               /* print_stmt  */
  YYSYMBOL_print_end_opt = 114,            /* print_end_opt  */
  YYSYMBOL_scan_stmt = 115,                /* scan_stmt  */
  YYSYMBOL_condition = 116,                /* condition  */
  YYSYMBOL_if_stmt = 117,                  /* if_stmt  */
  YYSYMBOL_else_if_part = 118,             /* else_if_part  */
  YYSYMBOL_switch_stmt = 119,              /* switch_stmt  */
  YYSYMBOL_case_list = 120,                /* case_list  */
  YYSYMBOL_case_item = 121,                /* case_item  */
  YYSYMBOL_case_expr = 122,                /* case_expr  */
  YYSYMBOL_default_item = 123,             /* default_item  */
  YYSYMBOL_for_init = 124,                 /* for_init  */
  YYSYMBOL_for_update = 125,               /* for_update  */
  YYSYMBOL_loop_stmt = 126,                /* loop_stmt  */
  YYSYMBOL_return_stmt = 127               /* return_stmt  */
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
#define YYLAST   1121

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  139
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  321

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   339


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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   107,   107,   111,   112,   113,   117,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   142,   153,   154,   158,
     166,   167,   171,   172,   176,   196,   212,   216,   217,   218,
     224,   230,   231,   232,   233,   234,   235,   239,   243,   244,
     245,   246,   254,   256,   264,   277,   285,   296,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   317,   325,   333,
     342,   358,   368,   376,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   408,   409,   410,
     411,   415,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   432,   439,   440,   444,   456,   463,   465,   474,
     476,   478,   480,   482,   490,   498,   516,   527,   534,   539,
     545,   559,   560,   561,   562,   563,   564,   580,   591,   599,
     605,   618,   628,   639,   649,   653,   672,   678,   688,   716,
     717,   718,   722,   723,   727,   734,   741,   755,   765,   787
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
  "GE", "LE", "GT", "LT", "AND", "OR", "NOT", "INC", "DEC", "IN",
  "INCREMENT", "DECREMENT", "PLUS", "MINUS", "MUL", "DIV", "MOD", "ASSIGN",
  "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT", "SHL", "SHR", "SEMI", "COMMA",
  "COLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
  "RANGE", "INT_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL",
  "CHAR_LITERAL", "IDENTIFIER", "UNARY", "$accept", "program",
  "top_level_list", "func_def", "ret_type", "param_list", "param",
  "preprocessor_list", "preprocessor", "main_function", "statement_list",
  "statement", "declaration", "declaration_no_semi", "array_size", "type",
  "identifier_list_decls", "assignment", "array_assignment", "expression",
  "term", "factor", "primary", "func_call_expr", "arg_list_opt",
  "arg_list", "array_access", "function_call", "print_stmt",
  "print_end_opt", "scan_stmt", "condition", "if_stmt", "else_if_part",
  "switch_stmt", "case_list", "case_item", "case_expr", "default_item",
  "for_init", "for_update", "loop_stmt", "return_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-155)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -155,    34,    77,  -155,    39,   -33,   853,  -155,  -155,   -27,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,   -14,
    -155,    -6,  -155,  -155,   -17,    43,    46,   331,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,   -22,  -155,
      44,   158,   331,    54,  -155,    58,    61,   -23,    62,    64,
      63,    66,   647,    69,    70,    65,    67,  -155,   -48,  -155,
    -155,    72,    75,    76,    78,  -155,  -155,  -155,  -155,  -155,
      82,  -155,  -155,   670,   670,    60,    92,   670,  -155,  -155,
    -155,  -155,  -155,    80,    81,    84,    85,    87,    57,    57,
      57,  -155,   670,  -155,  -155,  -155,   -46,  1053,    41,  -155,
    -155,  -155,  -155,  -155,   598,    79,    94,   104,   670,   670,
     670,   -29,   108,  -155,  -155,  -155,  -155,   271,   825,    88,
     859,   117,  -155,    99,  -155,   114,   118,   122,   302,   670,
     670,   670,   670,   670,    41,    41,    41,   871,   670,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,   161,   127,   987,   125,     2,  -155,  -155,  1053,  1053,
     126,   130,   697,   670,   119,   128,  -155,  -155,   670,   670,
     670,   670,   670,   670,   132,   135,   142,   670,   670,   136,
     184,  1009,   891,   903,   923,   935,  -155,   718,    41,    41,
      41,    41,    41,    41,    41,    41,    41,  -155,  -155,  -155,
     153,   144,   145,   151,   154,   670,  -155,   670,   -51,  1031,
     -58,  -155,  -155,   148,  1053,  1053,  1053,  1053,  1053,  1053,
    -155,  -155,   670,   160,   196,  -155,   150,   670,  -155,  -155,
    -155,  -155,   155,   146,   163,   165,  -155,  -155,   739,  1053,
     670,   670,   119,   -63,   353,   -16,  1053,   147,   670,   384,
     670,   955,   670,  -155,  -155,  -155,   162,  1053,   760,  -155,
    -155,   128,    68,   670,   166,  -155,  -155,  -155,  -155,   167,
     837,  -155,   175,  -155,   781,   170,   174,   172,   176,   179,
    -155,   594,   181,  -155,   182,   670,   183,   189,  -155,  -155,
     670,   198,  -155,   670,   670,  -155,     9,  -155,   967,  -155,
    -155,  1053,  -155,   435,   197,  1053,     9,   466,   195,   517,
    -155,   199,  -155,  -155,  -155,  -155,   548,   599,  -155,    68,
    -155
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      21,     0,     5,     1,     0,     0,     2,    20,    22,     0,
       7,     8,     9,    10,    11,    12,    13,    14,    15,     0,
       3,     0,     4,    23,     0,     0,     0,    18,    26,    48,
      49,    50,    51,    52,    53,    54,    55,    56,     0,    17,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,    25,
      27,     0,     0,     0,     0,    32,    33,    34,    35,    38,
       0,    16,    26,     0,     0,   131,     0,     0,    26,    36,
      37,    85,    86,     0,     0,     0,     0,     0,     0,     0,
       0,    41,     0,    83,    84,    87,    82,   139,    76,    80,
      81,    91,    90,    89,   108,     0,     0,     0,     0,    94,
       0,    57,     0,    28,    31,    40,    39,     0,     0,     0,
       0,     0,   130,     0,   129,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    74,    73,    75,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   108,   108,     0,     0,    29,    30,    61,    96,
       0,    93,     0,     0,     0,     0,    42,     6,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,    66,    67,
      64,    65,    70,    68,    69,    71,    72,    77,    78,    79,
       0,     0,     0,     0,     0,     0,    92,     0,     0,    58,
      57,    59,    47,     0,   111,   112,   115,   116,   113,   114,
      26,   124,     0,     0,     0,    26,     0,     0,   100,   101,
     102,   103,    97,     0,     0,     0,   106,   109,     0,    95,
       0,     0,     0,     0,     0,     0,    46,   133,     0,     0,
       0,     0,     0,   107,   104,   105,     0,    62,     0,    60,
      43,     0,   120,     0,     0,   121,   122,   123,   132,     0,
       0,   134,     0,    99,     0,     0,     0,     0,     0,     0,
     117,   126,     0,    26,     0,     0,     0,     0,    98,   110,
       0,     0,    26,     0,     0,    26,   128,    26,     0,    26,
     135,    63,    44,     0,     0,   127,   125,     0,     0,     0,
     119,     0,   136,    26,   137,    26,     0,     0,   138,   120,
     118
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,  -155,  -155,  -155,  -155,   229,  -155,  -155,  -155,
     -71,  -155,  -155,  -155,    11,     4,  -154,   -73,  -155,   -47,
     -35,   -31,  -155,   -41,  -155,  -155,  -155,  -155,  -155,   -39,
    -155,   -74,  -155,   -32,  -155,  -155,  -155,  -155,  -155,  -155,
    -155,  -155,  -155
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     6,    20,    21,    38,    39,     2,     7,    22,
      41,    59,    60,   122,   213,    61,   112,    62,    63,   118,
      98,    99,   100,   101,   160,   161,   102,   103,    65,   154,
      66,   119,    67,   280,    68,   245,   266,   282,   267,   125,
     269,    69,    70
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,   117,   124,   127,   163,    97,   260,   128,   263,   264,
     211,   240,   164,   261,   108,    29,    30,    31,    32,    33,
      34,    35,    36,    37,   109,   241,   109,   120,   110,    45,
     138,    40,    46,   163,     3,    47,    48,    49,    50,    51,
      52,   164,    53,    54,     8,   137,    40,   165,    42,    75,
       9,    43,    23,   134,   135,   136,    26,   153,    24,   265,
      76,   158,   159,   162,    55,    56,    29,    30,    31,    32,
      33,    34,    35,    36,    37,   204,    64,    25,   205,   123,
       4,     5,   181,   182,   183,   184,   185,    64,   259,   278,
     279,   187,    58,    81,    82,    83,    84,    85,    86,    87,
     148,   149,   150,   223,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   201,   202,    27,   209,   197,   198,   199,
      28,   214,   215,   216,   217,   218,   219,    44,    72,    92,
      73,   224,    79,    74,    77,    80,    93,    94,    78,    95,
      96,   104,   105,   121,   113,   114,   126,   115,   106,   244,
     107,   116,   129,   130,   249,   111,   131,   132,   238,   133,
     239,   174,   155,   156,    29,    30,    31,    32,    33,    34,
      35,    36,    37,   157,   268,   246,   272,   166,    45,   108,
     251,    46,   176,   177,    47,    48,    49,    50,    51,    52,
     178,    53,    54,   257,   258,   179,   200,   151,   203,   206,
     207,   270,   210,    64,   222,   274,   220,   212,    64,   221,
     225,   226,   296,    55,    56,   233,   281,   234,   235,   304,
     236,   303,   250,   237,   306,   243,   307,   253,   309,   247,
     121,   252,   254,    57,   255,   275,   290,   283,   298,   289,
     284,    58,   316,   301,   317,   139,   140,   305,   287,   291,
     292,   293,   295,   141,   142,    64,   297,   299,   300,   143,
     144,   145,    64,   146,   147,    64,    64,   302,    64,   313,
     311,    71,   277,   315,   248,    64,    64,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     0,   320,     0,     0,
       0,    45,     0,     0,    46,     0,     0,    47,    48,    49,
      50,    51,    52,     0,    53,    54,     0,     0,    29,    30,
      31,    32,    33,    34,    35,    36,    37,     0,     0,     0,
       0,     0,    45,     0,     0,    46,    55,    56,    47,    48,
      49,    50,    51,    52,     0,    53,    54,    29,    30,    31,
      32,    33,    34,    35,    36,    37,   167,     0,     0,     0,
       0,     0,     0,     0,    58,     0,     0,    55,    56,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     0,     0,
       0,     0,     0,    45,     0,     0,    46,   180,     0,    47,
      48,    49,    50,    51,    52,    58,    53,    54,     0,     0,
      29,    30,    31,    32,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     0,    45,     0,     0,    46,    55,    56,
      47,    48,    49,    50,    51,    52,     0,    53,    54,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   262,     0,
       0,     0,     0,     0,     0,     0,    58,     0,     0,    55,
      56,    29,    30,    31,    32,    33,    34,    35,    36,    37,
       0,     0,     0,     0,     0,    45,     0,     0,    46,   271,
       0,    47,    48,    49,    50,    51,    52,    58,    53,    54,
       0,     0,    29,    30,    31,    32,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     0,    45,     0,     0,    46,
      55,    56,    47,    48,    49,    50,    51,    52,     0,    53,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     310,     0,     0,     0,     0,     0,     0,     0,    58,     0,
       0,    55,    56,    29,    30,    31,    32,    33,    34,    35,
      36,    37,     0,     0,     0,     0,     0,    45,     0,     0,
      46,   312,     0,    47,    48,    49,    50,    51,    52,    58,
      53,    54,     0,     0,    29,    30,    31,    32,    33,    34,
      35,    36,    37,     0,     0,     0,     0,     0,    45,     0,
       0,    46,    55,    56,    47,    48,    49,    50,    51,    52,
       0,    53,    54,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   314,     0,     0,     0,     0,     0,     0,     0,
      58,     0,     0,    55,    56,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     0,     0,     0,     0,     0,    45,
       0,     0,    46,   318,     0,    47,    48,    49,    50,    51,
      52,    58,    53,    54,    81,    82,    83,    84,    85,    86,
      87,     0,     0,   139,   140,     0,     0,     0,     0,    88,
       0,   141,   142,     0,    55,    56,    89,   143,   144,   145,
       0,   146,   147,     0,    90,     0,     0,     0,   151,     0,
      92,     0,   294,     0,   319,     0,     0,    93,    94,   152,
      95,    96,    58,    81,    82,    83,    84,    85,    86,    87,
       0,     0,     0,     0,     0,     0,     0,     0,    88,     0,
       0,     0,     0,     0,     0,    89,    81,    82,    83,    84,
      85,    86,    87,    90,     0,     0,    91,     0,     0,    92,
       0,    88,     0,     0,     0,     0,    93,    94,    89,    95,
      96,     0,     0,     0,     0,     0,    90,     0,     0,     0,
       0,     0,    92,     0,     0,     0,   139,   140,     0,    93,
      94,     0,    95,    96,   141,   142,     0,     0,     0,     0,
     143,   144,   145,     0,   146,   147,     0,   139,   140,     0,
       0,     0,     0,     0,   208,   141,   142,     0,     0,     0,
       0,   143,   144,   145,     0,   146,   147,     0,   139,   140,
       0,     0,     0,     0,     0,   232,   141,   142,     0,     0,
       0,     0,   143,   144,   145,     0,   146,   147,     0,   139,
     140,     0,     0,     0,     0,     0,   256,   141,   142,     0,
       0,     0,     0,   143,   144,   145,     0,   146,   147,     0,
     139,   140,     0,     0,     0,     0,     0,   276,   141,   142,
       0,     0,     0,     0,   143,   144,   145,     0,   146,   147,
       0,     0,     0,     0,     0,     0,     0,     0,   288,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   168,   169,
     170,   171,   172,   173,   139,   140,     0,     0,     0,     0,
       0,     0,   141,   142,     0,    19,   139,   140,   143,   144,
     145,     0,   146,   147,   141,   142,     0,     0,     0,     0,
     143,   144,   145,     0,   146,   147,     0,   285,   139,   140,
     286,     0,     0,     0,     0,     0,   141,   142,     0,     0,
     139,   140,   143,   144,   145,     0,   146,   147,   141,   142,
       0,     0,   175,     0,   143,   144,   145,     0,   146,   147,
     139,   140,     0,     0,   186,     0,     0,     0,   141,   142,
       0,     0,   139,   140,   143,   144,   145,     0,   146,   147,
     141,   142,     0,     0,   228,     0,   143,   144,   145,     0,
     146,   147,   139,   140,     0,     0,   229,     0,     0,     0,
     141,   142,     0,     0,   139,   140,   143,   144,   145,     0,
     146,   147,   141,   142,     0,     0,   230,     0,   143,   144,
     145,     0,   146,   147,   139,   140,     0,     0,   231,     0,
       0,     0,   141,   142,     0,     0,   139,   140,   143,   144,
     145,     0,   146,   147,   141,   142,     0,     0,   273,     0,
     143,   144,   145,     0,   146,   147,   139,   140,     0,     0,
     308,     0,     0,     0,   141,   142,     0,     0,     0,     0,
     143,   144,   145,     0,   146,   147,     0,   151,   139,   140,
       0,     0,     0,     0,     0,     0,   141,   142,     0,     0,
       0,     0,   143,   144,   145,     0,   146,   147,     0,   227,
     139,   140,     0,     0,     0,     0,     0,     0,   141,   142,
       0,     0,     0,     0,   143,   144,   145,     0,   146,   147,
       0,   242,   139,   140,     0,     0,     0,     0,     0,     0,
     141,   142,     0,     0,     0,     0,   143,   144,   145,     0,
     146,   147
};

static const yytype_int16 yycheck[] =
{
      41,    72,    75,    77,    62,    52,    69,    78,    24,    25,
     164,    62,    70,    76,    62,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    72,    76,    72,    74,    76,    20,
      76,    27,    23,    62,     0,    26,    27,    28,    29,    30,
      31,    70,    33,    34,     5,    92,    42,    76,    70,    72,
      83,    73,    79,    88,    89,    90,    73,   104,    72,    75,
      83,   108,   109,   110,    55,    56,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    73,   117,    83,    76,    75,
       3,     4,   129,   130,   131,   132,   133,   128,   242,    21,
      22,   138,    83,    36,    37,    38,    39,    40,    41,    42,
      59,    60,    61,   177,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   152,   153,    72,   163,   148,   149,   150,
      74,   168,   169,   170,   171,   172,   173,    83,    74,    72,
      72,   178,    69,    72,    72,    69,    79,    80,    74,    82,
      83,    72,    72,    83,    69,    69,    54,    69,    83,   220,
      83,    69,    72,    72,   225,    83,    72,    72,   205,    72,
     207,    73,    83,    69,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    69,   247,   222,   250,    69,    20,    62,
     227,    23,    83,    69,    26,    27,    28,    29,    30,    31,
      72,    33,    34,   240,   241,    73,    35,    70,    73,    73,
      70,   248,    83,   244,    62,   252,    74,    79,   249,    74,
      74,    27,   283,    55,    56,    62,   263,    73,    73,   293,
      69,   292,    72,    69,   295,    77,   297,    81,   299,    69,
      83,    76,    69,    75,    69,    73,    62,    71,   285,    69,
      73,    83,   313,   290,   315,    49,    50,   294,    73,    77,
      74,    72,    71,    57,    58,   296,    74,    74,    69,    63,
      64,    65,   303,    67,    68,   306,   307,    69,   309,    74,
      73,    42,   261,    74,    78,   316,   317,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,   319,    -1,    -1,
      -1,    20,    -1,    -1,    23,    -1,    -1,    26,    27,    28,
      29,    30,    31,    -1,    33,    34,    -1,    -1,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    23,    55,    56,    26,    27,
      28,    29,    30,    31,    -1,    33,    34,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    -1,    -1,    55,    56,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    23,    75,    -1,    26,
      27,    28,    29,    30,    31,    83,    33,    34,    -1,    -1,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    23,    55,    56,
      26,    27,    28,    29,    30,    31,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    55,
      56,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    23,    75,
      -1,    26,    27,    28,    29,    30,    31,    83,    33,    34,
      -1,    -1,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    23,
      55,    56,    26,    27,    28,    29,    30,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,
      -1,    55,    56,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      23,    75,    -1,    26,    27,    28,    29,    30,    31,    83,
      33,    34,    -1,    -1,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    23,    55,    56,    26,    27,    28,    29,    30,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    -1,    -1,    55,    56,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    23,    75,    -1,    26,    27,    28,    29,    30,
      31,    83,    33,    34,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    49,    50,    -1,    -1,    -1,    -1,    51,
      -1,    57,    58,    -1,    55,    56,    58,    63,    64,    65,
      -1,    67,    68,    -1,    66,    -1,    -1,    -1,    70,    -1,
      72,    -1,    78,    -1,    75,    -1,    -1,    79,    80,    81,
      82,    83,    83,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    36,    37,    38,    39,
      40,    41,    42,    66,    -1,    -1,    69,    -1,    -1,    72,
      -1,    51,    -1,    -1,    -1,    -1,    79,    80,    58,    82,
      83,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    -1,    49,    50,    -1,    79,
      80,    -1,    82,    83,    57,    58,    -1,    -1,    -1,    -1,
      63,    64,    65,    -1,    67,    68,    -1,    49,    50,    -1,
      -1,    -1,    -1,    -1,    77,    57,    58,    -1,    -1,    -1,
      -1,    63,    64,    65,    -1,    67,    68,    -1,    49,    50,
      -1,    -1,    -1,    -1,    -1,    77,    57,    58,    -1,    -1,
      -1,    -1,    63,    64,    65,    -1,    67,    68,    -1,    49,
      50,    -1,    -1,    -1,    -1,    -1,    77,    57,    58,    -1,
      -1,    -1,    -1,    63,    64,    65,    -1,    67,    68,    -1,
      49,    50,    -1,    -1,    -1,    -1,    -1,    77,    57,    58,
      -1,    -1,    -1,    -1,    63,    64,    65,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    -1,    32,    49,    50,    63,    64,
      65,    -1,    67,    68,    57,    58,    -1,    -1,    -1,    -1,
      63,    64,    65,    -1,    67,    68,    -1,    70,    49,    50,
      73,    -1,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,
      49,    50,    63,    64,    65,    -1,    67,    68,    57,    58,
      -1,    -1,    73,    -1,    63,    64,    65,    -1,    67,    68,
      49,    50,    -1,    -1,    73,    -1,    -1,    -1,    57,    58,
      -1,    -1,    49,    50,    63,    64,    65,    -1,    67,    68,
      57,    58,    -1,    -1,    73,    -1,    63,    64,    65,    -1,
      67,    68,    49,    50,    -1,    -1,    73,    -1,    -1,    -1,
      57,    58,    -1,    -1,    49,    50,    63,    64,    65,    -1,
      67,    68,    57,    58,    -1,    -1,    73,    -1,    63,    64,
      65,    -1,    67,    68,    49,    50,    -1,    -1,    73,    -1,
      -1,    -1,    57,    58,    -1,    -1,    49,    50,    63,    64,
      65,    -1,    67,    68,    57,    58,    -1,    -1,    73,    -1,
      63,    64,    65,    -1,    67,    68,    49,    50,    -1,    -1,
      73,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    -1,
      63,    64,    65,    -1,    67,    68,    -1,    70,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    -1,    63,    64,    65,    -1,    67,    68,    -1,    70,
      49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    -1,    63,    64,    65,    -1,    67,    68,
      -1,    70,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,    -1,
      67,    68
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    86,    92,     0,     3,     4,    87,    93,     5,    83,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    32,
      88,    89,    94,    79,    72,    83,    73,    72,    74,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    90,    91,
     100,    95,    70,    73,    83,    20,    23,    26,    27,    28,
      29,    30,    31,    33,    34,    55,    56,    75,    83,    96,
      97,   100,   102,   103,   108,   113,   115,   117,   119,   126,
     127,    91,    74,    72,    72,    72,    83,    72,    74,    69,
      69,    36,    37,    38,    39,    40,    41,    42,    51,    58,
      66,    69,    72,    79,    80,    82,    83,   104,   105,   106,
     107,   108,   111,   112,    72,    72,    83,    83,    62,    72,
      76,    83,   101,    69,    69,    69,    69,    95,   104,   116,
     104,    83,    98,   100,   102,   124,    54,   116,    95,    72,
      72,    72,    72,    72,   105,   105,   105,   104,    76,    49,
      50,    57,    58,    63,    64,    65,    67,    68,    59,    60,
      61,    70,    81,   104,   114,    83,    69,    69,   104,   104,
     109,   110,   104,    62,    70,    76,    69,    75,    43,    44,
      45,    46,    47,    48,    73,    73,    83,    69,    72,    73,
      75,   104,   104,   104,   104,   104,    73,   104,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   106,
      35,   114,   114,    73,    73,    76,    73,    70,    77,   104,
      83,   101,    79,    99,   104,   104,   104,   104,   104,   104,
      74,    74,    62,   116,   104,    74,    27,    70,    73,    73,
      73,    73,    77,    62,    73,    73,    69,    69,   104,   104,
      62,    76,    70,    77,    95,   120,   104,    69,    78,    95,
      72,   104,    76,    81,    69,    69,    77,   104,   104,   101,
      69,    76,    75,    24,    25,    75,   121,   123,   102,   125,
     104,    75,   116,    73,   104,    73,    77,    99,    21,    22,
     118,   104,   122,    71,    73,    70,    73,    73,    77,    69,
      62,    77,    74,    72,    78,    71,    95,    74,   104,    74,
      69,   104,    69,    95,   116,   104,    95,    95,    73,    95,
      75,    73,    75,    74,    75,    74,    95,    95,    75,    75,
     118
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    85,    86,    87,    87,    87,    88,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    90,    90,    90,    91,
      92,    92,    93,    93,    94,    95,    95,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    97,    97,    97,    98,    98,    99,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   101,   101,   101,
     101,   102,   103,   103,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   105,   105,   105,
     105,   106,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   112,   112,   112,   113,   113,   113,   114,   114,   115,
     115,   116,   116,   116,   116,   116,   116,   117,   118,   118,
     118,   119,   120,   120,   120,   121,   122,   122,   123,   124,
     124,   124,   125,   125,   126,   126,   126,   126,   126,   127
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     8,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     2,
       2,     0,     2,     3,     6,     2,     0,     1,     2,     3,
       3,     2,     1,     1,     1,     1,     2,     2,     1,     2,
       2,     2,     3,     6,     9,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       5,     3,     6,     9,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     1,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     4,     1,     0,     3,     1,     4,     7,     6,
       4,     4,     4,     4,     6,     6,     5,     4,     0,     5,
       8,     3,     3,     3,     3,     3,     3,     8,     8,     4,
       0,     7,     2,     2,     0,     4,     1,     3,     3,     1,
       1,     0,     1,     0,     7,     9,    11,    11,    13,     2
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
#line 1592 "parser.tab.c"
    break;

  case 7: /* ret_type: INT_TYPE  */
#line 131 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1598 "parser.tab.c"
    break;

  case 8: /* ret_type: FLOAT_TYPE  */
#line 132 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1604 "parser.tab.c"
    break;

  case 9: /* ret_type: DOUBLE_TYPE  */
#line 133 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1610 "parser.tab.c"
    break;

  case 10: /* ret_type: CHAR_TYPE  */
#line 134 "parser.y"
                    { (yyval.ival) = 1; current_decl_type = 1; }
#line 1616 "parser.tab.c"
    break;

  case 11: /* ret_type: BOOL_TYPE  */
#line 135 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1622 "parser.tab.c"
    break;

  case 12: /* ret_type: VOID_TYPE  */
#line 136 "parser.y"
                    { (yyval.ival) = 2; current_decl_type = 0; }
#line 1628 "parser.tab.c"
    break;

  case 13: /* ret_type: LONG_TYPE  */
#line 137 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1634 "parser.tab.c"
    break;

  case 14: /* ret_type: SHORT_TYPE  */
#line 138 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1640 "parser.tab.c"
    break;

  case 15: /* ret_type: UNSIGNED_TYPE  */
#line 139 "parser.y"
                    { (yyval.ival) = 0; current_decl_type = 0; }
#line 1646 "parser.tab.c"
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
#line 1661 "parser.tab.c"
    break;

  case 17: /* param_list: param  */
#line 153 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1667 "parser.tab.c"
    break;

  case 18: /* param_list: %empty  */
#line 154 "parser.y"
                    { (yyval.node) = NULL; }
#line 1673 "parser.tab.c"
    break;

  case 19: /* param: type IDENTIFIER  */
#line 159 "parser.y"
        {
            (yyval.node) = make_param((yyvsp[0].sval), current_decl_type);
        }
#line 1681 "parser.tab.c"
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
#line 1698 "parser.tab.c"
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
#line 1718 "parser.tab.c"
    break;

  case 26: /* statement_list: %empty  */
#line 212 "parser.y"
                  { (yyval.node) = NULL; }
#line 1724 "parser.tab.c"
    break;

  case 27: /* statement: declaration  */
#line 216 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1730 "parser.tab.c"
    break;

  case 28: /* statement: assignment SEMI  */
#line 217 "parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1736 "parser.tab.c"
    break;

  case 29: /* statement: INCREMENT IDENTIFIER SEMI  */
#line 219 "parser.y"
        {
            ASTNode *n = make_node(NODE_INCREMENT);
            n->sval = strdup((yyvsp[-1].sval));
            (yyval.node) = n;
        }
#line 1746 "parser.tab.c"
    break;

  case 30: /* statement: DECREMENT IDENTIFIER SEMI  */
#line 225 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECREMENT);
            n->sval = strdup((yyvsp[-1].sval));
            (yyval.node) = n;
        }
#line 1756 "parser.tab.c"
    break;

  case 31: /* statement: array_assignment SEMI  */
#line 230 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1762 "parser.tab.c"
    break;

  case 32: /* statement: print_stmt  */
#line 231 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1768 "parser.tab.c"
    break;

  case 33: /* statement: scan_stmt  */
#line 232 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1774 "parser.tab.c"
    break;

  case 34: /* statement: if_stmt  */
#line 233 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1780 "parser.tab.c"
    break;

  case 35: /* statement: switch_stmt  */
#line 234 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1786 "parser.tab.c"
    break;

  case 36: /* statement: BREAK SEMI  */
#line 236 "parser.y"
        {
            (yyval.node) = make_node(NODE_BREAK);
        }
#line 1794 "parser.tab.c"
    break;

  case 37: /* statement: CONTINUE SEMI  */
#line 240 "parser.y"
        {
            (yyval.node) = make_node(NODE_CONTINUE);
        }
#line 1802 "parser.tab.c"
    break;

  case 38: /* statement: loop_stmt  */
#line 243 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1808 "parser.tab.c"
    break;

  case 39: /* statement: return_stmt SEMI  */
#line 244 "parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1814 "parser.tab.c"
    break;

  case 40: /* statement: func_call_expr SEMI  */
#line 245 "parser.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 1820 "parser.tab.c"
    break;

  case 41: /* statement: RETURN SEMI  */
#line 246 "parser.y"
                     { (yyval.node) = make_return_void(); }
#line 1826 "parser.tab.c"
    break;

  case 42: /* declaration: type identifier_list_decls SEMI  */
#line 255 "parser.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1832 "parser.tab.c"
    break;

  case 43: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET SEMI  */
#line 257 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL_ARRAY);
            n->sval      = strdup((yyvsp[-4].sval));
            n->cols      = (yyvsp[-2].ival);   /* size stored in cols */
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1844 "parser.tab.c"
    break;

  case 44: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET LBRACKET array_size RBRACKET SEMI  */
#line 265 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL_ARRAY_2D);
            n->sval      = strdup((yyvsp[-7].sval));
            n->rows      = (yyvsp[-5].ival);
            n->cols      = (yyvsp[-2].ival);
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1857 "parser.tab.c"
    break;

  case 45: /* declaration_no_semi: type IDENTIFIER  */
#line 278 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[0].sval));
            n->left      = NULL;
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1869 "parser.tab.c"
    break;

  case 46: /* declaration_no_semi: type IDENTIFIER ASSIGN expression  */
#line 286 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-2].sval));
            n->left      = (yyvsp[0].node);
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1881 "parser.tab.c"
    break;

  case 47: /* array_size: INT_LITERAL  */
#line 296 "parser.y"
                  { (yyval.ival) = (yyvsp[0].ival); }
#line 1887 "parser.tab.c"
    break;

  case 48: /* type: INT_TYPE  */
#line 300 "parser.y"
                    { current_decl_type = 0; }
#line 1893 "parser.tab.c"
    break;

  case 49: /* type: FLOAT_TYPE  */
#line 301 "parser.y"
                    { current_decl_type = 0; }
#line 1899 "parser.tab.c"
    break;

  case 50: /* type: DOUBLE_TYPE  */
#line 302 "parser.y"
                    { current_decl_type = 0; }
#line 1905 "parser.tab.c"
    break;

  case 51: /* type: CHAR_TYPE  */
#line 303 "parser.y"
                    { current_decl_type = 1; }
#line 1911 "parser.tab.c"
    break;

  case 52: /* type: BOOL_TYPE  */
#line 304 "parser.y"
                    { current_decl_type = 0; }
#line 1917 "parser.tab.c"
    break;

  case 53: /* type: VOID_TYPE  */
#line 305 "parser.y"
                    { current_decl_type = 0; }
#line 1923 "parser.tab.c"
    break;

  case 54: /* type: LONG_TYPE  */
#line 306 "parser.y"
                    { current_decl_type = 0; }
#line 1929 "parser.tab.c"
    break;

  case 55: /* type: SHORT_TYPE  */
#line 307 "parser.y"
                    { current_decl_type = 0; }
#line 1935 "parser.tab.c"
    break;

  case 56: /* type: UNSIGNED_TYPE  */
#line 308 "parser.y"
                    { current_decl_type = 0; }
#line 1941 "parser.tab.c"
    break;

  case 57: /* identifier_list_decls: IDENTIFIER  */
#line 318 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[0].sval));
            n->left      = NULL;   /* no initialiser */
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1953 "parser.tab.c"
    break;

  case 58: /* identifier_list_decls: IDENTIFIER ASSIGN expression  */
#line 326 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-2].sval));
            n->left      = (yyvsp[0].node);
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1965 "parser.tab.c"
    break;

  case 59: /* identifier_list_decls: IDENTIFIER COMMA identifier_list_decls  */
#line 334 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-2].sval));
            n->left      = NULL;
            n->decl_type = current_decl_type;
            n->next      = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1978 "parser.tab.c"
    break;

  case 60: /* identifier_list_decls: IDENTIFIER ASSIGN expression COMMA identifier_list_decls  */
#line 343 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-4].sval));
            n->left      = (yyvsp[-2].node);
            n->decl_type = current_decl_type;
            n->next      = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1991 "parser.tab.c"
    break;

  case 61: /* assignment: IDENTIFIER ASSIGN expression  */
#line 359 "parser.y"
        {
            ASTNode *n = make_node(NODE_ASSIGN);
            n->sval = strdup((yyvsp[-2].sval));
            n->left = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 2002 "parser.tab.c"
    break;

  case 62: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression  */
#line 369 "parser.y"
        {
            ASTNode *n = make_node(NODE_ARRAY_ASSIGN);
            n->sval  = strdup((yyvsp[-5].sval));
            n->left  = (yyvsp[-3].node);   /* index  */
            n->right = (yyvsp[0].node);   /* value  */
            (yyval.node) = n;
        }
#line 2014 "parser.tab.c"
    break;

  case 63: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET ASSIGN expression  */
#line 377 "parser.y"
        {
            ASTNode *n = make_node(NODE_ARRAY_ASSIGN_2D);
            n->sval  = strdup((yyvsp[-8].sval));
            n->left  = (yyvsp[-6].node);   /* row   */
            n->right = (yyvsp[-3].node);   /* col   */
            n->extra = (yyvsp[0].node);   /* value */
            (yyval.node) = n;
        }
#line 2027 "parser.tab.c"
    break;

  case 64: /* expression: expression PLUS term  */
#line 392 "parser.y"
                             { (yyval.node) = make_binop(NODE_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2033 "parser.tab.c"
    break;

  case 65: /* expression: expression MINUS term  */
#line 393 "parser.y"
                             { (yyval.node) = make_binop(NODE_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2039 "parser.tab.c"
    break;

  case 66: /* expression: expression AND term  */
#line 394 "parser.y"
                                  { (yyval.node) = make_binop(NODE_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2045 "parser.tab.c"
    break;

  case 67: /* expression: expression OR term  */
#line 395 "parser.y"
                                  { (yyval.node) = make_binop(NODE_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2051 "parser.tab.c"
    break;

  case 68: /* expression: expression BIT_OR term  */
#line 396 "parser.y"
                                  { (yyval.node) = make_binop(NODE_BIT_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2057 "parser.tab.c"
    break;

  case 69: /* expression: expression BIT_XOR term  */
#line 397 "parser.y"
                                  { (yyval.node) = make_binop(NODE_BIT_XOR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2063 "parser.tab.c"
    break;

  case 70: /* expression: expression BIT_AND term  */
#line 398 "parser.y"
                                  { (yyval.node) = make_binop(NODE_BIT_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2069 "parser.tab.c"
    break;

  case 71: /* expression: expression SHL term  */
#line 399 "parser.y"
                                  { (yyval.node) = make_binop(NODE_SHL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2075 "parser.tab.c"
    break;

  case 72: /* expression: expression SHR term  */
#line 400 "parser.y"
                                  { (yyval.node) = make_binop(NODE_SHR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2081 "parser.tab.c"
    break;

  case 73: /* expression: MINUS term  */
#line 401 "parser.y"
                             { (yyval.node) = make_unary(NODE_NEGATE, (yyvsp[0].node)); }
#line 2087 "parser.tab.c"
    break;

  case 74: /* expression: NOT term  */
#line 402 "parser.y"
                                  { (yyval.node) = make_unary(NODE_NOT, (yyvsp[0].node)); }
#line 2093 "parser.tab.c"
    break;

  case 75: /* expression: BIT_NOT term  */
#line 403 "parser.y"
                                  { (yyval.node) = make_unary(NODE_BIT_NOT, (yyvsp[0].node)); }
#line 2099 "parser.tab.c"
    break;

  case 76: /* expression: term  */
#line 404 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2105 "parser.tab.c"
    break;

  case 77: /* term: term MUL factor  */
#line 408 "parser.y"
                        { (yyval.node) = make_binop(NODE_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2111 "parser.tab.c"
    break;

  case 78: /* term: term DIV factor  */
#line 409 "parser.y"
                        { (yyval.node) = make_binop(NODE_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2117 "parser.tab.c"
    break;

  case 79: /* term: term MOD factor  */
#line 410 "parser.y"
                        { (yyval.node) = make_binop(NODE_MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2123 "parser.tab.c"
    break;

  case 80: /* term: factor  */
#line 411 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2129 "parser.tab.c"
    break;

  case 81: /* factor: primary  */
#line 415 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2135 "parser.tab.c"
    break;

  case 82: /* primary: IDENTIFIER  */
#line 419 "parser.y"
                        { (yyval.node) = make_ident((yyvsp[0].sval)); }
#line 2141 "parser.tab.c"
    break;

  case 83: /* primary: INT_LITERAL  */
#line 420 "parser.y"
                        { (yyval.node) = make_int_lit((yyvsp[0].ival)); }
#line 2147 "parser.tab.c"
    break;

  case 84: /* primary: FLOAT_LITERAL  */
#line 421 "parser.y"
                        { (yyval.node) = make_float_lit((double)(yyvsp[0].fval)); }
#line 2153 "parser.tab.c"
    break;

  case 85: /* primary: TRUE_LITERAL  */
#line 422 "parser.y"
                        { (yyval.node) = make_bool_lit(1); }
#line 2159 "parser.tab.c"
    break;

  case 86: /* primary: FALSE_LITERAL  */
#line 423 "parser.y"
                        { (yyval.node) = make_bool_lit(0); }
#line 2165 "parser.tab.c"
    break;

  case 87: /* primary: CHAR_LITERAL  */
#line 424 "parser.y"
                        { (yyval.node) = make_char_lit((yyvsp[0].cval)); }
#line 2171 "parser.tab.c"
    break;

  case 88: /* primary: LPAREN expression RPAREN  */
#line 425 "parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2177 "parser.tab.c"
    break;

  case 89: /* primary: function_call  */
#line 426 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2183 "parser.tab.c"
    break;

  case 90: /* primary: array_access  */
#line 427 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2189 "parser.tab.c"
    break;

  case 91: /* primary: func_call_expr  */
#line 428 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2195 "parser.tab.c"
    break;

  case 92: /* func_call_expr: IDENTIFIER LPAREN arg_list_opt RPAREN  */
#line 433 "parser.y"
        {
            (yyval.node) = make_func_call((yyvsp[-3].sval), (yyvsp[-1].node));
        }
#line 2203 "parser.tab.c"
    break;

  case 93: /* arg_list_opt: arg_list  */
#line 439 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2209 "parser.tab.c"
    break;

  case 94: /* arg_list_opt: %empty  */
#line 440 "parser.y"
                  { (yyval.node) = NULL; }
#line 2215 "parser.tab.c"
    break;

  case 95: /* arg_list: arg_list COMMA expression  */
#line 445 "parser.y"
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
#line 2231 "parser.tab.c"
    break;

  case 96: /* arg_list: expression  */
#line 457 "parser.y"
        {
            (yyval.node) = make_arg_list((yyvsp[0].node), NULL);
        }
#line 2239 "parser.tab.c"
    break;

  case 97: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 464 "parser.y"
        { (yyval.node) = make_array_access((yyvsp[-3].sval), (yyvsp[-1].node)); }
#line 2245 "parser.tab.c"
    break;

  case 98: /* array_access: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET  */
#line 466 "parser.y"
        { (yyval.node) = make_array_access_2d((yyvsp[-6].sval), (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2251 "parser.tab.c"
    break;

  case 99: /* function_call: POW LPAREN expression COMMA expression RPAREN  */
#line 475 "parser.y"
        { (yyval.node) = make_func2(NODE_POW, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2257 "parser.tab.c"
    break;

  case 100: /* function_call: SQRT LPAREN expression RPAREN  */
#line 477 "parser.y"
        { (yyval.node) = make_func1(NODE_SQRT, (yyvsp[-1].node)); }
#line 2263 "parser.tab.c"
    break;

  case 101: /* function_call: ABS LPAREN expression RPAREN  */
#line 479 "parser.y"
        { (yyval.node) = make_func1(NODE_ABS, (yyvsp[-1].node)); }
#line 2269 "parser.tab.c"
    break;

  case 102: /* function_call: FLOOR LPAREN expression RPAREN  */
#line 481 "parser.y"
        { (yyval.node) = make_func1(NODE_FLOOR, (yyvsp[-1].node)); }
#line 2275 "parser.tab.c"
    break;

  case 103: /* function_call: CEIL LPAREN expression RPAREN  */
#line 483 "parser.y"
        { (yyval.node) = make_func1(NODE_CEIL, (yyvsp[-1].node)); }
#line 2281 "parser.tab.c"
    break;

  case 104: /* print_stmt: PRINT LPAREN STRING_LITERAL print_end_opt RPAREN SEMI  */
#line 491 "parser.y"
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = strdup((yyvsp[-3].sval));   /* string literal */
            n->left = NULL;         /* marks this as a string-literal print */
            n->extra = (yyvsp[-2].node);
            (yyval.node) = n;
        }
#line 2293 "parser.tab.c"
    break;

  case 105: /* print_stmt: PRINT LPAREN expression print_end_opt RPAREN SEMI  */
#line 499 "parser.y"
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
#line 2315 "parser.tab.c"
    break;

  case 106: /* print_stmt: PRINT LPAREN print_end_opt RPAREN SEMI  */
#line 517 "parser.y"
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = NULL;
            n->left = NULL;
            n->extra = (yyvsp[-2].node);
            (yyval.node) = n;
        }
#line 2327 "parser.tab.c"
    break;

  case 107: /* print_end_opt: COMMA END ASSIGN STRING_LITERAL  */
#line 528 "parser.y"
        {
            ASTNode *n = make_node(NODE_STRING_LIT);
            n->sval = strdup((yyvsp[0].sval));
            (yyval.node) = n;
        }
#line 2337 "parser.tab.c"
    break;

  case 108: /* print_end_opt: %empty  */
#line 534 "parser.y"
        {
            (yyval.node) = NULL;
        }
#line 2345 "parser.tab.c"
    break;

  case 109: /* scan_stmt: SCAN LPAREN IDENTIFIER RPAREN SEMI  */
#line 540 "parser.y"
        {
            ASTNode *n = make_node(NODE_SCAN);
            n->sval = strdup((yyvsp[-2].sval));
            (yyval.node) = n;
        }
#line 2355 "parser.tab.c"
    break;

  case 110: /* scan_stmt: SCAN LPAREN IDENTIFIER LBRACKET expression RBRACKET RPAREN SEMI  */
#line 546 "parser.y"
        {
            ASTNode *n = make_node(NODE_SCAN_ARRAY);
            n->sval = strdup((yyvsp[-5].sval));
            n->left = (yyvsp[-3].node);   /* index expression */
            (yyval.node) = n;
        }
#line 2366 "parser.tab.c"
    break;

  case 111: /* condition: expression EQ expression  */
#line 559 "parser.y"
                                { (yyval.node) = make_binop(NODE_EQ,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2372 "parser.tab.c"
    break;

  case 112: /* condition: expression NEQ expression  */
#line 560 "parser.y"
                                { (yyval.node) = make_binop(NODE_NEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2378 "parser.tab.c"
    break;

  case 113: /* condition: expression GT expression  */
#line 561 "parser.y"
                                { (yyval.node) = make_binop(NODE_GT,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2384 "parser.tab.c"
    break;

  case 114: /* condition: expression LT expression  */
#line 562 "parser.y"
                                { (yyval.node) = make_binop(NODE_LT,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2390 "parser.tab.c"
    break;

  case 115: /* condition: expression GE expression  */
#line 563 "parser.y"
                                { (yyval.node) = make_binop(NODE_GE,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2396 "parser.tab.c"
    break;

  case 116: /* condition: expression LE expression  */
#line 564 "parser.y"
                                { (yyval.node) = make_binop(NODE_LE,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2402 "parser.tab.c"
    break;

  case 117: /* if_stmt: IF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part  */
#line 581 "parser.y"
        {
            ASTNode *n = make_node(NODE_IF);
            n->left  = (yyvsp[-5].node);   /* condition  */
            n->right = (yyvsp[-2].node);   /* then body  */
            n->extra = (yyvsp[0].node);   /* else chain */
            (yyval.node) = n;
        }
#line 2414 "parser.tab.c"
    break;

  case 118: /* else_if_part: ELSEIF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part  */
#line 592 "parser.y"
        {
            ASTNode *n = make_node(NODE_ELSEIF);
            n->left  = (yyvsp[-5].node);
            n->right = (yyvsp[-2].node);
            n->extra = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 2426 "parser.tab.c"
    break;

  case 119: /* else_if_part: ELSE LBRACE statement_list RBRACE  */
#line 600 "parser.y"
        {
            ASTNode *n = make_node(NODE_ELSE);
            n->left = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 2436 "parser.tab.c"
    break;

  case 120: /* else_if_part: %empty  */
#line 605 "parser.y"
                  { (yyval.node) = NULL; }
#line 2442 "parser.tab.c"
    break;

  case 121: /* switch_stmt: SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE  */
#line 619 "parser.y"
        {
            ASTNode *n = make_node(NODE_SWITCH);
            n->left  = (yyvsp[-4].node);   /* switch expression */
            n->right = (yyvsp[-1].node);   /* case list head    */
            (yyval.node) = n;
        }
#line 2453 "parser.tab.c"
    break;

  case 122: /* case_list: case_list case_item  */
#line 629 "parser.y"
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
#line 2468 "parser.tab.c"
    break;

  case 123: /* case_list: case_list default_item  */
#line 640 "parser.y"
        {
            if ((yyvsp[-1].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
            else {
                ASTNode *tail = (yyvsp[-1].node);
                while (tail->next) tail = tail->next;
                tail->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-1].node);
            }
        }
#line 2482 "parser.tab.c"
    break;

  case 124: /* case_list: %empty  */
#line 649 "parser.y"
                  { (yyval.node) = NULL; }
#line 2488 "parser.tab.c"
    break;

  case 125: /* case_item: CASE case_expr COLON statement_list  */
#line 654 "parser.y"
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
#line 2508 "parser.tab.c"
    break;

  case 126: /* case_expr: expression  */
#line 673 "parser.y"
        {
            ASTNode *n = make_node(NODE_CASE);
            n->left = (yyvsp[0].node);   /* case value expression */
            (yyval.node) = n;
        }
#line 2518 "parser.tab.c"
    break;

  case 127: /* case_expr: expression RANGE expression  */
#line 679 "parser.y"
        {
            ASTNode *n = make_node(NODE_CASE_RANGE);
            n->left  = (yyvsp[-2].node);  /* range start */
            n->right = (yyvsp[0].node);  /* range end   */
            (yyval.node) = n;
        }
#line 2529 "parser.tab.c"
    break;

  case 128: /* default_item: DEFAULT COLON statement_list  */
#line 689 "parser.y"
        {
            ASTNode *n = make_node(NODE_DEFAULT);
            n->left = (yyvsp[0].node);   /* body */
            (yyval.node) = n;
        }
#line 2539 "parser.tab.c"
    break;

  case 129: /* for_init: assignment  */
#line 716 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2545 "parser.tab.c"
    break;

  case 130: /* for_init: declaration_no_semi  */
#line 717 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2551 "parser.tab.c"
    break;

  case 131: /* for_init: %empty  */
#line 718 "parser.y"
                  { (yyval.node) = NULL; }
#line 2557 "parser.tab.c"
    break;

  case 132: /* for_update: assignment  */
#line 722 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2563 "parser.tab.c"
    break;

  case 133: /* for_update: %empty  */
#line 723 "parser.y"
                  { (yyval.node) = NULL; }
#line 2569 "parser.tab.c"
    break;

  case 134: /* loop_stmt: WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE  */
#line 728 "parser.y"
        {
            ASTNode *n = make_node(NODE_WHILE);
            n->left  = (yyvsp[-4].node);   /* condition */
            n->right = (yyvsp[-1].node);   /* body      */
            (yyval.node) = n;
        }
#line 2580 "parser.tab.c"
    break;

  case 135: /* loop_stmt: DO LBRACE statement_list RBRACE WHILE LPAREN condition RPAREN SEMI  */
#line 735 "parser.y"
        {
            ASTNode *n = make_node(NODE_DO_WHILE);
            n->left  = (yyvsp[-6].node);   /* body      */
            n->right = (yyvsp[-2].node);   /* condition */
            (yyval.node) = n;
        }
#line 2591 "parser.tab.c"
    break;

  case 136: /* loop_stmt: FOR LPAREN for_init SEMI condition SEMI for_update RPAREN LBRACE statement_list RBRACE  */
#line 743 "parser.y"
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
#line 2608 "parser.tab.c"
    break;

  case 137: /* loop_stmt: FOR IDENTIFIER IN LPAREN expression RANGE expression RPAREN LBRACE statement_list RBRACE  */
#line 757 "parser.y"
        {
            ASTNode *n = make_node(NODE_FOR_RANGE);
            n->sval  = strdup((yyvsp[-9].sval));       /* loop variable name */
            n->left  = (yyvsp[-6].node);              /* start expression   */
            n->right = (yyvsp[-1].node);             /* body               */
            n->extra = (yyvsp[-4].node);              /* end expression     */
            (yyval.node) = n;
        }
#line 2621 "parser.tab.c"
    break;

  case 138: /* loop_stmt: FOR IDENTIFIER IN LPAREN expression RANGE expression COMMA expression RPAREN LBRACE statement_list RBRACE  */
#line 767 "parser.y"
        {
            /* pack end + step into a helper node */
            ASTNode *parts = make_node(NODE_STMT_LIST);
            parts->left  = (yyvsp[-6].node);   /* end  */
            parts->right = (yyvsp[-4].node);   /* step */

            ASTNode *n = make_node(NODE_FOR_RANGE_STEP);
            n->sval  = strdup((yyvsp[-11].sval));   /* loop variable name */
            n->left  = (yyvsp[-8].node);           /* start              */
            n->right = (yyvsp[-1].node);          /* body               */
            n->extra = parts;        /* end + step         */
            (yyval.node) = n;
        }
#line 2639 "parser.tab.c"
    break;

  case 139: /* return_stmt: RETURN expression  */
#line 788 "parser.y"
        {
            ASTNode *n = make_node(NODE_RETURN);
            n->left = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 2649 "parser.tab.c"
    break;


#line 2653 "parser.tab.c"

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

#line 795 "parser.y"


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
