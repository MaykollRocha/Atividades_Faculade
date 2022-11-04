/**
  *
  * @author Maykoll Rocha
  * @email <maykoll1412@gmail.com>
  * @date 2022-10-30
  *
**/

#ifndef baixar_h
#define baixar_h
float anteriores_extrato(char *nome);
/*
Esse estruct serve para auxiliar na hora da retirada de dados dos arquivos
*/
typedef struct
{
    char nome_client[20];
    int cod;
    unsigned int idade;
    unsigned int senha;
    float saldo;
    int tipo;
}auxiliar;

banco *baixar_banco(char nome[])
{
    banco *aux = malloc(sizeof(banco));
    strcpy(aux->nome_banco,nome);
    aux->primeiro = NULL;
    aux->prox = NULL;
    return aux;
}


cliente *Baixar_cliente(char nome[],int idade,int senha,int saldo)
{
    cliente *aux = malloc(sizeof(cliente));
    strcpy(aux->nome_client,nome);
    aux->idade = idade;
    aux->senha = senha;
    aux->cod = rand()%10000;
    aux->saldo = anteriores_extrato(aux->nome_client);
    aux->prox = NULL;
    return aux;
}

float anteriores_extrato(char *nome)
{
    char nomebin[20];
    float soma=0;
    strcpy(nomebin,nome);
    strcat(nomebin,".data");
    tirar_extrato a[100];
    FILE *arq1 = abrirArquivo(nomebin,"rb");
    rewind(arq1);
    int c = fgetc(arq1);
    int i = 0;
    if (c!=EOF)
    {
        rewind(arq1);
        while (fread(&a[i],sizeof(tirar_extrato),1,arq1)>0)
        {
            i++;
        }
    }
    for(int j=0;j< i;j++)
    {
        switch(a[j].tipo)
        {
        case 1:soma += a[j].valor;break;
        case 0:soma -= a[j].valor;break;
        }
    }
    fclose(arq1);

    return soma;
}

void baixar_contas(char nome_banco[],pivo *pivo)
{
    banco *novo_banco = baixar_banco(nome_banco);
    char aux[20];
    int i=0;
    auxiliar a[100];
    strcpy(aux,nome_banco);
    strcat(aux,".txt");
    FILE *banc = fopen(aux,"r");
    while(fscanf(banc,"%i;%i;%f;%[^\n]s\n",&a[i].idade,&a[i].senha,&a[i].saldo,&a[i].nome_client)>0)
    {
        cliente *novo = Baixar_cliente(a[i].nome_client,a[i].idade,a[i].senha,a[i].saldo);
        if(novo_banco->primeiro == NULL)
        {
            novo_banco->primeiro=novo;
        }else{
            cliente *ultimo =  novo_banco->primeiro;
            while(ultimo->prox != NULL)
            {
                ultimo = ultimo->prox;
            }
            ultimo->prox = novo;
        }
    }

    if(pivo->primeio == NULL)
    {
        pivo->primeio = novo_banco;
        pivo->ultimo = novo_banco;
    }else{
        pivo->ultimo->prox = novo_banco;
        pivo->ultimo = novo_banco;
    }
    fclose(banc);

    return;
}

void baixar_registros(pivo *pivo)
{
    FILE *arq=fopen("bancos.txt","r");

    char tirarnome[20];
    while(!feof(arq))
    {
        fscanf(arq,"%s",&tirarnome);
        baixar_contas(tirarnome,pivo);
    }

    fclose(arq);
    return ;
}

#endif
