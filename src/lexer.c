#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

lexer_t* init_lexer(char* contents) {
    lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];
    return lexer;
}

void next_character(lexer_t* lexer) {
    if(lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        lexer->i++;
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_t* lexer) {
    while(lexer->c == ' ' || lexer->c == 10) {         //10 means newline
        next_character(lexer); 
    }
}

token_t* get_next_token(lexer_t* lexer) {
    while(lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        int isalnum = isalnum(lexer->c);
        if(isalpha(lexer->c)) {
            return collect_id_token(lexer);
        }
        switch(lexer->c) {
            case ' ':
            case 10:
                lexer_skip_whitespace(lexer);
                break; 
            case '=':
                return next_character_with_token(lexer, init_token(TOKEN_EQUALS, get_curr_char_as_string(lexer)));
            case ';':
                return next_character_with_token(lexer, init_token(TOKEN_SEMI, get_curr_char_as_string(lexer))); 
            case '(':
                return next_character_with_token(lexer, init_token(TOKEN_L_PARE, get_curr_char_as_string(lexer))); 
            case ')':
                return next_character_with_token(lexer, init_token(TOKEN_R_PARE, get_curr_char_as_string(lexer)));  
            case '{':
                return next_character_with_token(lexer, init_token(TOKEN_L_BRACK, get_curr_char_as_string(lexer))); 
            case '}':
                return next_character_with_token(lexer, init_token(TOKEN_R_BRACK, get_curr_char_as_string(lexer)));
            case ',':
                return next_character_with_token(lexer, init_token(TOKEN_COMMA, get_curr_char_as_string(lexer)));  
            case '"':
                return collect_string_token(lexer);
            default:
                next_character(lexer);
        }
    }
    return init_token(TOKEN_END, "\0");
} 

token_t* collect_string_token(lexer_t* lexer) {
    next_character(lexer);
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    while (lexer->c != '"') {
        char* s = get_curr_char_as_string(lexer);
        value = realloc(value, (strlen(value)+strlen(s)+1)*sizeof(char));
        strcat(value, s);
        next_character(lexer);
    }
    next_character(lexer);
    return init_token(TOKEN_STRING, value);
}

token_t* collect_id_token(lexer_t* lexer) {
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    while (isalnum(lexer->c) || lexer->c == '_') {
        char* s = get_curr_char_as_string(lexer);
        value = realloc(value, (strlen(value)+strlen(s)+1)*sizeof(char));
        strcat(value, s);
        next_character(lexer);
    }
    return init_token(TOKEN_ID, value);
}

token_t* next_character_with_token(lexer_t* lexer, token_t* token) {        //when we get to the special character, this function will send them to the token and advance the place we're at in the string
    next_character(lexer); 
    return token;
}

char* get_curr_char_as_string(lexer_t* lexer) {
    char* curr_c = calloc(2, sizeof(char));
    curr_c[0] = lexer->c;
    curr_c[1] = '\0';                                 //'\0' means null character
    return curr_c;
}