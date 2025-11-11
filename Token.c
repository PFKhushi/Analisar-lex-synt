#include "Token.h"
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TokenType.h"


typedef struct Token {
    TokenType type;
    char *text;

    TokenType   (*GetType)(struct Token *token);
    int         (*SetType)(struct Token *token, TokenType tokenType);
    const char* (*GetText)(struct Token *token);
    int         (*SetText)(struct Token *token, char *text);
    char*       (*ToString)(struct Token *token);


} Token;
*/
const char* get_token_text(Token *token){
    return token->text;
}

char* token_to_string(Token *token){
    if(!token) return NULL;
    char *buf = malloc(40+(strlen(token->text + 1)));
    if (!buf) return NULL;
    sprintf(buf, "Token [type=%s, text=%s]", TOKEN_TYPE_TO_STRING(token->type), token->text);
    return buf;
}

int set_token_type(Token *token, TokenType type){
    if(token == NULL || IS_TOKENTYPE(type) == 0) return 0;
    token->type = type;
    return 1;
}
TokenType get_token_type(Token *token){
    return token->type;
}

int set_token_text(Token *token, char *text) {
    if(!token || !text) return 0;
    token->text = malloc(strlen(text) + 1);
    if(!token->text){
        free(token->text);
        return 0;
    }
    strcpy(token->text, text);
    return 1;
}

int TokenInit(Token *token, TokenType type, char *text){
    if (!token || IS_TOKENTYPE(type) == 0 || !text) return 0;

    token->text = malloc(strlen(text) + 1);
    if(!token->text) {
        free(token->text);
        return 0;
    }
    strcpy(token->text, text);

    token->type = type;

    return 1;
}

Token* CreateToken(){
    Token *tk = malloc(sizeof(Token));
    if(!tk) return NULL;

    tk->GetText     = get_token_text;
    tk->SetText     = set_token_text;
    tk->GetType     = get_token_type;
    tk->SetType     = set_token_type;
    tk->ToString    = token_to_string;

    return tk;
}

void DestroyToken(Token *tk) {
    if (tk) {
        free(tk->text);
        free(tk);
    }
}

