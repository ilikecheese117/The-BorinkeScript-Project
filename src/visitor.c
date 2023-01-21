#include "include/visitor.h"
#include "include/custom.h"
#include <string.h>
#include <stdio.h>

static ast_t* builtin_func_print(ast_t** func_call_args, int args_size) {
    char* output = calloc(1, sizeof(char));
    for(int i = 0; i <= args_size; i++) {
        ast_t* visited_ast = visit(func_call_args[i]);
        switch(visited_ast->type) {
            case STRING:
                output = realloc(
                    output, 
                    (strlen(output)+strlen(visited_ast->string_val)+2)*sizeof(char)
                    );
                output = strcat(output, visited_ast->string_val);
                break;
            default:
                printf("%p\n", visited_ast->type);
                exit(1);
        }
    }
    printf("%s\n", output);
    return init_ast(NONE);
}

ast_t* visit(ast_t* node) {
    switch(node->type) {
        case VAR_DEC: 
            return visit_var_dec(node); 
        case FUNC_CALL:
            return visit_func_call(node);
        case FUNC_DEC:
            return visit_func_dec(node);
        case VAR:
            return visit_var(node);
        case STRING:
            return visit_string(node);
        case COMPOUND:
            return visit_compound(node);
        case NONE:
            return node;
        default:
            printf("uncaught statement of type %d\n", node->type); 
            exit(1);
    }
}

ast_t* visit_compound(ast_t* node) {
    for(int i = 0; i < node->compound_size; i++) {
        visit(node->compound_val[i]);
    }
    return init_ast(NONE);
}

ast_t* visit_func_call(ast_t* node) {
    if(strcmp(node->func_call_name, "dimelo") == 0) {
        return builtin_func_print(node->func_call_args, node->func_call_args_size);
    }
    ast_t* func_dec = get_custom_func(node->custom, node->func_call_name);
    if(func_dec == (void*)0) {
        printf("undefined function/method \"%s\"", node->func_call_name);
        exit(1);
    }
    for(int i = 0; i < func_dec->func_dec_args_size; i++) {
        ast_t* var = func_dec->func_dec_args[i];
        ast_t* var_val = node->func_call_args[i];
        //create variable declaration 
        ast_t* var_dec = init_ast(VAR_DEC);
        //copy variable name into variable declaration
        var_dec->var_dec_name = calloc(strlen(var->var_name)+1, sizeof(char));
        strcpy(var_dec->var_dec_name, var->var_name);
        //attach node value into variable declaration
        var_dec->var_dec_val = var_val;
        add_var_dec(func_dec->func_dec_body->custom, var_dec);
    }
    return visit(func_dec->func_dec_body);
}

ast_t* visit_func_dec(ast_t* node) {
    add_func_dec(node->custom, node);
    return node;
}

ast_t* visit_var_dec(ast_t* node) {
    add_var_dec(node->custom, node);
    return node;
}

ast_t* visit_var(ast_t* node) {
    ast_t* var = get_var(node->custom, node->var_name);
    if(var != (void*)0) {
        return visit(var->var_dec_val);
    }
    printf("undefinded variable \"%s\"", node->var_name);
    exit(1); 
}

ast_t* visit_string(ast_t* node) {
    return node;
}