/**
  *
  * @author Maykoll Rocha
  * @email <maykoll1412@gmail.com>
  * @date 2022-10-30
  *
**/

#ifndef login_clientes_h
#define login_clientes_h

void extrato(char *nome)
{
    char nomebin[20];
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

    printf("Extrato\n_____________\n");
    for(int j=0;j< i;j++)
    {
        switch(a[j].tipo)
        {
        case 1:printf("Deposito de %0.2f\n",a[j].valor);break;
        case 0:printf("Saque: de %0.2f\n",a[j].valor);break;
        }
    }
    fclose(arq1);
}

void deposito(cliente *cliente,float valor)
{
    tirar_extrato a;
    char nomebin[20];
    int i=0;
    strcpy(nomebin,cliente->nome_client);
    strcat(nomebin,".data");
    a.tipo=1;
    a.valor = valor;
    cliente->saldo += a.valor;
    FILE *arq1 = abrirArquivo(nomebin,"ab");
    if(fwrite(&a,sizeof(tirar_extrato),1,arq1)==0)
    {
        printf("erro\n");
    }
    fclose(arq1);
}

void sacar(cliente *cliente,float valor)
{
    tirar_extrato a;
    char nomebin[20];
    int i=0;
    strcpy(nomebin,cliente->nome_client);
    strcat(nomebin,".data");
    a.tipo=0;// tipo para retirada é 0 e para adicinar 1.
    a.valor = valor;
    cliente->saldo -= a.valor;
    FILE *arq1 = abrirArquivo(nomebin,"ab");
    if(fwrite(&a,sizeof(tirar_extrato),1,arq1)==0)
    {
        printf("erro\n");
    }
    fclose(arq1);
}

void transferencia(cliente *client,pivo *pivo,banco *banc)
{
    unsigned int op;
    char nome_banco[20];
    printf("É do mesmo banco ?1.sim 0.não");
    do{
        scanf("%i",&op);
    }while(op>1);

    cliente *aux = banc->primeiro;
    switch(op)
    {
    case 1://Mesmo banco
        if(client->prox == NULL)
        {
            printf("Novo é o unico cliente.\n");
        }else{
            char nome[20];
            printf("Entre com o nome do cliente: ");
            fflush(stdin);
            scanf("%[^\n]s",&nome);
            arrumar_nome(nome);
            while(aux != NULL)
            {
                if(strcmp(aux->nome_client,nome)==0)
                {
                    float valor;
                    printf("Cliente da mesma agencia não cobra acrescimo.\nDigite o valor do deposito: ");
                    do{
                        scanf("%f",&valor);
                    }while(valor > client->saldo);
                    deposito(aux,valor);
                    sacar(client,valor);
                    return;
                }else{
                    aux = aux->prox;
                }
            }
            if(aux == NULL)
            {
                printf("Cliente não existe na sua compania.\n");
            }
        }
        break;

    case 0://Outro banco
        printf("Entre com o nome do banco: ");
        fflush(stdin);
        scanf("%[^\n]s",&nome_banco);
        arrumar_nome(nome_banco);
        banco *aux_banc=banc->prox;
        while(aux_banc != NULL)
        {
                if(strcmp(aux_banc->nome_banco,nome_banco)==0)
                {
                if(client->prox == NULL)
                {
                printf("Novo é o unico cliente.\n");
                }else{
                char nome[20];
                printf("Entre com o nome do cliente: ");
                fflush(stdin);
                scanf("%[^\n]s",&nome);
                arrumar_nome(nome);
                cliente *aux_cliente = aux_banc->primeiro;
                while(aux_cliente != NULL)
                {
                    if(strcmp(aux_cliente->nome_client,nome)==0)
                    {
                        float valor;
                        printf("Cliente da mesma agencia cobra acrescimo de 2 reais.\nDigite o valor do deposito: ");
                        do{
                            scanf("%f",&valor);
                            valor +=2;
                        }while(valor > client->saldo);
                        deposito(aux_cliente,valor-2);
                        sacar(client,valor);
                        return;
                    }else{
                        aux_cliente = aux_cliente->prox;
                    }
                }
                if(aux == NULL)
                {
                    printf("Cliente não existe na sua compania.\n");
                }
                }
            }else{
                aux_banc = aux_banc->prox;
            }
        }
    }
}

void apagar_conta(banco *banc,cliente *client)
{
    //Apaga o extrato do cliente.
    char nomebin[20];
    strcpy(nomebin,client->nome_client);
    strcat(nomebin,".data");
    remove(nomebin);

    //Cria um novo aquivo de banco sem a pessoa retirada.
    char aux[20];
    int i=0;
    auxiliar a[100];
    strcpy(aux,banc->nome_banco);
    strcat(aux,".txt");
    FILE *arq = fopen(aux,"r");
    FILE *repositorio = fopen("repo.txt","w");
    while(fscanf(arq,"%i;%i;%f;%[^\n]s\n",&a[i].idade,&a[i].senha,&a[i].saldo,&a[i].nome_client)>0)
    {
        if(strcmp(a[i].nome_client,client->nome_client)!=0)
        {
            fprintf(repositorio,"%i;%i;%f;%s\n",a[i].idade,a[i].senha,a[i].saldo,a[i].nome_client);
        }
    }
    fclose(arq);
    remove(aux);
    fclose(repositorio);
    rename("repo.txt",aux);

    if(banc->primeiro->prox == NULL )
    {
        banc->primeiro = NULL;
    }else{

        cliente *aux_cliet = banc->primeiro;
        while(aux_cliet->prox != client)
        {
            aux_cliet =aux_cliet->prox;
        }
        aux_cliet->prox = client->prox;
    }


    free(client);
    return;
}

void longin_sucess(pivo *pivo,cliente *cliente,banco *banco)
{
    unsigned int op;
    float valor;
    do
    {
        printf_client(cliente);
        printf("--BEM VINDO--\n 1.deposito;\n 2.saque;\n 3.Extrato;\n 4.tranferencia;\n 5.Fechar Conta;\n 0.voltar.\n",cliente->nome_client);
        do{
            scanf("%i",&op);
        }while(op>5);
        switch(op)
        {
        case 1:
            printf("Entre com o valor a Depositar: ");
            scanf("%f",&valor);
            deposito(cliente,valor);
            break;
        case 2:
            if(cliente->saldo != 0)
            {
                printf("Entre com o valor a ser sacado: ");
                do{
                   scanf("%f",&valor);
                }while(valor > cliente->saldo);
                sacar(cliente,valor);
            }else{
                printf("Sem saldo");
            }
            break;
        case 3:
            extrato(cliente->nome_client);
            break;
        case 4:
            transferencia(cliente,pivo,banco);
            break;
        case 5:
            apagar_conta(banco,cliente);
            return;
        }
        getch();
        system("cls");
    }while(op != 0);

}

void login(banco *banco,pivo *pivo)
{
    unsigned int op;
    char nome[30];
    printf("Entre com o nome do cliente: ");
    fflush(stdin);
    scanf("%[^\n]s",&nome);
    arrumar_nome(nome);
    cliente *aux = banco->primeiro;

    while(aux != NULL)
    {
        if(strcmp(nome,aux->nome_client) == 0)
        {
            int senha;
            printf("Entre com a senha: ");
            scanf("%i",&senha);
            if(senha == aux->senha)
            {
                longin_sucess(pivo,aux,banco);
                return;
            }else{
                printf("Senha Errada.\n");
                return;
            }
        }else{
            aux = aux->prox;
        }
    }
}

#endif
