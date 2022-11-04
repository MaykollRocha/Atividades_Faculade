/**
  *
  * @author Maykoll Rocha
  * @email <maykoll1412@gmail.com>
  * @date 2022-10-30
  *
**/

#ifndef structs_h
#define structs_h

/*
OS structs usados no corpo principal da contas.
*/

typedef struct _cliente
{
    char nome_client[30];
    int cod;
    unsigned int idade;
    unsigned int senha;
    float saldo;
    struct _cliente *prox;//a ligação é para facilitar as coisas.
}cliente;


typedef struct _banco
{
    char nome_banco[20];
    struct _cliente *primeiro;
    struct _banco *prox;
}banco;

typedef struct _pivo
{
    struct _banco *primeio;
    struct _banco *ultimo;
}pivo;

typedef struct
{
    float valor;
    int tipo;
}tirar_extrato;

// uma função para arrumar os nomes.
void arrumar_nome(char nome[])
{
    int tam = strlen(nome);
    for(int i=0;i<tam;i++)
    {
        if(i==0)
        {
            nome[i]=toupper(nome[i]);
        }else if(nome[i]==' ')
        {
            i+=1;
            nome[i]=toupper(nome[i]);
        }else{
            nome[i]=tolower(nome[i]);
        }
    }

    return;
}

FILE *abrirArquivo(char *nome,char *tipo)
{
    FILE *arq = fopen(nome,tipo);

    if(!arq)
    {
        printf("ERRO arquivo não exite\n");
        exit(1);
    }

    return arq;
}

//prototipações
void printf_contas(banco *banco);
void printf_client(cliente *clin);
void limpar_tudo(pivo *pivo);

//Funções de criação em tempo de compilação
cliente *criar_cliente(char nome_banco[])
{
    cliente *aux = malloc(sizeof(cliente));
    printf("Nome do cliente: ");
    scanf("%[^\n]s",aux->nome_client);
    arrumar_nome(aux->nome_client);
    printf("Entre com sua idade: ");
    do{
            scanf("%i",&aux->idade);
    }while(aux->idade < 17);
    printf("Entre com a senha de 4 digitos:");
    scanf("%i",&aux->senha);
    aux->cod = rand()%10000;
    printf("Seu codigo de 4 digitos aleatorio %i\n",aux->cod);
    aux->saldo = 0;
    aux->prox = NULL;
    char nometxt[20],nomebin[20];
    strcpy(nometxt,nome_banco);
    strcpy(nomebin,aux->nome_client);
    strcat(nometxt,".txt");
    strcat(nomebin,".data");

    FILE *arq1 = abrirArquivo(nomebin,"wb");
    fclose(arq1);

    FILE *arq = fopen(nometxt,"a+");
    fprintf(arq,"%i;%i;%f;%s\n",aux->idade,aux->senha,aux->saldo,aux->nome_client);
    fclose(arq);

    return aux;
}


banco *criar_banco()
{
    banco *aux = malloc(sizeof(banco));
    printf("Nome do banco: ");
    scanf("%[^\n]s",aux->nome_banco);
    arrumar_nome(aux->nome_banco);
    aux->primeiro = NULL;
    aux->prox = NULL;

    char txt[20];
    strcpy(txt,aux->nome_banco);
    strcat(txt,".txt");
    FILE *arq= fopen(txt,"w");
    fclose(arq);
    FILE *arq1 = fopen("bancos.txt","a+");
    fprintf(arq1,"\n%s",aux->nome_banco);
    fclose(arq1);

    return aux;
}

pivo *criar_pivo()
{
    pivo *aux = malloc(sizeof(pivo));
    aux->primeio = NULL;
    aux->ultimo = NULL;
}

#endif
