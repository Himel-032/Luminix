/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INCLUDE = 258,                 /* INCLUDE  */
    DEFINE = 259,                  /* DEFINE  */
    HEADER = 260,                  /* HEADER  */
    INT_TYPE = 261,                /* INT_TYPE  */
    FLOAT_TYPE = 262,              /* FLOAT_TYPE  */
    DOUBLE_TYPE = 263,             /* DOUBLE_TYPE  */
    CHAR_TYPE = 264,               /* CHAR_TYPE  */
    BOOL_TYPE = 265,               /* BOOL_TYPE  */
    VOID_TYPE = 266,               /* VOID_TYPE  */
    LONG_TYPE = 267,               /* LONG_TYPE  */
    SHORT_TYPE = 268,              /* SHORT_TYPE  */
    UNSIGNED_TYPE = 269,           /* UNSIGNED_TYPE  */
    CONST = 270,                   /* CONST  */
    STRUCT = 271,                  /* STRUCT  */
    UNION = 272,                   /* UNION  */
    TYPEDEF = 273,                 /* TYPEDEF  */
    ENUM = 274,                    /* ENUM  */
    IF = 275,                      /* IF  */
    ELSE = 276,                    /* ELSE  */
    ELSEIF = 277,                  /* ELSEIF  */
    SWITCH = 278,                  /* SWITCH  */
    CASE = 279,                    /* CASE  */
    DEFAULT = 280,                 /* DEFAULT  */
    FOR = 281,                     /* FOR  */
    WHILE = 282,                   /* WHILE  */
    DO = 283,                      /* DO  */
    BREAK = 284,                   /* BREAK  */
    CONTINUE = 285,                /* CONTINUE  */
    RETURN = 286,                  /* RETURN  */
    MAIN = 287,                    /* MAIN  */
    PRINT = 288,                   /* PRINT  */
    SCAN = 289,                    /* SCAN  */
    END = 290,                     /* END  */
    TRUE_LITERAL = 291,            /* TRUE_LITERAL  */
    FALSE_LITERAL = 292,           /* FALSE_LITERAL  */
    POW = 293,                     /* POW  */
    SQRT = 294,                    /* SQRT  */
    ABS = 295,                     /* ABS  */
    FLOOR = 296,                   /* FLOOR  */
    CEIL = 297,                    /* CEIL  */
    EQ = 298,                      /* EQ  */
    NEQ = 299,                     /* NEQ  */
    GE = 300,                      /* GE  */
    LE = 301,                      /* LE  */
    GT = 302,                      /* GT  */
    LT = 303,                      /* LT  */
    AND = 304,                     /* AND  */
    OR = 305,                      /* OR  */
    NOT = 306,                     /* NOT  */
    INC = 307,                     /* INC  */
    DEC = 308,                     /* DEC  */
    IN = 309,                      /* IN  */
    INCREMENT = 310,               /* INCREMENT  */
    DECREMENT = 311,               /* DECREMENT  */
    PLUS = 312,                    /* PLUS  */
    MINUS = 313,                   /* MINUS  */
    MUL = 314,                     /* MUL  */
    DIV = 315,                     /* DIV  */
    MOD = 316,                     /* MOD  */
    ASSIGN = 317,                  /* ASSIGN  */
    BIT_AND = 318,                 /* BIT_AND  */
    BIT_OR = 319,                  /* BIT_OR  */
    BIT_XOR = 320,                 /* BIT_XOR  */
    BIT_NOT = 321,                 /* BIT_NOT  */
    SHL = 322,                     /* SHL  */
    SHR = 323,                     /* SHR  */
    SEMI = 324,                    /* SEMI  */
    COMMA = 325,                   /* COMMA  */
    COLON = 326,                   /* COLON  */
    LPAREN = 327,                  /* LPAREN  */
    RPAREN = 328,                  /* RPAREN  */
    LBRACE = 329,                  /* LBRACE  */
    RBRACE = 330,                  /* RBRACE  */
    LBRACKET = 331,                /* LBRACKET  */
    RBRACKET = 332,                /* RBRACKET  */
    RANGE = 333,                   /* RANGE  */
    INT_LITERAL = 334,             /* INT_LITERAL  */
    FLOAT_LITERAL = 335,           /* FLOAT_LITERAL  */
    STRING_LITERAL = 336,          /* STRING_LITERAL  */
    CHAR_LITERAL = 337,            /* CHAR_LITERAL  */
    IDENTIFIER = 338,              /* IDENTIFIER  */
    UNARY = 339                    /* UNARY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "parser.y"

    int      ival;
    float    fval;
    char     cval;
    char    *sval;
    double   dval;
    ASTNode *node;   /* <-- NEW: AST node pointer */

#line 157 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
