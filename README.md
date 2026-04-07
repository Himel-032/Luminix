# Luminix - a Beginner-Friendly C-like Programming Language

**Project Report**  
Department of Computer Science and Engineering  
Khulna University of Engineering & Technology, Khulna-9203

**Course Title:** Compiler Design Laboratory  
**Course No:** CSE 3212  
**Date of Submission:** 06-04-2026

## Submitted To

Md. Badiuzzaman Shuvo  
Lecturer, Dept. of CSE, Khulna University of Engineering & Technology

Subah Nawar  
Lecturer, Dept. of CSE, Khulna University of Engineering & Technology

## Submitted By

Md Himel  
Dept: CSE  
Roll: 2107032  
Year: Third  
Term: Second  
Group: A2  
Session: 2023-2024  
Batch: 2K21

## Table of Contents

1. Introduction  
2. Flex - Lexical Analyzer  
3. Bison - Parser Generator  
4. Luminix Language Overview  
5. Tokens  
6. Context-Free Grammar  
7. Semantic Analysis  
8. Symbol Table  
9. AST Interpreter  
10. Main Features  
11. Unique Features Beyond C Language  
12. Sample Programs  
13. Conclusion

## 1. Introduction

Luminix is a custom programming language developed for the Compiler Design Lab (CSE 3212). It is built using Flex for lexical analysis and Bison for parsing. The compiled file `luminix.exe` reads Luminix source code and produces output.

The language is similar to C but uses easier and more descriptive keywords so beginners can understand it better. For example, `int` is written as `Number`, `while` as `WhileStudy`, and `printf` as `Show`.

This project includes all major parts of a compiler front-end and interpreter: lexical analysis (`lexer.l`), syntax analysis (`parser.y`), AST generation (`ast.c` and `ast.h`), semantic analysis (`semantic.c` and `semantic.h`), symbol table management (`symtab.c` and `symtab.h`), and execution using an interpreter (`interpreter.c` and `interpreter.h`).

## 2. Flex - Lexical Analyzer

### Basic Structure

Flex (Fast Lexical Analyzer) is a tool for generating lexical analyzers from regular-expression rules. A Flex source file has three sections separated by `%%` delimiters:

- Definitions section: macro definitions, options, and included headers
- Rules section: pattern-action pairs that define how tokens are recognized
- User code section: auxiliary C functions such as `yywrap()`

Flex reads the source file, applies the rules in order, and returns token codes to the Bison parser. The `%option yylineno` directive is used in Luminix to track line numbers for error reporting.

### Lexical Patterns in Luminix

The Luminix lexer defines the following named macros:

```text
DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          [a-zA-Z_][a-zA-Z0-9_]*
INTEGER     {DIGIT}+
FLOAT       {DIGIT}+"."{DIGIT}+
EXPONENT    {DIGIT}+("."{DIGIT}+)?[eE][+-]?{DIGIT}+
STRING      \"([^\"\\\n]|\\.)*\"
CHAR        \'([^\'\\\n]|\\.)\'
HEADER_SYS  <[a-zA-Z_][a-zA-Z0-9_]*\.h>
HEADER_USER "[a-zA-Z_][a-zA-Z0-9_]*\.h"
```

The lexer recognizes integers, decimal values, character literals, string literals, identifiers, keywords, operators, punctuation, and comments.

Comment handling uses a Flex exclusive start condition called `MULTILINE_COMMENT`. Single-line comments begin with `##` and ignore the rest of the line. Multi-line comments open with `#*` and close with `*#`.

Whitespace such as spaces, tabs, carriage returns, and newlines is ignored. All keywords in Luminix are reserved and recognized before the general identifier pattern.

## 3. Bison - Parser Generator

### Basic Structure

Bison is a parser generator that reads a grammar specification and produces a C parser. The Bison grammar file `parser.y` uses a union to define semantic value types, and `%type` directives assign types to non-terminals. Precedence is declared using `%left` and `%right`.

The parser builds an abstract syntax tree as its output. Each grammar rule's semantic action calls AST node constructors such as `make_node`, `make_binop`, and `make_unary` to create and link tree nodes using the `next` attribute. Statements are linked into lists via the node's `->next` pointer.

### How Flex and Bison Work Together

Flex generates the `yylex()` function and Bison calls it from `yyparse()` whenever a new token is needed. The workflow is:

- `yyparse()` is called from `main()` in `parser.y`
- when the parser needs a token, it calls `yylex()`
- `yylex()` scans the input and returns a token code with semantic value in `yylval`
- grammar rules reduce the token stream into AST nodes
- after parsing, semantic analysis and interpretation run on the completed AST

The shared header `parser.tab.h` defines token constants so that `lexer.l` and `parser.y` agree on the same integer codes.

## 4. Luminix Language Overview

| Feature | Luminix Syntax | C Equivalent | Notes |
|---|---|---|---|
| Integer Declaration | `Number x = 5;` | `int x = 5;` | Whole number type |
| Float Declaration | `Decimal x = 3.14;` | `float x = 3.14;` | Single precision decimal |
| Double Declaration | `LargeDecimal x = 3.14;` | `double x = 3.14;` | Double precision decimal |
| Char Declaration | `Letter c = 'A';` | `char c = 'A';` | Single character |
| Boolean | `TrueFalse f = True;` | `bool f = true;` | True / False literals |
| Void Return | `Nothing func()` | `void func()` | No return value |
| Long Integer | `BigNumber n;` | `long n;` | Extended integer range |
| Short Integer | `SmallNumber n;` | `short n;` | Compact integer |
| Unsigned | `Positive n;` | `unsigned n;` | Non-negative integer |
| 1-D Array | `Number arr[5];` | `int arr[5];` | Fixed-size array |
| 2-D Array | `Number mat[3][3];` | `int mat[3][3];` | Matrix-style array |
| If Statement | `Check(cond){...}` | `if(cond){...}` | Conditional branch |
| Else | `Otherwise{...}` | `else{...}` | Default branch |
| Else-If | `ElseCheck(cond){...}` | `else if(cond){...}` | Chained condition |
| Switch | `Choose(expr){...}` | `switch(expr){...}` | Multi-way branch |
| Case | `Option val: ...` | `case val: ...` | Case clause |
| Range Case | `Option 1..10: ...` | `case 1 ... 10:` | Range-based case |
| Default | `DefaultOption: ...` | `default: ...` | Fallback case |
| Break | `Stop;` | `break;` | Exit loop/switch |
| Continue | `Skip;` | `continue;` | Skip to next iteration |
| Return | `Return expr;` | `return expr;` | Return from function |
| While Loop | `WhileStudy(cond){...}` | `while(cond){...}` | Pre-test loop |
| Do-While | `DoOnce{...}WhileStudy(c);` | `do{...}while(c);` | Post-test loop |
| For Loop | `Repeat(init;cond;upd){...}` | `for(init;cond;upd){...}` | Classic for loop |
| Range For | `Repeat i in (0..10){...}` | - | Pythonic range loop |
| Stepped Range | `Repeat i in (0..20,5){...}` | - | Range with step |
| Pre-Increment | `Increment x;` | `++x` | Increment by 1 |
| Pre-Decrement | `Decrement x;` | `--x` | Decrement by 1 |
| Print | `Show("text");` | `printf("text");` | Output to console |
| Print Newline | `Show("t",End="\n");` | `printf("t\n");` | Output with newline |
| Input | `Take(var);` | `scanf("%d",&var);` | Read from stdin |
| Function Def | `Number add(Number a){...}` | `int add(int a){...}` | User function |
| Function Call | `result = add(5);` | `result = add(5);` | Invoke function |
| Power | `Power(2, 8)` | `pow(2.0, 8.0)` | Built-in math |
| Square Root | `Root(16)` | `sqrt(16.0)` | Built-in math |
| Absolute | `Absolute(-5)` | `abs(-5)` | Built-in math |
| Floor | `Floor(3.7)` | `floor(3.7)` | Built-in math |
| Ceil | `Ceil(3.2)` | `ceil(3.2)` | Built-in math |
| Single Comment | `## This is a comment` | `// comment` | Line comment |
| Multi Comment | `#* ... *#` | `/* ... */` | Block comment |
| Include | `#Attach <stdio.h>` | `#include <stdio.h>` | File include |
| Define | `#Suppose MAX 100` | `#define MAX 100` | Macro define |
| Logical AND | `&&` | `&&` | Logical AND |
| Logical OR | `||` | `||` | Logical OR |
| Logical NOT | `!` | `!` | Logical NOT |
| Bitwise AND | `&` | `&` | Bitwise AND |
| Bitwise OR | `|` | `|` | Bitwise OR |
| Bitwise XOR | `^` | `^` | XOR |
| Bitwise NOT | `~` | `~` | Bitwise NOT |
| Left Shift | `<<` | `<<` | Shift left |
| Right Shift | `>>` | `>>` | Shift right |

## 5. Tokens

The Luminix lexer recognizes the full set of tokens listed below.

| Token Type | Luminix Keyword | C Equivalent | Description |
|---|---|---|---|
| `INT_TYPE` | `Number` | `int` | Integer variable |
| `FLOAT_TYPE` | `Decimal` | `float` | Float variable |
| `DOUBLE_TYPE` | `LargeDecimal` | `double` | Double precision float |
| `CHAR_TYPE` | `Letter` | `char` | Character variable |
| `BOOL_TYPE` | `TrueFalse` | `bool` | Boolean variable |
| `VOID_TYPE` | `Nothing` | `void` | Void return type |
| `LONG_TYPE` | `BigNumber` | `long` | Long integer |
| `SHORT_TYPE` | `SmallNumber` | `short` | Short integer |
| `UNSIGNED_TYPE` | `Positive` | `unsigned` | Unsigned integer |
| `CONST` | `Constant` | `const` | Constant modifier |
| `IF` | `Check` | `if` | Conditional check |
| `ELSE` | `Otherwise` | `else` | Else branch |
| `ELSEIF` | `ElseCheck` | `else if` | Else-if branch |
| `SWITCH` | `Choose` | `switch` | Switch statement |
| `CASE` | `Option` | `case` | Switch case |
| `DEFAULT` | `DefaultOption` | `default` | Default case |
| `BREAK` | `Stop` | `break` | Break from loop/switch |
| `CONTINUE` | `Skip` | `continue` | Continue loop |
| `RETURN` | `Return` | `return` | Return statement |
| `FOR` | `Repeat` | `for` | For loop |
| `WHILE` | `WhileStudy` | `while` | While loop |
| `DO` | `DoOnce` | `do` | Do-while loop |
| `IN` | `in` | - | Range-based for |
| `INCREMENT` | `Increment` | - | Pre-increment macro |
| `DECREMENT` | `Decrement` | - | Pre-decrement macro |
| `MAIN` | `StartExam` | `main` | Program entry |
| `PRINT` | `Show` | `printf` | Output statement |
| `SCAN` | `Take` | `scanf` | Input statement |
| `END` | `End` | `\n` | Print newline option |
| `POW` | `Power` | `pow()` | Power function |
| `SQRT` | `Root` | `sqrt()` | Square root |
| `ABS` | `Absolute` | `abs()` | Absolute value |
| `FLOOR` | `Floor` | `floor()` | Floor function |
| `CEIL` | `Ceil` | `ceil()` | Ceil function |
| `INCLUDE` | `#Attach` | `#include` | File inclusion |
| `DEFINE` | `#Suppose` | `#define` | Macro definition |

## 6. Context-Free Grammar

The Luminix grammar is an LALR(1) context-free grammar defined in `parser.y`.

### Program Structure

| Non-terminal | Production Rule |
|---|---|
| `program` | `preprocessor_list top_level_list` |
| `top_level_list` | `top_level_list func_def` |
| `top_level_list` | `top_level_list main_function` |
| `top_level_list` | `ε` |
| `main_function` | `StartExam ( ) { statement_list }` |
| `preprocessor` | `#Attach HEADER` |
| `preprocessor` | `#Suppose IDENTIFIER INT_LITERAL` |

### Variable Declarations

| Non-terminal | Production Rule |
|---|---|
| `declaration` | `type identifier_list_decls ;` |
| `declaration` | `type IDENTIFIER [ array_size ] ;` |
| `declaration` | `type IDENTIFIER [ array_size ] [ array_size ] ;` |
| `identifier_list_decls` | `IDENTIFIER` |
| `identifier_list_decls` | `IDENTIFIER = expression` |
| `identifier_list_decls` | `IDENTIFIER , identifier_list_decls` |
| `identifier_list_decls` | `IDENTIFIER = expression , identifier_list_decls` |

### Function Definition and Calls

| Non-terminal | Production Rule |
|---|---|
| `func_def` | `ret_type IDENTIFIER ( param_list ) { statement_list }` |
| `param_list` | `param_list , param` |
| `param_list` | `param` |
| `param_list` | `ε` |
| `param` | `type IDENTIFIER` |
| `func_call_expr` | `IDENTIFIER ( arg_list_opt )` |
| `arg_list_opt` | `arg_list` |
| `arg_list_opt` | `ε` |
| `arg_list` | `arg_list , expression` |
| `arg_list` | `expression` |
| `return_stmt` | `Return expression` |

### Control Flow

| Non-terminal | Production Rule |
|---|---|
| `if_stmt` | `Check ( condition ) { statement_list } else_if_part` |
| `else_if_part` | `ElseCheck ( condition ) { statement_list } else_if_part` |
| `else_if_part` | `Otherwise { statement_list }` |
| `else_if_part` | `ε` |
| `switch_stmt` | `Choose ( expression ) { case_list }` |
| `case_item` | `Option case_expr : statement_list` |
| `case_expr` | `expression` |
| `case_expr` | `expression .. expression` |
| `default_item` | `DefaultOption : statement_list` |

### Looping Constructs

| Non-terminal | Production Rule |
|---|---|
| `loop_stmt` | `WhileStudy ( condition ) { statement_list }` |
| `loop_stmt` | `DoOnce { statement_list } WhileStudy ( condition ) ;` |
| `loop_stmt` | `Repeat ( for_init ; condition ; for_update ) { statement_list }` |
| `loop_stmt` | `Repeat IDENTIFIER in ( expression .. expression ) { statement_list }` |
| `loop_stmt` | `Repeat IDENTIFIER in ( expression .. expression , expression ) { statement_list }` |
| `for_init` | `assignment | declaration_no_semi | ε` |
| `for_update` | `assignment | ε` |

### Expression Grammar

| Non-terminal | Production Rule |
|---|---|
| `expression` | `expression + term` |
| `expression` | `expression - term` |
| `expression` | `expression && term` |
| `expression` | `expression || term` |
| `expression` | `expression & | ^ term` |
| `expression` | `expression << >> term` |
| `expression` | `- term` |
| `expression` | `! term` |
| `expression` | `~ term` |
| `expression` | `term` |
| `term` | `term * factor` |
| `term` | `term / factor` |
| `term` | `term % factor` |
| `term` | `factor` |
| `factor` | `primary` |
| `primary` | `IDENTIFIER | INT_LITERAL | FLOAT_LITERAL | CHAR_LITERAL` |
| `primary` | `True | False | ( expression ) | function_call | array_access` |
| `condition` | `expression == expression` |
| `condition` | `expression != expression` |
| `condition` | `expression > < >= <= expression` |

## 7. Semantic Analysis

The semantic analysis phase (`semantic.c` and `semantic.h`) performs a walk over the AST to enforce the language's semantic rules. This phase runs after parsing and before interpretation.

Semantic checks include:

- variable declared before use
- no redeclaration in the same scope
- function existence before call
- argument count matching
- type compatibility for numeric and char values
- return type correctness
- break/continue used in valid context
- array vs scalar consistency
- literal-level division by zero detection
- void result used in an expression

The analyzer also maintains scope information and a function signature table.

## 8. Symbol Table

The symbol table (`symtab.c` and `symtab.h`) stores runtime information for all variables in a Luminix program.

### Symbol Fields

| Field | Type | Description |
|---|---|---|
| `name` | `char[64]` | Identifier name |
| `value` | `double` | Current numeric value |
| `type` | `int` | 0 = numeric, 1 = char |
| `is_array` | `int` | 1 if array, 0 otherwise |
| `dimensions` | `int` | 1 for 1-D, 2 for 2-D |
| `rows` | `int` | 2-D row count |
| `cols` | `int` | 2-D column count |
| `array_size` | `int` | Size of a 1-D array |
| `array_values[100]` | `double[]` | Storage for 1-D arrays |
| `array2d[50][50]` | `double[][]` | Storage for 2-D arrays |

The symbol table supports up to 1000 symbols, 1-D arrays up to 100 elements, and 2-D arrays up to 50x50 elements.

### Scope Management

Scope management is handled using `sym_push_frame()` and `sym_pop_frame()`. These functions save and restore the current symbol count so that local variables declared inside a function, loop, or block are not visible outside that scope.

### Function Table

The function table stores every user-defined function with its name, return type, parameter list, and body AST. It is populated during parsing using `func_define()`.

## 9. AST Interpreter

The AST interpreter (`interpreter.c` and `interpreter.h`) is a tree-walking evaluator that traverses the AST produced by the parser and executes each node.

### Interpreter Interface

```c
void interpret(ASTNode *root);
double eval_expr(ASTNode *n);
void exec_stmt(ASTNode *n);
double call_function(const char *name, ASTNode *arg_list);
```

### Behavior

- `eval_expr()` evaluates expression nodes and returns a numeric value
- `exec_stmt()` executes statements and control flow constructs
- `call_function()` invokes user-defined functions using a separate scope frame
- built-in math functions map to C math library functions
- runtime errors include undefined variables, out-of-bounds array access, and divide-by-zero

## 10. Main Features

### Program Entry Point

Every Luminix program starts from `StartExam()`.

```luminix
#Attach <stdio.h>

StartExam(){
	Show("Hello, Luminix!");
	Return 0;
}
```

### Variable Declarations

```luminix
Number a = 10;
Decimal pi = 3.14159;
Letter ch = 'A';
TrueFalse flag = True;
Number arr[5];
Number mat[3][3];
```

### Input / Output

```luminix
Show("Enter your age:");
Take(age);
Show(age);
Show("Result:", End="\n");
```

### Looping Statements

```luminix
WhileStudy(i < 5){ ... }
DoOnce{ ... }WhileStudy(i < 3);
Repeat(Number j = 0; j < 10; j = j + 1){ ... }
Repeat k in (0..10){ ... }
Repeat m in (0..20, 5){ ... }
```

### User-Defined Functions

```luminix
Number add(Number a, Number b){
	Return a + b;
}
```

### Built-in Math Functions

```luminix
Power(2, 8)
Root(16)
Absolute(-5)
Floor(3.7)
Ceil(3.2)
```

### Comments

```luminix
## single-line comment

#*
  multi-line comment
*#
```

### Switch Case

```luminix
Choose(score){
	Option 0..39:
		Show("Failed");
		Stop;
	DefaultOption:
		Show("Invalid score");
}
```

### If-Else

```luminix
Check(a > 100){
	Show("Large");
}
ElseCheck(a == 100){
	Show("Exactly 100");
}
Otherwise{
	Show("Small");
}
```

## 11. Unique Features Beyond C Language

Luminix includes several features that are not standard C syntax:

- beginner-friendly keywords such as `Check`, `Otherwise`, `Repeat`, `WhileStudy`, `DoOnce`, `Show`, and `Take`
- range-based for loops like `Repeat i in (0..10)`
- stepped range loops like `Repeat i in (0..20, 5)`
- range-based switch cases like `Option 10..100:`
- dedicated built-in math keywords: `Power`, `Root`, `Absolute`, `Floor`, and `Ceil`
- a custom include style using `#Attach`
- a custom define style using `#Suppose`
- custom comment syntax using `##` and `#* ... *#`
- output customization using `End` inside `Show()`

These features make the language more readable and beginner-friendly than standard C.

## 12. Sample Programs

### Fibonacci Series

```luminix
#Attach <stdio.h>

StartExam(){
	Number a = 0, b = 1, temp;
	Number i = 0;
	Show("Fibonacci Series:");
	WhileStudy(i < 10){
		Show(a);
		temp = a + b;
		a = b;
		b = temp;
		i = i + 1;
	}
	Return 0;
}
```

### Factorial Using Recursive Function

```luminix
#Attach <stdio.h>

Number factorial(Number n){
	Check(n <= 1){
		Return 1;
	}
	Return n * factorial(n - 1);
}

StartExam(){
	Number n = 7;
	Show("Factorial of 7 =", End=" ");
	Show(factorial(n));
	Return 0;
}
```

### Grade Calculator Using Switch Case

```luminix
#Attach <stdio.h>

StartExam(){
	Number marks;
	Take(marks);
	Choose(marks){
		Option 80..100:
			Show("Grade A - Excellent");
			Stop;
		Option 60..79:
			Show("Grade B - Good");
			Stop;
		Option 40..59:
			Show("Grade C - Pass");
			Stop;
		Option 0..39:
			Show("Grade F - Fail");
			Stop;
		DefaultOption:
			Show("Invalid marks");
	}
	Return 0;
}
```

### Sum of Array Elements

```luminix
#Attach <stdio.h>

StartExam(){
	Number arr[5];
	arr[0] = 10; arr[1] = 20; arr[2] = 30;
	arr[3] = 40; arr[4] = 50;

	Number sum = 0;
	Repeat i in (0..5){
		sum = sum + arr[i];
	}
	Show("Sum =");
	Show(sum);
	Return 0;
}
```

### Prime Number Check

```luminix
#Attach <stdio.h>

TrueFalse isPrime(Number n){
	Check(n <= 1){ Return False; }
	Number i = 2;
	WhileStudy(i * i <= n){
		Check(n % i == 0){ Return False; }
		i = i + 1;
	}
	Return True;
}

StartExam(){
	Number num;
	Take(num);
	Check(isPrime(num) == 1){
		Show("Prime");
	}
	Otherwise{
		Show("Not Prime");
	}
	Return 0;
}
```

## 13. Conclusion

The Luminix project successfully demonstrates how a compiler front end works by combining lexical analysis, parsing, AST generation, semantic checking, and execution. The language is similar to C but uses more readable keywords, making it easier for beginners to understand.

It supports loops, functions, arrays, switch-case, conditionals, and built-in math functions. Overall, this project provided practical experience in building a programming language and deepened understanding of compiler concepts.

## References

1. https://github.com/SubahNawarMahi/CSE-3212-Compiler-Design-Project.git
2. https://github.com/mdakilraihaniftee/Compiler-Design-with-Flex-and-Bison.git
3. *Compilers: Principles, Techniques, and Tools* (2nd ed.), Aho, Lam, Sethi, and Ullman.