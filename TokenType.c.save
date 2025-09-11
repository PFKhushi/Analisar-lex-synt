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
    RETORNO             // return
} TokenType;


int IS_TOKENTYPE(TokenType type){
    switch(type){
    case PREPROCESSADOR:
    case TIPO:
    case QUALIFICADOR:
    case IDENTIFICADOR: ///////
    case BIBLIOTECA:
    case NUMERO:        ///////
    case STRING:
    case CARACTERE:
    case PARENTESE_ABRE:///////
    case PARENTESE_FECHA://////
    case CHAVE_ABRE:///////////
    case CHAVE_FECHA://////////
    case COLCHETE_ABRE:////////
    case COLCHETE_FECHA:///////
/*
    case ASPAS:
    case APOSTROFO:
*/
    case OPERADOR_REL:
    case OPERADOR_MAT://///////
    case ATRIBUICAO:///////////
    case SEPARADOR:////////////
    case QUEBRA_LINHA:
    case FIM_COMANDO://////////
    case RETORNO:
    case ERRO://///////
        return 1;
    default:
        return 0;

    }
}

const char* TOKEN_TYPE_TO_STRING(TokenType type) {
    switch(type) {
    case PREPROCESSADOR:    return "PREPROCESSADOR";
    case TIPO:              return "TIPO";
    case QUALIFICADOR:      return "QUALIFICADOR";
    case IDENTIFICADOR:     return "IDENTIFICADOR";
    case BIBLIOTECA:        return "BIBLIOTECA";
    case NUMERO:            return "NUMERO";
    case STRING:            return "STRING";
    case CARACTERE:         return "CARACTERE";
    case PARENTESE_ABRE:    return "PARENTESE_ABRE";
    case PARENTESE_FECHA:   return "PARENTESE_FECHA";
    case CHAVE_ABRE:        return "CHAVE_ABRE";
    case CHAVE_FECHA:       return "CHAVE_FECHA";
    case COLCHETE_ABRE:     return "COLCHETE_ABRE";
    case COLCHETE_FECHA:    return "COLCHETE_FECHA";
/*
    case ASPAS:             return "ASPAS";
    case APOSTROFO:         return "APOSTROFO";
*/
    case OPERADOR_REL:      return "OPERADOR_REL";
    case OPERADOR_MAT:      return "OPERADOR_MAT";
    case ATRIBUICAO:        return "ATRIBUICAO";
    case SEPARADOR:         return "SEPARADOR";
    case QUEBRA_LINHA:      return "QUEBRA_LINHA";
    case FIM_COMANDO:       return "FIM_COMANDO";
    case RETORNO:           return "RETORNO";
    case ERRO:              return "ERRO";
    default:                return "UNKNOWN";
    }
}
