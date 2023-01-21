#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) { //argv is a list of the executible commands presed to start the program
    lexer_t* lexer = init_lexer(get_file(argv[1]));
    token_t* token = (void*)0;
    /*while((token = get_next_token(lexer))->type != TOKEN_END) {   //this loop is for debugging purposes
        printf("TOKEN(%d, %s)\n",token->type, token->value);
    }*/
    parser_t* parser = init_parser(lexer);
    ast_t* root = parse(parser, parser->custom);
    visit(root);
}