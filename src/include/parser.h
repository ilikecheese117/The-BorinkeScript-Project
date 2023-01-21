#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "custom.h"

typedef struct PARSER_STRUCT {
    lexer_t* lexer;
    token_t* curr_token;
    token_t* prev_token;
    custom_t* custom;
} parser_t;

parser_t* init_parser(lexer_t* lexer);

void parser_expect(parser_t* parser, int token_type); //will make sure source code we looking at ain't broken

ast_t* parse(parser_t* parser, custom_t* custom); //will return the entire source code as an ast tree. the functions below will return ast nodes. to parse is to convert to an ast node

ast_t* parse_statement(parser_t* parser, custom_t* custom); //parses a singular statement

ast_t* parse_statements(parser_t* parser, custom_t* custom); //parses list of statements

ast_t* parse_mult(parser_t* parser, custom_t* custom); //parses multiplication

ast_t* parse_sum(parser_t* parser, custom_t* custom); //parses simple addition/subtraction

ast_t* parse_func_call(parser_t* parser, custom_t* custom); //parses a function call

ast_t* parse_func_dec(parser_t* parser, custom_t* custom); //makes user defined function

ast_t* parse_var(parser_t* parser, custom_t* custom); //parses a variable

ast_t* parse_var_dec(parser_t* parser, custom_t* custom); //parses a variable declaration

ast_t* parse_string(parser_t* parser, custom_t* custom); //parses a string

ast_t* parse_id(parser_t* parser, custom_t* custom); //parses an id token (declaration, variable name, math, etc.)

#endif