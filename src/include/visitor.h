#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"

ast_t* visit(ast_t* node);

ast_t* visit_compound(ast_t* node);

ast_t* visit_func_call(ast_t* node);

ast_t* visit_func_dec(ast_t* node);

ast_t* visit_var_dec(ast_t* node);

ast_t* visit_var(ast_t* node);

ast_t* visit_string(ast_t* node);

#endif