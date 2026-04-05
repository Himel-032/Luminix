

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylineno;  

ASTNode *make_node(NodeType type) {
    ASTNode *n = calloc(1, sizeof(ASTNode));
    if (!n) { fprintf(stderr, "Out of memory\n"); exit(1); }
    n->type = type;
    n->line = yylineno;
    return n;
}


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

// identifier 
ASTNode *make_ident(const char *name) {
    ASTNode *n = make_node(NODE_IDENT);
    n->sval = strdup(name);
    return n;
}

// binary operator 
ASTNode *make_binop(NodeType op, ASTNode *l, ASTNode *r) {
    ASTNode *n = make_node(op);
    n->left  = l;
    n->right = r;
    return n;
}

//  unary operator 
ASTNode *make_unary(NodeType op, ASTNode *operand) {
    ASTNode *n = make_node(op);
    n->left = operand;
    return n;
}

//  built-in function with 1 argument 
ASTNode *make_func1(NodeType fn, ASTNode *arg) {
    ASTNode *n = make_node(fn);
    n->left = arg;
    return n;
}

//  built-in function with 2 arguments 
ASTNode *make_func2(NodeType fn, ASTNode *a, ASTNode *b) {
    ASTNode *n = make_node(fn);
    n->left  = a;
    n->right = b;
    return n;
}

/*  array access  */
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

// statement list
ASTNode *make_stmt_list(ASTNode *stmt, ASTNode *rest) {
    ASTNode *n = make_node(NODE_STMT_LIST);
    n->left = stmt;  /* current statement  */
    n->next = rest;  /* next in list       */
    return n;
}

/*  single parameter */
ASTNode *make_param(const char *name, int type) {
    ASTNode *n = make_node(NODE_PARAM);
    n->sval      = strdup(name);
    n->decl_type = type;
    return n;
}

// function definition 

ASTNode *make_func_def(const char *name, int ret_type,
                       ASTNode *params, ASTNode *body) {
    ASTNode *n  = make_node(NODE_FUNC_DEF);
    n->sval     = strdup(name);
    n->ret_type = ret_type;
    n->left     = params;
    n->right    = body;
    return n;
}

// function call 

ASTNode *make_func_call(const char *name, ASTNode *args) {
    ASTNode *n = make_node(NODE_FUNC_CALL);
    n->sval    = strdup(name);
    n->left    = args;
    return n;
}

// argument list node 

ASTNode *make_arg_list(ASTNode *expr, ASTNode *next) {
    ASTNode *n = make_node(NODE_ARG_LIST);
    n->left    = expr;
    n->next    = next;
    return n;
}


ASTNode *make_return_void(void) {
    return make_node(NODE_RETURN_VOID);
}


void free_ast(ASTNode *n) {
    if (!n) return;
    free_ast(n->left);
    free_ast(n->right);
    free_ast(n->extra);
    free_ast(n->next);

    /* free heap  */
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
        case NODE_FUNC_DEF:
        case NODE_FUNC_CALL:
        case NODE_PARAM:
         if (n->sval) free(n->sval);
            break;
        case NODE_FOR_RANGE:
        case NODE_FOR_RANGE_STEP:
            if (n->sval) free(n->sval);
            break;

        case NODE_INCREMENT:
        case NODE_DECREMENT:
            if (n->sval) free(n->sval);
            break;
        default:
            break;
    }
    free(n);
}




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
        case NODE_AND:           return "AND";
        case NODE_OR:            return "OR";
        case NODE_NOT:           return "NOT";
        
        case NODE_BIT_AND:       return "BIT_AND";
        case NODE_BIT_OR:        return "BIT_OR";
        case NODE_BIT_XOR:       return "BIT_XOR";
        case NODE_BIT_NOT:       return "BIT_NOT";
        case NODE_SHL:           return "SHL";
        case NODE_SHR:           return "SHR";
        
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
        case NODE_FOR_RANGE:       return "FOR_RANGE";
        case NODE_FOR_RANGE_STEP:  return "FOR_RANGE_STEP";
        case NODE_INCREMENT:       return "INCREMENT";
        case NODE_DECREMENT:       return "DECREMENT";
        case NODE_PROGRAM:       return "PROGRAM";
        case NODE_RETURN:        return "RETURN";

        case NODE_FUNC_DEF:    return "FUNC_DEF";
        case NODE_FUNC_CALL:   return "FUNC_CALL";
        case NODE_PARAM:       return "PARAM";
        case NODE_PARAM_LIST:  return "PARAM_LIST";
        case NODE_ARG_LIST:    return "ARG_LIST";
        case NODE_RETURN_VOID: return "RETURN_VOID";

        default:                 return "UNKNOWN";
    }
}

void print_ast_file(ASTNode *n, int indent, FILE *out) {
    if (!n) return;
    for (int i = 0; i < indent; i++) fprintf(out, "  ");

    fprintf(out, "[%s]", node_name(n->type));

    switch (n->type) {
        case NODE_INT_LIT:    fprintf(out, " %d", n->ival);          break;
        case NODE_FLOAT_LIT:  fprintf(out, " %g", n->dval);          break;
        case NODE_CHAR_LIT:   fprintf(out, " '%c'", n->cval);        break;
        case NODE_BOOL_LIT:   fprintf(out, " %s", n->ival ? "true" : "false"); break;
        case NODE_STRING_LIT: fprintf(out, " \"%s\"", n->sval);      break;
        case NODE_IDENT:      fprintf(out, " %s", n->sval);          break;
        case NODE_DECL:       fprintf(out, " %s (type=%d)", n->sval, n->decl_type); break;
        case NODE_DECL_ARRAY: fprintf(out, " %s[%d] (type=%d)", n->sval, n->cols, n->decl_type); break;
        case NODE_DECL_ARRAY_2D: fprintf(out, " %s[%d][%d]", n->sval, n->rows, n->cols); break;
        case NODE_ASSIGN:
        case NODE_ARRAY_ASSIGN:
        case NODE_ARRAY_ASSIGN_2D:
        case NODE_ARRAY_ACCESS:
        case NODE_ARRAY_ACCESS_2D:
        case NODE_PRINT:
        case NODE_SCAN:
        case NODE_SCAN_ARRAY:
            if (n->sval) fprintf(out, " %s", n->sval);
            break;
        case NODE_FUNC_DEF:
        case NODE_FUNC_CALL:
        case NODE_PARAM:
            if (n->sval) fprintf(out, " %s", n->sval);
            break;
        case NODE_FOR_RANGE:
        case NODE_FOR_RANGE_STEP:
        case NODE_INCREMENT:
        case NODE_DECREMENT:
            if (n->sval) fprintf(out, " %s", n->sval);
            break;
        default: break;
    }
    fprintf(out, "\n");

    print_ast_file(n->left,  indent + 1, out);
    print_ast_file(n->right, indent + 1, out);
    print_ast_file(n->extra, indent + 1, out);

    /* print sibling statements */
    if (n->next) {
        print_ast_file(n->next, indent, out);
    }
}

void print_ast(ASTNode *n, int indent) {
    print_ast_file(n, indent, stdout);
}
