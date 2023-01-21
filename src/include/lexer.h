#ifndef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct LEXER_STRUCT {
    char c;
    unsigned int i;
    char* contents;

} lexer_t; // lexer state

lexer_t* init_lexer(char* contents); //create lexer

void next_character(lexer_t* lexer);

void lexer_skip_whitespace(lexer_t* lexer);

token_t* get_next_token(lexer_t* lexer);

token_t* collect_string_token(lexer_t* lexer);

token_t* collect_id_token(lexer_t* lexer);

token_t* next_character_with_token(lexer_t* lexer, token_t* token);

char* get_curr_char_as_string(lexer_t* lexer);

#endif