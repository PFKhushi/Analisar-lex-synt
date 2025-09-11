#include <stdio.h>
#include <stdlib.h>
#include "Token.h"



typedef struct Scanner{
    int state;
    FILE *file_pointer;
    char character, previous_character;

    int     (*ScannerInit)(struct Scanner *scanner, char *file_name);
    Token*  (*NextToken)(struct Scanner *scanner);
    int     (*IsLetter)(char character);////////
    int     (*IsDigit)(char character);////////
    int     (*IsMathOperator)(char character);////////
    int     (*IsRelOperator)(char character);////////
    Token*  (*GetTokenDone)(struct Scanner* scanner, char* content, int content_size, TokenType type);
    char*   (*AddCharToken)(char *content, int content_size, char character);
    void    (*NextChar)(struct Scanner *scanner);////////
    void    (*Back)(struct Scanner *scanner);///////


} Scanner;


Scanner* CreateScanner();
void DestroyScanner(Scanner *scanner);
Token* next_token(Scanner *scanner);
int scanner_init(Scanner *scanner, char* file_name);
int is_token_digit(char character);
int is_token_letter(char character);
int is_token_math_operator(char character);
int is_token_relational_operator(char character);
char* add_character_token(char *content, int content_size, char character);
Token* get_token_done(Scanner* scanner, char* content, int content_size, TokenType type);
void next_char(Scanner *scanner);
void back_char_tracker(Scanner *scanner);
