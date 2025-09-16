#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int scanner_init(Scanner *scanner, char* file_name){
    scanner->file_pointer = fopen(file_name, "r");
    if(scanner->file_pointer==NULL) return 0;
    return 1;
}

Token* next_token(Scanner *scanner){

    char *content = NULL; //calloc(1, sizeof(char*));//malloc(sizeof(char*));
    int content_size = 0;
    scanner->state = 0;
    scanner->inner_state = 0;
    Token *tk = CreateToken(); /// Lembrar de destruir antes de sair da funcao quando for retornar outro.

    while(scanner->character != EOF){

        scanner->linha++;
        scanner->NextChar(scanner);
        if(scanner->character == EOF) return NULL;
        //printf("\n\nState = %d\nContent_size = %d\nContent = %s\nCaracter = %c\n\n", scanner->state, content_size, content, scanner->character);
        switch(scanner->state){

            case 0:
                //printf("CASE 0");
                if(scanner->IsLetter(scanner->character) || scanner->character == '_'){             /// Se for caracter
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 1;
                }else if(scanner->IsDigit(scanner->character)){ /// Se for numero
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 2;
                }else if(scanner->IsMathOperator(scanner->character)){  /// Se for operador matematico
                    return scanner->GetTokenDone(scanner, tk,content,++content_size, OPERADOR_MAT);
                }else if(scanner->IsRelOperator(scanner->character)){  /// Se for operado relacional ou atribuicao

                    switch(scanner->character){
                        case '=':
                            scanner->inner_state = 0;
                            break;
                        case '!':
                            scanner->inner_state = 1;
                            break;
                        case '<':
                            scanner->inner_state = 2;
                            break;
                        default:
                            scanner->inner_state = 1;
                            break;
                    }
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state=6;
                }else{
                    switch(scanner->character){
                    case ' ': break;
                    case ',': return scanner->GetTokenDone(scanner, tk,content,++content_size, SEPARADOR);
                    case ';': return scanner->GetTokenDone(scanner, tk,content,++content_size, FIM_COMANDO);

                    case '\"':
                        content = scanner->AddCharToken(content, ++content_size, scanner->character);
                        scanner->state = 4;
                        break;

                    case '\'':
                        content = scanner->AddCharToken(content, ++content_size, scanner->character);
                        scanner->state = 5;
                        break;

                    case '(': return scanner->GetTokenDone(scanner, tk, content, ++content_size, PARENTESE_ABRE);
                    case ')': return scanner->GetTokenDone(scanner, tk, content, ++content_size, PARENTESE_FECHA);
                    case '{': return scanner->GetTokenDone(scanner, tk, content, ++content_size, CHAVE_ABRE);
                    case '}': return scanner->GetTokenDone(scanner, tk, content, ++content_size, CHAVE_FECHA);
                    case '[': return scanner->GetTokenDone(scanner, tk, content, ++content_size, COLCHETE_ABRE);
                    case ']': return scanner->GetTokenDone(scanner, tk, content, ++content_size, COLCHETE_FECHA);
                    case ':': return scanner->GetTokenDone(scanner, tk, content, ++content_size, LABELCOLON);

                    case '#':
                        //printf("\nProvavel preprocessador\n");
                        content = scanner->AddCharToken(content, ++content_size, scanner->character);
                        scanner->state = 12;
                        break;

                    case '\n':
                        scanner->coluna++;
                        scanner->linha = 0;
                        break;

                    default:
                        return NULL;
                    }
                }
                //printf("\nRedirecionando para case correto\n");
                break;

            case 1: /// Lida com possiveis identificadores
                //printf("CASE 1");
                if(scanner->character=='.'){
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 13;
                }else if(scanner->IsLetter(scanner->character) || scanner->IsDigit(scanner->character) || scanner->character == '_'){ /// Se for caracter valido continua case 1 no proximo loop
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 1;
                }else{ /// Encerra o token identificador voltando um char no leitor, pois o ultimo caracter ja esta em content
                    scanner->Back(scanner);
                    if(scanner->IsTokenInList(scanner->tipos,scanner->qtd_tipos,content)) {
                        TokenInit(tk,TIPO, content);
                        return tk;
                    }
                    if(scanner->IsTokenInList(scanner->qualificadores, scanner->qtd_qualificadores, content)) {
                        TokenInit(tk,QUALIFICADOR, content);
                        return tk;
                    }
                    TokenType tktp = IS_TOKEN_TOKENTYPE(content);
                    //printf("\n%s %d\n", TOKEN_TYPE_TO_STRING(tktp), tktp);

                    TokenInit(tk, tktp, content);
                    return tk;

                }
                break;

            case 2: // Lida com possíveis números
                //printf("CASE 2");
                if(scanner->IsDigit(scanner->character)){ /// Enquanto for numero, continua no case 2
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 2;
                }else if(scanner->character == '.'){ /// Se for um ponto, tem q obrigatoriamente ter um numero a seguir
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 3;
                }else if(scanner->IsLetter(scanner->character) || scanner->character=='@' || scanner->character=='#' || scanner->character=='&'){
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 13;
                }else if(scanner->character=='%'){
                    scanner->AddCharToken(content, ++content_size, scanner->character); /// Qualquer coisa fora numero e ponto, volta um caracter e retorna o token
                    TokenInit(tk, NUMERO, content);
                    return tk;
                }else{
                    scanner->Back(scanner); /// Qualquer coisa fora numero e ponto, volta um caracter e retorna o token
                    TokenInit(tk, NUMERO, content);
                    return tk;
                }
                break;
            case 3: // Lida com os decimais de um numero
                //printf("CASE 3");
                if(scanner->IsDigit(scanner->character)){
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 3;
                }else{ /// se caracter for qualquer coisa fora um numero
                    scanner->Back(scanner);
                    TokenInit(tk, NUMERO, content);
                    return tk;/// decimal
                }
                break;
            case 4:
                //printf("CASE 4");
                if(scanner->character=='"') {
                    char tmp[256];
                    snprintf(tmp, sizeof(tmp), "Error: Aspas devem conter apenas um caracter. Conteudo: [%s]. Coluna: [%d]. Linha: [%d].", content, scanner->coluna, scanner->linha);
                    TokenInit(tk, ERRO, tmp);
                    return tk;
                }else if(scanner->character=='\\'){
                    scanner->state = 8;
                }else if(scanner->character=='%') {
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    content = scanner->AddCharToken(content, ++content_size, '%');
                    break;
                }else{
                    scanner->state = 9;
                }

                content = scanner->AddCharToken(content,++content_size,scanner->character);

                break;

            case 5:
                //printf("CASE 5");
                if(scanner->character=='\'') {
                    char tmp[256];
                    snprintf(tmp, sizeof(tmp), "Error: Aspas simples devem conter apenas um caracter. Conteudo: [%s]. Coluna: [%d]. Linha: [%d].", content, scanner->coluna, scanner->linha);
                    TokenInit(tk, ERRO, tmp);
                    return tk;
                }
                else if(scanner->character=='\\')   scanner->state = 10;
                else                                scanner->state = 11;

                content = scanner->AddCharToken(content,++content_size,scanner->character);
                break;

            case 6:
                //printf("\nCASE 6");
                if(scanner->character=='='){ /// Se proximo caracter for = é com certeza um relacional, ignora caracteres posteriores fazendo com que === seja igual a relacional + atribuicao
                    return scanner->GetTokenDone(scanner, tk, content, ++content_size, OPERADOR_REL);
                }
                switch(scanner->inner_state){

                case 0: /// Como o primeiro  char é = e proximo n é um =, isso é uma atribuicao
                //printf("\nINNER CASE 0");
                    scanner->Back(scanner);
                    TokenInit(tk, ATRIBUICAO, content);
                    return tk;

                case 1: /// Como o primeiro char ! ou um > e o proximo n é um =, ossp é um relcaional
                    //printf("\nINNER CASE 1");
                    scanner->Back(scanner);
                    TokenInit(tk, OPERADOR_REL, content);
                    return tk;

                case 2: /// Como o primeiro char é um < e o priximo n é um =, se o proximo n for um letra minuscula, é um relaciona, caso contrario é uma biblioteca
                    //printf("\nINNER CASE 2");
                    if(scanner->character>='a' && scanner->character<='z'){
                        content = scanner->AddCharToken(content, ++content_size, scanner->character);
                        scanner->state = 7;
                        scanner->inner_state = 0;
                    }else{
                        scanner->Back(scanner);
                        TokenInit(tk, OPERADOR_REL, content);
                        return tk;
                    }
                break;
                }
                break;
            case 7:
                //printf("\nCASE 7");

                switch(scanner->inner_state){

                case 0:
                    if(scanner->IsLetter(scanner->character) || scanner->character == '_'){
                        //printf("\neh um caracter");
                        content = scanner->AddCharToken(content, ++content_size,scanner->character);
                        scanner->inner_state = 0;
                    }else if(scanner->character == '.') {
                        content = scanner->AddCharToken(content, ++content_size, scanner->character);
                        scanner->inner_state = 1;
                    }else {
                        char tmp[256];
                        snprintf(tmp, sizeof(tmp), "Error: Biblioteca mal construida. Conteudo: [%s]. Coluna: [%d]. Linha: [%d].", content, scanner->coluna, scanner->linha);
                        TokenInit(tk, ERRO, tmp);
                        return tk;
                    }
                    break;

                case 1:
                    if(scanner->character>='a' && scanner->character<='z'){
                        content = scanner->AddCharToken(content, ++content_size, scanner->character);
                        scanner->inner_state = 1;
                    }else if(scanner->character=='>'){
                        scanner->AddCharToken(content, ++content_size, scanner->character);
                        if(scanner->IsTokenInList(scanner->bibliotecas, scanner->qtd_bibliotecas, content)){
                            TokenInit(tk, BIBLIOTECA, content);
                            return tk;
                        }else {
                            char tmp[256];
                            snprintf(tmp, sizeof(tmp), "Error: Biblioteca mal construida. Conteudo: [%s]. Coluna: [%d]. Linha: [%d].", content, scanner->coluna, scanner->linha);
                            TokenInit(tk, ERRO, tmp);
                            return tk;
                        }
                    }
                    break;
                }
                scanner->state = 7;
                break;

            case 8:////
                //printf("\nCASE 8");
                content = scanner->AddCharToken(content,++content_size, scanner->character);
                scanner->state = 9;
                break;

            case 9:///
                //printf("\nCASE 9");
                if(scanner->character=='"'){
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    TokenInit(tk, STRING, content);
                    return tk;
                }
                else if(scanner->character=='\'')   scanner->state = 8;
                else                                scanner->state = 9;

                content = scanner->AddCharToken(content, ++content_size, scanner->character);
                break;
            case 10:////
                //printf("\nCASE 10");
                content = scanner->AddCharToken(content,++content_size, scanner->character);
                scanner->state=11;
                break;
            case 11:////
                //printf("\nCASE 11");
                if(scanner->character=='\'') return scanner->GetTokenDone(scanner, tk, ++content, content_size,STRING);

                char tmp[256];
                snprintf(tmp, sizeof(tmp), "Error: Aspas simples devem conter apenas um caracter. Conteudo: [%s]. Coluna: [%d]. Linha: [%d].", content, scanner->coluna, scanner->linha);
                TokenInit(tk, ERRO, tmp);
                return tk;

            case 12:
                //printf("\nCASE 12");
                //fflush(stdout);
                //printf("\nPREPROCESSADOR:\n\n");
                if(scanner->character>='a' && scanner->character<='z'){
                    content = scanner->AddCharToken(content, ++content_size,scanner->character);
                    scanner->state = 12;
                }else{
                    scanner->Back(scanner);
                    if(scanner->IsTokenInList(scanner->preprocessadores, scanner->qtd_preprocessadores, content)){
                        TokenInit(tk, PREPROCESSADOR, content);
                        return tk;
                    }else{
                        char tmp[256];
                        snprintf(tmp, sizeof(tmp), "Error: PREPROCESSADOR mal construido. Conteudo: [%s]. Coluna: [%d]. Linha: [%d].", content, scanner->coluna, scanner->linha);
                        TokenInit(tk, ERRO, tmp);
                        return tk;
                    }
                }
                break;

            case 13:
                if((
                    scanner->IsLetter(scanner->character) ||
                    scanner->IsDigit(scanner->character) ||
                    scanner->character=='@' ||
                    scanner->character=='$' ||
                    scanner->character=='_' ||
                    scanner->character=='#' ||
                    scanner->character=='.' ||
                    scanner->character=='?' )
                ){
                    content = scanner->AddCharToken(content, ++content_size, scanner->character);
                    scanner->state = 13;
                }else{
                    scanner->Back(scanner);

                    char tmp[256]; // ajuste o tamanho conforme necessário

                    snprintf(tmp, sizeof(tmp), "Error: NUMERO ou IDENTIFICADOR mal construido. Conteudo: [%s]. Coluna: [%d]. Linha: [%d].", content, scanner->coluna, scanner->linha);

                    TokenInit(tk, ERRO, tmp);
                    return tk;
                }
                break;

        }
    }
    return NULL;
}

////////////////////////////////////////////////////////////////

int is_token_letter(char character){
    //printf("\nis_token_letter\n");
    return (character>='a' && character<='z') || (character>='A' && character<='Z');
}

////////////////////////////////////////////////////////////////

int is_token_digit(char character){
    //printf("\nis_token_digit\n");
    return (character>='0' && character<='9');
}

////////////////////////////////////////////////////////////////

int is_token_math_operator(char character){
    //printf("\nis_token_math_operator\n");
    return character == '+' || character == '-' || character == '*' || character == '/' || character == '%';
}

////////////////////////////////////////////////////////////////

int is_token_relational_operator(char character){
    //printf("\nis_token_relational_operator\n");
    return character == '>' || character == '<' || character == '=' || character == '!';
}

////////////////////////////////////////////////////////////////

int is_token_in_list(char **lista, int list_size,  char *palavra){
    //printf("\nis_token_in_list\n");
    for(int i=0; i<list_size; i++){
        if(!strcmp(lista[i], palavra)) return 1;
    }
    return 0;
}


////////////////////////////////////////////////////////////////

char* add_character_token(char *content, int content_size, char character){
    //printf("\nadd_character_token\n");
    content = realloc(content, (sizeof(char)*(content_size+1)));
    //printf("tst");
    if (!content) {
        return NULL;
    }
    //printf("tst");
    content[content_size - 1] = character;
    content[content_size] = '\0';
    //printf("tst");
    return content;
}

////////////////////////////////////////////////////////////////

Token* get_token_done(Scanner* scanner, Token *tk, char* content, int content_size, TokenType type){
    //printf("\nget_token_done\n");
    content = scanner->AddCharToken(content, content_size, scanner->character);
    //printf("tst");
    //printf("\n%s %d\n", TOKEN_TYPE_TO_STRING(type), type);

    TokenInit(tk, type, content);
    return tk;
}

////////////////////////////////////////////////////////////////

void next_char(Scanner *scanner){
    //printf("\nnext_char\n");
    scanner->previous_character = scanner->character;
    scanner->character = fgetc(scanner->file_pointer);
}

////////////////////////////////////////////////////////////////

void back_char_tracker(Scanner *scanner){
    //printf("\nback_char_tracker\n");
    ungetc(scanner->character, scanner->file_pointer);
}

////////////////////////////////////////////////////////////////

void print_list_reservadas(Scanner *scanner, TokenType tipo){

    switch (tipo){
        case TIPO:
            printf("\nqtd tipo: %d", scanner->qtd_tipos);
            for(int i = 0; i<scanner->qtd_tipos; i++){
                printf("\nTIPO: %s\n", scanner->tipos[i]);
            }
            break;

        case PREPROCESSADOR:
            printf("\nqtd preprocessador: %d", scanner->qtd_preprocessadores);
            for(int i = 0; i<scanner->qtd_preprocessadores; i++) {
                    printf("\nPREPROCESSADOR: %s\n", scanner->preprocessadores[i]);
            }
            break;
        case QUALIFICADOR:
            printf("\nqtd qualificador: %d", scanner->qtd_qualificadores);
            for(int i = 0; i<scanner->qtd_qualificadores; i++) {
                    printf("\nQUALIFICADOR: %s\n", scanner->qualificadores[i]);
            }
            break;
        case BIBLIOTECA:
            printf("\nqtd biblioteca: %d", scanner->qtd_bibliotecas);
            for(int i = 0; i<scanner->qtd_bibliotecas; i++) {
                    printf("\nBIBLIOTECA: %s\n", scanner->bibliotecas[i]);
            }
            break;
        default:
            perror("TokenType incorreto.");
            exit(1);
    }

}


void alocar_palavras_reservadas(Scanner *scanner, char **palavras, TokenType tipo){

    switch (tipo){
        case TIPO:

            for (int i = 0; palavras[i] != NULL; i++){
                //printf("\nPalavra[%d]: %s\n", i, palavras[i]);
                scanner->qtd_tipos++;
                scanner->tipos = realloc(scanner->tipos, sizeof(char*) * scanner->qtd_tipos);
                if (scanner->tipos == NULL) {
                    perror("realloc falhou");
                    exit(1);
                }
                scanner->tipos[i] = malloc(strlen(palavras[i]) + 1);
                if (scanner->tipos[i] == NULL) {
                    perror("malloc falhou");
                    exit(1);
                }
                strcpy((scanner->tipos[i]), palavras[i]);
                //printf("\nPalavra salva: %s\n%p\n", (scanner->tipos[i]), scanner->tipos[i]);

            }

            break;

        case PREPROCESSADOR:

            for (int i = 0; palavras[i] != NULL; i++){
                //printf("\nPalavra[%d]: %s\n", i, palavras[i]);
                scanner->qtd_preprocessadores++;
                scanner->preprocessadores = realloc(scanner->preprocessadores, sizeof(char*) * scanner->qtd_preprocessadores);
                if (scanner->preprocessadores == NULL) {
                    perror("realloc falhou");
                    exit(1);
                }
                scanner->preprocessadores[i] = malloc(strlen(palavras[i]) + 1);
                if (scanner->preprocessadores[i] == NULL) {
                    perror("malloc falhou");
                    exit(1);
                }
                strcpy((scanner->preprocessadores[i]), palavras[i]);
                //printf("\nPalavra salva: %s\n%p\n", (scanner->preprocessadores[i]), (scanner->preprocessadores[i]));

            }
            break;
        case QUALIFICADOR:

            for (int i = 0; palavras[i] != NULL; i++){
                //printf("\nPalavra[%d]: %s\n", i, palavras[i]);
                scanner->qtd_qualificadores++;
                scanner->qualificadores = realloc(scanner->qualificadores, sizeof(char*) * scanner->qtd_qualificadores);
                if (scanner->qualificadores == NULL) {
                    perror("realloc falhou");
                    exit(1);
                }
                scanner->qualificadores[i] = malloc(strlen(palavras[i]) + 1);
                if (scanner->qualificadores[i] == NULL) {
                    perror("malloc falhou");
                    exit(1);
                }
                strcpy((scanner->qualificadores[i]), palavras[i]);
                //printf("\nPalavra salva: %s\n%p\n", (scanner->qualificadores[i]), (scanner->qualificadores[i]));
            }

            break;
        case BIBLIOTECA:

            for (int i = 0; palavras[i] != NULL; i++){
                //printf("\nPalavra[%d]: %s\n", i, palavras[i]);
                scanner->qtd_bibliotecas++;
                scanner->bibliotecas = realloc(scanner->bibliotecas, sizeof(char*) * scanner->qtd_bibliotecas);
                if (scanner->bibliotecas == NULL) {
                    perror("realloc falhou");
                    exit(1);
                }
                scanner->bibliotecas[i] = malloc(strlen(palavras[i]) + 1);
                if (scanner->bibliotecas[i] == NULL) {
                    perror("malloc falhou");
                    exit(1);
                }
                strcpy((scanner->bibliotecas[i]), palavras[i]);
                //printf("\nPalavra salva: %s\n%p\n", (scanner->bibliotecas[i]), (scanner->bibliotecas[i]));
            }

            break;
        default:
            perror("TokenType incorreto.");
            exit(1);
    }

}


Scanner* CreateScanner(char** tipos, char** preprocessadores, char** qualificadores, char** bibliotecas){

    Scanner *scanner = calloc(1, sizeof(Scanner));
    if(!scanner) return NULL;

    scanner->preprocessadores = malloc(sizeof(char**));
    scanner->qualificadores = malloc(sizeof(char**));
    scanner->tipos = malloc(sizeof(char**));
    scanner->bibliotecas = malloc(sizeof(char**));


    scanner->qtd_tipos = 0;
    scanner->qtd_bibliotecas = 0;
    scanner->qtd_preprocessadores = 0;
    scanner->qtd_qualificadores = 0;

    //printf("\ntest\n");
    if(tipos)               alocar_palavras_reservadas(scanner,tipos,TIPO);
    if(preprocessadores)    alocar_palavras_reservadas(scanner,preprocessadores,PREPROCESSADOR);
    if(qualificadores)      alocar_palavras_reservadas(scanner,qualificadores,QUALIFICADOR);
    if(qualificadores)      alocar_palavras_reservadas(scanner,bibliotecas,BIBLIOTECA);


    scanner->ScannerInit    = scanner_init;
    scanner->NextToken      = next_token;
    scanner->IsLetter       = is_token_letter;
    scanner->IsDigit        = is_token_digit;
    scanner->IsMathOperator = is_token_math_operator;
    scanner->IsRelOperator  = is_token_relational_operator;
    scanner->IsTokenInList  = is_token_in_list;
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
        if(scanner->qtd_preprocessadores>0){
            for(int i = 0; i<scanner->qtd_preprocessadores; i++) {free(scanner->preprocessadores[i]);}
            free(scanner->preprocessadores);
        }
        if(scanner->qtd_tipos>0){
            for(int i = 0; i<scanner->qtd_tipos; i++) {free(scanner->tipos[i]);}
            free(scanner->tipos);
        }
        if(scanner->qtd_qualificadores>0){
            for(int i = 0; i<scanner->qtd_qualificadores; i++) {free(scanner->qualificadores[i]);}
            free(scanner->qualificadores);
        }
        free(scanner);
    }
}
