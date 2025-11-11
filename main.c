#include <stdio.h>
#include <stdlib.h>

#include "Parser.h"

void TestToken();
void TestScanner();
///  gcc main.c Scanner.c Token.c TokenType.c -o analisador -Wall -Wextra -std=c11

int main()
{
    /// Maria Vitório
    /// Pedro Firmino

    Parser *parser = CreateParser();
    parser->ParserInit(parser, "ArquivoAnalisar/arquivo_para_analise.c");

    if(parser->ComecarAnalise(parser) == 0){
        printf("Analise deu errado");
    }else{
        printf("Analise deu certo");
    }

    //TestParser(parser);
    //printf("agora foi");
    DestroyParser(parser);

/*
    char *preprocessadores[] = {
        "#include",
        "#define",
        NULL
    };
    char *tipos[] = {
        "int",
        "char",
        "float",
        "double",
        NULL
    };
    char *qualificadores[] = {
        "const",
        NULL
    };
    char *bibliotecas[] = {
        "<stdlib.h>",
        "<stdio.h>",
        NULL
    };

    Scanner *scanner = CreateScanner(tipos, preprocessadores, qualificadores, bibliotecas);
    if (!scanner) return 0;

    scanner->ScannerInit(scanner, "ArquivoAnalisar/arquivo_para_analise.c");

    Token *tk;



    do{
        tk = scanner->NextToken(scanner);
        if(tk != NULL){
            printf(tk->ToString(tk));
            printf("\n");
            DestroyToken(tk);
        }else{
            printf("NULL");
        }
    }while(tk != NULL);


    DestroyScanner(scanner);

*/
    return 0;
}










void TestToken(){

    Token *tk = CreateToken();
    if(!tk) return;

    printf("\n\nTestando ponteiros:\n");

    printf("\nGetText:                %p", tk->GetText);
    printf("\nFuncao get_token_text:  %p", get_token_text);

    printf("\nSetText:                %p", tk->SetText);
    printf("\nFuncao set_token_text:  %p", set_token_text);

    printf("\nGetType:                %p", tk->GetType);
    printf("\nFuncao get_token_type:  %p", get_token_type);

    printf("\nSetType:                %p", tk->SetType);
    printf("\nFuncao set_token_type:  %p", set_token_type);

    printf("\nToString:               %p", tk->ToString);
    printf("\nFuncao token_to_string: %p\n\n\n", token_to_string);

    int check = TokenInit(tk, IDENTIFICADOR, "variable");

    printf("Token created? %d\n",check);

    printf("Token ident: %s\n", TOKEN_TYPE_TO_STRING(tk->GetType(tk)));

    printf("Token Text %s\n",tk->GetText(tk));

    printf("%s\n", tk->ToString(tk));

    printf("Token set type: %d\n", tk->SetType(tk, ATRIBUICAO));

    printf("Token set text: %d\n", tk->SetText(tk, "constant"));

    printf("%s\n", tk->ToString(tk));


    DestroyToken(tk);
}
void TestScanner(){
    char *preprocessadores[] = {
        "#include",
        "#define",
        NULL
    };
    char *tipos[] = {
        "int",
        "char",
        "float",
        "double",
        NULL
    };
    char *qualificadores[] = {
        "const",
        NULL
    };
    char *bibliotecas[] = {
        "<stdlib.h>",
        "<stdio.h>",
        NULL
    };

    Scanner *scanner = CreateScanner(tipos, preprocessadores, qualificadores, bibliotecas);
    if (!scanner) return;
    /*//printf("\n\nCOMECOU DE NOVO");
    printf("\n\nTestando ponteiros:\n");

    printf("ScannerInit:                         %p\n", (void*)scanner->ScannerInit);
    printf("Funcao scanner_init:                 %p\n", (void*)scanner_init);

    printf("IsDigit:                             %p\n", (void*)scanner->IsDigit);
    printf("Funcao is_token_digit:               %p\n", (void*)is_token_digit);

    printf("IsLetter:                            %p\n", (void*)scanner->IsLetter);
    printf("Funcao is_token_letter:              %p\n", (void*)is_token_letter);

    printf("IsMathOperator:                      %p\n", (void*)scanner->IsMathOperator);
    printf("Funcao is_token_math_operator:       %p\n", (void*)is_token_math_operator);

    printf("IsRelOperator:                       %p\n", (void*)scanner->IsRelOperator);
    printf("Funcao is_token_relational_operator: %p\n", (void*)is_token_relational_operator);

    printf("AddCharToken:                        %p\n", (void*)scanner->AddCharToken);
    printf("Funcao add_char_token:               %p\n", (void*)add_character_token);

    printf("NextChar:                            %p\n", (void*)scanner->NextChar);
    printf("Funcao next_char:                    %p\n", (void*)next_char);

    printf("Back:                                %p\n", (void*)scanner->Back);
    printf("Funcao back_char_tracker:            %p\n\n\n", (void*)back_char_tracker);

    printf("Is \'p\' a digit: %d\n", scanner->IsDigit('p'));
    printf("Is \'5\' a digit: %d\n", scanner->IsDigit('5'));

    printf("Is \'p\' a letter: %d\n", scanner->IsLetter('p'));
    printf("Is \'5\' a letter: %d\n", scanner->IsLetter('5'));

    printf("Is \'T\' a relational operator: %d\n", scanner->IsRelOperator('T'));
    printf("Is \'>\' a relational operator: %d\n", scanner->IsRelOperator('>'));

    printf("Is \'T\' a relational operator: %d\n", scanner->IsRelOperator('T'));
    printf("Is \'+\' a math operator: %d\n", scanner->IsMathOperator('+'));
*/
    //printf("\n\n\n");
    //print_list_reservadas(scanner, PREPROCESSADOR);
    //print_list_reservadas(scanner, TIPO);
    //print_list_reservadas(scanner, QUALIFICADOR);
    //printf("test");

    scanner->ScannerInit(scanner, "ArquivoAnalisar/arquivo_para_analise.c");
    //printf("\n\n Scanner Init: %d\n", test);

    Token *tk;
    do{
        tk = scanner->NextToken(scanner);
        if(tk != NULL){
            printf(tk->ToString(tk));
            printf("\n");
            //printf("\n\n\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n\n");
            DestroyToken(tk);
        }else{
            printf("NULL");
        }
    }while(tk != NULL);

    DestroyScanner(scanner);



}

