/* =========================================================
 *  ast.c  –  AST node constructors, printer, and cleanup
 * ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* ---- generic allocator ---- */
ASTNode *make_node(NodeType type) {
    ASTNode *n = calloc(1, sizeof(ASTNode));
    if (!n) { fprintf(stderr, "Out of memory\n"); exit(1); }
    n->type = type;
    return n;
}

/* ---- literal constructors ---- */
ASTNode *make_int_lit(int v) {
    ASTNode *n = make_node(NODE_INT_LIT);
    n->ival = v;
    return n;
}

ASTNode *make_float_lit(double v) {
    ASTNode *n = make_node(NODE_FLOAT_LIT);
    n->dval = v;
    return n;
}

ASTNode *make_char_lit(char v) {
    ASTNode *n = make_node(NODE_CHAR_LIT);
    n->cval = v;
    return n;
}

ASTNode *make_string_lit(const char *s) {
    ASTNode *n = make_node(NODE_STRING_LIT);
    n->sval = strdup(s);
    return n;
}

ASTNode *make_bool_lit(int v) {
    ASTNode *n = make_node(NODE_BOOL_LIT);
    n->ival = v;
    return n;
}

/* ---- identifier ---- */
ASTNode *make_ident(const char *name) {
    ASTNode *n = make_node(NODE_IDENT);
    n->sval = strdup(name);
    return n;
}

/* ---- binary operator ---- */
ASTNode *make_binop(NodeType op, ASTNode *l, ASTNode *r) {
    ASTNode *n = make_node(op);
    n->left  = l;
    n->right = r;
    return n;
}

/* ---- unary operator ---- */
ASTNode *make_unary(NodeType op, ASTNode *operand) {
    ASTNode *n = make_node(op);
    n->left = operand;
    return n;
}

/* ---- built-in function with 1 argument ---- */
ASTNode *make_func1(NodeType fn, ASTNode *arg) {
    ASTNode *n = make_node(fn);
    n->left = arg;
    return n;
}

/* ---- built-in function with 2 arguments ---- */
ASTNode *make_func2(NodeType fn, ASTNode *a, ASTNode *b) {
    ASTNode *n = make_node(fn);
    n->left  = a;
    n->right = b;
    return n;
}

/* ---- array access ---- */
ASTNode *make_array_access(const char *name, ASTNode *idx) {
    ASTNode *n = make_node(NODE_ARRAY_ACCESS);
    n->sval = strdup(name);
    n->left = idx;
    return n;
}

ASTNode *make_array_access_2d(const char *name, ASTNode *row, ASTNode *col) {
    ASTNode *n = make_node(NODE_ARRAY_ACCESS_2D);
    n->sval  = strdup(name);
    n->left  = row;
    n->right = col;
    return n;
}

/* ---- statement list (prepend style — reversed in grammar) ---- */
ASTNode *make_stmt_list(ASTNode *stmt, ASTNode *rest) {
    ASTNode *n = make_node(NODE_STMT_LIST);
    n->left = stmt;  /* current statement  */
    n->next = rest;  /* next in list       */
    return n;
}

/* ================================================================
 *  free_ast  –  recursive tree destructor
 * ================================================================ */
void free_ast(ASTNode *n) {
    if (!n) return;
    free_ast(n->left);
    free_ast(n->right);
    free_ast(n->extra);
    free_ast(n->next);

    /* free heap strings */
    switch (n->type) {
        case NODE_IDENT:
        case NODE_STRING_LIT:
        case NODE_DECL:
        case NODE_DECL_ARRAY:
        case NODE_DECL_ARRAY_2D:
        case NODE_ASSIGN:
        case NODE_ARRAY_ASSIGN:
        case NODE_ARRAY_ASSIGN_2D:
        case NODE_ARRAY_ACCESS:
        case NODE_ARRAY_ACCESS_2D:
        case NODE_PRINT:
        case NODE_SCAN:
        case NODE_SCAN_ARRAY:
            if (n->sval) free(n->sval);
            break;
        default:
            break;
    }
    free(n);
}

/* ================================================================
 *  print_ast  –  human-readable tree dump (for debugging)
 * ================================================================ */
static const char *node_name(NodeType t) {
    switch (t) {
        case NODE_INT_LIT:       return "INT_LIT";
        case NODE_FLOAT_LIT:     return "FLOAT_LIT";
        case NODE_CHAR_LIT:      return "CHAR_LIT";
        case NODE_STRING_LIT:    return "STRING_LIT";
        case NODE_BOOL_LIT:      return "BOOL_LIT";
        case NODE_IDENT:         return "IDENT";
        case NODE_ADD:           return "ADD";
        case NODE_SUB:           return "SUB";
        case NODE_MUL:           return "MUL";
        case NODE_DIV:           return "DIV";
        case NODE_MOD:           return "MOD";
        case NODE_NEGATE:        return "NEGATE";
        case NODE_EQ:            return "EQ";
        case NODE_NEQ:           return "NEQ";
        case NODE_GT:            return "GT";
        case NODE_LT:            return "LT";
        case NODE_GE:            return "GE";
        case NODE_LE:            return "LE";
        case NODE_POW:           return "POW";
        case NODE_SQRT:          return "SQRT";
        case NODE_ABS:           return "ABS";
        case NODE_FLOOR:         return "FLOOR";
        case NODE_CEIL:          return "CEIL";
        case NODE_ARRAY_ACCESS:  return "ARRAY_ACCESS";
        case NODE_ARRAY_ACCESS_2D: return "ARRAY_ACCESS_2D";
        case NODE_STMT_LIST:     return "STMT_LIST";
        case NODE_DECL:          return "DECL";
        case NODE_DECL_ARRAY:    return "DECL_ARRAY";
        case NODE_DECL_ARRAY_2D: return "DECL_ARRAY_2D";
        case NODE_ASSIGN:        return "ASSIGN";
        case NODE_ARRAY_ASSIGN:  return "ARRAY_ASSIGN";
        case NODE_ARRAY_ASSIGN_2D: return "ARRAY_ASSIGN_2D";
        case NODE_PRINT:         return "PRINT";
        case NODE_SCAN:          return "SCAN";
        case NODE_SCAN_ARRAY:    return "SCAN_ARRAY";
        case NODE_IF:            return "IF";
        case NODE_ELSEIF:        return "ELSEIF";
        case NODE_ELSE:          return "ELSE";
        case NODE_SWITCH:        return "SWITCH";
        case NODE_CASE:          return "CASE";
        case NODE_CASE_RANGE:    return "CASE_RANGE";
        case NODE_DEFAULT:       return "DEFAULT";
        case NODE_BREAK:         return "BREAK";
        case NODE_CONTINUE:      return "CONTINUE";
        case NODE_WHILE:         return "WHILE";
        case NODE_DO_WHILE:      return "DO_WHILE";
        case NODE_FOR:           return "FOR";
        case NODE_PROGRAM:       return "PROGRAM";
        case NODE_RETURN:        return "RETURN";
        default:                 return "UNKNOWN";
    }
}

void print_ast(ASTNode *n, int indent) {
    if (!n) return;
    for (int i = 0; i < indent; i++) printf("  ");

    printf("[%s]", node_name(n->type));

    switch (n->type) {
        case NODE_INT_LIT:    printf(" %d", n->ival);          break;
        case NODE_FLOAT_LIT:  printf(" %g", n->dval);          break;
        case NODE_CHAR_LIT:   printf(" '%c'", n->cval);        break;
        case NODE_BOOL_LIT:   printf(" %s", n->ival ? "true" : "false"); break;
        case NODE_STRING_LIT: printf(" \"%s\"", n->sval);      break;
        case NODE_IDENT:      printf(" %s", n->sval);          break;
        case NODE_DECL:       printf(" %s (type=%d)", n->sval, n->decl_type); break;
        case NODE_DECL_ARRAY: printf(" %s[%d] (type=%d)", n->sval, n->cols, n->decl_type); break;
        case NODE_DECL_ARRAY_2D: printf(" %s[%d][%d]", n->sval, n->rows, n->cols); break;
        case NODE_ASSIGN:
        case NODE_ARRAY_ASSIGN:
        case NODE_ARRAY_ASSIGN_2D:
        case NODE_ARRAY_ACCESS:
        case NODE_ARRAY_ACCESS_2D:
        case NODE_PRINT:
        case NODE_SCAN:
        case NODE_SCAN_ARRAY:
            if (n->sval) printf(" %s", n->sval);
            break;
        default: break;
    }
    printf("\n");

    print_ast(n->left,  indent + 1);
    print_ast(n->right, indent + 1);
    print_ast(n->extra, indent + 1);

    /* print sibling statements */
    if (n->next) {
        print_ast(n->next, indent);
    }
}
