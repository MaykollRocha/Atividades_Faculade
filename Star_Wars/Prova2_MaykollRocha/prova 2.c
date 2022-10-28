#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
  *
  * @nome: Maykoll Rocha
  * @email: <maykoll1412@gmail.com>
  * @data: 25/10/2022
  *
  **/



//OBS IMPORTANTE esse struct sera de auxiliar para eu conseguir colocar nos meus structs
typedef struct{
    char nome[35];
    int codEstrela;
    float temperatura;
    int peso;
    float distDoAnterior;
    int tipoCorpo;
    //Planeta
    int temVida;
    int temAtmosfera;
    float percOxigenio;
    float percToxica;
    //PlanetaAnao
    int formato;
    float velocRotacao;
    //Asteroide
    int quantMinerios;
    float velocidade;
    //Satelite
    float temperInterna;
    float rotacao;
}CORPOCELESTE;

//Struct da estrutura que mais uso
typedef struct _asteroid
{
    int quantMinerios;
    float velocidade;
}asteroid;

typedef struct _planetaAnao
{
    int format;
    float velociade;
}planetaAnao;

typedef struct _satelite
{
    float tempeInterna;
    float velocidade;
}satelite;

typedef struct _planeta
{
    int temVida;
    int temAtmosfera;
    float percOxigeneio;
    float percToxica;
}planeta;

typedef struct _corpoCeleste
{
    char nome[30];
    int codEstrela;
    float temperatura;
    int peso;
    float distanciaDoAnterior;
    struct _corpoCeleste *prox;
    int tipoCorpo;
    union _type
    {
        planeta *planet;
        planetaAnao *planetaA;
        satelite *sat;
        asteroid *ast;
    }type;
}CorpoCeleste;

typedef struct _Estrela
{
    char nome[30];
    int numCorpos;
    float fatordedobra;
    int codEstrelas;
    struct _corpoCeleste *lista;
    struct _Estrela *prox;
}Estrela;

typedef struct _galx
{
    char nome[30];
    int numEstrelas;
    struct _Estrela *incio;
    struct _Estrela *limiteAtual;
}Galaxia;

typedef struct _lista
{
    CorpoCeleste *atual;
    struct _lista *prox;
    struct _lista *ant;
}Lista;

typedef struct _pivo
{
    Lista *primeiro;
    Lista *ultimo;
}Pivo;

void print_corp(CorpoCeleste *corpo)
{
                printf("\nnome: %s temperatura: %f peso: %i  distancia do planta anterior: %f Codigo da estrela: %i\n",corpo->nome,corpo->temperatura,corpo->peso,corpo->distanciaDoAnterior,corpo->codEstrela);
                switch(corpo->tipoCorpo)
                {
                case 4:
                    printf("Ox:%f Tox:%f vida: %i atm: %i \n",corpo->type.planet->percOxigeneio,corpo->type.planet->percToxica,corpo->type.planet->temVida,corpo->type.planet->temAtmosfera);
                    break;
                case 3:
                    printf("Format:%i veloc: %f \n",corpo->type.planetaA->format,corpo->type.planetaA->velociade);break;
                case 2:
                    printf("quant:%i veloc: %f \n",corpo->type.ast->quantMinerios,corpo->type.ast->velocidade);break;
                case 1:
                    printf(" veloc: %f temp: %f \n",corpo->type.sat->velocidade,corpo->type.sat->tempeInterna);break;
                }
}


void proc_peso(int X,CorpoCeleste *atual)
{
    if(atual->peso <= X)
    {
        print_corp(atual);
    }

    if(atual->prox == NULL)
    {
        return;
    }else{
        return proc_peso(X,atual->prox);
    }
}

void procuar_peso(int X,Estrela *atual)
{
    if(atual->prox == NULL)
    {
        if(atual->numCorpos > 0)
        proc_peso(X,atual->lista);
        return;
    }else{
        if(atual->numCorpos > 0)
            proc_peso(X,atual->lista);
        return procuar_peso(X,atual->prox);
    }


}

void prinrf_fila(Pivo *pivo,Galaxia *glax)
{
    Lista *atual= pivo->primeiro;
    do
    {
        Estrela *atual_star = glax->incio;
        while(atual_star->prox != NULL)
        {
            if(atual_star->numCorpos >0)
                if(atual->atual->codEstrela == atual_star->codEstrelas)
                {
                    printf("Nome da estrela que tem vida: %s\n",atual_star->nome);
                    break;
                }
            atual_star = atual_star->prox;
        }
        atual = atual->prox;
    }while(atual != pivo->ultimo);
    if(pivo->primeiro != pivo->primeiro)
    {
        Estrela *atual_star = glax->incio;
        while(atual_star->prox != NULL)
        {
            if(atual_star->numCorpos >0)
                if(atual->atual->codEstrela == atual_star->codEstrelas)
                {
                    printf("Nome da estrela que tem vida: %s\n",atual_star->nome);
                    break;
                }
            atual_star = atual_star->prox;
        }

        if(atual_star->prox == NULL){
            if(atual_star->numCorpos >0)
                if(atual->atual->codEstrela == atual_star->codEstrelas)
                {
                    printf("Nome da estrela que tem vida: %s\n",atual_star->nome);
                }
        }
    }

    return;

}

void tempcorpo(float x,float y,CorpoCeleste *atual)
{
    if(atual->temperatura > x && atual->temperatura < y)
    {
        print_corp(atual);
    }

    if(atual->prox == NULL)
    {
        return;
    }else{
        return tempcorpo(x,y,atual->prox);
    }
}

void temparatura(float x,float y,Estrela *atual)
{
    if(atual->prox == NULL)
    {
        if(atual->numCorpos > 0)
            tempcorpo(x,y,atual->lista);
        return;
    }else{
        if(atual->numCorpos > 0)
            tempcorpo(x,y,atual->lista);
        return temparatura(x,y,atual->prox);
    }


}


void printf_pivo(Pivo *pivo)
{
    Lista *atual= pivo->ultimo;
    do
    {
        print_corp(atual->atual);
        atual = atual->ant;
    }while(atual != pivo->primeiro);
    if(pivo->primeiro != pivo->ultimo)
        print_corp(atual->atual);
    return;
}

Lista *criar_lista_SEC(CorpoCeleste *a)
{
    Lista *aux = malloc(sizeof(Lista));
    aux->atual = a;
    aux->prox = NULL;
    aux->ant = NULL;
    return aux;
}

int vazia(Pivo *pivo)
{
    return (pivo->primeiro == NULL);
}

void lista(Pivo *pivo,CorpoCeleste *a)
{
    Lista *novo= criar_lista_SEC(a);

    if(vazia(pivo))//Se tiver vazia ele coloca o novo nos dois.
    {
        pivo->primeiro = novo;
        pivo->ultimo = novo;
        novo->ant = novo;
        novo->prox = novo;
    }else{
        //Coloca sempre no fim da lista usa o pivo ultimo como suporte.
        pivo->ultimo->prox = novo;
        novo->ant = pivo->ultimo;
        pivo->ultimo = novo;

    }
}

void proxurar_vida(Pivo *pivo,CorpoCeleste *atual)
{
    if(atual->tipoCorpo == 4)
        if(atual->type.planet->temVida)
            lista(pivo,atual);

    if(atual->prox != NULL){
        return proxurar_vida(pivo,atual->prox);
    }

    return;

}

void entraproc(Pivo *aux,Estrela *atual)
{
    if(atual->prox == NULL)
    {
        if(atual->numCorpos > 0)
            proxurar_vida(aux,atual->lista);
        return;
    }else{
        if(atual->numCorpos > 0)
            proxurar_vida(aux,atual->lista);
        return entraproc(aux,atual->prox);
    }
}



// Tudo abaixo ate a Main é viradao para xcriar a matrix sparts
FILE *openFile(char *filename,char *tipo)
{
    FILE *f = fopen(filename,"r");
    if (f==NULL)
    {
        printf("Error\n");
        exit(0);
    }
    return f;
}

void mostrar_universo(Galaxia *glax)
{
    printf("Nome Galxia: %s\n",glax->nome);
    Estrela *aux = glax->incio;
    for(int i=0;i < glax->numEstrelas;i++)
    {
        printf("%s || %i || %i || %f\n",aux->nome,aux->numCorpos,aux->codEstrelas,aux->fatordedobra);
        CorpoCeleste *corpo = aux->lista;
        for(int j = 0; j< aux->numCorpos ; j++)
        {
            if(corpo->nome != NULL)
            {
                printf("nome: %s temperatura: %f peso: %i  distancia do planta anterior: %f \n",corpo->nome,corpo->temperatura,corpo->peso,corpo->distanciaDoAnterior);
                switch(corpo->tipoCorpo)
                {
                case 4:
                    printf("Ox:%f Tox:%f vida: %i atm: %i \n",corpo->type.planet->percOxigeneio,corpo->type.planet->percToxica,corpo->type.planet->temVida,corpo->type.planet->temAtmosfera);
                    break;
                case 3:
                    printf("Format:%i veloc: %f \n",corpo->type.planetaA->format,corpo->type.planetaA->velociade);break;
                case 2:
                    printf("quant:%i veloc: %f \n",corpo->type.ast->quantMinerios,corpo->type.ast->velocidade);break;
                case 1:
                    printf(" veloc: %f temp: %f \n",corpo->type.sat->velocidade,corpo->type.sat->tempeInterna);break;
                }
                corpo = corpo->prox;
            }

        }
        aux = aux->prox;
    }

    return;
}


satelite *criarsat(float temp,float velocidade)
{
    satelite *aux=malloc(sizeof(satelite));

    aux->tempeInterna = temp;
    aux->velocidade = velocidade;

    return aux;
}

asteroid *criarasteroid(int qmine ,float veloc)
{
    asteroid *aux = malloc(sizeof(asteroid));
    aux->quantMinerios = qmine;
    aux->velocidade = veloc;

    return aux;
}

planetaAnao *criarplanetaA(int formt,float veloc)
{
    planetaAnao *aux = malloc(sizeof(planetaAnao));
    aux->format = formt;
    aux->velociade = veloc;

    return aux;
}

planeta *criarplaneta(int vida,int atm,float ox,float tox)
{
    planeta *aux = malloc(sizeof(planeta));
    aux->percOxigeneio = ox;
    aux->percToxica = tox;
    aux->temAtmosfera = atm;
    aux->temVida = vida;

    return aux;
}

CorpoCeleste *criarCorpo(char nome[],float temp,int peso,float dist,int tcp,int Cod)
{
    CorpoCeleste *aux = malloc(sizeof(CorpoCeleste));
    strcpy(aux->nome,nome);
    aux->temperatura = temp;
    aux->peso = peso;
    aux->distanciaDoAnterior = dist;
    aux->tipoCorpo = tcp;
    aux->prox = NULL;
    aux->codEstrela = Cod;
    return aux;
}

Estrela *criaEstrela(char nomeStar[],int numCorpos,int linha,float fator)
{
    Estrela *aux = malloc(sizeof(Estrela));
    strcpy(aux->nome,nomeStar);
    aux->numCorpos = numCorpos;
    aux->codEstrelas = linha;
    aux->lista = NULL;
    aux->prox = NULL;
    aux->fatordedobra = fator;

    return aux;
}

void criarStar(char nomeStar[],int numCorpos,int linha,Galaxia *pivo,float fator)
{
    Estrela *novo = criaEstrela(nomeStar,numCorpos,linha,fator);

    if(pivo->incio == NULL)
    {
        pivo->incio = novo;
        pivo->limiteAtual = novo;
    }else{
        pivo->limiteAtual->prox = novo;
        pivo->limiteAtual = novo;
    }
}

Galaxia *Criar_galaxia(char nome[],int numStar)
{
    Galaxia *aux=malloc(sizeof(Galaxia));
    strcpy(aux->nome,nome);
    aux->numEstrelas = numStar;
    aux->incio = NULL;
    aux->limiteAtual = NULL;
    return aux;
}

void leituraCorpos(char *filename,CORPOCELESTE corpos[],int *numCorpos,Galaxia *pivo)
{
    int i=0,n=0;
    char txt[255];
    FILE *f = openFile(filename,"r");
    while (fgets(txt,255,f)>0)
    {
        n++;
    }
    printf("N:%i\n",n);
    rewind(f);
    Estrela *aux_Estrela = pivo->incio;

    while (i<n)
    {
        fscanf(f,"%i;%[^;];%i;%f;%i;%f;",&corpos[i].tipoCorpo,corpos[i].nome,&corpos[i].codEstrela,&corpos[i].temperatura,&corpos[i].peso,&corpos[i].distDoAnterior);
        while(aux_Estrela->codEstrelas != corpos[i].codEstrela)
        {
            aux_Estrela = aux_Estrela->prox;
        }

        CorpoCeleste *novoc = criarCorpo(corpos[i].nome,corpos[i].temperatura,corpos[i].peso,corpos[i].distDoAnterior,corpos[i].tipoCorpo,corpos[i].codEstrela);
        switch (corpos[i].tipoCorpo)
        {
            case 1:{//Satélite
                fscanf(f,"%f;%f\n",&corpos[i].temperInterna,&corpos[i].rotacao);
                novoc->type.sat = criarsat(corpos[i].temperInterna,corpos[i].rotacao);
                break;
            }
            case 2:{//Asteroide
                fscanf(f,"%i;%f\n",&corpos[i].quantMinerios,&corpos[i].velocidade);
                novoc->type.ast = criarasteroid(corpos[i].quantMinerios,corpos[i].velocidade);
                break;
            }
            case 3:{//Planeta Anão
                fscanf(f,"%i;%f\n",&corpos[i].formato,&corpos[i].velocRotacao);
                novoc->type.planetaA = criarplanetaA(corpos[i].formato,corpos[i].velocRotacao);
                break;
            }
            case 4:{//Planeta
                fscanf(f,"%i;%i;%f;%f\n",&corpos[i].temVida,&corpos[i].temAtmosfera,&corpos[i].percOxigenio,&corpos[i].percToxica);
                novoc->type.planet = criarplaneta(corpos[i].temVida,corpos[i].temAtmosfera,corpos[i].percOxigenio,corpos[i].percToxica);
                break;
            }
        }


        if(aux_Estrela->lista ==  NULL)
        {
                aux_Estrela->lista = novoc;
        }else{
            CorpoCeleste *aux1 = aux_Estrela->lista;
            while(aux1->prox != NULL)
            {
                aux1 = aux1->prox;
            }
            aux1->prox = novoc;
            novoc->prox = NULL;
        }

        aux_Estrela = pivo->incio;
        i++;
    }
    *numCorpos=i;
    fclose(f);
}

void leituraEstrelas(char *filename,int codEstrelas[],char nomesEstrelas[][35],int numCorpos[],float fatoresDobra[],int codProx[],Galaxia *pivo)
{
    int i=0;
    FILE *f = openFile(filename,"r");

    while (fscanf(f,"%i;%i;%f;%i;%[^\n]s\n",&codEstrelas[i],&numCorpos[i],&fatoresDobra[i],&codProx[i],nomesEstrelas[i])>0)
    {
        criarStar(nomesEstrelas[i],numCorpos[i],codEstrelas[i],pivo,fatoresDobra[i]);
        i++;
    }

    fclose(f);
}

void leituraGalaxia(char *filename,char nome[],int *numEstrelas)
{
    FILE *f = openFile(filename,"r");
    fscanf(f,"%i;%[^\n]s",numEstrelas,nome);
    fclose(f);
}

Galaxia *CriarUNIVERSO()
{
    char nomeGalx[30],nomeStar[30],nomeCorp[30];
    int NumEstrelas = 0,numCorpos,linha = -1,peso,tpc;
    float temp,dist;

    leituraGalaxia("Galaxia.txt",nomeGalx,&NumEstrelas);
    Galaxia *glax = Criar_galaxia(nomeGalx,NumEstrelas);

    int codEstrelas[NumEstrelas];
    char nomesEstrelas[NumEstrelas][35];
    int numcorpos[NumEstrelas];
    float fatoresDobra[NumEstrelas];
    int codProx[NumEstrelas];
    leituraEstrelas("Estrelas.txt",codEstrelas,nomesEstrelas,numcorpos,fatoresDobra,codProx,glax);

    CORPOCELESTE corpos[100];
    int nCorpos;

    leituraCorpos("Corpos.txt",corpos,&nCorpos,glax);

    /*
    for(int i=0;i < glax->numEstrelas;i++)
    {
        printf("Entre com o nome da estrelas: ");
        scanf("%s",&nomeStar);
        printf("Ente com o numero de Corpos Celeste: ");
        scanf("%i",&numCorpos);
        linha++;
        criarStar(nomeStar,numCorpos,linha,glax);
        Estrela *aux = glax->limiteAtual;
        for(int j = 0; j< aux->numCorpos ; j++)
        {
            printf("Entre com o nome do corpo: ");
            scanf("%s",&nomeCorp);
            printf("Entre com tempratura: ");
            scanf("%f",&temp);
            printf("Peso do planeta: ");
            scanf("%i",&peso);
            printf("Distancia da estrela: ");
            scanf("%f",&dist);
            printf("tipo: ");
            scanf("%i",&tpc);
            CorpoCeleste *novoc = criarCorpo(nomeCorp,temp,peso,dist,tpc);
            switch(tpc)
            {
            case 1: novoc->type.planet = criarplaneta(1,2,12.5,15.2);break;
            case 2: novoc->type.planetaA = criarplanetaA(1,2.3);break;
            case 3: novoc->type.ast = criarasteroid(1,2.3);break;
            case 4: novoc->type.sat = criarsat(1.1,1.3,1.2);break;
            };

            if(aux->lista ==  NULL)
            {
                aux->lista = novoc;
            }else{
                CorpoCeleste *aux1 = aux->lista;
                while(aux1->prox != NULL)
                {
                    aux1 = aux1->prox;
                }
                aux1->prox = novoc;
                novoc->prox = NULL;
            }
        }
        system("cls");
    }
    */
    system("cls");
    return glax;
}

Pivo *criarPivo()
{
    Pivo *aux = malloc(sizeof(Pivo));
    aux->primeiro = NULL;
    aux->ultimo = NULL;
    return aux;
}


void limpargalxia(Galaxia *glax)
{
    Estrela *estrela = glax->incio;
    for(int i=0;i < glax->numEstrelas;i++)
    {
        CorpoCeleste *corpo = estrela->lista;
        if(estrela->numCorpos> 0)
            for(int j = 0; j< estrela->numCorpos ; j++)
            {
                    CorpoCeleste *limpa = corpo;
                    corpo = corpo->prox;
                    free(limpa);
            }
        Estrela *limpa = estrela;
        estrela = estrela->prox;
        free(limpa);
    }
}

int main()
{
    Pivo *aux = criarPivo();
    Galaxia *pivo = CriarUNIVERSO();
    //mostrar_universo(pivo);

    printf("\n--------Exercio 4---------\n");
    entraproc(aux,pivo->incio);
    printf_pivo(aux);

    printf("\n--------Exercio 5---------\n");
    prinrf_fila(aux,pivo);

    printf("\n--------Exercio 6---------\n");
    int X = 1000;//Mude a variavel para outros pesos
    printf("Planetas com peso<%i\n",X);
    procuar_peso(X,pivo->incio);

   printf("\n--------Exercio 7---------\n");
    float x=-10,y = 60;//mude a variavel pra outras temp.
    printf("Temperatura entre: %0.2f <temp< %0.2f\n",x,y);
    temparatura(x,y,pivo->incio);

    limpargalxia(pivo);
    free(pivo);
    return 0;
}
