#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Cabeça.h"

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
        printf("--Menu--\n 1.Simplesmente Encadeada;\n 2.Duplamente Encadeada\n 3.Fila Circular Simplesmente Encadeada;\n 0.sair.\n");
        do{
            scanf("%i",&op);
        }while(op >3);
        system("cls");
        switch(op)
        {
            case 1:main_SE();break;
            case 2:main_DE();break;
            case 3:main_SEC();break;
        }
    }while(op != 0);

    system("cls");
    return 1;
}

void main_SE()
{
    Pivo *pivo = criarPivo();

    int op;
    do{
        printf("--MENU SIMPLESMENTE ENCADEADA--\n 1.Add;\n 2.Monstra;\n 3.Remove Pilha;\n 4.Remove Fila;\n 5.Remove escolha;\n 6.limpar;\n 0.Sair.\n");
        do{
            scanf("%i",&op);
        }while(op > 6);
        switch(op)
        {
        case 1:  addicinar_SE(pivo);break;
        case 2: !vazia(pivo) ? mostrar(pivo):printf("Vazia");break;
        case 3: !vazia(pivo) ? remover_Fila_SE(pivo):printf("Vazia");break;
        case 4: !vazia(pivo) ? remover_pilha_SE(pivo):printf("Vazia");break;
        case 5: !vazia(pivo) ? remover_SE(pivo):printf("Vazia");break;
        case 6: !vazia(pivo) ? limpar_SE(pivo):printf("Vazia");break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_SE(pivo);
    free(pivo);

    return;
}

void main_DE()
{
    Pivo *pivo = criarPivo();

    int op;
    do{
        printf("--MENU DUPLAMENTE ENCADEADA--\n 1.Add;\n 2.Monstra;\n 3.Remove Fila;\n 4.Remove Pilha;\n 5.Remove escolha;\n 6.limpar;\n 0.Sair.\n");
        do{
            scanf("%i",&op);
        }while(op > 6);
        switch(op)
        {
        case 1:  addicinar_DE(pivo);break;
        case 2: !vazia(pivo) ? mostrar(pivo):printf("Vazia");break;
        case 3: !vazia(pivo) ? remover_Fila_DE(pivo):printf("Vazia");break;
        case 4: !vazia(pivo) ? remover_pilha_DE(pivo):printf("Vazia");break;
        case 5: !vazia(pivo) ? remover_DE(pivo):printf("Vazia");break;
        case 6: !vazia(pivo) ? limpar_DE(pivo):printf("Vazia");break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_DE(pivo);
    free(pivo);

    return;
}

int main_SEC()
{
    unsigned int op;
    Pivo *pivo = criarPivo();
    do{
        printf("--MENU FILA CIRCULAR SIMPLESMENTE ENCADEADA--\n 1.Adicionar;\n 2.Mostar;\n 3.Remover;\n 4.Limpar tudo;\n 0.sair.\n");
        do{
            scanf("%i",&op);
        }while(op > 4);
        switch(op)
        {
            case 1: add_lista_SEC(pivo);break;
            case 2: !vazia(pivo) ? mostrar_lista_SEC(pivo->primeiro,pivo):printf("Vazio");break;
            case 3: !vazia(pivo) ? removevalor_SEC(pivo):printf("Vazio");break;
            case 4: !vazia(pivo) ? limpar_tudo_SEC(pivo):printf("Vazio");break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_tudo_SEC(pivo);
    free(pivo);

    return 0;
}
