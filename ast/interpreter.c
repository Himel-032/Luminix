

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ast.h"
#include "symtab.h"
#include "interpreter.h"


static int g_break    = 0;   // set when BREAK is hit   
static int g_continue = 0;
static int g_return   = 0;   // set when RETURN is hit
static double g_retval = 0;  // value from RETURN       


#define SIGNAL_ACTIVE() (g_break || g_continue || g_return)


double eval_expr(ASTNode *n) {
    if (!n) return 0;

    switch (n->type) {

        
        case NODE_INT_LIT:    return (double)n->ival;
        case NODE_FLOAT_LIT:  return n->dval;
        case NODE_CHAR_LIT:   return (double)n->cval;
        case NODE_BOOL_LIT:   return (double)n->ival;
        case NODE_STRING_LIT:
            fprintf(stderr, "Runtime error: cannot use string literal in numeric expression\n");
            return 0;

       
        case NODE_IDENT:
            return sym_get(n->sval);

       
        case NODE_ADD:    return eval_expr(n->left) + eval_expr(n->right);
        case NODE_SUB:    return eval_expr(n->left) - eval_expr(n->right);
        case NODE_MUL:    return eval_expr(n->left) * eval_expr(n->right);
        case NODE_DIV: {
            double rhs = eval_expr(n->right);
            if (rhs == 0) { fprintf(stderr, "Runtime error: division by zero\n"); return 0; }
            return eval_expr(n->left) / rhs;
        }
        case NODE_MOD: {
            int rhs = (int)eval_expr(n->right);
            if (rhs == 0) { fprintf(stderr, "Runtime error: modulo by zero\n"); return 0; }
            return (double)((int)eval_expr(n->left) % rhs);
        }
        case NODE_NEGATE:
            return -eval_expr(n->left);

       
        case NODE_EQ:  return eval_expr(n->left) == eval_expr(n->right);
        case NODE_NEQ: return eval_expr(n->left) != eval_expr(n->right);
        case NODE_GT:  return eval_expr(n->left) >  eval_expr(n->right);
        case NODE_LT:  return eval_expr(n->left) <  eval_expr(n->right);
        case NODE_GE:  return eval_expr(n->left) >= eval_expr(n->right);
        case NODE_LE:  return eval_expr(n->left) <= eval_expr(n->right);

       
        case NODE_AND: return (eval_expr(n->left) != 0) && (eval_expr(n->right) != 0);
        case NODE_OR:  return (eval_expr(n->left) != 0) || (eval_expr(n->right) != 0);
        case NODE_NOT: return eval_expr(n->left) == 0 ? 1 : 0;

        
        case NODE_BIT_AND: return (double)((int)eval_expr(n->left) & (int)eval_expr(n->right));
        case NODE_BIT_OR:  return (double)((int)eval_expr(n->left) | (int)eval_expr(n->right));
        case NODE_BIT_XOR: return (double)((int)eval_expr(n->left) ^ (int)eval_expr(n->right));
        case NODE_BIT_NOT: return (double)(~(int)eval_expr(n->left));
        case NODE_SHL:     return (double)((int)eval_expr(n->left) << (int)eval_expr(n->right));
        case NODE_SHR:     return (double)((int)eval_expr(n->left) >> (int)eval_expr(n->right));

       
        case NODE_POW:   return pow(eval_expr(n->left), eval_expr(n->right));
        case NODE_SQRT:  return sqrt(eval_expr(n->left));
        case NODE_ABS:   return fabs(eval_expr(n->left));
        case NODE_FLOOR: return floor(eval_expr(n->left));
        case NODE_CEIL:  return ceil(eval_expr(n->left));

       
        case NODE_ARRAY_ACCESS: {
            int idx = (int)eval_expr(n->left);
            return sym_get_array(n->sval, idx);
        }
        case NODE_ARRAY_ACCESS_2D: {
            int r = (int)eval_expr(n->left);
            int c = (int)eval_expr(n->right);
            return sym_get_array2d(n->sval, r, c);
        }

       
        case NODE_FUNC_CALL:
            return call_function(n->sval, n->left);

        default:
            fprintf(stderr, "Runtime error: unknown expression node type %d\n", n->type);
            return 0;
    }
}


static void exec_if(ASTNode *n, int already_matched) {
    if (!n) return;

    if (n->type == NODE_IF || n->type == NODE_ELSEIF) {
        if (!already_matched) {
            double cond = eval_expr(n->left);
            if (cond) {
                exec_stmt(n->right);
                already_matched = 1;
            }
        }
        exec_if(n->extra, already_matched);
    } else if (n->type == NODE_ELSE) {
        if (!already_matched) {
            exec_stmt(n->left);
        }
    }
}



// static void exec_switch(ASTNode *n) {
//     double val  = eval_expr(n->left);
//     int matched = 0;

//     ASTNode *clause = n->right;
//     while (clause) {
//         if (g_break) { g_break = 0; break; }

//         if (clause->type == NODE_CASE) {
//             double case_val = eval_expr(clause->left);
//             if (!matched && fabs(val - case_val) < 1e-9) matched = 1;
//             if (matched) {
//                 exec_stmt(clause->right);
//                 if (g_break) { g_break = 0; break; }
//             }

//         } else if (clause->type == NODE_CASE_RANGE) {
//             int start = (int)eval_expr(clause->left);
//             int end   = (int)eval_expr(clause->right);
//             int ival  = (int)val;
//             if (!matched && ival >= start && ival <= end) matched = 1;
//             if (matched) {
//                 exec_stmt(clause->extra);
//                 if (g_break) { g_break = 0; break; }
//             }

//         } else if (clause->type == NODE_DEFAULT) {
//             if (!matched) matched = 1;
//             if (matched) {
//                 exec_stmt(clause->left);
//                 if (g_break) { g_break = 0; break; }
//             }
//         }

//         clause = clause->next;
//     }
//     g_break = 0; /* consume any leftover break */
// }
static void exec_switch(ASTNode *n) {
    double val  = eval_expr(n->left);
    int matched = 0;

    ASTNode *clause = n->right;
    while (clause) {
        
        if (g_break)    { g_break = 0; break; }
        if (g_continue) break;
        if (g_return)   break;

        if (clause->type == NODE_CASE) {
            double case_val = eval_expr(clause->left);
            if (!matched && fabs(val - case_val) < 1e-9) matched = 1;
            if (matched) exec_stmt(clause->right);

        } else if (clause->type == NODE_CASE_RANGE) {
            int start = (int)eval_expr(clause->left);
            int end   = (int)eval_expr(clause->right);
            int ival  = (int)val;
            if (!matched && ival >= start && ival <= end) matched = 1;
            if (matched) exec_stmt(clause->extra);

        } else if (clause->type == NODE_DEFAULT) {
            if (!matched) matched = 1;
            if (matched)  exec_stmt(clause->left);
        }

        clause = clause->next;
    }
    g_break = 0; 
}


void exec_stmt(ASTNode *n) {
    if (!n || g_return) return;

    switch (n->type) {

       
        case NODE_STMT_LIST:
            exec_stmt(n->left);
            if (!SIGNAL_ACTIVE())
                exec_stmt(n->next);
            break;

       
        case NODE_DECL:
            
            sym_set(n->sval,
                    n->left ? eval_expr(n->left) : 0,
                    n->decl_type);
            break;

        case NODE_DECL_ARRAY:
           
            sym_declare_array(n->sval, n->cols, n->decl_type);
            break;

        case NODE_DECL_ARRAY_2D:
            sym_declare_array2d(n->sval, n->rows, n->cols, n->decl_type);
            break;

       
        case NODE_ASSIGN:
            sym_set(n->sval, eval_expr(n->left), n->decl_type);
            break;

        case NODE_ARRAY_ASSIGN: {
            int idx = (int)eval_expr(n->left);
            sym_set_array(n->sval, idx, eval_expr(n->right));
            break;
        }

        case NODE_ARRAY_ASSIGN_2D: {
            int r = (int)eval_expr(n->left);
            int c = (int)eval_expr(n->right);
            sym_set_array2d(n->sval, r, c, eval_expr(n->extra));
            break;
        }

       
        case NODE_PRINT: {
           
            char *end_str = "\n";
            int should_free_end = 0;
            
            if (n->extra && n->extra->type == NODE_STRING_LIT) {
                /* Custom end string provided */
                end_str = n->extra->sval;
               
                if (end_str[0] == '"') {
                    end_str = strdup(end_str + 1);
                    int len = (int)strlen(end_str);
                    if (len > 0 && end_str[len-1] == '"') {
                        end_str[len-1] = '\0';
                    }
                    should_free_end = 1;
                } else {
                    end_str = strdup(end_str);
                    should_free_end = 1;
                }
                
               
                char *processed = (char*)malloc(strlen(end_str) + 1);
                int j = 0;
                for (int i = 0; end_str[i]; i++) {
                    if (end_str[i] == '\\' && end_str[i+1]) {
                        switch (end_str[i+1]) {
                            case 'n': processed[j++] = '\n'; i++; break;
                            case 't': processed[j++] = '\t'; i++; break;
                            case 'r': processed[j++] = '\r'; i++; break;
                            case '\\': processed[j++] = '\\'; i++; break;
                            case '"': processed[j++] = '"'; i++; break;
                            default: processed[j++] = end_str[i]; break;
                        }
                    } else {
                        processed[j++] = end_str[i];
                    }
                }
                processed[j] = '\0';
                
                if (should_free_end) free(end_str);
                end_str = processed;
                should_free_end = 1;
            }
            
           
            if (n->sval) {
                /* print a string literal or identifier */
                if (n->left) {
                    
                    int t = sym_get_type(n->sval);
                    double v = sym_get(n->sval);
                    if (t == 1) printf("%c", (int)v);
                    else        printf("%g", v);
                } else {
                   
                    char *s = n->sval;
                    
                    if (s[0] == '"') s++;
                    int len = (int)strlen(s);
                    if (len > 0 && s[len-1] == '"') s[len-1] = '\0';
                    printf("%s", s);
                }
            } else if (n->left) {
                // printf("%g", eval_expr(n->left));
                /* Check if expression is array access to determine type */
                int expr_type = 0; /* default numeric */
                if (n->left->type == NODE_ARRAY_ACCESS || n->left->type == NODE_ARRAY_ACCESS_2D) {
                    expr_type = sym_get_type(n->left->sval);
                }
                
                double v = eval_expr(n->left);
                if (expr_type == 1) printf("%c", (int)v);
                else                printf("%g", v);
            }
           
            printf("%s", end_str);
            
            if (should_free_end) free(end_str);
            break;
        }


       
        case NODE_SCAN: {
            int t = sym_get_type(n->sval);
            if (t == 1) {
                char c; scanf(" %c", &c);
                sym_set(n->sval, (double)c, t);
            } else {
                double v; scanf("%lf", &v);
                sym_set(n->sval, v, t);
            }
            break;
        }

        case NODE_SCAN_ARRAY: {
            int idx = (int)eval_expr(n->left);
            double v; scanf("%lf", &v);
            sym_set_array(n->sval, idx, v);
            break;
        }

       
        case NODE_IF:
            exec_if(n, 0);
            break;

        case NODE_SWITCH:
            exec_switch(n);
            break;

        case NODE_BREAK:
            g_break = 1;
            break;
        case NODE_CONTINUE:
            g_continue = 1;
            break;


       
        case NODE_WHILE: {
            
            while (eval_expr(n->left)) {
                exec_stmt(n->right);
                if (g_continue) { g_continue = 0; continue; }
                if (g_break)    { g_break    = 0; break;    }
                if (g_return)   break;
            }
            break;
        }

       
        case NODE_DO_WHILE: {
           
            do {
                exec_stmt(n->left);
                if (g_continue) { g_continue = 0; /* fall to condition */ }
                if (g_break)    { g_break    = 0; break; }
                if (g_return)   break;
            } while (eval_expr(n->right));
            break;
        }

        
        case NODE_FOR: {
           
            if (n->left)                            
                exec_stmt(n->left);
            while (eval_expr(n->extra->left)) {    
                exec_stmt(n->right);                
                if (g_continue) { g_continue = 0; }/* fall to update */
                if (g_break)    { g_break    = 0; break; }
                if (g_return)   break;
                if (n->extra->right)                
                    exec_stmt(n->extra->right);
            }
            break;
        }
        case NODE_FOR_RANGE: {
            /* Repeat x in (start..end)  */
            double start = eval_expr(n->left);
            double end   = eval_expr(n->extra);
            double step  = (start <= end) ? 1.0 : -1.0;
            if(start == end) break; 
            sym_set(n->sval, start, 0);
            while ((step > 0) ? (sym_get(n->sval) < end)
                               : (sym_get(n->sval) > end)) {
                exec_stmt(n->right);
                if (g_continue) { g_continue = 0; }
                if (g_break)    { g_break    = 0; break; }
                if (g_return)   break;
                sym_set(n->sval, sym_get(n->sval) + step, 0);
            }
            break;
        }

        case NODE_FOR_RANGE_STEP: {
            
            double start = eval_expr(n->left);
            double end   = eval_expr(n->extra->left);
            double step  = eval_expr(n->extra->right);
            if (step == 0.0) {
                fprintf(stderr, "Runtime error: range step cannot be zero\n");
                break;
            }
            sym_set(n->sval, start, 0);
            while ((step > 0) ? (sym_get(n->sval) < end)
                               : (sym_get(n->sval) > end)) {
                exec_stmt(n->right);
                if (g_continue) { g_continue = 0; }
                if (g_break)    { g_break    = 0; break; }
                if (g_return)   break;
                sym_set(n->sval, sym_get(n->sval) + step, 0);
            }
            break;
        }

        case NODE_INCREMENT: {
            sym_set(n->sval, sym_get(n->sval) + 1.0, 0);
            break;
        }

        case NODE_DECREMENT: {
            sym_set(n->sval, sym_get(n->sval) - 1.0, 0);
            break;
        }
       
        case NODE_RETURN:
            g_retval = eval_expr(n->left);
            //printf("Program returned: %g\n", g_retval);
            g_return = 1;
            break;

       
        case NODE_FUNC_CALL:
            call_function(n->sval, n->left);
            break;
       
        case NODE_RETURN_VOID:
            g_retval = 0;
            g_return = 1;
            break;

        default:
            fprintf(stderr, "Runtime error: unknown statement node type %d\n", n->type);
            break;
    }
    
    
    if (!g_break && !g_continue && !g_return && n->next) {
        exec_stmt(n->next);
    }
}


double call_function(const char *name, ASTNode *arg_list) {
    FuncEntry *f = func_lookup(name);
    if (!f) {
        fprintf(stderr, "Runtime error: undefined function '%s'\n", name);
        return 0;
    }

   
    double argv[PARAM_MAX];
    int    argc = 0;
    ASTNode *a  = arg_list;
    while (a && argc < PARAM_MAX) {
        argv[argc++] = eval_expr(a->left);
        a = a->next;
    }
    if (argc != f->param_count) {
        fprintf(stderr,
            "Runtime error: function '%s' expects %d args, got %d\n",
            name, f->param_count, argc);
        return 0;
    }

    
    sym_push_frame();

    
    for (int i = 0; i < f->param_count; i++)
        sym_set(f->param_names[i], argv[i], f->param_types[i]);

    
    int    saved_break    = g_break;
    int    saved_continue = g_continue;
    int    saved_return   = g_return;
    double saved_retval   = g_retval;

    g_break    = 0;
    g_continue = 0;
    g_return   = 0;
    g_retval   = 0;

    
    exec_stmt(f->body);

    double result = g_retval;

    
    g_break    = saved_break;
    g_continue = saved_continue;
    g_return   = saved_return;
    g_retval   = saved_retval;

    
    sym_pop_frame();

    return result;
}


void interpret(ASTNode *root) {
    if (!root) return;
    
    exec_stmt(root->left);
}
