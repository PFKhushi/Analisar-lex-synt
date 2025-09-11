typedef enum TokenType{

    PREPROCESSADOR,     // #include, #define

    TIPO,               // int, float, char, double, void

    QUALIFICADOR,       // const, _Atomic, volatile

    IDENTIFICADOR,      // nomeDeVariavel, funcaoTeste (a-z | A-Z | _)(a-z | A-Z | _ | 0-9)*

    BIBLIOTECA,         // <stdio.h>, "my_biblio.h"

    NUMERO,             // 123, 45.6
    STRING,             // "texto"
    CARACTERE,          // 'a'

    PARENTESE_ABRE,     // (
    PARENTESE_FECHA,    // )
    CHAVE_ABRE,         // {
    CHAVE_FECHA,        // }
    COLCHETE_ABRE,      // [
    COLCHETE_FECHA,     // ]
/*
    ASPAS,              // "
    APOSTROFO,          // '
*/
    OPERADOR_REL,       // ==, !=, <, >, <=, >=
    OPERADOR_MAT,       // +, -, *, /
    ATRIBUICAO,         // =

    SEPARADOR,          // ,

    QUEBRA_LINHA,       // '\n'
    FIM_COMANDO,        // ;
    RETORNO,            // return
    ERRO                // Mensagem de erro

} TokenType;

const char* TOKEN_TYPE_TO_STRING(TokenType type);
int IS_TOKENTYPE(TokenType type);
