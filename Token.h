#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Declaração da estrutura Token
typedef struct Token {
    TokenType type;
    char *text;
    TokenType   (*GetType)(struct Token *token);
    int         (*SetType)(struct Token *token, TokenType tokenType);
    const char* (*GetText)(struct Token *token);
    int         (*SetText)(struct Token *token, char *text);
    char*       (*ToString)(struct Token *token);
} Token;

// Declarações das funções públicas
Token* CreateToken();
int TokenInit(Token *token, TokenType type, char *text);
void DestroyToken(Token *tk);
//void TokenCleanup(Token *token);

// Funções auxiliares públicas
int IS_TOKENTYPE(TokenType type);
const char* TokenTypeToString(TokenType type);

// Funções dos ponteiros (caso queira usar diretamente)
const char* get_token_text(Token *token);
int set_token_type(Token *token, TokenType type);
TokenType get_token_type(Token *token);
int set_token_text(Token *token, char *text);
char* token_to_string(Token *token);

#endif // TOKEN_H
