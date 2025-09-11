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

int scanner_init(Scanner *scanner, char* file_name){
    scanner->file_pointer = fopen(file_name, "r");
    if(scanner->file_pointer==NULL) return 0;
    return 1;
}

Token* next_token(Scanner *scanner){

    char *content = malloc(sizeof(char));
    int content_size = 0;
    scanner->state = 0;


    while(scanner->character != EOF){

        scanner->previous_character = scanner->character;
        scanner->NextChar(scanner);
        printf("%c", scanner->character);

        switch(scanner->state){
        case 0:

            if(scanner->IsLetter(scanner->character)==1){
                content = scanner->AddCharToken(content, ++content_size, scanner->character);
                scanner->state = 1;
            }else if(scanner->IsDigit(scanner->character)==1){
                content = scanner->AddCharToken(content, ++content_size, scanner->character);
                scanner->state = 2;
            }else if(scanner->IsMathOperator(scanner->character)){
                return scanner->GetTokenDone(scanner,content,++content_size, OPERADOR_MAT);
            }else{
                switch(scanner->character){
                case ' ':
                    break;
                case '=':
                    //// ERROOU return scanner->GetTokenDone(scanner,content,++content_size, ATRIBUICAO);
                case ',':
                    return scanner->GetTokenDone(scanner,content,++content_size, SEPARADOR);
                case ';':
                    return scanner->GetTokenDone(scanner,content,++content_size, FIM_COMANDO);
                case '\"':
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 4;
                    ////////////////////
                case '\'':
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 5;
                    ////////////////////
                case '<':
                case '>':
                case '!':
                    ////////////////////
                case '(': return scanner->GetTokenDone(scanner, content, ++content_size, PARENTESE_ABRE);
                case ')': return scanner->GetTokenDone(scanner, content, ++content_size, PARENTESE_FECHA);
                case '{': return scanner->GetTokenDone(scanner, content, ++content_size, CHAVE_ABRE);
                case '}': return scanner->GetTokenDone(scanner, content, ++content_size, CHAVE_FECHA);
                case '[': return scanner->GetTokenDone(scanner, content, ++content_size, COLCHETE_ABRE);
                case ']': return scanner->GetTokenDone(scanner, content, ++content_size, COLCHETE_FECHA);
                case '#':
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 666;
                default:
                    return NULL;
                    ////////////////////
                }
            }

            break;
        case 1:
            if(scanner->IsLetter(scanner->character) || scanner->IsDigit(scanner) || scanner->character == '_'){
                content = scanner->AddCharToken(content, ++content_size, scanner->character);
                scanner->state = 1;
            }else{
                scanner->Back(scanner);
                return scanner->GetTokenDone(scanner, content, ++content_size, IDENTIFICADOR);
            }
        case 2:
            if(scanner->IsDigit(scanner->character)){
                content = scanner->AddCharToken(content, ++content_size, scanner->character);
                scanner->state = 2;
            }else if(scanner->character == '.'){
                content = scanner->AddCharToken(content, ++content_size, scanner->character);
                scanner->state = 3;
            }else{
                scanner->Back(scanner);
                return scanner->GetTokenDone(scanner, content, ++content_size, NUMERO);
            }
        case 3:
            if(scanner->IsDigit(scanner->character)){
                content = scanner->AddCharToken(content, ++content_size, scanner->character);
                scanner->state = 3;
            }else{
                scanner->Back(scanner);
                return scanner->GetTokenDone(scanner, content, ++content_size, NUMERO);
            }
        case 5:
            if(scanner->character=='\''){
                return scanner->GetTokenDone(scanner, content, ++content_size, ERRO);
            }
        case 6:
        default:
            break;

        }


    }
    return NULL;

}

int is_token_letter(char character){
    return (character>='a' && character<='z') || (character>='a' && character<='z');
}

int is_token_digit(char character){
    return (character>='0' && character<='9');
}

int is_token_math_operator(char character){
    return character == '+' || character == '-' || character == '*' || character == '/' || character == '%';
}

int is_token_relational_operator(char character){
    return character == '>' || character == '<' || character == '=' || character == '!';
}

int is_token_relational_operator_complement(char character){
    return character == '>' || character == '<' || character == '=' || character == '!';

char* add_character_token(char *content, int content_size, char character){

    content = realloc(content, (sizeof(char)*content_size+1));
    if (!content) {
        return NULL; // falha de alocação
    }
    content[content_size - 1] = character;
    content[content_size] = '\0';

    return content;
}

Token* get_token_done(Scanner* scanner, char* content, int content_size, TokenType type){
    content = scanner->AddCharToken(content, content_size, scanner->character);
    return TokenInit(CreateToken(), type, content);
}

void next_char(Scanner *scanner){
    scanner->previous_character = scanner->character;
    scanner->character = fgetc(scanner->file_pointer);
}

void back_char_tracker(Scanner *scanner){
    ungetc(scanner->character, scanner->file_pointer);
}


const Scanner* CreateScanner(){

    Scanner *scanner = calloc(2, sizeof(Scanner));
    if(!scanner) return NULL;

    scanner->ScannerInit    = scanner_init;
    scanner->NextToken      = next_token;
    scanner->IsLetter       = is_token_letter;
    scanner->IsDigit        = is_token_digit;
    scanner->IsMathOperator = is_token_math_operator;
    scanner->IsRelOperator  = is_token_relational_operator;
    scanner->AddCharToken   = add_character_token;
    scanner->GetTokenDone   = get_token_done;
    scanner->NextChar       = next_char;
    scanner->Back           = back_char_tracker;

    scanner->file_pointer = NULL;
    scanner->character = '\0';
    scanner->previous_character = '\0';
    scanner->state = 0;


    return scanner;
}


void DestroyScanner(Scanner *scanner){
    if(scanner){
        if(scanner->file_pointer) fclose(scanner->file_pointer);
        free(scanner);
    }
}
