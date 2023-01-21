#include "include/parser.h"
#include <stdio.h>
#include <string.h>

parser_t* init_parser(lexer_t* lexer) {
    parser_t* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->curr_token = get_next_token(lexer);
    parser->prev_token = parser->curr_token;
    parser->custom = init_custom();
    return parser;
}

void parser_expect(parser_t* parser, int token_type) {
    if (parser->curr_token->type == token_type) {
        parser->prev_token = parser->curr_token;
        parser->curr_token = get_next_token(parser->lexer);
    }
    else {
        printf("Expected token type %d, but instead got unexpected token '%s' with type %d\n", token_type, parser->curr_token->value, parser->curr_token->type);
        exit(1);
    }
}

ast_t* parse(parser_t* parser, custom_t* custom) {
    return parse_statements(parser, custom);
}

ast_t* parse_statement(parser_t* parser, custom_t* custom) {
    switch(parser->curr_token->type) {
        case TOKEN_ID:
            return parse_id(parser, custom);
        case TOKEN_STRING:
            return parse_string(parser, custom);
    }
}

ast_t* parse_statements(parser_t* parser, custom_t* custom) {
    ast_t* compound = init_ast(COMPOUND);
    compound->custom = custom;
    compound->compound_val = calloc(1, sizeof(struct AST_STRUCT*));
    ast_t* statement = parse_statement(parser, custom);
    compound->compound_val[0] = statement;
    while(parser->curr_token->type == TOKEN_SEMI) {
        compound->compound_size++;
        parser_expect(parser, TOKEN_SEMI);
        ast_t* statement = parse_statement(parser, custom);
        compound->compound_val = realloc(
            compound->compound_val, 
            compound->compound_size*sizeof(struct AST_STRUCT*)
        );
        compound->compound_val[compound->compound_size] = statement;
    }
    return compound;
}

ast_t* parse_mult(parser_t* parser, custom_t* custom) {

}

ast_t* parse_sum(parser_t* parser, custom_t* custom) {

}

ast_t* parse_func_call(parser_t* parser, custom_t* custom) {
   ast_t* func_call = init_ast(FUNC_CALL);
   func_call->func_call_name = parser->prev_token->value;
   parser_expect(parser, TOKEN_L_PARE);
   func_call->func_call_args = calloc(1, sizeof(struct AST_STRUCT*));
   ast_t* arg = parse_statement(parser, custom);
   func_call->func_call_args[0] = arg;
  while(parser->curr_token->type == TOKEN_COMMA) {
        func_call->func_call_args_size++;
        parser_expect(parser, TOKEN_COMMA);
        ast_t* arg = parse_statement(parser, custom);
        func_call->func_call_args = realloc(
            func_call->func_call_args,
            func_call->func_call_args_size*sizeof(struct AST_STRUCT*)
        );
        func_call->func_call_args[func_call->func_call_args_size] = arg;
   }
   parser_expect(parser, TOKEN_R_PARE);
   func_call->custom = custom;
   return func_call;
}

ast_t* parse_func_dec(parser_t* parser, custom_t* custom) {
    ast_t* func_dec = init_ast(FUNC_DEC);
    parser_expect(parser, TOKEN_ID);
    char* func_name = parser->curr_token->value;
    func_dec->func_dec_name = calloc(strlen(func_name)+1, sizeof(char));
    strcpy(func_dec->func_dec_name, func_name);
    parser_expect(parser, TOKEN_ID);
    parser_expect(parser, TOKEN_L_PARE);
    ast_t* arg = parse_var(parser, custom);
    func_dec->func_dec_args = calloc(1, sizeof(struct AST_STRUCT*));
    func_dec->func_dec_args[func_dec->func_dec_args_size] = arg;
    func_dec->func_dec_args_size++;
    while(parser->curr_token->type == TOKEN_COMMA) {
        parser_expect(parser, TOKEN_COMMA);
        ast_t* arg = parse_var(parser, custom);
        func_dec->func_dec_args = realloc(
                func_dec->func_dec_args,
                func_dec->func_dec_args_size*sizeof(struct AST_STRUCT*)
        );
        func_dec->func_dec_args[func_dec->func_dec_args_size] = arg;
        func_dec->func_dec_args_size++;
    }
    parser_expect(parser, TOKEN_R_PARE); 
    parser_expect(parser, TOKEN_L_BRACK);
    func_dec->func_dec_body = parse_statements(parser, custom);
    parser_expect(parser, TOKEN_R_BRACK);
    func_dec->custom = custom;
    return func_dec; 

}

ast_t* parse_var(parser_t* parser, custom_t* custom) {
    char* token_value = parser->curr_token->value;
    parser_expect(parser, TOKEN_ID);
    if(parser->curr_token->type == TOKEN_L_PARE) {
        return parse_func_call(parser, custom);
    }
    ast_t* ast_var = init_ast(VAR);
    ast_var->var_name = token_value;
    ast_var->custom = custom;
    return ast_var;
}

ast_t* parse_var_dec(parser_t* parser, custom_t* custom) {
    parser_expect(parser, TOKEN_ID); //variable declaration
    char* var_dec_name = parser->curr_token->value;
    parser_expect(parser, TOKEN_ID);//variable name
    parser_expect(parser, TOKEN_EQUALS);
    ast_t* var_dec_val = parse_statement(parser, custom);
    ast_t* var_dec = init_ast(VAR_DEC);
    var_dec->var_dec_name = var_dec_name;
    var_dec->var_dec_val = var_dec_val;
    var_dec->custom = custom;
    return var_dec;
}

ast_t* parse_string(parser_t* parser, custom_t* custom) {
    ast_t* ast_string = init_ast(STRING);
    ast_string->string_val = parser->curr_token->value;
    parser_expect(parser, TOKEN_STRING);
    ast_string->custom = custom;
    return ast_string;
}

ast_t* parse_id(parser_t* parser, custom_t* custom) {
    if(strcmp(parser->curr_token->value, "cosa") == 0){
        return parse_var_dec(parser, custom);
    }
    else if(strcmp(parser->curr_token->value, "definelo") == 0) {
        return parse_func_dec(parser, custom);
    }
    else {
        return parse_var(parser, custom);
    }
}