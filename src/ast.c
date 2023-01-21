#include "include/ast.h"

ast_t* init_ast(int type) {
    ast_t* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;
    ast->custom = (void*)0;
    //VAR_DECLARATION
    ast->var_dec_name = (void*)0;    //this is a void pointer
    ast->var_dec_val = (void*)0; 
    //VAR
    ast->var_name = (void*)0;
    //FUNC_CALL
    ast->func_call_name = (void*)0;
    ast->func_call_args = (void*)0;
    ast->func_call_args_size = 0; 
    //FUNC_DEC
    ast->func_dec_name = (void*)0;
    ast->func_dec_body = (void*)0;
    ast->func_dec_args = (void*)0;
    ast->func_dec_args_size = 0;    
    //STRING
    ast->string_val = (void*)0;
    //COMPOUND
    ast->compound_val = (void*)0;
    ast->compound_size = 0;
    return ast;
}