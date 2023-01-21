#include "include/custom.h"
#include <string.h>
#include <stdio.h>

custom_t* init_custom() {
    custom_t* custom = calloc(1, sizeof(struct CUSTOM_STRUCT));
    custom->func_decs = (void*)0;
    custom->func_decs_size = 0;
    custom->var_decs = (void*)0;
    custom->var_decs_size = 0;
    return custom;
}

ast_t* add_func_dec(custom_t* custom, ast_t* node) {
    if(custom->func_decs == (void*)0) {
        custom->func_decs = calloc(1, sizeof(struct AST_STRUCT*));
    }
    else {
        custom->func_decs = realloc(
            custom->func_decs, 
            custom->func_decs_size*sizeof(struct AST_STRUCT**)
        );
    }
    custom->func_decs[custom->func_decs_size] = node;
    custom->func_decs_size++;
    return node;
}

ast_t* get_custom_func(custom_t* custom, char* func_name) {
    for(int i = 0; i < custom->func_decs_size; i++) {
        ast_t* func = custom->func_decs[i];
        if(strcmp(func->func_dec_name, func_name) == 0) {
            return func;
        }
    }
    return (void*)0;
}

ast_t* add_var_dec(custom_t* custom, ast_t* node) {
    if(custom->var_decs == (void*)0) {
        custom->var_decs = calloc(1, sizeof(struct AST_STRUCT*));
    }
    else {
        custom->var_decs = realloc(
            custom->var_decs, 
            custom->var_decs_size*sizeof(struct AST_STRUCT**)
        );
    }
    custom->var_decs[custom->var_decs_size] = node;
    custom->var_decs_size++;
    return node;
}

ast_t* get_var(custom_t* custom, char* var_name) {
    for(int i = 0; i < custom->var_decs_size; i++) {
        ast_t* var = custom->var_decs[i];
        if(strcmp(var->var_dec_name, var_name) == 0) {
            return var;
        }
    }
    return (void*)0;
}