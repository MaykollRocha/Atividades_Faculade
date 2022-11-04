/**
  *
  * @author Maykoll Rocha
  * @email <maykoll1412@gmail.com>
  * @date 2022-10-30
  *
**/

#ifndef area_banco_h
#define area_banco_h

//Funções com o banco.
void registrar_banco(pivo*pivo)
{
    fflush(stdin);
    banco *novo = criar_banco();

    if(pivo->ultimo == NULL)
    {
        pivo->primeio = novo;
        pivo->ultimo = novo;
    }else{
        banco *ult = pivo->ultimo;
        ult->prox = novo;
        pivo->ultimo = novo;
    }

    return;
}

void novo_cliente(banco *banco)
{
    cliente *novo = criar_cliente(banco->nome_banco);

    if(banco->primeiro == NULL)
    {
        banco->primeiro = novo;
    }else{
        cliente *ultimo = banco->primeiro;

        while(ultimo->prox != NULL)
        {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo;
    }
    return;
}

void fechar_banco(banco *banc,pivo *pivo)
{
    //apgar o arquivo do banco.
    char aux[20];
    int t=0;//auxiliar pra fazer uma leve troca na hora de por os arquivos no repositorio.
    strcpy(aux,banc->nome_banco);
    strcat(aux,".txt");
    remove(aux);

    //Arrumar o txt.
    FILE *arq=fopen("bancos.txt","r");
    FILE *repo=fopen("repo.txt","w");
    char tirarnome[20];
    while(!feof(arq))
    {
        fscanf(arq,"%s",&tirarnome);
        if(strcmp(tirarnome,banc->nome_banco)!=0)
        {
           t==0? fprintf(repo,"%s",&tirarnome):fprintf(repo,"\n%s",&tirarnome);
           t=1;
        }
    }

    fclose(arq);
    fclose(repo);
    remove("bancos.txt");
    rename("repo.txt","bancos.txt");

    if(pivo->primeio->prox == NULL)
    {
        pivo->primeio=NULL;
        pivo->ultimo=NULL;
    }else{
        banco *aux_banc=pivo->primeio;

        if(pivo->primeio == banc)
        {
            pivo->primeio = banc->prox;
        }else{
            while(aux_banc->prox != banc)
                aux_banc = aux_banc->prox;

            aux_banc->prox = banc->prox;
            if(pivo->ultimo == banc)
                pivo->ultimo = aux_banc;
        }

    }

    cliente *prim=banc->primeiro;
    while(prim != NULL)
    {
        cliente *aux = prim;
        prim = prim->prox;
        free(aux);
    }

    free(banc);
    return;
}

void Menu_banco(pivo *pivo)
{
    char bancos[30];
    printf("Nome do banco: ");
    scanf("%s",&bancos);
    arrumar_nome(bancos);
    banco *banco = pivo->primeio;
    while(strcmp(bancos,banco->nome_banco) != 0)
    {
        banco = banco->prox;
        if(banco==NULL)
        {
            printf("Banco não encontrado.\n");
            return;
        }
    }
    system("cls");
    unsigned int op;
    do{
        printf("--MENU BANCO %s--\n 1.Criar Cliente;\n 2.Entrar em conta;\n 3.Fechar Banco;\n 0.Voltar menu.\n ");
        do{
            scanf("%i",&op);
        }while(op >3);

        switch(op)
        {
        case 1:
            fflush(stdin);
            novo_cliente(banco);
            break;
        case 2:
            banco->primeiro!=NULL ? login(banco,pivo): printf("Não tem contas");
            break;
        case 3:
            fechar_banco(banco,pivo);
            return;
        }
        getch();
        system("cls");
    }while(op!=0);


}


#endif
