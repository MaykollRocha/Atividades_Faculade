#ifndef CABECA_PILHAEFILA_H
#define CABECA_PILHAEFILA_H

/**
 *
 * @author Maykoll Rocha
 * @email <maykoll.rocha422@academico.ufgd.edu.br>
 * @date  2022-10-10
 *
 */

typedef struct _lista
{
    int dado;
    struct _lista *prox;
    struct _lista *ant;
}lista;

typedef struct
{
    lista *primeiro;
    lista *ultimo;
}pivo;
//DC-Duplamente Encadeada
//SC-Simplesmente Encadeada
//SCC-Simplesmente Encadeada Circular

//Protipação dos menus de cada mapeamento.
void Pilha_Duplamente();
void Fila_Duplamente();
void Pilha_Simplesmente();
void Fila_Simplesmente();
void Fila_Simplesmente_Circular();

//Usadas na maioria das funções.
void mostrar_lista(lista *lista);
pivo *criar_Pivo();
int vazia(lista *lista);
lista *criar_lista(int dado);

// prototipações da DC
void add_lista_DC(pivo *pivo);
void removevalor_DC(pivo *pivo,lista *lista, int valor);
void limpar_tudo_DC(pivo *pivo);

// prototipações da SC
lista *criar_lista_SC(int dado);
void limpar_da_lista_SC(pivo *pivo);
void removevalor_SC(pivo *pivo,int valor);
void limpar_tudo_SC(pivo *pivo);

// prototipações da SCC
void limpar_da_lista_SCC(pivo *pivo);
void removevalor_SCC(pivo *pivo);
void limpar_tudo_SCC(pivo *pivo);
void mostrar_lista_SCC(lista *lista,pivo *pivo);
void add_lista_SCC(pivo *pivo);

// faz a criação do pivo onde .
pivo *criar_Pivo()
{
    pivo *aux = malloc(sizeof(pivo));
    aux->primeiro = NULL;
    aux->ultimo = NULL;

    return aux;
}

//Addcina na lista e faz diferentes entre elas caso seja a primeira.
lista *criar_lista(int dado)
{
    lista *aux = malloc(sizeof(lista));
    aux->dado = dado;
    aux->prox = NULL;
    aux->ant = NULL;
    return aux;
}

int vazia(lista *lista)
{
    return (lista == NULL);
}

//Mostra todos os valores da suplamente encadeada.
void mostrar_lista(lista *lista)
{
    if(lista->prox == NULL)
    {
        printf("%i.\n",lista->dado);
    }else{
        printf("%i->",lista->dado);
        mostrar_lista(lista->prox);
    }
}
//Acima funções da Funções usadas em ambas
//Abaixo funções da Duplamente encadeada

void add_lista_DC(pivo *pivo)
{
    int dado;
    printf("Escreva um numero para entrar na lista: ");
    scanf("%i",&dado);
    lista *nova= criar_lista(dado);

    if(vazia(pivo->primeiro))
    {
        pivo->primeiro = nova;
        pivo->ultimo = nova;
    }else{
        nova->ant = pivo->ultimo;
        pivo->ultimo->prox = nova;
        pivo->ultimo = nova;
    }

}

//Remouve valores da Duplamente encadeada.
void removevalor_DC(pivo *pivo,lista *lista, int valor)
{
    if(lista->dado == valor)
    {
        if(pivo->ultimo ==  pivo->primeiro && lista == pivo->ultimo)
        {
            free(lista);
            pivo->primeiro = NULL;
            pivo->ultimo = NULL;
            return;
        }

        if(lista == pivo->ultimo)
        {
            lista->ant->prox = NULL;
            pivo->ultimo = lista->ant;

        }else if(lista == pivo->primeiro)
        {
            pivo->primeiro = lista->prox;
            lista->prox->ant = NULL;
        }else{
            lista->ant->prox = lista->prox;
            lista->prox->ant = lista->ant;
        }
        free(lista);
    }else{
        if(lista->prox != NULL)
            removevalor_DC(pivo,lista->prox,valor);
        else
            return;
    }
}

//limpa todo meu vetor DC.
void limpar_tudo_DC(pivo *pivo)
{
    if(pivo->primeiro == NULL)
    {
        printf("Vazio\n");
    }else{
        removevalor_DC(pivo,pivo->primeiro,pivo->primeiro->dado);
        limpar_tudo_DC(pivo);
    }
}
//Acima funções da Duplamente encadeada
//Abaixo funções da simplesmente encadeada

void add_lista_SC(pivo *pivo)
{
    int dado;
    printf("Escreva um numero para entrar na lista: ");
    scanf("%i",&dado);
    lista *nova= criar_lista_SC(dado);

    if(vazia(pivo->primeiro))
    {
        pivo->primeiro = nova;
        pivo->ultimo = nova;
    }else{
        pivo->ultimo->prox = nova;
        pivo->ultimo = nova;
    }

}

lista *criar_lista_SC(int dado)
{
    lista *aux = malloc(sizeof(lista));
    aux->dado = dado;
    aux->prox = NULL;
    return aux;
}


void remover_Fila_SE(pivo *pivo)
{
    lista *aux = pivo->primeiro;
    if(pivo->primeiro == pivo->ultimo)
    {
        pivo->ultimo = NULL;
        pivo->primeiro = NULL;
    }else{
        pivo->primeiro = aux->prox;
    }
    free(aux);
    return;
}

void remover_pilha_SE(pivo *pivo)
{
    lista *aux = pivo->primeiro;

    if(pivo->primeiro == pivo->ultimo)
    {
        pivo->ultimo = NULL;
        pivo->primeiro = NULL;
    }else{
        while(aux->prox != pivo->ultimo)//vejo qual é o anteriro ao ultimo da fila.
            aux = aux->prox;

        pivo->ultimo = aux;
        aux = aux->prox;// meu aux esta apontando para o proximo antes de perder esse fio para poder liberar a malloc mais afrente
        pivo->ultimo->prox = NULL;//faço meu novo ultimo apontar para nada
    }
    free(aux);

    return;
}

void limpar_tudo_SC(pivo *pivo)
{
    if(pivo->primeiro == NULL)
    {
        printf("Vazio\n");
    }else{
        remover_pilha_SE(pivo);
        remover_Fila_SE(pivo);
        limpar_tudo_SC(pivo);
    }
}
//Acima funções da simplesmente encadeada
//Abaixo funções da simplesmente encadeada Circular

void mostrar_lista_SCC(lista *lista,pivo *pivo)
{
    if(lista->prox == pivo->primeiro)
    {
        printf("%i.\n",lista->dado);
    }else{
        printf("%i->",lista->dado);
        mostrar_lista_SCC(lista->prox,pivo);
    }
}

void add_lista_SCC(pivo *pivo)
{
    int dado;
    printf("Escreva um numero para entrar na lista: ");
    scanf("%i",&dado);
    lista *nova= criar_lista_SC(dado);

    if(vazia(pivo->primeiro))
    {
        pivo->primeiro = nova;
        nova->prox = nova;
    }else{
        lista *atual = pivo->primeiro;
        lista *prox = pivo->primeiro->prox;
        do
        {
                atual = prox;
                prox = prox->prox;
        }while(prox != pivo->primeiro);
        atual->prox = nova;
        nova->prox = pivo->primeiro;
    }

}

/*
Como era uma fila cirular
so entrei com o pivo e fiz as trocas nescessarias.
*/

void removevalor_SCC(pivo *pivo)
{
    if(vazia(pivo->primeiro))
    {
        puts("Lista Vazia\n");
    }
    else
    {   lista *atual = pivo->primeiro;
        lista *prox = pivo->primeiro->prox;
        if(atual == prox)
        {
            pivo->ultimo = NULL;
            pivo->primeiro = NULL;
        }else{
            do
            {
                atual = prox;
                prox = prox->prox;
            }while(prox != pivo->primeiro);
            pivo->primeiro = prox->prox;
            atual->prox = pivo->primeiro;
            free(prox);
        }
    }
}


void limpar_tudo_SCC(pivo *pivo)
{
    if(pivo->primeiro == NULL)
    {
        printf("Vazio\n");
    }else{
        removevalor_SCC(pivo);
        limpar_tudo_SCC(pivo);
    }
}
//Acima funções da simplesmente encadeada Circular
#endif
