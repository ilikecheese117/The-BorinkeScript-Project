#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT {
    enum {
        TOKEN_ID, //an id can be print statements, names, variable declarations, etc
        TOKEN_EQUALS, //self explanatory
        TOKEN_STRING,
        TOKEN_SEMI,
        TOKEN_L_PARE,
        TOKEN_R_PARE,
        TOKEN_L_BRACK,
        TOKEN_R_BRACK,
        TOKEN_COMMA,
        TOKEN_END //end of file
    } type;
    char* value;

} token_t;

token_t* init_token(int type, char* value);

#endif