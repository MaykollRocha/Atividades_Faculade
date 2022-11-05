#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Pastas
{
    char nome_pasta[20];
    char name_arq[10];
    struct _Pastas *SubPasta;
    struct _Pastas *prox;
    struct _Pastas *ant;
}Pasta;

void compret_comand(Pasta *past);

Pasta *criar_pasta(char nome_pasta[],char nome_arq[])
{
    Pasta *aux = malloc(sizeof(Pasta));
    strcpy(aux->nome_pasta,nome_pasta);
    strcpy(aux->name_arq,nome_arq);
    aux->SubPasta = NULL;
    aux->prox = NULL;
    aux->ant = NULL;

    return aux;
}
void ler_txt(char txt[])
{
    FILE *arq = fopen(txt,"r");

    if(!arq)
    {
        printf("Arquivo não existe");
        return;
    }


    char c;

    while((c = getc(arq))!= EOF)
    {
        printf("%c",c);
    }
    printf("\n");
    fclose(arq);
    return;
}

void mk(char name_pasta[],Pasta *past)
{
    Pasta *nova =criar_pasta(name_pasta,"NULL");

    if(past->SubPasta == NULL)
    {
        past->SubPasta = nova;
        nova->ant = past;
    }else{
        Pasta *subpast = past->SubPasta;

        while(subpast->prox != NULL)
        {
            subpast = subpast->prox;
        }

        subpast->prox = nova;
        nova->ant = subpast;
    }
}

void ls(Pasta *past)
{
    strcmp(past->name_arq,"NULL") ? printf("%s\n",past->name_arq) : printf("Não tem arquivo\n");
    Pasta *subpast = past->SubPasta;
    while(subpast != NULL)
    {
        printf("Subpasta: %s\n",subpast->nome_pasta);
        strcmp(subpast->name_arq,"NULL") ? printf("%s\n",past->name_arq) : printf("Nao tem arquivo\n");
        printf("\n");
        subpast = subpast->prox;
    }

    return;
}

void cd(char mudapasta[],Pasta *past)
{
    Pasta *subpastas = past->SubPasta;

    while(subpastas != NULL)
    {
        if(strcmp(mudapasta,subpastas->nome_pasta)==0)
        {
            compret_comand(subpastas);
            return;
        }
    }

}

void rm(char nome[],Pasta *past)
{
    Pasta *subpast = past->SubPasta;
    if(strcmp(past->nome_pasta,nome)==0)
    {
        if(strcmp(past->name_arq,"NULL")!=0)
        {
            int op;
            printf("Tem certeza que quer excluir? 1.sim 2.Não");
            scanf("%i",&op);
            if(op==2)
                return;
        }
        Pasta *aux = past;
        past = subpast;
        past->ant = NULL;
        free(aux);
    }else{
        while(strcmp(subpast->nome_pasta,nome) != 0)
        {
            subpast = subpast->prox;
            if(subpast == NULL)
            {
                printf("Não existe essa pasta\n");
                return;
            }
        }
            if(strcmp(subpast->name_arq,"NULL")!=0)
            {
                int op;
                printf("Tem certeza que quer excluir? 1.sim 2.Não");
                scanf("%i",&op);
                if(op==2)
                    return;
            }


            if(subpast->prox == NULL)
            {
                if(subpast->ant == past)
                {
                    past->SubPasta = NULL;
                }else{
                    subpast->ant->prox = NULL;
                }
            }else{
                if(subpast->ant == past){
                    past->SubPasta = subpast->prox;
                    subpast->prox->ant = past;
                }else{
                    subpast->ant->prox = subpast->prox;
                    subpast->prox->ant = subpast->ant;
                }


            }
            free(subpast);
    }
}

void novo(char nome_arq[],Pasta *past)
{
    FILE *arq=fopen(nome_arq,"w");
    fclose(arq);
    strcpy(past->name_arq,nome_arq);

    return;
}

void add_conteu(char nome_arq[])
{
    FILE *arq = fopen(nome_arq,"r");

    if(!arq)
    {
        printf("Arquivo não existe");
        return;
    }else{
        fclose(arq);
    }
    FILE *arq1=fopen(nome_arq,"a");

    char txt[256];
    fflush(stdin);
    scanf("%[^\n]s",txt);

    fprintf(arq1,"%s",txt);

    fclose(arq1);
}

void compret_comand(Pasta *past)
{
    char comand[10],loc[20];
    while(1)
    {
        fflush(stdin);
        printf(">> %s/",past->nome_pasta);
        scanf("%s%[^\n]s",comand,loc);

        if(strcmp(comand,"ls")==0)
        {
            ls(past);
        }


        if(strcmp(comand,"cd")==0)
            cd(loc,past);

        if(strcmp(comand,"cd..")==0)
        {
           if(strcmp(past->nome_pasta,"root")!=0)
                return;
           else
                printf("Não pode voltar ja esta no root.\n");
        }


        if(strcmp(comand,"mk")==0)
            mk(loc,past);


        if(strcmp(comand,"rm")==0)
            rm(loc,past);

        if(strcmp(comand,"new")==0)
            novo(loc,past);

        if(strcmp(comand,"del")==0)
            if(strcmp(past->name_arq,loc) == 0)
                strcpy(past->name_arq,"NULL");
            else
                printf("Não tem esse aquivo na pasta\n");

        if(strcmp(comand,"edit")==0)
            add_conteu(loc);

        if(strcmp(comand,"view")==0)
            ler_txt(loc);

    }

    return;
}

int main()
{
    Pasta *root = criar_pasta("root","File 1.txt");
    compret_comand(root);

    system("cls");
    return 1;
}
