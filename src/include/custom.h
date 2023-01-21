#ifndef CUSTOM_H
#define CUSTOM_H
#include "ast.h"

typedef struct CUSTOM_STRUCT {
    ast_t** func_decs;
    size_t func_decs_size;
    ast_t** var_decs; //this will store our variable declarations so that when we look over our variables later we know what we're referring to
    size_t var_decs_size;
} custom_t;

custom_t* init_custom();

ast_t* add_func_dec(custom_t* custom, ast_t* node);

ast_t* get_custom_func(custom_t* custom, char* func_name);

ast_t* add_var_dec(custom_t* custom, ast_t* node);

ast_t* get_var(custom_t* custom, char* func_name);

#endif