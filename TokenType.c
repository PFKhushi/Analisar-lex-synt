#include "TokenType.h"
/*
#include <string.h>

typedef enum TokenType{

    PREPROCESSADOR,     // #include, #define

    TIPO,               // int, float, char, double, void

    QUALIFICADOR,       // const, _Atomic, volatile

    IDENTIFICADOR,      // nomeDeVariavel, funcaoTeste (a-z | A-Z | _)(a-z | A-Z | _ | 0-9)*

    BIBLIOTECA,         // <stdio.h>, "my_biblio.h"

    IF,
    ELSE,
    WHILE,
    FOR,
    RETURN,
    PRINTF,
    BREAK,
    CONTINUE,
    SWITCH,
    CASE,
    DEFAULT,

    NUMERO,             // 123, 45.6
    STRING,             // "texto"
    CARACTERE,          // 'a'

    PARENTESE_ABRE,     // (
    PARENTESE_FECHA,    // )
    CHAVE_ABRE,         // {
    CHAVE_FECHA,        // }
    COLCHETE_ABRE,      // [
    COLCHETE_FECHA,     // ]

    OPERADOR_REL,       // ==, !=, <, >, <=, >=
    OPERADOR_MAT,       // +, -, *, /
    ATRIBUICAO,         // =

    SEPARADOR,          // ,
    LABELCOLON,         // :

    QUEBRA_LINHA,       // '\n'
    FIM_COMANDO,        // ;
    ERRO

} TokenType;
*/

int IS_TOKENTYPE(TokenType type){
    switch(type){
    case PREPROCESSADOR:///////
    case TIPO://///////////////
    case QUALIFICADOR://///////
    case IDENTIFICADOR:////////
    case BIBLIOTECA:///////////
    case NUMERO:///////////////
    case STRING:///////////////
    case CARACTERE:////////////
    case PARENTESE_ABRE:///////
    case PARENTESE_FECHA://////
    case CHAVE_ABRE:///////////
    case CHAVE_FECHA://////////
    case COLCHETE_ABRE:////////
    case COLCHETE_FECHA:///////

    case IF:
    case ELSE:
    case WHILE:
    case FOR:
    case RETURN:
    case PRINTF:
    case BREAK:
    case CONTINUE:
    case SWITCH:
    case CASE:
    case DEFAULT:

    case OPERADOR_REL://///////
    case OPERADOR_MAT://///////
    case ATRIBUICAO:///////////
    case SEPARADOR:////////////
    case LABELCOLON:///////////

    case QUEBRA_LINHA:
    case FIM_COMANDO://////////

    case ERRO://///////////////
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

    case IF:                return "IF";
    case ELSE:              return "ELSE";
    case WHILE:             return "WHILE";
    case FOR:               return "FOR";
    case RETURN:            return "RETURN";
    case PRINTF:            return "PRINTF";
    case BREAK:             return "BREAK";
    case CONTINUE:          return "CONTINUE";
    case SWITCH:            return "SWITCH";
    case CASE:              return "CASE";
    case DEFAULT:           return "DEFAULT";

    case OPERADOR_REL:      return "OPERADOR_REL";
    case OPERADOR_MAT:      return "OPERADOR_MAT";
    case ATRIBUICAO:        return "ATRIBUICAO";

    case SEPARADOR:         return "SEPARADOR";
    case LABELCOLON:        return "LABELCOLON";

    case QUEBRA_LINHA:      return "QUEBRA_LINHA";
    case FIM_COMANDO:       return "FIM_COMANDO";
    case ERRO:              return "ERRO";
    default:                return "UNKNOWN";
    }
}


TokenType IS_TOKEN_TOKENTYPE(char *content){

    //printf("\n\nIS_TOKEN_TOKENTYPE  %s", content);
    //printf("\n%d", strcmp(content, "printf"));

    if (strcmp(content,"if")==0)            return IF;
    else if (strcmp(content,"else")==0)     return ELSE;
    else if (strcmp(content,"while")==0)    return WHILE;
    else if (strcmp(content,"for")==0)      return FOR;
    else if (strcmp(content,"return")==0)   return RETURN;
    else if (strcmp(content,"printf")==0)   return PRINTF;
    else if (strcmp(content,"break")==0)    return BREAK;
    else if (strcmp(content,"continue")==0) return CONTINUE;
    else if (strcmp(content,"switch")==0)   return SWITCH;
    else if (strcmp(content,"case")==0)     return CASE;
    else if (strcmp(content,"default")==0)  return DEFAULT;
    else return IDENTIFICADOR;

}
