#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include "structs.h"
#include "baixar.h"
#include "login_clientes.h"
#include "area_banco.h"


/**
  *
  * @author Maykoll Rocha
  * @email <maykoll1412@gmail.com>
  * @date 2022-10-30
  *
**/

int main()
{
    pivo *pivo = criar_pivo();
    baixar_registros(pivo);
    unsigned int op;

    do{
        printf("--MENU BANCOS--\n 1.Registrar bancos\n 2.Entrar no banco;\n 3.Printar bancos;\n 0.Sair.");
        do{
            scanf("%i",&op);
        }while(op>3);
        switch(op)
        {
        case 1:
            registrar_banco(pivo);
            break;
        case 2:
            Menu_banco(pivo);
            break;
        case 3:
            printf_contas(pivo->primeio);
            break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_tudo(pivo);
    free(pivo);

    return 0;
}

void printf_contas(banco *banco)
{
    while(banco != NULL )
    {
        printf("Nome banco: %s\n",banco->nome_banco);
        cliente *clin = banco->primeiro;
        while(clin != NULL)
        {
            printf_client(clin);
            clin = clin->prox;
        }
        banco = banco->prox;
    }
}

void printf_client(cliente *clin)
{
    printf("nome: %s idade: %i Codigo: %i\n",clin->nome_client,clin->idade,clin->cod);
    printf("senha: %i saldo: %0.2f\n\n",clin->senha,clin->saldo);
}


void limpar_tudo(pivo *pivo)
{
    banco *banco = pivo->primeio;
    while(banco != NULL)
    {
        cliente *clin = banco->primeiro;
        while(clin != NULL)
        {
            cliente *aux = clin;
            clin = clin->prox;
            free(aux);
        }
        banco = banco->prox;
        free(pivo->primeio);
        pivo->primeio = banco;
    }
}
