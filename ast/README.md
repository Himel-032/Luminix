# Luminix Compiler Project

## 1. Introduction

Luminix is a custom programming language developed for the Compiler Design Lab (CSE 3212). It is built using Flex for lexical analysis and Bison for parsing. The compiled file (`luminix.exe`) reads Luminix source code and produces output.

The language is similar to C but uses easier and more descriptive keywords so beginners can understand it better. For example, `int` is written as `Number`, `while` as `WhileStudy`, and `printf` as `Show`.

This project includes all main parts of a compiler front-end such as lexical analysis (`lexer.l`), syntax analysis (`parser.y`), AST generation (`ast.c` / `ast.h`), semantic analysis (`semantic.c` / `semantic.h`), and execution using an interpreter (`interpreter.c` / `interpreter.h`).

## 2. Flex - Lexical Analyzer

### Basic Structure

Flex (Fast Lexical Analyzer) is a tool for generating lexical analyzers (scanners) from regular expression rules. A Flex source file has three sections separated by `%%` delimiters:

- Definitions section - macro definitions, options, and included headers
- Rules section - pattern-action pairs that define how tokens are recognized
- User code section - auxiliary C functions such as `yywrap()`

Flex reads the source file, applies the rules in order, and returns token codes to the Bison parser. The `%option yylineno` directive is used in Luminix to track line numbers for error reporting.

### Lexical Patterns in Luminix

The Luminix lexer (`lexer.l`) defines the following named macros for use in rules:

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

The lexer recognizes four literal types: plain integers (`Number`), floating-point (`Decimal`) numbers, character literals (single-quoted: `Letter`), and string literals (double-quoted). Identifiers can start with a letter or underscore and may contain alphanumeric characters and underscores.

Comment handling uses a Flex exclusive start condition called `MULTILINE_COMMENT`. Single-line comments start with `##` and ignore the rest of the line. Multi-line comments open with `#*` and close with `*#`, and the `MULTILINE_COMMENT` state ignores all content within.

Example:

```text
## Example: single line comments
#*
   Example;
   multi-line comment
*#
```

Whitespace such as spaces, tabs, carriage returns, and newlines is ignored. All keywords in Luminix are reserved and recognized before the general identifier pattern, ensuring they cannot be used as variable names.

## 3. Bison - Parser Generator

### Basic Structure

Bison is an LALR(1) parser generator that reads a grammar specification and produces a C language parser.

The Bison grammar file (`parser.y`) uses a union to define the semantic value type, and `%type` directives assign types to non-terminals. `%left` and `%right` are used to declare operator precedence directives:

```text
%left  OR
%left  AND
%left  BIT_OR
%left  BIT_XOR
%left  BIT_AND
%left  EQ NEQ
%left  GT LT GE LE
%left  SHL SHR
%left  PLUS MINUS
%left  MUL DIV MOD
%right UNARY
```

The parser builds an abstract syntax tree (AST) as its output. Each grammar rule's semantic action calls AST node constructors (`make_node`, `make_binop`, `make_unary`, etc.) to create and link tree nodes using the `next` attribute. Statements are linked into lists via the node's `->next` pointer.

### How Flex and Bison Work Together

Flex and Bison are designed to work together. Flex generates the function `yylex()` and it is called by the parser `yyparse()` when a new token is needed. The workflow is:

- `yyparse()` is called from `main()` in `parser.y`. It drives the entire parse process.
- If the parser needs a token, it calls `yylex()` which scans the input and returns a token code along with a semantic value stored in the `yylval` union.
- The parser matches tokens with grammar rules and when a rule is fully matched, AST nodes are created.
- After the complete program is parsed, the `main_function` rule triggers semantic analysis and interpretation of the completed AST.

The shared header `parser.tab.h` defines all token constants so that `lexer.l` and `parser.y` agree on the same integer codes.

The compilation command is:

```bash
bison -d parser.y
flex lexer.l
gcc parser.tab.c lex.yy.c ast.c interpreter.c symtab.c semantic.c -o luminix -lm
./luminix input.txt
```

## 4. Luminix Language Overview

The following table provides a comprehensive overview of all Luminix language constructs, their equivalent C syntax, and a brief description of each feature.

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
| Pre-Decrement | `Decrement x;` | `--x;` | Decrement by 1 |
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

The Luminix lexer recognizes the following complete set of tokens. Each token has a unique integer constant generated by Bison and recognized by the Flex scanner.

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

The Luminix grammar is an LALR(1) context-free grammar defined in `parser.y`. The following subsections present the key production rules organized by construct.

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
| `type` | `Number | Decimal | LargeDecimal | Letter | TrueFalse` |
| `type` | `Nothing | BigNumber | SmallNumber | Positive` |

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
| `case_list` | `case_list case_item` |
| `case_list` | `case_list default_item` |
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
| `expression` | `expression & | ^ term` (bitwise) |
| `expression` | `expression << >> term` (shift) |
| `expression` | `- term` (unary negation) |
| `expression` | `! term` (logical NOT) |
| `expression` | `~ term` (bitwise NOT) |
| `expression` | `term` |
| `term` | `term * factor | term / factor | term % factor` |
| `term` | `factor` |
| `factor` | `primary` |
| `primary` | `IDENTIFIER | INT_LITERAL | FLOAT_LITERAL | CHAR_LITERAL` |
| `primary` | `True | False | ( expression ) | function_call | array_access` |
| `condition` | `expression == expression` |
| `condition` | `expression != expression` |
| `condition` | `expression > | < | >= | <= expression` |

## 7. Semantic Analysis

The semantic analysis phase (`semantic.c` / `semantic.h`) performs a three-pass walk over the AST to enforce the language's semantic rules. This phase runs after parsing and before interpretation. It maintains its own lightweight scoped symbol table and function table, entirely separate from the runtime tables used by the interpreter.

### Architecture

The semantic analyser uses two internal data structures. The first is a flat array of `SemSymbol` records forming a scoped symbol table, with a scope stack that records the count of symbols at each scope entry. The second is an array of `SemFunc` records that stores function signatures (name, return type, parameter count, parameter types). A multi-pass strategy is employed:

- Pass 1: Seed the semantic function table from the runtime function table (`functab`). All functions registered by the parser are mirrored into `sem_funcs`, enabling forward calls.
- Pass 2: Walk each user-defined function body in `functab`, checking all statements and expressions within.
- Pass 3: Walk the `StartExam` (main) function body, checking the top-level program statements.

### Semantic Checks

The following table lists all semantic checks performed by the analyser:

| # | Check | Description | Error / Warning Example |
|---|---|---|---|
| 1 | Variable declared before use | Ensures every identifier used is declared in a visible scope | use of undeclared variable `x` |
| 2 | No redeclaration in same scope | Prevents declaring the same variable twice in one scope | redeclaration of `n` in the same scope |
| 3 | Function declared before call | Validates all called functions exist in the function table | call to undeclared function `foo` |
| 4 | Argument count match | Checks the number of arguments matches the parameter list | function `add` expects 2 argument(s), got 1 |
| 5 | Type compatibility | Warns on numeric-char mismatches in assignments/initialisers | assigning numeric value to char variable `c` |
| 6 | Return value check | Ensures return expression matches function return type | returning a value from void function `f` |
| 7 | Break/Continue placement | `break` and `continue` are only valid inside a loop or switch | `break` used outside of loop or switch |
| 8 | Array vs scalar access | Ensures arrays are accessed with an index and scalars are not | `x` is not an array |
| 9 | Division by zero (literal) | Detects literal-level division by zero at compile time | division by zero (literal) |
| 10 | Void result in expression | Flags use of a void function's return value in an expression | void function result used in arithmetic expression |
| 11 | 2-D array single-index access | Prevents accessing a 2-D array with only one index | 2-D array `mat` accessed with a single index |
| 12 | Array used without index | Warns when an array name is used directly without subscript | array `arr` used without index (treating as pointer) |
| 13 | Arithmetic on char | Warns when char operands appear in arithmetic operations | arithmetic on char value (implicit numeric promotion) |
| 14 | Char used as array index | Warns when a char expression is used as an array subscript | char used as array index for `arr` |
| 15 | Switch on char | Warns when a char expression is used as a switch discriminant | switch on char expression (numeric value will be used) |
| 16 | Scope stack overflow | Protects against excessively deep nesting (>64 levels) | scope stack overflow (too many nested blocks) |

## 8. Symbol Table

The symbol table (`symtab.c` / `symtab.h`) is the runtime data store for all variables in a Luminix program. It uses a flat array of `Symbol` structs combined with a scope stack mechanism to support nested scopes (function calls, loop bodies, conditional blocks).

### Symbol Table Fields

| Field | Type | Description |
|---|---|---|
| `name` | `char[64]` | The identifier name (up to 63 characters) |
| `value` | `double` | Current numeric value of the variable |
| `type` | `int` | `0 = numeric`, `1 = char` |
| `is_array` | `int` | Flag: `1` if variable is an array, `0` otherwise |
| `dimensions` | `int` | Number of dimensions: `1` (1-D) or `2` (2-D) |
| `rows` | `int` | Number of rows for 2-D arrays |
| `cols` | `int` | Number of columns for 2-D arrays |
| `array_size` | `int` | Total size of a 1-D array (max 100 elements) |
| `array_values[100]` | `double[]` | Storage for 1-D array elements (max 100) |
| `array2d[50][50]` | `double[][]` | Storage for 2-D array elements (max 50x50) |

The symbol table supports up to 1000 symbols (`SYMTAB_MAX = 1000`), 1-D arrays up to 100 elements (`ARRAY_MAX = 100`), and 2-D arrays up to 50x50 elements (`ARRAY2D_MAX = 50`).

### Scope Management

Scope management is handled using `sym_push_frame()` and `sym_pop_frame()` functions. `sym_push_frame()` saves the current `symcount` value in a scope stack and `sym_pop_frame()` restores it, effectively ignoring all symbols declared since the frame was pushed. This ensures that local variables declared inside a function, loop, or block are invisible outside of it.

```c
void sym_push_frame(void);   /* save current symcount, enter new scope */
void sym_pop_frame(void);    /* restore symcount, exit scope, discard locals */
```

### Function Table

The function table (`functab`) is a separate global array that stores `FuncEntry` records for every user-defined function. Functions are registered during parsing by the `func_define()` call inside the `func_def` grammar rule. The function table supports up to 200 functions (`FUNC_MAX = 200`) each with up to 32 parameters (`PARAM_MAX = 32`).

| Field | Type | Description |
|---|---|---|
| `name` | `char[64]` | Function name |
| `ret_type` | `int` | Return type: `0 = numeric`, `1 = char`, `2 = void` |
| `param_count` | `int` | Number of formal parameters |
| `param_names[32][64]` | `char[][]` | Names of each parameter |
| `param_types[32]` | `int[]` | Types of each parameter (`0 = numeric`, `1 = char`) |
| `body` | `ASTNode *` | Pointer to the function body AST (not owned) |
| `params` | `ASTNode *` | Pointer to the parameter list AST (not owned) |

## 9. AST Interpreter

The AST interpreter (`interpreter.c` / `interpreter.h`) is a tree-walking evaluator that traverses the AST produced by the parser and executes each node. It is the execution engine of the Luminix system and replaces the code generation and runtime phases of a traditional compiler.

### Interpreter Interface

```c
void   interpret(ASTNode *root);                        /* Program entry: walk and execute */
double eval_expr(ASTNode *n);                           /* Evaluate expression -> double */
void   exec_stmt(ASTNode *n);                           /* Execute a statement node */
double call_function(const char *name, ASTNode *args);  /* Call a user-defined function */
```

### Expression Evaluation

The `eval_expr()` function handles all expression node types. Arithmetic operations (`ADD`, `SUB`, `MUL`, `DIV`, `MOD`) evaluate both children recursively and combine the results. Comparison operators return `1.0` (true) or `0.0` (false). Logical operators implement short-circuit evaluation. Built-in math functions (`Power`, `Root`, `Absolute`, `Floor`, `Ceil`) delegate to the corresponding C standard library functions via `math.h`.

### Statement Execution

`exec_stmt()` handles all statement node types via a large switch statement. Key behaviors include:

- `NODE_DECL`: Calls `sym_set()` to register the variable and evaluates any initializer expression.

### AST Node Types Reference

| Category | Node Type | Usage | Children |
|---|---|---|---|
| Literals | `NODE_INT_LIT` | Integer constant | `ival` payload |
| Literals | `NODE_FLOAT_LIT` | Float constant | `dval` payload |
| Literals | `NODE_CHAR_LIT` | Character constant | `cval` payload |
| Literals | `NODE_STRING_LIT` | String literal | `sval` payload |
| Literals | `NODE_BOOL_LIT` | Boolean (`True` / `False`) | `ival` (0 or 1) |
| Identifier | `NODE_IDENT` | Variable reference | `sval = name` |
| Arithmetic | `NODE_ADD` / `NODE_SUB` | Addition, subtraction | `left`, `right` |
| Arithmetic | `NODE_MUL` / `NODE_DIV` | Multiplication, division | `left`, `right` |
| Arithmetic | `NODE_MOD` | Modulus | `left`, `right` |
| Arithmetic | `NODE_NEGATE` | Unary negation | `left` |
| Comparison | `NODE_EQ` / `NODE_NEQ` | Equal / Not equal | `left`, `right` |
| Comparison | `NODE_GT` / `NODE_LT` | Greater / Less than | `left`, `right` |
| Comparison | `NODE_GE` / `NODE_LE` | GE / LE comparisons | `left`, `right` |
| Logical | `NODE_AND` / `NODE_OR` | Logical AND / OR | `left`, `right` |
| Logical | `NODE_NOT` | Logical NOT | `left` |
| Bitwise | `NODE_BIT_AND` / `NODE_BIT_OR` / `NODE_BIT_XOR` | Bitwise operations | `left`, `right` |
| Bitwise | `NODE_SHL` / `NODE_SHR` | Shift operations | `left`, `right` |
| Bitwise | `NODE_BIT_NOT` | Bitwise NOT | `left` |
| Math | `NODE_POW` | `Power(base, exp)` | `left = base`, `right = exp` |
| Math | `NODE_SQRT` / `NODE_ABS` / `NODE_FLOOR` / `NODE_CEIL` | Built-in math | `left = arg` |
| Array | `NODE_ARRAY_ACCESS` | `arr[i]` | `left = index`, `sval = name` |
| Array | `NODE_ARRAY_ACCESS_2D` | `arr[i][j]` | `left = row`, `right = col` |
| Statement | `NODE_DECL` | Variable declaration | `sval = name`, `left = init` |
| Statement | `NODE_DECL_ARRAY` | 1-D array declaration | `sval`, `cols = size` |
| Statement | `NODE_DECL_ARRAY_2D` | 2-D array declaration | `sval`, `rows`, `cols` |
| Statement | `NODE_ASSIGN` | Assignment | `sval = name`, `left = expr` |
| Statement | `NODE_ARRAY_ASSIGN` | Array element assign | `sval`, `left = idx`, `right = val` |
| Statement | `NODE_PRINT` | `Show()` statement | `sval = str` or `left = expr` |
| Statement | `NODE_SCAN` | `Take()` statement | `sval = varname` |
| Control | `NODE_IF` | `Check()` branch | `left = cond`, `right = body`, `extra = chain` |
| Control | `NODE_ELSEIF` | `ElseCheck()` branch | `left = cond`, `right = body`, `extra = next` |
| Control | `NODE_ELSE` | `Otherwise{}` block | `left = body` |
| Control | `NODE_SWITCH` | `Choose()` switch | `left = expr`, `right = cases` |
| Control | `NODE_CASE` | `Option` clause | `left = val`, `right = body` |
| Control | `NODE_CASE_RANGE` | `Option` range clause | `left = start`, `right = end`, `extra = body` |
| Control | `NODE_DEFAULT` | `DefaultOption` clause | `left = body` |
| Control | `NODE_BREAK` | `Stop;` | no children |
| Control | `NODE_CONTINUE` | `Skip;` | no children |
| Loop | `NODE_WHILE` | `WhileStudy` loop | `left = cond`, `right = body` |
| Loop | `NODE_DO_WHILE` | `DoOnce` loop | `left = body`, `right = cond` |
| Loop | `NODE_FOR` | `Repeat()` loop | `left = init`, `right = body`, `extra = parts` |
| Loop | `NODE_FOR_RANGE` | `Repeat i in (s..e)` | `sval = var`, `left = start`, `extra = end` |
| Loop | `NODE_FOR_RANGE_STEP` | `Repeat i in (s..e,step)` | `sval`, `left`, `extra = end + step` |
| Loop | `NODE_INCREMENT` | `Increment var;` | `sval = name` |
| Loop | `NODE_DECREMENT` | `Decrement var;` | `sval = name` |
| Function | `NODE_FUNC_DEF` | Function definition | `sval = name`, `left = params`, `right = body` |
| Function | `NODE_FUNC_CALL` | Function call | `sval = name`, `left = args` |
| Function | `NODE_PARAM` | Parameter | `sval = name`, `decl_type` |
| Function | `NODE_ARG_LIST` | Argument list | `left = expr`, `next = next arg` |
| Function | `NODE_RETURN` | `Return expr;` | `left = expr` |
| Function | `NODE_RETURN_VOID` | `Return;` | no children |
| Program | `NODE_PROGRAM` | Program root | `left = statement list` |

## 10. Main Features

### Program Entry Point

Every Luminix program must have a `StartExam()` function, which acts as the main entry point.

If multiple `StartExam()` functions are present, only the first one is executed; the rest are ignored.

Execution begins at the first statement inside `StartExam()`.

```text
#Attach <stdio.h>

StartExam(){
    Show("Hello, Luminix!");
    Return 0;
}
```

### Variable Declarations

Variables are declared using Luminix type keywords. Multiple variables can be declared in a single statement. Variables can optionally be initialised at declaration time.

```text
Number a = 10;
Number b, c;           ## multiple declarations
Decimal pi = 3.14159;
LargeDecimal e = 2.718281828;
Letter ch = 'Z';
TrueFalse flag = True;
BigNumber bigVal = 1000000;
Positive count = 5;
Number arr[10];         ## 1-D array of 10 elements
Number matrix[3][3];    ## 2-D array (3x3)
```

### Input / Output

Luminix uses `Show()` for output and `Take()` for input. The `Show()` function can print string literals, variable values, or arbitrary expressions. The optional `End` parameter controls the line ending.

```text
## Print a string literal
Show("Enter your age: ");

## Read a value into a variable
Number age;
Take(age);

## Print a variable
Show(age);

## Print with newline
Show("Result:", End="\n");

## Print an expression
Show(age * 2);
```

### Looping Statements

#### While Loop (`WhileStudy`)

The while loop evaluates its condition before each iteration.

```text
Number i = 0;
WhileStudy(i < 5){
    Show(i);
    i = i + 1;
}
```

#### Do-While Loop (`DoOnce`)

The do-while loop executes the body at least once, then checks the condition.

```text
Number x = 0;
DoOnce{
    Show(x);
    x = x + 1;
}WhileStudy(x < 3);
```

#### Classic For Loop (`Repeat`)

The classic for loop with initializer, condition and update.

```text
Repeat(Number j = 0; j < 10; j = j + 1){
    Show(j);
}
```

#### Range-Based For Loop

Luminix supports a Python-style range-based for loop, iterating from a start value up to, but not including, the end value.

```text
## Iterate i from 0 to 9
Repeat i in (0..10){
    Show(i);
}

## Iterate with a step (0, 5, 10, 15)
Repeat i in (0..20, 5){
    Show(i);
}
```

#### Break and Continue

`Stop` exits the innermost loop or switch. `Skip` skips to the next iteration of the innermost loop.

```text
Number n = 0;
WhileStudy(n < 10){
    n = n + 1;
    Check(n == 5){ Skip; }   ## skip iteration where n == 5
    Check(n == 8){ Stop; }    ## exit loop when n == 8
    Show(n);
}
```

### User-Defined Functions

Functions are defined above `StartExam()` with a return type, name, and parameter list. The function body may contain any statements. Recursive and mutually recursive calls are supported. The `Return` keyword is used to return a value.

```text
Number add(Number a, Number b){
    Return a + b;
}

Nothing greet(Number times){
    Number i = 0;
    WhileStudy(i < times){
        Show("Hello!");
        i = i + 1;
    }
}

StartExam(){
    Number result = add(3, 7);
    Show(result);
    greet(3);
    Return 0;
}
```

### Built-in Math Functions

Luminix provides five built-in mathematical functions that map directly to the C standard library:

| Function | Description and Example |
|---|---|
| `Power(base, exp)` | Raises base to the power exp. Example: `Power(2, 8)` returns `256` |
| `Root(x)` | Returns the square root of x. Example: `Root(16)` returns `4` |
| `Absolute(x)` | Returns the absolute value of x. Example: `Absolute(-25)` returns `25` |
| `Floor(x)` | Rounds x down to the nearest integer. Example: `Floor(3.7)` returns `3` |
| `Ceil(x)` | Rounds x up to the nearest integer. Example: `Ceil(3.2)` returns `4` |

```text
Number pw = Power(2, 10);
Number sq = Root(144);
Number ab = Absolute(-99);
Number fl = Floor(7.9);
Number ce = Ceil(7.1);
Show(pw);    ## 1024
Show(sq);    ## 12
Show(ab);    ## 99
Show(fl);    ## 7
Show(ce);    ## 8
```

### Comments

Luminix supports two comment styles. Single-line comments begin with `##` and continue to the end of the line. Multi-line (block) comments are enclosed between `#*` and `*#`.

```text
## This is a single-line comment

#*
   This is a multi-line comment.
   It can span many lines.
*#

Number x = 10;  ## inline comment after a statement
```

### Switch-Case

Luminix's `Choose` statement provides multi-way branching. In addition to standard single-value cases, Luminix uniquely supports range-based cases using the `..` operator. This allows matching a range of consecutive values with a single `Option` clause.

```text
Number score = 75;
Choose(score){
    Option 0..39:
        Show("Failed");
        Stop;
    Option 40..59:
        Show("Pass");
        Stop;
    Option 60..79:
        Show("Good");
        Stop;
    Option 80..100:
        Show("Excellent");
        Stop;
    DefaultOption:
        Show("Invalid score");
}
```

### If-Else

Luminix supports full if / else-if / else chains using `Check`, `ElseCheck`, and `Otherwise`. Branches can be nested to limited depth.

```text
Number a = 50;
Check(a > 100){
    Show("Large");
}ElseCheck(a > 50){
    Show("Medium");
}ElseCheck(a == 50){
    Show("Exactly 50");
}Otherwise{
    Show("Small");
}
```

## 11. Sample Programs

### Fibonacci Series

Computes and prints the first 10 Fibonacci numbers using a while loop.

```text
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

Demonstrates recursive user-defined functions in Luminix.

```text
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

### Grade Calculator Using Switch-Case

Demonstrates range-based switch-case with the `Choose` statement.

```text
#Attach <stdio.h>

StartExam(){
    Number marks;
    Show("Enter marks (0-100): ");
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

Demonstrates 1-D array declaration, assignment, and range-based for loop.

```text
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

Demonstrates nested control flow and user-defined functions.

```text
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
    Show("Enter a number: ");
    Take(num);
    Check(isPrime(num) == 1){
        Show("Prime");
    }Otherwise{
        Show("Not Prime");
    }
    Return 0;
}
```

### Bubble Sort

Demonstrates nested loops and array manipulation.

```text
#Attach <stdio.h>

StartExam(){
    Number arr[5];
    arr[0] = 64; arr[1] = 34; arr[2] = 25;
    arr[3] = 12; arr[4] = 22;

    ## Bubble sort
    Number i = 0;
    WhileStudy(i < 4){
        Number j = 0;
        WhileStudy(j < 4 - i){
            Check(arr[j] > arr[j + 1]){
                Number temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    Show("Sorted array:");
    Repeat k in (0..5){ Show(arr[k]); }
    Return 0;
}
```

## 12. Conclusion

The Luminix project successfully shows how a compiler front end works by combining all main phases like lexical analysis, parsing, AST generation, semantic checking, and execution. The language is designed similar to C but with simpler and more readable keywords, which makes it easier to understand.

It supports features like loops, functions, arrays, and switch-case, and the interpreter can execute them properly. Overall, this project gave practical experience of building a programming language and helped to understand compiler concepts in a better way.

## References

1. https://github.com/SubahNawarMahi/CSE-3212-Compiler-Design-Project.git
2. https://github.com/mdakilraihaniftee/Compiler-Design-with-Flex-and-Bison.git
3. Compilers: Principles, Techniques, and Tools (2nd ed.) - Aho, A. V., Lam, M. S., Sethi, R., & Ullman, J. D. Addison-Wesley.
