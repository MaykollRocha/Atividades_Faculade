#ifndef CABECA_H
#define CABECA_H

/**
 *
 * @author Maykoll Rocha
 * @email <maykoll.rocha422@academico.ufgd.edu.br>
 * @date  2022-10-10
 *
 */


void main_SE();//SE - Simplesmente Encadeada;
void main_DE();//DE - Duplamente Encadeada;
int main_SEC();//SEC- Simplesmente Encadeada Circular;

/*
 Algumas parte abaixo são usadas para os 3 tipos de encadeamaento porem não usa algumas
 funções dependendo.EX: no Simplesmente encadeada tem um ant porem quando trabalho com ela essa função
 não é usada em nenhuma parte do processo so o proximo.E na SEC tem um pivo ultimo porem so usamos o privo primeiro.
*/
typedef struct _lista
{
    int dado;
    struct _lista *prox;
    struct _lista *ant;
}Lista;

typedef struct _pivo
{
    Lista *primeiro;
    Lista *ultimo;
}Pivo;

int vazia(Pivo *pivo)
{
    return (pivo->primeiro == NULL);
}

Pivo *criarPivo()
{
    Pivo *aux = malloc(sizeof(Pivo));
    aux->primeiro = NULL;
    aux->ultimo = NULL;
    return aux;
}

Lista *criarLista(int num)
{
    Lista *aux = malloc(sizeof(Lista));
    aux->dado = num;
    aux->prox = NULL;
    aux->ant = NULL;
}

void mostrar(Pivo *pivo)
{
    Lista *aux=pivo->primeiro;

    while(aux->prox != NULL)
    {
        printf("%i->",aux->dado);
        aux = aux->prox;
    }
    printf("%i.",aux->dado);
}
//Até aqui são funções usadas em todo o codigo para os tres com execessão do mostrar e do Criar lista.

/*
no final de cada função abaixo mostra para qual tipo de encadeamento ta sendo usanda utilizando as
letras maiuscular DE,SE e SEC(que são citadas no início de codigo.
*/

void addicinar_DE(Pivo *pivo)
{
    int num;
    printf("Entre com um Número: ");
    scanf("%i",&num);
    Lista *novo = criarLista(num);

    if(vazia(pivo))//Se tiver vazia ele coloca o novo nos dois.
    {
        pivo->primeiro = novo;
        pivo->ultimo = novo;
    }else{
        //Coloca sempre no fim da lista usa o pivo ultimo como suporte.
        pivo->ultimo->prox = novo;
        novo->ant = pivo->ultimo;
        pivo->ultimo = novo;

    }
}



void remover_Fila_DE(Pivo *pivo)
{
    Lista *aux = pivo->primeiro;//Pega o primeiro valor da fila para poder retirar como fila.

    if(pivo->primeiro == pivo->ultimo)//Verifica se tem so um valor
    {
        pivo->primeiro = NULL;
        pivo->ultimo = NULL;
    }else{
        pivo->primeiro = aux->prox;
        pivo->primeiro->ant = NULL;
    }
    free(aux);//Libera a malloc criada.
    return;
}

void remover_pilha_DE(Pivo *pivo)
{
    Lista *aux = pivo->ultimo;//Pega o ultimo valor da pilha para poder retirar como pilha.

    if(pivo->primeiro == pivo->ultimo)//Verifica se tem so um valor.
    {
        pivo->primeiro = NULL;
        pivo->ultimo = NULL;
    }else{
        pivo->ultimo = aux->ant;
        pivo->ultimo->prox = NULL;
    }
    free(aux);//Libera a malloc criada.
    return;
}

void remover_DE(Pivo *pivo)
{
    //Função extra pra tirar qualquer valor.
    int ret;
    printf("Entre com o número que quer retirar:");
    scanf("%i",&ret);
    Lista *aux = pivo->primeiro;
    while(aux->dado != ret)//Verifica se o valor existe
    {
        aux = aux->prox;
        if(aux == NULL)//Se for NULL esta no final da fila ai ele retorna que não encontrou nada
        {
           printf("Não encontrado");
           return;
        }
    }

    if(aux == pivo->primeiro)//Checa se ele é o primeiro
    {
        remover_Fila_DE(pivo);
    }else if(aux == pivo->ultimo)//Checa se ele é o ultimo
    {
        remover_pilha_DE(pivo);
    }else{
        aux->ant->prox = aux->prox;//retira ele e concta o seu proximo no seu anterior
        aux->prox->ant = aux->ant;// e seu anterior no seu proximo.para não perder os fios.
        free(aux);
    }
    return;
}

void  limpar_DE(Pivo *pivo)
{
    if(vazia(pivo))
    {
        printf("Esvaziado.\n");
        return;
    }else{
        //faz duas remoções por vez como pilha e como fila para agilizar.
        remover_Fila_DE(pivo);
        remover_pilha_DE(pivo);
        limpar_DE(pivo);
    }

}
//todas as funções acima é para duplamente encadeada.

//na simplesmente encadeada não usa o struct de *ant porem poe motivos de agilizar o codigo ele é criado como NULL em todos.

void addicinar_SE(Pivo *pivo)
{
    int num;
    printf("Entre com um Número: ");
    scanf("%i",&num);
    Lista *novo = criarLista(num);

    if(pivo->primeiro == NULL)
    {
        pivo->primeiro = novo;
        pivo->ultimo = novo;
    }else{
        pivo->ultimo->prox = novo;
        pivo->ultimo = novo;
    }
}

void remover_Fila_SE(Pivo *pivo)
{
    Lista *aux = pivo->primeiro;
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

void remover_pilha_SE(Pivo *pivo)
{
    Lista *aux = pivo->primeiro;

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

void remover_SE(Pivo *pivo)
{
    //Remove valores específicos.
    int ret;
    printf("Entre com o número que quer retirar:");
    scanf("%i",&ret);
    Lista *aux = pivo->primeiro;
    Lista *ant = NULL;
    while(aux->dado != ret)
    {
        ant = aux;
        aux = aux->prox;
        if(aux == NULL)
        {
           printf("Não encontrado");
           return;
        }
    }

    if(aux == pivo->primeiro)
    {
        remover_Fila_SE(pivo);
    }else if(aux == pivo->ultimo)
    {
        remover_pilha_SE(pivo);
    }else{
        ant->prox = aux->prox;
        free(aux);
    }

    return;
}

void  limpar_SE(Pivo *pivo)
{
    if(vazia(pivo))
    {
        printf("Esvaziado.\n");
        return;
    }else{
        remover_Fila_SE(pivo);
        remover_pilha_SE(pivo);
        limpar_SE(pivo);
    }

}
//Todas as funções acima é da simplesmente encadeada.

// Aqui são todas das SEC.
//Ela não usa do Pivo ultimo nem da lista ant porem ela tem um NULL em ambas.

void mostrar_lista_SEC(Lista *lista,Pivo *pivo)
{
    if(lista->prox == pivo->primeiro)
    {
        printf("%i.",lista->dado);
        return;
    }else{
        printf("%i->",lista->dado);
        mostrar_lista_SEC(lista->prox,pivo);
    }
}

Lista *criar_lista_SEC()
{
    Lista *aux = malloc(sizeof(Lista));
    printf("Que numero quer colocar: ");
    scanf("%i",&aux->dado);
    aux->prox = NULL;
    return aux;
}

void add_lista_SEC(Pivo *pivo)
{
    Lista *nova= criar_lista_SEC();

    if(vazia(pivo))
    {
        pivo->primeiro = nova;
        nova->prox = nova;
    }else{
        Lista *atual = pivo->primeiro;
        Lista *prox = pivo->primeiro->prox;
        do
        {
                atual = prox;
                prox = prox->prox;
        }while(prox != pivo->primeiro);
        atual->prox = nova;
        nova->prox = pivo->primeiro;
    }
}

void removevalor_SEC(Pivo *pivo)
{
    if(vazia(pivo))
    {
        printf("Lista Vazia\n");
    }
    else
    {
        Lista *atual = pivo->primeiro;
        Lista *prox = pivo->primeiro->prox;
        if(atual == prox)
        {
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

void limpar_tudo_SEC(Pivo *pivo)
{
    if(pivo->primeiro == NULL)
    {
        printf("Vazio\n");
    }else{
        removevalor_SEC(pivo);
        limpar_tudo_SEC(pivo);
    }
}

#endif
