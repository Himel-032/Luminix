# AST Folder Documentation (Luminix Compiler/Interpreter)

## 1. Purpose Of This Folder
The `ast` folder contains the full Luminix language pipeline:
- lexical analysis (Flex)
- parsing (Bison)
- AST construction
- semantic analysis
- interpretation (runtime execution)
- symbol/function table management
- sample and test programs

This README documents every file in this folder and explains the function-level behavior for source files.

---

## 2. File Inventory (All Files In `ast`)

### Core source and headers
- `.gitignore`: ignores generated/build artifacts such as parser/scanner outputs and executable files.
- `ast.h`: defines AST node types (`NodeType`) and `ASTNode` structure, plus constructor/destructor/printer declarations.
- `ast.c`: implements AST node construction, AST printing, and AST memory cleanup.
- `interpreter.h`: public API for evaluating and executing AST.
- `interpreter.c`: tree-walking interpreter runtime.
- `symtab.h`: symbol table and function table declarations and APIs.
- `symtab.c`: symbol/function table implementation, including scoped frames.
- `semantic.h`: semantic analysis API and semantic type definitions.
- `semantic.c`: semantic checker implementation (errors/warnings before execution).

### Grammar and lexer
- `parser.y`: main Bison grammar (current parser with semantic pass, functions, loops, print end option, etc.).
- `parser_19.y`: older/alternate grammar snapshot.
- `lexer.l`: Flex lexer specification mapping Luminix keywords/syntax to tokens.

### Generated files
- `parser.tab.c`: generated C parser from `parser.y` (Bison output).
- `parser.tab.h`: generated token/YYSTYPE header from Bison.
- `lex.yy.c`: generated scanner C source from `lexer.l` (Flex output).
- `parser.output`: Bison parser report (states, shifts/reductions, conflicts).

### Build and binaries
- `Makefile`: build/run automation for Windows-style cleanup and input switching.
- `luminix.exe`: compiled executable.
- `Luminix v2.pdf`: project/specification document.

### Input/output and tests at folder root
- `input.txt`: primary sample program.
- `input_fixed.txt`: corrected/variant sample program.
- `output.txt`: output capture file (currently empty in this workspace).
- `test_while_loops.txt`: while-loop behavior tests.
- `test_for_loops.txt`: for-loop behavior tests.
- `test_advanced_loops.txt`: advanced nested/mixed loop tests.
- `test_all_loops.txt`: comprehensive loop feature test suite.
- `test_skip_minimal.txt`: minimal `continue` (`Skip`) loop test.

### Input suite subfolder
- `input/conditional.txt`: if/elseif/else scenarios.
- `input/function.txt`: user-defined function call/return scenarios.
- `input/logical_bitwise.txt`: logical and bitwise operator tests.
- `input/loop.txt`: mixed loop examples, including range loops.
- `input/switch.txt`: switch/case/range/default examples.
- `input/variables.txt`: variable declarations, arrays, math functions, IO.
- `input/loops/while.txt`: while loop with nested for example.

---

## 3. Function-Level Documentation

## `ast.c`
AST construction and utility implementation.

- `make_node(NodeType type)`
  - Allocates and zero-initializes an `ASTNode`.
  - Sets node type and source line number (`yylineno`).
- `make_int_lit(int v)`
  - Creates integer literal node (`NODE_INT_LIT`).
- `make_float_lit(double v)`
  - Creates float literal node (`NODE_FLOAT_LIT`).
- `make_char_lit(char v)`
  - Creates character literal node (`NODE_CHAR_LIT`).
- `make_string_lit(const char *s)`
  - Creates string literal node (`NODE_STRING_LIT`) and duplicates string.
- `make_bool_lit(int v)`
  - Creates boolean literal node (`NODE_BOOL_LIT`).
- `make_ident(const char *name)`
  - Creates identifier node (`NODE_IDENT`) with copied symbol name.
- `make_binop(NodeType op, ASTNode *l, ASTNode *r)`
  - Creates binary operator node (`left` and `right` operands).
- `make_unary(NodeType op, ASTNode *operand)`
  - Creates unary operator node (`left` operand).
- `make_func1(NodeType fn, ASTNode *arg)`
  - Creates one-argument built-in function node (`SQRT`, `ABS`, etc.).
- `make_func2(NodeType fn, ASTNode *a, ASTNode *b)`
  - Creates two-argument built-in function node (for example `POW`).
- `make_array_access(const char *name, ASTNode *idx)`
  - Creates one-dimensional array access node.
- `make_array_access_2d(const char *name, ASTNode *row, ASTNode *col)`
  - Creates two-dimensional array access node.
- `make_stmt_list(ASTNode *stmt, ASTNode *rest)`
  - Creates statement-list wrapper node and links siblings.
- `make_param(const char *name, int type)`
  - Creates function parameter node with declaration type.
- `make_func_def(const char *name, int ret_type, ASTNode *params, ASTNode *body)`
  - Creates function definition node, storing function signature/body pointers.
- `make_func_call(const char *name, ASTNode *args)`
  - Creates user-defined function call node.
- `make_arg_list(ASTNode *expr, ASTNode *next)`
  - Creates linked list node for function call arguments.
- `make_return_void(void)`
  - Creates `NODE_RETURN_VOID` for `return;`.
- `free_ast(ASTNode *n)`
  - Recursively frees all AST descendants and owned strings.
- `node_name(NodeType t)` (static)
  - Maps node enum to readable label for debug printing.
- `print_ast_file(ASTNode *n, int indent, FILE *out)`
  - Pretty-prints AST recursively to file stream.
- `print_ast(ASTNode *n, int indent)`
  - Convenience wrapper that prints AST to stdout.

## `interpreter.c`
Runtime execution engine for AST.

- `eval_expr(ASTNode *n)`
  - Evaluates expression nodes to `double`.
  - Handles literals, arithmetic, comparisons, logical/bitwise ops, arrays, built-ins, and user function calls.
- `exec_if(ASTNode *n, int already_matched)` (static)
  - Executes `if/elseif/else` chain, ensuring first matched branch only.
- `exec_switch(ASTNode *n)` (static)
  - Executes switch/case/range/default chains.
  - Consumes `break` at switch level while preserving loop `continue` semantics.
- `exec_stmt(ASTNode *n)`
  - Executes statement nodes: declarations, assignments, print/scan, control flow, loops, returns, and statement lists.
  - Propagates and consumes control-flow signals (`break`, `continue`, `return`) correctly.
- `call_function(const char *name, ASTNode *arg_list)`
  - Looks up function, evaluates arguments in caller context, creates new frame, binds params, executes function body, returns value.
- `interpret(ASTNode *root)`
  - Entry point; executes program root statement list.

## `symtab.c`
Symbol/function table and scope frame implementation.

- `func_define(const char *name, int ret_type, ASTNode *params, ASTNode *body)`
  - Registers or overwrites a function entry with return type, params, and AST body.
- `func_lookup(const char *name)`
  - Searches function table and returns function entry pointer.
- `sym_push_frame(void)`
  - Pushes current symbol count to frame stack (new local scope).
- `sym_pop_frame(void)`
  - Restores previous symbol count, discarding locals created in current frame.
- `sym_find(const char *name)` (static)
  - Finds symbol index in full table.
- `sym_find_in_frame(const char *name)` (static)
  - Finds symbol only in current frame region.
- `sym_set(const char *name, double value, int decl_type)`
  - Declares/updates scalar symbol.
- `sym_get(const char *name)`
  - Reads scalar value, checking current frame then global scope.
- `sym_get_type(const char *name)`
  - Returns declared scalar type.
- `sym_declare_array(const char *name, int size, int decl_type)`
  - Declares 1-D array symbol and initializes values.
- `sym_set_array(const char *name, int idx, double value)`
  - Writes one element in 1-D array with bounds checks.
- `sym_get_array(const char *name, int idx)`
  - Reads one element in 1-D array with bounds checks.
- `sym_declare_array2d(const char *name, int r, int c, int decl_type)`
  - Declares 2-D array symbol and initializes cells.
- `sym_set_array2d(const char *name, int r, int c, double value)`
  - Writes one element in 2-D array with bounds checks.
- `sym_get_array2d(const char *name, int r, int c)`
  - Reads one element in 2-D array with bounds checks.

## `semantic.c`
Semantic validation pass before interpretation.

- `sem_error(int line, const char *fmt, ...)` (static)
  - Emits semantic error message and increments `sem_error_count`.
- `sem_warning(int line, const char *fmt, ...)` (static)
  - Emits semantic warning message and increments `sem_warning_count`.
- `scope_push(void)` (static)
  - Opens semantic scope by saving symbol-table cursor.
- `scope_pop(void)` (static)
  - Closes semantic scope and drops symbols from that scope.
- `sym_find_visible(const char *name)` (static)
  - Looks up symbol in visible scopes (inner to outer).
- `sym_find_current_scope(const char *name)` (static)
  - Looks up symbol only in current scope.
- `sym_declare(...)` (static)
  - Declares semantic symbol with redeclaration checks.
- `func_find(const char *name)` (static)
  - Finds function signature in semantic function table.
- `func_register(ASTNode *n)` (static)
  - Registers function signature from AST `NODE_FUNC_DEF`.
- `check_expr_nonvoid(ASTNode *n, int line, const char *ctx)` (static)
  - Wraps expression checking and reports invalid void-in-expression usage.
- `check_expr(ASTNode *n)` (static)
  - Infers/checks expression type and validates undeclared uses, argument counts, division-by-zero literals, etc.
- `check_stmt(ASTNode *n)` (static)
  - Semantic checks for statements (decl/assign/control-flow/returns/loops/switch/functions).
- `check_stmts(ASTNode *n)` (static)
  - Iterates linked statement chains and calls `check_stmt`.
- `collect_functions(ASTNode *n)` (static)
  - First-pass AST traversal to collect function signatures for forward-call support.
- `sem_analyse(ASTNode *root)`
  - Public semantic pass entry.
  - Resets state, seeds function signatures, validates function bodies and main body, prints summary.

## `lexer.l`
Flex lexer rules file.

- `yywrap()`
  - Signals scanner termination by returning `1` at end-of-input.

Additional behavior in rules section:
- Maps custom Luminix keywords (`StartExam`, `Repeat`, `WhileStudy`, `Show`, `Take`, etc.) to parser tokens.
- Tokenizes literals, identifiers, operators, punctuation.
- Skips whitespace/comments.

## `parser.y`
Main grammar and driver entry points.

- `yyerror(const char *s)`
  - Reports syntax error with source line number.
- `main(int argc, char *argv[])`
  - Opens input file.
  - Calls `yyparse()`.
  - Drives parse -> semantic pass -> interpretation via grammar actions.

Grammar actions in this file are responsible for:
- creating AST nodes for expressions/statements
- registering function definitions via `func_define`
- assembling control-flow structures and loop forms
- building program root and invoking `sem_analyse` + `interpret`

## `parser_19.y`
Legacy/alternate grammar variant.

- `yyerror(const char *s)`
  - Syntax error printer for this variant.
- `main(int argc, char *argv[])`
  - Parser driver entry for this grammar variant.

## `lex.yy.c` (generated)
Generated scanner implementation from Flex. Core scanner/runtime functions include:

- `yylex`
  - Main tokenizer used by parser.
- `yyrestart`, `yy_switch_to_buffer`, `yy_create_buffer`, `yy_delete_buffer`, `yy_flush_buffer`
  - Input buffer lifecycle and switching.
- `yypush_buffer_state`, `yypop_buffer_state`, `yyensure_buffer_stack`, `yy_load_buffer_state`, `yy_init_buffer`
  - Buffer stack and scanner state management.
- `yy_scan_buffer`, `yy_scan_string`, `yy_scan_bytes`
  - Scan from memory buffers/strings.
- `yy_get_next_buffer`, `yyinput`
  - Low-level scanner input flow.
- `yyget_lineno`, `yyset_lineno`, `yyget_debug`, `yyset_debug`, `yyset_in`, `yyset_out`
  - Scanner getters/setters.
- `yy_init_globals`, `yylex_destroy`
  - Scanner lifecycle/global teardown.
- `yy_flex_strncpy`, `yy_flex_strlen`, `yyfree`
  - Internal generated helper utilities.
- `yywrap`
  - End-of-input hook (user-defined in lexer source).

## `parser.tab.c` (generated)
Generated parser implementation from Bison. Key parser functions include:

- `yyparse`
  - Core shift-reduce parser.
- `yy_symbol_print`, `yy_reduce_print`
  - Debug printing helpers for parse symbols/reductions.
- `yydestruct`
  - Token/value cleanup during error recovery and stack unwinding.
- `yyerror`
  - User-provided syntax error reporter.
- `main`
  - User-provided parser driver in grammar epilogue.

---

## 4. Notes On Non-Function Files
These files contain data/config/artifacts and therefore have no C functions:
- `.gitignore`
- `Makefile`
- `parser.tab.h`
- `parser.output`
- `luminix.exe`
- `Luminix v2.pdf`
- all `.txt` files in this folder and in `input/`

---

## 5. Typical Execution Flow
1. `lexer.l` tokenizes source input.
2. `parser.y` builds AST and function table entries.
3. `semantic.c` validates AST (`sem_analyse`).
4. `interpreter.c` executes AST (`interpret`).
5. `symtab.c` stores runtime symbols/functions/scopes.
