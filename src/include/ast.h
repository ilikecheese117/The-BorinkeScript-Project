#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct AST_STRUCT {
    enum {
        VAR_DEC,  
        FUNC_CALL,
        FUNC_DEC,
        VAR,
        STRING,
        COMPOUND, //list of multiple statements
        NONE //no operation took place or takes place
    } type; //all the types are ast nodes
    struct CUSTOM_STRUCT* custom; 
    //VAR_DEC
    char* var_dec_name;
    struct AST_STRUCT* var_dec_val;
    //VAR
    char* var_name;
    //FUNC_CALL
    char* func_call_name;
    struct AST_STRUCT** func_call_args;
    size_t func_call_args_size; //size_t returns the size in bytes
    //FUNC_DEC
    char* func_dec_name;
    struct AST_STRUCT* func_dec_body;
    struct AST_STRUCT** func_dec_args;
    size_t func_dec_args_size;
    //STRING
    char* string_val;
    //COMPOUND
    struct AST_STRUCT** compound_val;
    size_t compound_size;
} ast_t;

ast_t* init_ast(int type);

#endif