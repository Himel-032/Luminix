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

void yyerror(const char *s);
int  yylex(void);
extern int yylineno;

/* tracks declaration type for declarations */
static int current_decl_type = 0;   /* 0 = numeric, 1 = char */

#line 87 "parser.tab.c"

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
  YYSYMBOL_declaration_no_semi = 89,       /* declaration_no_semi  */
  YYSYMBOL_array_size = 90,                /* array_size  */
  YYSYMBOL_type = 91,                      /* type  */
  YYSYMBOL_identifier_list_decls = 92,     /* identifier_list_decls  */
  YYSYMBOL_assignment = 93,                /* assignment  */
  YYSYMBOL_array_assignment = 94,          /* array_assignment  */
  YYSYMBOL_expression = 95,                /* expression  */
  YYSYMBOL_term = 96,                      /* term  */
  YYSYMBOL_factor = 97,                    /* factor  */
  YYSYMBOL_primary = 98,                   /* primary  */
  YYSYMBOL_array_access = 99,              /* array_access  */
  YYSYMBOL_function_call = 100,            /* function_call  */
  YYSYMBOL_print_stmt = 101,               /* print_stmt  */
  YYSYMBOL_scan_stmt = 102,                /* scan_stmt  */
  YYSYMBOL_condition = 103,                /* condition  */
  YYSYMBOL_if_stmt = 104,                  /* if_stmt  */
  YYSYMBOL_else_if_part = 105,             /* else_if_part  */
  YYSYMBOL_switch_stmt = 106,              /* switch_stmt  */
  YYSYMBOL_case_list = 107,                /* case_list  */
  YYSYMBOL_case_item = 108,                /* case_item  */
  YYSYMBOL_case_expr = 109,                /* case_expr  */
  YYSYMBOL_default_item = 110,             /* default_item  */
  YYSYMBOL_for_init = 111,                 /* for_init  */
  YYSYMBOL_for_update = 112,               /* for_update  */
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
#define YYLAST   491

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  240

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
       0,    97,    97,   101,   102,   106,   107,   111,   126,   142,
     146,   147,   148,   149,   150,   151,   152,   153,   157,   161,
     162,   170,   172,   180,   193,   201,   212,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   233,   241,   249,   258,
     274,   284,   292,   308,   309,   310,   311,   315,   316,   317,
     318,   322,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   338,   340,   349,   351,   353,   355,   357,   366,   373,
     381,   391,   397,   411,   412,   413,   414,   415,   416,   432,
     443,   451,   457,   470,   480,   491,   501,   505,   524,   530,
     540,   568,   569,   570,   574,   575,   579,   586,   593,   614
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
  "statement_list", "statement", "declaration", "declaration_no_semi",
  "array_size", "type", "identifier_list_decls", "assignment",
  "array_assignment", "expression", "term", "factor", "primary",
  "array_access", "function_call", "print_stmt", "scan_stmt", "condition",
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

#define YYPACT_NINF (-111)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -111,     5,    15,  -111,    17,   -55,   -10,  -111,  -111,  -111,
       6,    25,  -111,    28,  -111,    26,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,    38,    62,    91,    92,    67,
     100,   101,   400,   102,   103,  -111,   -42,  -111,  -111,    84,
     110,   122,  -111,  -111,  -111,  -111,  -111,   123,   400,   400,
       0,   400,  -111,  -111,  -111,  -111,  -111,   126,   127,   134,
     149,   150,   412,   400,  -111,  -111,  -111,    24,    86,   159,
    -111,  -111,  -111,  -111,    79,    89,   400,   400,   -43,   155,
    -111,  -111,  -111,   268,   152,   -28,   133,  -111,   113,  -111,
     158,   162,   170,   400,   400,   400,   400,   400,   159,    55,
     400,   412,   412,   412,   412,   412,   167,    31,    69,    41,
      86,    -3,   400,   145,   164,  -111,   400,   400,   400,   400,
     400,   400,   175,   176,   182,   400,   178,   224,   181,    72,
      75,    81,    95,  -111,    18,   159,   159,  -111,  -111,  -111,
     196,   197,   198,   200,   400,    32,   184,    11,  -111,  -111,
     191,    86,    86,    86,    86,    86,    86,  -111,  -111,   400,
     202,  -111,   203,   400,  -111,  -111,  -111,  -111,   218,  -111,
    -111,  -111,  -111,    20,   400,   400,   145,    27,   199,    -4,
      86,   189,   246,   400,    98,   400,   222,    86,    22,  -111,
    -111,   164,   124,   400,   225,  -111,  -111,  -111,  -111,   227,
    -111,   228,  -111,    48,   229,   235,   226,   230,   239,  -111,
     -26,   249,  -111,   248,   254,  -111,  -111,   400,   255,  -111,
     400,   400,  -111,   398,  -111,  -111,    86,  -111,   275,   257,
      86,   398,   322,  -111,   253,  -111,  -111,   351,   124,  -111
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,     3,     2,     5,
       0,     0,     6,     0,     9,     0,    27,    28,    29,    30,
      31,    32,    33,    34,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,     0,     8,    10,     0,
       0,     0,    13,    14,    15,    16,    19,     0,     0,     0,
      93,     0,     9,    17,    18,    55,    56,     0,     0,     0,
       0,     0,     0,     0,    53,    54,    57,    52,    99,    46,
      50,    51,    60,    59,     0,     0,     0,     0,    36,     0,
      11,    12,    20,     0,     0,     0,     0,    92,     0,    91,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
       0,     0,     0,     0,     0,     0,     0,    52,     0,     0,
      40,     0,     0,     0,     0,    21,     0,     0,     0,     0,
       0,     0,     0,     0,    24,     0,     0,     0,     0,     0,
       0,     0,     0,    58,     0,    43,    44,    47,    48,    49,
       0,     0,     0,     0,     0,     0,    37,    36,    38,    26,
       0,    73,    74,    77,    78,    75,    76,     9,    86,     0,
       0,     9,     0,     0,    64,    65,    66,    67,    61,    68,
      69,    70,    71,     0,     0,     0,     0,     0,     0,     0,
      25,    95,     0,     0,     0,     0,     0,    41,     0,    39,
      22,     0,    82,     0,     0,    83,    84,    85,    94,     0,
      96,     0,    63,     0,     0,     0,     0,     0,     0,    79,
      88,     0,     9,     0,     0,    62,    72,     0,     0,     9,
       0,     0,     9,    90,     9,    97,    42,    23,     0,     0,
      89,    87,     0,    81,     0,    98,     9,     0,    82,    80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,  -111,  -111,  -111,   -50,  -111,  -111,  -111,   136,
     274,  -110,   -49,  -111,   -32,   -19,   139,  -111,  -111,  -111,
    -111,  -111,   -47,  -111,    99,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     7,     8,    15,    37,    38,    87,   150,
      39,    79,    40,    41,    83,    69,    70,    71,    72,    73,
      42,    43,    84,    44,   209,    45,   179,   196,   211,   197,
      90,   199,    46,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      68,    89,    92,   148,    91,     3,    16,    17,    18,    19,
      20,    21,    22,    23,    24,   112,    76,    85,     4,     5,
     193,   194,     9,   113,    10,   101,   102,   101,   102,   114,
      77,    99,    16,    17,    18,    19,    20,    21,    22,    23,
      24,   123,   108,    98,   110,   111,    25,     6,   221,    26,
     101,   102,    27,    28,    29,    30,    31,    32,    11,    33,
      34,   128,   129,   130,   131,   132,   189,   195,   134,   112,
     145,   101,   102,   101,   102,   101,   102,   113,   160,    86,
     146,    12,   135,   136,   151,   152,   153,   154,   155,   156,
     174,   168,   190,   186,    13,   205,   100,    35,    14,   191,
     141,   101,   102,   100,   175,    36,    48,   178,   101,   102,
     143,   182,   173,   144,    55,    56,    57,    58,    59,    60,
      61,   215,   101,   102,   133,   101,   102,   180,   101,   102,
      49,   184,   198,    62,   101,   102,   201,    52,   142,   101,
     102,   164,   187,   188,   165,   207,   208,    63,   101,   102,
     166,   101,   102,   203,    64,    65,   106,    66,   107,    50,
      51,   210,   223,    78,   167,    53,    54,   202,   109,   228,
      74,    75,   231,   229,   232,    80,    16,    17,    18,    19,
      20,    21,    22,    23,    24,   226,   237,    81,    82,   230,
      25,    76,   124,    26,    93,    94,    27,    28,    29,    30,
      31,    32,    95,    33,    34,    16,    17,    18,    19,    20,
      21,    22,    23,    24,   103,   104,   105,    96,    97,    25,
     115,   122,    26,   125,   147,    27,    28,    29,    30,    31,
      32,   126,    33,    34,   101,   102,   140,   101,   102,   149,
     159,   127,   137,   138,   139,   157,   158,   163,   161,    36,
     176,   162,    16,    17,    18,    19,    20,    21,    22,    23,
      24,   169,   170,   171,   177,   172,    25,   181,    86,    26,
     192,   183,    27,    28,    29,    30,    31,    32,    36,    33,
      34,    16,    17,    18,    19,    20,    21,    22,    23,    24,
     185,   204,   212,   217,   216,    25,   213,   214,    26,   218,
     219,    27,    28,    29,    30,    31,    32,   220,    33,    34,
     116,   117,   118,   119,   120,   121,   222,   200,   224,   225,
     227,   101,   102,   236,    88,    36,   234,   206,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   239,     0,     0,
       0,     0,    25,     0,     0,    26,   233,     0,    27,    28,
      29,    30,    31,    32,    36,    33,    34,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     0,     0,     0,     0,
       0,    25,     0,     0,    26,     0,     0,    27,    28,    29,
      30,    31,    32,     0,    33,    34,     0,     0,     0,     0,
       0,     0,     0,   235,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,     0,     0,     0,    25,     0,
       0,    26,   238,     0,    27,    28,    29,    30,    31,    32,
      36,    33,    34,     0,     0,    55,    56,    57,    58,    59,
      60,    61,     0,     0,     0,     0,     0,    55,    56,    57,
      58,    59,    60,    61,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,     0,
       0,     0,     0,     0,     0,    64,    65,    36,    66,    67,
      63,     0,     0,     0,     0,     0,     0,    64,    65,     0,
      66,    67
};

static const yytype_int16 yycheck[] =
{
      32,    50,    52,   113,    51,     0,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    58,    58,    49,     3,     4,
      24,    25,     5,    66,    79,    53,    54,    53,    54,    72,
      72,    63,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    69,    74,    62,    76,    77,    20,    32,    74,    23,
      53,    54,    26,    27,    28,    29,    30,    31,    68,    33,
      34,    93,    94,    95,    96,    97,   176,    71,   100,    58,
      73,    53,    54,    53,    54,    53,    54,    66,   125,    79,
     112,    75,   101,   102,   116,   117,   118,   119,   120,   121,
      58,    73,    65,    73,    69,    73,    72,    71,    70,    72,
      69,    53,    54,    72,    72,    79,    68,   157,    53,    54,
      69,   161,   144,    72,    35,    36,    37,    38,    39,    40,
      41,    73,    53,    54,    69,    53,    54,   159,    53,    54,
      68,   163,   181,    54,    53,    54,   183,    70,    69,    53,
      54,    69,   174,   175,    69,    21,    22,    68,    53,    54,
      69,    53,    54,   185,    75,    76,    77,    78,    79,    68,
      68,   193,   212,    79,    69,    65,    65,    69,    79,   219,
      68,    68,   222,   220,   224,    65,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   217,   236,    65,    65,   221,
      20,    58,    79,    23,    68,    68,    26,    27,    28,    29,
      30,    31,    68,    33,    34,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    55,    56,    57,    68,    68,    20,
      65,    69,    23,    65,    79,    26,    27,    28,    29,    30,
      31,    69,    33,    34,    53,    54,    69,    53,    54,    75,
      58,    71,   103,   104,   105,    70,    70,    66,    70,    79,
      66,    27,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    65,    65,    65,    73,    65,    20,    65,    79,    23,
      71,    68,    26,    27,    28,    29,    30,    31,    79,    33,
      34,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      72,    69,    67,    58,    65,    20,    69,    69,    23,    73,
      70,    26,    27,    28,    29,    30,    31,    68,    33,    34,
      42,    43,    44,    45,    46,    47,    67,    71,    70,    65,
      65,    53,    54,    70,    50,    79,    69,   191,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   238,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    23,    71,    -1,    26,    27,
      28,    29,    30,    31,    79,    33,    34,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    23,    -1,    -1,    26,    27,    28,
      29,    30,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    -1,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    23,    71,    -1,    26,    27,    28,    29,    30,    31,
      79,    33,    34,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    40,    41,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    79,    78,    79,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      78,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    82,    83,     0,     3,     4,    32,    84,    85,     5,
      79,    68,    75,    69,    70,    86,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    20,    23,    26,    27,    28,
      29,    30,    31,    33,    34,    71,    79,    87,    88,    91,
      93,    94,   101,   102,   104,   106,   113,   114,    68,    68,
      68,    68,    70,    65,    65,    35,    36,    37,    38,    39,
      40,    41,    54,    68,    75,    76,    78,    79,    95,    96,
      97,    98,    99,   100,    68,    68,    58,    72,    79,    92,
      65,    65,    65,    95,   103,    95,    79,    89,    91,    93,
     111,   103,    86,    68,    68,    68,    68,    68,    96,    95,
      72,    53,    54,    55,    56,    57,    77,    79,    95,    79,
      95,    95,    58,    66,    72,    65,    42,    43,    44,    45,
      46,    47,    69,    69,    79,    65,    69,    71,    95,    95,
      95,    95,    95,    69,    95,    96,    96,    97,    97,    97,
      69,    69,    69,    69,    72,    73,    95,    79,    92,    75,
      90,    95,    95,    95,    95,    95,    95,    70,    70,    58,
     103,    70,    27,    66,    69,    69,    69,    69,    73,    65,
      65,    65,    65,    95,    58,    72,    66,    73,    86,   107,
      95,    65,    86,    68,    95,    72,    73,    95,    95,    92,
      65,    72,    71,    24,    25,    71,   108,   110,    93,   112,
      71,   103,    69,    95,    69,    73,    90,    21,    22,   105,
      95,   109,    67,    69,    69,    73,    65,    58,    73,    70,
      68,    74,    67,    86,    70,    65,    95,    65,    86,   103,
      95,    86,    86,    71,    69,    71,    70,    86,    71,   105
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    88,    88,    88,    89,    89,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    92,    92,    92,
      93,    94,    94,    95,    95,    95,    95,    96,    96,    96,
      96,    97,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    99,    99,   100,   100,   100,   100,   100,   101,   101,
     101,   102,   102,   103,   103,   103,   103,   103,   103,   104,
     105,   105,   105,   106,   107,   107,   107,   108,   109,   109,
     110,   111,   111,   111,   112,   112,   113,   113,   113,   114
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     3,     6,     2,     0,
       1,     2,     2,     1,     1,     1,     1,     2,     2,     1,
       2,     3,     6,     9,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     5,
       3,     6,     9,     3,     3,     2,     1,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     4,     7,     6,     4,     4,     4,     4,     5,     5,
       5,     5,     8,     3,     3,     3,     3,     3,     3,     8,
       8,     4,     0,     7,     2,     2,     0,     4,     1,     3,
       3,     1,     1,     0,     1,     0,     7,     9,    11,     2
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
  case 7: /* main_function: MAIN LPAREN RPAREN LBRACE statement_list RBRACE  */
#line 112 "parser.y"
        {
            /* Build program root and immediately interpret it */
            ASTNode *prog = make_node(NODE_PROGRAM);
            prog->left = (yyvsp[-1].node);
            interpret(prog);
            free_ast(prog);
        }
#line 1406 "parser.tab.c"
    break;

  case 8: /* statement_list: statement_list statement  */
#line 127 "parser.y"
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
#line 1426 "parser.tab.c"
    break;

  case 9: /* statement_list: %empty  */
#line 142 "parser.y"
                  { (yyval.node) = NULL; }
#line 1432 "parser.tab.c"
    break;

  case 10: /* statement: declaration  */
#line 146 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1438 "parser.tab.c"
    break;

  case 11: /* statement: assignment SEMI  */
#line 147 "parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1444 "parser.tab.c"
    break;

  case 12: /* statement: array_assignment SEMI  */
#line 148 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1450 "parser.tab.c"
    break;

  case 13: /* statement: print_stmt  */
#line 149 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1456 "parser.tab.c"
    break;

  case 14: /* statement: scan_stmt  */
#line 150 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1462 "parser.tab.c"
    break;

  case 15: /* statement: if_stmt  */
#line 151 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1468 "parser.tab.c"
    break;

  case 16: /* statement: switch_stmt  */
#line 152 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1474 "parser.tab.c"
    break;

  case 17: /* statement: BREAK SEMI  */
#line 154 "parser.y"
        {
            (yyval.node) = make_node(NODE_BREAK);
        }
#line 1482 "parser.tab.c"
    break;

  case 18: /* statement: CONTINUE SEMI  */
#line 158 "parser.y"
        {
            (yyval.node) = make_node(NODE_CONTINUE);
        }
#line 1490 "parser.tab.c"
    break;

  case 19: /* statement: loop_stmt  */
#line 161 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1496 "parser.tab.c"
    break;

  case 20: /* statement: return_stmt SEMI  */
#line 162 "parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1502 "parser.tab.c"
    break;

  case 21: /* declaration: type identifier_list_decls SEMI  */
#line 171 "parser.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1508 "parser.tab.c"
    break;

  case 22: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET SEMI  */
#line 173 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL_ARRAY);
            n->sval      = strdup((yyvsp[-4].sval));
            n->cols      = (yyvsp[-2].ival);   /* size stored in cols */
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1520 "parser.tab.c"
    break;

  case 23: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET LBRACKET array_size RBRACKET SEMI  */
#line 181 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL_ARRAY_2D);
            n->sval      = strdup((yyvsp[-7].sval));
            n->rows      = (yyvsp[-5].ival);
            n->cols      = (yyvsp[-2].ival);
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1533 "parser.tab.c"
    break;

  case 24: /* declaration_no_semi: type IDENTIFIER  */
#line 194 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[0].sval));
            n->left      = NULL;
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1545 "parser.tab.c"
    break;

  case 25: /* declaration_no_semi: type IDENTIFIER ASSIGN expression  */
#line 202 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-2].sval));
            n->left      = (yyvsp[0].node);
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1557 "parser.tab.c"
    break;

  case 26: /* array_size: INT_LITERAL  */
#line 212 "parser.y"
                  { (yyval.ival) = (yyvsp[0].ival); }
#line 1563 "parser.tab.c"
    break;

  case 27: /* type: INT_TYPE  */
#line 216 "parser.y"
                    { current_decl_type = 0; }
#line 1569 "parser.tab.c"
    break;

  case 28: /* type: FLOAT_TYPE  */
#line 217 "parser.y"
                    { current_decl_type = 0; }
#line 1575 "parser.tab.c"
    break;

  case 29: /* type: DOUBLE_TYPE  */
#line 218 "parser.y"
                    { current_decl_type = 0; }
#line 1581 "parser.tab.c"
    break;

  case 30: /* type: CHAR_TYPE  */
#line 219 "parser.y"
                    { current_decl_type = 1; }
#line 1587 "parser.tab.c"
    break;

  case 31: /* type: BOOL_TYPE  */
#line 220 "parser.y"
                    { current_decl_type = 0; }
#line 1593 "parser.tab.c"
    break;

  case 32: /* type: VOID_TYPE  */
#line 221 "parser.y"
                    { current_decl_type = 0; }
#line 1599 "parser.tab.c"
    break;

  case 33: /* type: LONG_TYPE  */
#line 222 "parser.y"
                    { current_decl_type = 0; }
#line 1605 "parser.tab.c"
    break;

  case 34: /* type: SHORT_TYPE  */
#line 223 "parser.y"
                    { current_decl_type = 0; }
#line 1611 "parser.tab.c"
    break;

  case 35: /* type: UNSIGNED_TYPE  */
#line 224 "parser.y"
                    { current_decl_type = 0; }
#line 1617 "parser.tab.c"
    break;

  case 36: /* identifier_list_decls: IDENTIFIER  */
#line 234 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[0].sval));
            n->left      = NULL;   /* no initialiser */
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1629 "parser.tab.c"
    break;

  case 37: /* identifier_list_decls: IDENTIFIER ASSIGN expression  */
#line 242 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-2].sval));
            n->left      = (yyvsp[0].node);
            n->decl_type = current_decl_type;
            (yyval.node) = n;
        }
#line 1641 "parser.tab.c"
    break;

  case 38: /* identifier_list_decls: IDENTIFIER COMMA identifier_list_decls  */
#line 250 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-2].sval));
            n->left      = NULL;
            n->decl_type = current_decl_type;
            n->next      = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1654 "parser.tab.c"
    break;

  case 39: /* identifier_list_decls: IDENTIFIER ASSIGN expression COMMA identifier_list_decls  */
#line 259 "parser.y"
        {
            ASTNode *n = make_node(NODE_DECL);
            n->sval      = strdup((yyvsp[-4].sval));
            n->left      = (yyvsp[-2].node);
            n->decl_type = current_decl_type;
            n->next      = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1667 "parser.tab.c"
    break;

  case 40: /* assignment: IDENTIFIER ASSIGN expression  */
#line 275 "parser.y"
        {
            ASTNode *n = make_node(NODE_ASSIGN);
            n->sval = strdup((yyvsp[-2].sval));
            n->left = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1678 "parser.tab.c"
    break;

  case 41: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression  */
#line 285 "parser.y"
        {
            ASTNode *n = make_node(NODE_ARRAY_ASSIGN);
            n->sval  = strdup((yyvsp[-5].sval));
            n->left  = (yyvsp[-3].node);   /* index  */
            n->right = (yyvsp[0].node);   /* value  */
            (yyval.node) = n;
        }
#line 1690 "parser.tab.c"
    break;

  case 42: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET ASSIGN expression  */
#line 293 "parser.y"
        {
            ASTNode *n = make_node(NODE_ARRAY_ASSIGN_2D);
            n->sval  = strdup((yyvsp[-8].sval));
            n->left  = (yyvsp[-6].node);   /* row   */
            n->right = (yyvsp[-3].node);   /* col   */
            n->extra = (yyvsp[0].node);   /* value */
            (yyval.node) = n;
        }
#line 1703 "parser.tab.c"
    break;

  case 43: /* expression: expression PLUS term  */
#line 308 "parser.y"
                             { (yyval.node) = make_binop(NODE_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1709 "parser.tab.c"
    break;

  case 44: /* expression: expression MINUS term  */
#line 309 "parser.y"
                             { (yyval.node) = make_binop(NODE_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1715 "parser.tab.c"
    break;

  case 45: /* expression: MINUS term  */
#line 310 "parser.y"
                             { (yyval.node) = make_unary(NODE_NEGATE, (yyvsp[0].node)); }
#line 1721 "parser.tab.c"
    break;

  case 46: /* expression: term  */
#line 311 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1727 "parser.tab.c"
    break;

  case 47: /* term: term MUL factor  */
#line 315 "parser.y"
                        { (yyval.node) = make_binop(NODE_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1733 "parser.tab.c"
    break;

  case 48: /* term: term DIV factor  */
#line 316 "parser.y"
                        { (yyval.node) = make_binop(NODE_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1739 "parser.tab.c"
    break;

  case 49: /* term: term MOD factor  */
#line 317 "parser.y"
                        { (yyval.node) = make_binop(NODE_MOD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1745 "parser.tab.c"
    break;

  case 50: /* term: factor  */
#line 318 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1751 "parser.tab.c"
    break;

  case 51: /* factor: primary  */
#line 322 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1757 "parser.tab.c"
    break;

  case 52: /* primary: IDENTIFIER  */
#line 326 "parser.y"
                        { (yyval.node) = make_ident((yyvsp[0].sval)); }
#line 1763 "parser.tab.c"
    break;

  case 53: /* primary: INT_LITERAL  */
#line 327 "parser.y"
                        { (yyval.node) = make_int_lit((yyvsp[0].ival)); }
#line 1769 "parser.tab.c"
    break;

  case 54: /* primary: FLOAT_LITERAL  */
#line 328 "parser.y"
                        { (yyval.node) = make_float_lit((double)(yyvsp[0].fval)); }
#line 1775 "parser.tab.c"
    break;

  case 55: /* primary: TRUE_LITERAL  */
#line 329 "parser.y"
                        { (yyval.node) = make_bool_lit(1); }
#line 1781 "parser.tab.c"
    break;

  case 56: /* primary: FALSE_LITERAL  */
#line 330 "parser.y"
                        { (yyval.node) = make_bool_lit(0); }
#line 1787 "parser.tab.c"
    break;

  case 57: /* primary: CHAR_LITERAL  */
#line 331 "parser.y"
                        { (yyval.node) = make_char_lit((yyvsp[0].cval)); }
#line 1793 "parser.tab.c"
    break;

  case 58: /* primary: LPAREN expression RPAREN  */
#line 332 "parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 1799 "parser.tab.c"
    break;

  case 59: /* primary: function_call  */
#line 333 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1805 "parser.tab.c"
    break;

  case 60: /* primary: array_access  */
#line 334 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1811 "parser.tab.c"
    break;

  case 61: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 339 "parser.y"
        { (yyval.node) = make_array_access((yyvsp[-3].sval), (yyvsp[-1].node)); }
#line 1817 "parser.tab.c"
    break;

  case 62: /* array_access: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET  */
#line 341 "parser.y"
        { (yyval.node) = make_array_access_2d((yyvsp[-6].sval), (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1823 "parser.tab.c"
    break;

  case 63: /* function_call: POW LPAREN expression COMMA expression RPAREN  */
#line 350 "parser.y"
        { (yyval.node) = make_func2(NODE_POW, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1829 "parser.tab.c"
    break;

  case 64: /* function_call: SQRT LPAREN expression RPAREN  */
#line 352 "parser.y"
        { (yyval.node) = make_func1(NODE_SQRT, (yyvsp[-1].node)); }
#line 1835 "parser.tab.c"
    break;

  case 65: /* function_call: ABS LPAREN expression RPAREN  */
#line 354 "parser.y"
        { (yyval.node) = make_func1(NODE_ABS, (yyvsp[-1].node)); }
#line 1841 "parser.tab.c"
    break;

  case 66: /* function_call: FLOOR LPAREN expression RPAREN  */
#line 356 "parser.y"
        { (yyval.node) = make_func1(NODE_FLOOR, (yyvsp[-1].node)); }
#line 1847 "parser.tab.c"
    break;

  case 67: /* function_call: CEIL LPAREN expression RPAREN  */
#line 358 "parser.y"
        { (yyval.node) = make_func1(NODE_CEIL, (yyvsp[-1].node)); }
#line 1853 "parser.tab.c"
    break;

  case 68: /* print_stmt: PRINT LPAREN STRING_LITERAL RPAREN SEMI  */
#line 367 "parser.y"
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = strdup((yyvsp[-2].sval));   /* string literal */
            n->left = NULL;         /* marks this as a string-literal print */
            (yyval.node) = n;
        }
#line 1864 "parser.tab.c"
    break;

  case 69: /* print_stmt: PRINT LPAREN IDENTIFIER RPAREN SEMI  */
#line 374 "parser.y"
        {
            /* print a variable — left != NULL signals identifier mode */
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = strdup((yyvsp[-2].sval));
            n->left = make_ident((yyvsp[-2].sval));   /* non-NULL → identifier print */
            (yyval.node) = n;
        }
#line 1876 "parser.tab.c"
    break;

  case 70: /* print_stmt: PRINT LPAREN expression RPAREN SEMI  */
#line 382 "parser.y"
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->sval = NULL;   /* NULL → expression print */
            n->left = (yyvsp[-2].node);
            (yyval.node) = n;
        }
#line 1887 "parser.tab.c"
    break;

  case 71: /* scan_stmt: SCAN LPAREN IDENTIFIER RPAREN SEMI  */
#line 392 "parser.y"
        {
            ASTNode *n = make_node(NODE_SCAN);
            n->sval = strdup((yyvsp[-2].sval));
            (yyval.node) = n;
        }
#line 1897 "parser.tab.c"
    break;

  case 72: /* scan_stmt: SCAN LPAREN IDENTIFIER LBRACKET expression RBRACKET RPAREN SEMI  */
#line 398 "parser.y"
        {
            ASTNode *n = make_node(NODE_SCAN_ARRAY);
            n->sval = strdup((yyvsp[-5].sval));
            n->left = (yyvsp[-3].node);   /* index expression */
            (yyval.node) = n;
        }
#line 1908 "parser.tab.c"
    break;

  case 73: /* condition: expression EQ expression  */
#line 411 "parser.y"
                                { (yyval.node) = make_binop(NODE_EQ,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1914 "parser.tab.c"
    break;

  case 74: /* condition: expression NEQ expression  */
#line 412 "parser.y"
                                { (yyval.node) = make_binop(NODE_NEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1920 "parser.tab.c"
    break;

  case 75: /* condition: expression GT expression  */
#line 413 "parser.y"
                                { (yyval.node) = make_binop(NODE_GT,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1926 "parser.tab.c"
    break;

  case 76: /* condition: expression LT expression  */
#line 414 "parser.y"
                                { (yyval.node) = make_binop(NODE_LT,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1932 "parser.tab.c"
    break;

  case 77: /* condition: expression GE expression  */
#line 415 "parser.y"
                                { (yyval.node) = make_binop(NODE_GE,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1938 "parser.tab.c"
    break;

  case 78: /* condition: expression LE expression  */
#line 416 "parser.y"
                                { (yyval.node) = make_binop(NODE_LE,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1944 "parser.tab.c"
    break;

  case 79: /* if_stmt: IF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part  */
#line 433 "parser.y"
        {
            ASTNode *n = make_node(NODE_IF);
            n->left  = (yyvsp[-5].node);   /* condition  */
            n->right = (yyvsp[-2].node);   /* then body  */
            n->extra = (yyvsp[0].node);   /* else chain */
            (yyval.node) = n;
        }
#line 1956 "parser.tab.c"
    break;

  case 80: /* else_if_part: ELSEIF LPAREN condition RPAREN LBRACE statement_list RBRACE else_if_part  */
#line 444 "parser.y"
        {
            ASTNode *n = make_node(NODE_ELSEIF);
            n->left  = (yyvsp[-5].node);
            n->right = (yyvsp[-2].node);
            n->extra = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1968 "parser.tab.c"
    break;

  case 81: /* else_if_part: ELSE LBRACE statement_list RBRACE  */
#line 452 "parser.y"
        {
            ASTNode *n = make_node(NODE_ELSE);
            n->left = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1978 "parser.tab.c"
    break;

  case 82: /* else_if_part: %empty  */
#line 457 "parser.y"
                  { (yyval.node) = NULL; }
#line 1984 "parser.tab.c"
    break;

  case 83: /* switch_stmt: SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE  */
#line 471 "parser.y"
        {
            ASTNode *n = make_node(NODE_SWITCH);
            n->left  = (yyvsp[-4].node);   /* switch expression */
            n->right = (yyvsp[-1].node);   /* case list head    */
            (yyval.node) = n;
        }
#line 1995 "parser.tab.c"
    break;

  case 84: /* case_list: case_list case_item  */
#line 481 "parser.y"
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
#line 2010 "parser.tab.c"
    break;

  case 85: /* case_list: case_list default_item  */
#line 492 "parser.y"
        {
            if ((yyvsp[-1].node) == NULL) { (yyval.node) = (yyvsp[0].node); }
            else {
                ASTNode *tail = (yyvsp[-1].node);
                while (tail->next) tail = tail->next;
                tail->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-1].node);
            }
        }
#line 2024 "parser.tab.c"
    break;

  case 86: /* case_list: %empty  */
#line 501 "parser.y"
                  { (yyval.node) = NULL; }
#line 2030 "parser.tab.c"
    break;

  case 87: /* case_item: CASE case_expr COLON statement_list  */
#line 506 "parser.y"
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
#line 2050 "parser.tab.c"
    break;

  case 88: /* case_expr: expression  */
#line 525 "parser.y"
        {
            ASTNode *n = make_node(NODE_CASE);
            n->left = (yyvsp[0].node);   /* case value expression */
            (yyval.node) = n;
        }
#line 2060 "parser.tab.c"
    break;

  case 89: /* case_expr: expression RANGE expression  */
#line 531 "parser.y"
        {
            ASTNode *n = make_node(NODE_CASE_RANGE);
            n->left  = (yyvsp[-2].node);  /* range start */
            n->right = (yyvsp[0].node);  /* range end   */
            (yyval.node) = n;
        }
#line 2071 "parser.tab.c"
    break;

  case 90: /* default_item: DEFAULT COLON statement_list  */
#line 541 "parser.y"
        {
            ASTNode *n = make_node(NODE_DEFAULT);
            n->left = (yyvsp[0].node);   /* body */
            (yyval.node) = n;
        }
#line 2081 "parser.tab.c"
    break;

  case 91: /* for_init: assignment  */
#line 568 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2087 "parser.tab.c"
    break;

  case 92: /* for_init: declaration_no_semi  */
#line 569 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2093 "parser.tab.c"
    break;

  case 93: /* for_init: %empty  */
#line 570 "parser.y"
                  { (yyval.node) = NULL; }
#line 2099 "parser.tab.c"
    break;

  case 94: /* for_update: assignment  */
#line 574 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2105 "parser.tab.c"
    break;

  case 95: /* for_update: %empty  */
#line 575 "parser.y"
                  { (yyval.node) = NULL; }
#line 2111 "parser.tab.c"
    break;

  case 96: /* loop_stmt: WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE  */
#line 580 "parser.y"
        {
            ASTNode *n = make_node(NODE_WHILE);
            n->left  = (yyvsp[-4].node);   /* condition */
            n->right = (yyvsp[-1].node);   /* body      */
            (yyval.node) = n;
        }
#line 2122 "parser.tab.c"
    break;

  case 97: /* loop_stmt: DO LBRACE statement_list RBRACE WHILE LPAREN condition RPAREN SEMI  */
#line 587 "parser.y"
        {
            ASTNode *n = make_node(NODE_DO_WHILE);
            n->left  = (yyvsp[-6].node);   /* body      */
            n->right = (yyvsp[-2].node);   /* condition */
            (yyval.node) = n;
        }
#line 2133 "parser.tab.c"
    break;

  case 98: /* loop_stmt: FOR LPAREN for_init SEMI condition SEMI for_update RPAREN LBRACE statement_list RBRACE  */
#line 595 "parser.y"
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
#line 2150 "parser.tab.c"
    break;

  case 99: /* return_stmt: RETURN expression  */
#line 615 "parser.y"
        {
            ASTNode *n = make_node(NODE_RETURN);
            n->left = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 2160 "parser.tab.c"
    break;


#line 2164 "parser.tab.c"

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

#line 622 "parser.y"


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
