#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Trabalho_cabeca.h"
/**
 *
 * @author Maykoll Rocha
 * @email <maykoll.rocha422@academico.ufgd.edu.br>
 * @date  2022-10-10
 *
 */


int main()
{
    unsigned int op;

    do{
        printf("--MENU--\nDuplamente Encadeada:\n 1.Pilha;\n 2.Fila;\nSimplesmente Encadeda:\n 3.Pilha;\n 4.Fila;\n 5.Fila Circular.\n");
        do{
            scanf("%i",&op);
        }while(op > 5);
        system("cls");
        switch(op)
        {
        case 1:Pilha_Duplamente();break;
        case 2:Fila_Duplamente();break;
        case 3:Pilha_Simplesmente();break;
        case 4:Fila_Simplesmente();break;
        case 5:Fila_Simplesmente_Circular();break;
        }

    }while(op != 0);

    return 1;
}

void Fila_Duplamente()
{
    unsigned int op;
    pivo *pivo = criar_Pivo();
    do{
        printf("--MENU ENCADEADA DUPLHA FILA--\n 1.Adicionar;\n 2.Mostar;\n 3.Remover;\n 4.Limpar tudo;\n 0.sair.\n");
        do{
            scanf("%i",&op);
        }while(op > 4);
        switch(op)
        {
            case 1: add_lista_DC(pivo);break;
            case 2: !vazia(pivo->primeiro) ? mostrar_lista(pivo->primeiro):printf("Vazia.\n");break;
            case 3: !vazia(pivo->primeiro) ? removevalor_DC(pivo,pivo->primeiro,pivo->primeiro->dado):printf("Vazia.\n");break;
            case 4: !vazia(pivo->primeiro) ? limpar_tudo_DC(pivo):printf("Vazia.\n");break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_tudo_DC(pivo);
    free(pivo);
    system("cls");
    return ;
}


void Pilha_Duplamente()
{
    unsigned int op;
    pivo *pivo = criar_Pivo();
    do{
        printf("--MENU ENCADEADA DUPLA PILHA--\n 1.Adicionar;\n 2.Mostar;\n 3.Remover;\n 4.Limpar tudo;\n 0.sair.\n");
        do{
            scanf("%i",&op);
        }while(op > 4);
        switch(op)
        {
            case 1: add_lista_DC(pivo);break;
            case 2: !vazia(pivo->primeiro) ? mostrar_lista(pivo->primeiro):printf("Vazia.\n");break;
            case 3: !vazia(pivo->primeiro) ? removevalor_DC(pivo,pivo->ultimo,pivo->ultimo->dado): printf("Vazia.\n");break;
            case 4: !vazia(pivo->primeiro) ? limpar_tudo_DC(pivo):printf("Vazia.\n");break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_tudo_DC(pivo);
    free(pivo);
    system("cls");
    return ;
}


void Pilha_Simplesmente()
{
    unsigned int op;
    pivo *pivo = criar_Pivo();
    do{
        printf("--MENU ENCADEADA SIMPLES PILHA--\n 1.Adicionar;\n 2.Mostar;\n 3.Remover;\n 4.Limpar tudo;\n 0.sair.\n");
        do{
            scanf("%i",&op);
        }while(op > 6);
        switch(op)
        {
            case 1: add_lista_SC(pivo);break;
            case 2: if(!vazia(pivo->primeiro)){mostrar_lista(pivo->primeiro);} ;break;
            case 3: if(!vazia(pivo->primeiro)){remover_pilha_SE(pivo);};break;
            case 4: if(!vazia(pivo->primeiro)){limpar_tudo_SC(pivo);};break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_tudo_SC(pivo);
    free(pivo);
    system("cls");
    return;
}

void Fila_Simplesmente()
{
    unsigned int op;
    pivo *pivo = criar_Pivo();
    do{
        printf("--MENU ENCADEADA SIMPLES FILA--\n 1.Adicionar;\n 2.Mostar;\n 3.Remover;\n 4.Limpar tudo;\n 0.sair.\n");
        do{
            scanf("%i",&op);
        }while(op > 6);
        switch(op)
        {
            case 1: add_lista_SC(pivo);break;
            case 2: if(!vazia(pivo->primeiro)){mostrar_lista(pivo->primeiro);} ;break;
            case 3: if(!vazia(pivo->primeiro)){remover_Fila_SE(pivo);};break;
            case 4: if(!vazia(pivo->primeiro)){limpar_tudo_SC(pivo);};break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_tudo_SC(pivo);
    free(pivo);
    system("cls");
    return;
}

void Fila_Simplesmente_Circular()
{
    unsigned int op;
    pivo *pivo = criar_Pivo();
    do{
        printf("--MENU ENCADEADA SIMPLES FILA CIRCULAR--\n 1.Adicionar;\n 2.Mostar;\n 3.Remover;\n 4.Limpar tudo;\n 0.sair.\n");
        do{
            scanf("%i",&op);
        }while(op > 6);
        switch(op)
        {
            case 1: add_lista_SCC(pivo);break;
            case 2: !vazia(pivo->primeiro) ? mostrar_lista_SCC(pivo->primeiro,pivo):printf("Vazio");break;
            case 3: !vazia(pivo->primeiro) ? removevalor_SCC(pivo):printf("Vazio");break;
            case 4: !vazia(pivo->primeiro) ? limpar_tudo_SCC(pivo):printf("Vazio");break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_tudo_SCC(pivo);
    free(pivo);
    system("cls");
    return;
}
