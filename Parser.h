#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"

typedef struct Parser{
    Scanner *scnr;
    Token *tk;

    int (*ParserInit)(struct Parser *prsr, char *arquivo);
    int (*ComecarAnalise)(struct Parser *prsr);

}Parser;

int TestParser(Parser *parser);
Parser* CreateParser();
void DestroyParser(Parser *parser);

int parser_init(Parser *prsr, char *arquivo);
int parser_next_token(Parser *parser);
int comecar_analise(Parser *parser);

void print_error(char *erro, Scanner *scanner, Token * token);
int comeco(Parser *parser);
int processar(Parser *parser);
int valor(Parser *parser);
int declaracao_const(Parser *parser);
int declaracao_ou_funcao(Parser *parser);
int apos_identificador(Parser *parser);
int paramentros(Parser *parser);
int inicializacao(Parser *parser);
int resto_declaracao(Parser *parser);
int resto_declaracao_mat(Parser *parser);
int corpo_funcao(Parser *parser);
int inicializacao_array(Parser *parser);
int lista_valores(Parser *parser);
int resto_valores(Parser *parser);
int lista_parametros(Parser *parser);
int bloco_comandos(Parser *parser);
int declaracao_local(Parser *parser);
int declaracao_local_resto(Parser *parser);
int declaracao_local_const(Parser *parser);
int comando_identificador(Parser *parser);
int expressao(Parser *parser);
int expressao_id(Parser *parser);
int expressao_rest(Parser *parser);
int resto_parametros(Parser *parser);
int argumentos(Parser *parser);
int resto_argumentos(Parser *parser);
int comando_if(Parser *parser);
int comando_while(Parser *parser);
int comando_for(Parser *parser);
int comando_switch(Parser *parser);
int comando_return(Parser *parser);
int comando_printf(Parser *parser);
int condicao(Parser *parser);
int condicao_rest(Parser *parser);
int comando(Parser *parser);
int comando_else(Parser *parser);
int comando_else_aux(Parser *parser);
int comando_else_fim(Parser *parser);
int chamada_printf(Parser *parser);
int inicializacao_for(Parser *parser);
int incremento_for(Parser *parser);
int lista_cases(Parser *parser);
int comando_case(Parser *parser);
int comando_default(Parser *parser);
int bloco_comandos_case(Parser *parser);
int expressao_return(Parser *parser);
int expressao_id_return(Parser *parser);
int bloco_comandos_fim(Parser *parser);

#endif // PARSER_H
