#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/**
 *
 * @author Maykoll Rocha
 * @email <maykoll.rocha422@academico.ufgd.edu.br>
 * @date  2022-10-10
 *
 */


typedef struct _tipo{
    char text[256];
    int num;
    float numero;
    char carater;
}tipo;

typedef struct _lista
{
    char type;
    struct _tipo *ti;
    struct _lista *prox;
    struct _lista *ant;
}lista;

typedef struct
{
    lista *primeiro;
    lista *ultimo;
}pivo;

pivo *criar_Pivo();
int vazia(lista *lista);
void mostrar_lista(lista *lista,pivo *pivo);
void printf_entra(lista *lista);

void add_lista(pivo *pivo);
lista *criar_lista();
void limpar_da_lista(pivo *pivo);
void removevalor_Fila(pivo *pivo);
void limpar_tudo(pivo *pivo);
void remover_pilha(pivo *pivo);

int main()
{
    unsigned int op;
    pivo *pivo = criar_Pivo();
    do{
        printf("--MENU ENCADEADA SIMPLES--\n 1.Adicionar;\n 2.Mostar;\n 3.Remover Fila;\n 4.Remover Pilha;\n 5.Limpar tudo;\n 0.sair.\n");
        do{
            scanf("%i",&op);
        }while(op > 6);
        switch(op)
        {
            case 1: add_lista(pivo);break;
            case 2: !vazia(pivo->primeiro) ? mostrar_lista(pivo->primeiro,pivo):printf("Vazio");break;
            case 3: !vazia(pivo->primeiro) ? removevalor_Fila(pivo):printf("Vazio");break;
            case 4: !vazia(pivo->primeiro) ? remover_pilha(pivo):printf("Vazio");break;
            case 5: !vazia(pivo->primeiro) ? limpar_tudo(pivo):printf("Vazio");break;
        }
        getch();
        system("cls");
    }while(op != 0);

    limpar_tudo(pivo);
    free(pivo);
    return 0;
}


pivo *criar_Pivo()
{
    pivo *aux = malloc(sizeof(pivo));
    aux->primeiro = NULL;
    aux->ultimo = NULL;

    return aux;
}

int vazia(lista *lista)
{
    return (lista == NULL);
}

void mostrar_lista(lista *lista,pivo *pivo)
{
    if(lista->prox == pivo->primeiro)
    {
        printf_entra(lista);
        return;
    }else{
        printf_entra(lista);
        mostrar_lista(lista->prox,pivo);
    }
}

void printf_entra(lista *lista)
{
    switch(lista->type)
    {
        case 'c':printf("%c->",lista->ti->carater);break;
        case 's':printf("%s->",lista->ti->text);break;
        case 'i':printf("%i->",lista->ti->num);break;
        case 'f':printf("%f->",lista->ti->numero);break;
    }
 }

void add_lista(pivo *pivo)
{
    lista *nova= criar_lista();

    if(vazia(pivo->primeiro))
    {
        pivo->primeiro = nova;
        pivo->ultimo = nova;
        nova->prox = nova;
        nova->ant = nova;
    }else{
        lista *atual = pivo->primeiro;
        lista *prox = pivo->primeiro->prox;
        do
        {
                atual = prox;
                prox = prox->prox;
        }while(prox != pivo->primeiro);
        nova->ant = atual;
        atual->prox = nova;
        nova->prox = pivo->primeiro;
        pivo->ultimo = nova;
    }

}

lista *criar_lista(int dado)
{
    lista *aux = malloc(sizeof(lista));
    aux->ti = malloc(sizeof(tipo));
    printf("Entre com o tipo:\n c-char\n i-int\n s-string\n f-float\n");
    do{
        scanf("%c",&aux->type);
    }while(aux->type != 'c' && aux->type != 'i' && aux->type != 's' && aux->type != 'f');
    switch(aux->type)
    {
        case 'c':scanf(" %c",&aux->ti->carater);break;
        case 's':scanf(" %[^\n]s",aux->ti->text);break;
        case 'i':scanf("%i",&aux->ti->num);break;
        case 'f':scanf("%f",&aux->ti->numero);break;
    }
    aux->prox = NULL;
    aux->ant = NULL;
    return aux;
}

void removevalor_Fila(pivo *pivo)
{
    if(vazia(pivo->primeiro))
    {
        puts("Lista Vazia\n");
    }
    else
    {
        if(pivo->primeiro == pivo->ultimo)
        {
            lista *aux = pivo->primeiro;
            pivo->primeiro = NULL;
            pivo->ultimo = NULL;
            free(aux);
        }else{
            lista *aux = pivo->primeiro;
            pivo->primeiro = pivo->primeiro->prox;
            pivo->ultimo->prox = pivo->primeiro;
            free(aux);
        }

    }
}


void limpar_tudo(pivo *pivo)
{
    if(pivo->primeiro == NULL)
    {
        printf("Vazio\n");
    }else{
        removevalor_Fila(pivo);
        remover_pilha(pivo);
        limpar_tudo(pivo);
    }
}

void remover_pilha(pivo *pivo)
{
    if(vazia(pivo->primeiro))
    {
        puts("Lista Vazia\n");
    }
    else
    {
        if(pivo->primeiro == pivo->ultimo)
        {
            lista *aux = pivo->primeiro;
            pivo->primeiro = NULL;
            pivo->ultimo = NULL;
            free(aux);
        }else{
            lista *aux = pivo->ultimo;
            pivo->ultimo = pivo->ultimo->ant;
            pivo->ultimo->prox = pivo->primeiro;
            pivo->primeiro->ant = pivo->ultimo;
            free(aux);
        }
    }
}
