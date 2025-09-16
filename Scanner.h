#include <stdio.h>
#include <stdlib.h>
#include "Token.h"

typedef struct Scanner{
    int state, inner_state,qtd_tipos, qtd_preprocessadores, qtd_qualificadores, qtd_bibliotecas, linha, coluna;
    FILE *file_pointer;
    char character, previous_character, **tipos, **preprocessadores, **qualificadores, **bibliotecas;

    int     (*ScannerInit)(struct Scanner *scanner, char *file_name);
    Token*  (*NextToken)(struct Scanner *scanner);
    int     (*IsLetter)(char character);////////
    int     (*IsDigit)(char character); ////////
    int     (*IsMathOperator)(char character);////////
    int     (*IsRelOperator)(char character); ////////
    int     (*IsTokenInList)(char **lista, int list_size,  char *palavra);
    Token*  (*GetTokenDone)(struct Scanner* scanner, Token *tk, char* content, int content_size, TokenType type);
    char*   (*AddCharToken)(char *content, int content_size, char character);
    void    (*NextChar)(struct Scanner *scanner);////////
    void    (*GetRelational)(struct Scanner *scanner);
    void    (*Back)(struct Scanner *scanner);///////

} Scanner;


Scanner* CreateScanner(char** tipos, char** preprocessadores, char** qualificadores, char** bibliotecas);
void DestroyScanner(Scanner *scanner);
Token* next_token(Scanner *scanner);
int scanner_init(Scanner *scanner, char* file_name);
void alocar_palavras_reservadas(Scanner *scanner, char **palavras, TokenType tipo);
int is_token_digit(char character);
int is_token_letter(char character);
int is_token_math_operator(char character);
int is_token_relational_operator(char character);
int is_token_in_list(char **lista, int list_size,  char *palavra);
char* add_character_token(char *content, int content_size, char character);
Token* get_token_done(Scanner* scanner, Token *tk, char* content, int content_size, TokenType type);
void next_char(Scanner *scanner);
void back_char_tracker(Scanner *scanner);
void print_list_reservadas(Scanner *scanner, TokenType tipo);
void alocar_palavras_reservadas(Scanner *scanner, char **palavras, TokenType tipo);
