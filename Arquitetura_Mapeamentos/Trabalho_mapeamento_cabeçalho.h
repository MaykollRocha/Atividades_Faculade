/**
 *
 * @author Maykoll Rocha & Rian Carrasco Gonçalves
 * @email <maykoll.rocha422@academico.ufgd.edu.br>
 * @email <rian.goncalves064@academico.ufgd.edu.br>
 * @date  2022-09-05
 *
 */

#ifndef TRABALHO_MAPEAMENTO_CABECALHO_H
#define TRABALHO_MAPEAMENTO_CABECALHO_H

typedef struct
{
    int numero;
    int *num_bin;
}palavra_cache;

typedef struct
{
    palavra_cache *palavras;
    int *num_bin;
}linha_cache;

typedef struct
{
    palavra_cache *palavras;
    linha_cache *linhas;
    int *num_bin;
}tag_cache;


//Prototipações
//Mapeamento direto
void mapeamento_direto(int s,int w,int r);
tag_cache *Criando_espacos_na_caches (int tag, int w, int r);
void aloca_cache(int tag,int r, int w,int num,tag_cache *tag_new);
void procura_cahche(int tag,int r, int w,int num,tag_cache *tag_new,float *falha,float *acerto);
void ler_arquivo_escolhe_mapeamento(char nomearq[]);
void print_acertos(int tag,int r, int w, int num, tag_cache *tag_new);
void print_loca_MC(int tag,int r, int w, int num, tag_cache *tag_new);
void print_vet_int(int vet[],int tam);
//Mapeamento associativo
void mapeamento_associativo(int tag,int w);
tag_cache *Criando_MA(int tag,int w);
void procura_MA(int tag,int w,int num,tag_cache *cache,float *falha,float *acerto);
void aloca_MA(int tag,int w,int num,tag_cache *cache);
void print_acertos_MA(int tag,int w,int num,tag_cache *cache);
void print_loca_MP(int tag,int w,int num,tag_cache *cache);
//Mapemanto associativo por conjunto
void mapeamento_associativo_por_conjunto(int tag,int w,int sets);
void procurar_associativo_conj(int tag,int w, int sets,int num,tag_cache *cache,float *falha,float *acerto);
void print_acertos_MPC(int tag,int r, int w, int num,tag_cache *tag_new);

// Função de converções binarias

// essa função é pra printar qualquer numero binario registrado em vetor.
void print_vet_int(int vet[],int tam)
{
    for(int h = 0;h <tam;h++)
        printf("%i",vet[h]);

    printf(" ");

    return;
}

int tranforma_vet(int bin[],int tam)
{
    int soma=0;
    for(int i=0,f=tam-1;i<tam;i++,f--)
    {
       soma += pow(2,f)*bin[i];
    }

    return soma;
}

int tranforma_vet_MA(int bin[],int bin2[],int tam,int tag)
{
    int soma=0,g=0;
    for(int i=0,f=tam-1;i<tam;i++,f--)
    {
        if(i<tag)
            soma += pow(2,f)*bin[i];
        else{
            soma += pow(2,f)*bin2[g];
            g++;
        }
    }


    return soma;
}
// essa função é exclusiva para a separação da tag, linha e palavra pra fazer as
//comparações nas suas devidas partes para um vetor de comparação com a Memoria cache.
void arrumar_aux(int vet_tag[],int vet_r[], int vet_w[], int vet_aux[],int tag,int r,int w )
{
    int j=0,k=0;
    for(int i=0;i<tag+r+w;i++)
    {
        if(i < tag)
        {
            vet_tag[i]=vet_aux[i];
        }else if(i < r+tag){
            vet_r[j] = vet_aux[i];
            j++;
        }else{
            vet_w[k] = vet_aux[i];
            k++;
        }
    }

    return;
}

// convert numeros em binarios transformando em vetor de inteiro.
void convert_num_bin(int as,int vet_aux[],int tam)
{
   int num = as;
   int f=0,vet_aux2[tam];
   while(f<tam)
    {
        vet_aux2[f] = 0;
        f++;
    }
    f=0;
    while(num > 0)
    {
        vet_aux2[f] = num%2;
        f++;
        num = num/2;
    }

    for(int j = tam-1, x = 0; j >= 0; j--,x++)
    {
        vet_aux[x]= vet_aux2[j];
    }

    return;
}

/*
    faz uma conversão de binario para inteiro unico exemplo:
    temos numero 3 com nossa S sendo 5 sua representação no vetor
    é 00011 na conta da nossa somatoria(nosso laço for) teriamos na sequencia:
    i=0 x= 4 vet[0]=0 ele multiplica com 0*10**4 = 0*10000 = 00000
    i=1 x= 3 vet[1]=0 ele multiplica com 0*10**3 = 0*1000 = 0000
    i=2 x= 2 vet[2]=0 ele multiplica com 0*10**2 = 0*100 = 000
    i=3 x= 1 vet[3]=1 ele multiplica com 1*10**1 = 0*10 = 10
    i=4 x= 0 vet[4]=1 ele multiplica com 1*10**0 = 0*1 = 1
    e ele vai somando a um inteiro inicial 0
    00000+0000+000+10+1=00011
    como desconsidera os priemiro 0 ele so volta como 11.

*/
int Conversor_bin(int vet [],int tam)
{
    int v=0;
    for(int i=0,x=(tam-1);i<tam;i++,x--)
        v += vet[i]*pow(10,x);

    return v;
}

//As proximas 3 função são as que colocam na Tag,linha e palavras seus representativos binarios para na hora do mapeamento eles salvaram.
void criando_palavras(tag_cache *MC,int w,int tag,int r,int num)
{
    int o = num;
    MC[tag].linhas[r].palavras[o].num_bin = (int *)malloc(w*sizeof(int));

    int vet_aux[w];
    int f = 0;
    while(f<w)
    {
        vet_aux[f] = 0;
        f++;
    }
    f=0;
    while(num > 0)
    {
        vet_aux[f] = num%2;
        f++;
        num = num/2;
    }

    for(int j = w-1, x = 0; j >= 0; j--,x++)
    {
        MC[tag].linhas[r].palavras[o].num_bin[x]= vet_aux[j];
    }
}


void criando_linhas(int r,int tag,int num,tag_cache *MC)
{
    int o = num;
    MC[tag].linhas[o].num_bin = (int *)malloc(r*sizeof(int));

    int vet_aux[r];
    int f = 0;
    while(f<r)
    {
        vet_aux[f] = 0;
        f++;
    }
    f=0;
    while(num > 0)
    {
        vet_aux[f] = num%2;
        f++;
        num = num/2;
    }

    for(int j = r-1, x = 0; j >= 0; j--,x++)
    {
        MC[tag].linhas[o].num_bin[x] = vet_aux[j];
    }
}

void criando_tags(int tag_num,int num,tag_cache *tag)
{
    int i = num;
    tag[i].num_bin = (int *)malloc(tag_num*sizeof(int));

    int vet_aux[tag_num];
    int f = 0;
    while(f<tag_num)
    {
        vet_aux[f] = 0;
        f++;
    }
    f=0;
    while(num > 0)
    {
        vet_aux[f] = num%2;
        f++;
        num = num/2;
    }

    for(int j = tag_num-1, x = 0; j >= 0; j--,x++)
    {
        tag[i].num_bin[x] = vet_aux[j];
    }
}


//Limpa as mallocs e allocs criadas anteriomento nos vetores.
void limpar_alocs(tag_cache *cache)
{
    free(cache->linhas->palavras->num_bin);
    free(cache->linhas->palavras);
    free(cache->linhas->num_bin);
    free(cache->linhas);
    free(cache->num_bin);
    free(cache);
}
/**
Funações da nosso Mapeamento Associartivo.
**/
// printa um local específico da cache;
void print_loca_MC(int tag,int r, int w, int num, tag_cache *tag_new)
{
    if(num >= 0 && num <= pow(2,tag+w+r)-1)
    {
        int vet_aux[tag+r+w];
        convert_num_bin(num,vet_aux,tag+r+w);
        int vet_w[w],vet_r[r],vet_tag[tag];
        arrumar_aux(vet_tag,vet_r,vet_w,vet_aux,tag,r,w);


        for(int i=0;i<pow(2,tag);i++)// anda por todas as TAG
        {
            if(Conversor_bin(vet_tag,tag) == Conversor_bin(tag_new[i].num_bin,tag))
            {
                for(int j=0;j<pow(2,r);j++)// anda por toda a R
                    if(Conversor_bin(vet_r,r) == Conversor_bin(tag_new[i].linhas[j].num_bin,r))
                    {
                        for(int p=0;p<pow(2,w);p++)// anda por toda W
                        {
                            if(Conversor_bin(vet_w,w) == Conversor_bin(tag_new[i].linhas[j].palavras[p].num_bin,w))
                            {
                                printf("Local na MP: ");
                                print_vet_int(vet_aux,tag+w+r);
                                printf("|TAG: ");
                                print_vet_int(vet_tag,tag);
                                printf("Linha: ");
                                print_vet_int(vet_r,r);
                                printf("Palavra: ");
                                print_vet_int(vet_w,w);
                                if(num == tag_new[i].linhas[j].palavras[p].numero)
                                {
                                    printf("|Dados\n");
                                }else{
                                    printf("|Vazio\n");
                                }
                            }
                        }
                    }

            }
        }
    }else{
        printf("Não existe esse espaço na cache.\n");
    }

}

/*
    As duas funções a abaixo tem o memso motivo da nossa ciração no mapeamento direto é feito para colocar a localização da nossa tag
e da nossa palavra dentro dos structs;
*/

void tags_MA(int tag_num,int num,tag_cache *tag)
{
    int i = num;
    tag[i].num_bin = (int *)malloc(tag_num*sizeof(int));

    int vet_aux[tag_num];
    int f = 0;
    while(f<tag_num)
    {
        vet_aux[f] = 0;
        f++;
    }
    f=0;
    while(num > 0)
    {
        vet_aux[f] = num%2;
        f++;
        num = num/2;
    }

    for(int j = tag_num-1, x = 0; j >= 0; j--,x++)
    {
        tag[i].num_bin[x] = vet_aux[j];
    }
}

void palavras_MA(tag_cache *tags,int num,int tag,int k)
{

    int o = num;
    tags[tag].palavras[o].num_bin= (int *)malloc(k*sizeof(int));

    int vet_aux[k];
    int f = 0;
    while(f<k)
    {
        vet_aux[f] = 0;
        f++;
    }
    f=0;
    while(num > 0)
    {
        vet_aux[f] = num%2;
        f++;
        num = num/2;
    }

    for(int j = k-1, x = 0; j >= 0; j--,x++)
    {
        tags[tag].palavras[o].num_bin[x] = vet_aux[j];
    }
}


// coloca -1 que é um representativo de NULL pra gente em todos os epaços no incio da nossa cache;
void limpa_MA(int tag,int w,tag_cache *tags)
{
    int f=0;
    for(int i=0;i<pow(2,tag);i++)
            for(int p=0;p<pow(2,w);p++)
            {
                tags[i].palavras[p].numero = -1;
            }
}

/*
A ideia de arrumar o vetor da meu mapeamento associativo colocando o que for da tag e da palavra
separase os dois pra ajudar em outras funções ele funcina como um auxilio não é muito complexa;
*/
 void arrumar_aux_MA(int vet_tag[],int vet_w[],int vet_aux[],int tag,int w)
 {
     int k=0;
    for(int i=0;i<tag+w;i++)
    {
        if(i < tag)
        {
            vet_tag[i]=vet_aux[i];
        }else{
            vet_w[k] = vet_aux[i];
            k++;
        }
    }

    return;
}
/*
ideia de print bem simples sempre que você entra cim um valor ele é limitado ao tamanho da sua cache ele checa
se esse valor já esta na cache se ele tiver ele retorna como dado como se tivesse algo la e não estiver ele retorna
vazio que é um local sem dado ou com -1.
*/
void print_loca_MP(int tag,int w,int num,tag_cache *cache)
{
    if(num >= 0 && num < pow(2,tag+w))
    {
        int vet_aux[tag+w],vet_w[w],vet_tag[tag];
        convert_num_bin(num,vet_aux,tag+w);
        arrumar_aux_MA(vet_tag,vet_w,vet_aux,tag,w);
        for(int i=0;i<pow(2,tag);i++)// anda por todas as TAG
            for(int p=0;p<pow(2,w);p++)// anda por toda W
            {
                    if(Conversor_bin(cache[i].palavras[p].num_bin,w) == Conversor_bin(vet_w,w) && Conversor_bin(cache[i].num_bin,tag) == Conversor_bin(vet_tag,tag) )
                    {
                        printf("Local na MP: ");
                        print_vet_int(vet_aux,tag+w);
                        printf("TAG:");
                        print_vet_int(cache[i].num_bin,tag);
                        printf("Palavra:");
                        print_vet_int(cache[i].palavras[p].num_bin,w);
                        if(-1 != cache[i].palavras[p].numero)
                        {
                            printf("Dados\n");
                        }else{
                            printf("Vazio\n");
                        }
                    }
            }
    }else{
        printf("Não existe esse espaço na cache.\n");
    }
}


//Limpa os espaços armazenados com malloc da cache
void liberar_MA(tag_cache *cache)
{
    free(cache->palavras);
    free(cache);

    return;
}

void print_loca_MPC(int tag,int r, int w, int num, tag_cache *tag_new)
{
    if(num >= 0 && num <= pow(2,tag+w+r)-1)
    {
        int vet_aux[tag+r+w];
        convert_num_bin(num,vet_aux,tag+r+w);
        int vet_w[w],vet_r[r],vet_tag[tag];
        arrumar_aux(vet_tag,vet_r,vet_w,vet_aux,tag,r,w);


        for(int i=0;i<pow(2,tag);i++)// anda por todas as TAG
        {
            if(Conversor_bin(vet_tag,tag) == Conversor_bin(tag_new[i].num_bin,tag))
            {
                for(int j=0;j<pow(2,r);j++)// anda por toda a R
                    if(Conversor_bin(vet_r,r) == Conversor_bin(tag_new[i].linhas[j].num_bin,r))
                    {
                        for(int p=0;p<pow(2,w);p++)// anda por toda W
                        {
                            if(Conversor_bin(vet_w,w) == Conversor_bin(tag_new[i].linhas[j].palavras[p].num_bin,w))
                            {
                                printf("Local na MP: ");
                                print_vet_int(vet_aux,tag+w+r);
                                printf("|TAG: ");
                                print_vet_int(vet_tag,tag);
                                printf("Linha: ");
                                print_vet_int(vet_r,r);
                                if(num == tag_new[i].linhas[j].palavras[p].numero)
                                {
                                    printf("|Dados\n");
                                }else{
                                    printf("|Vazio\n");
                                }
                            }
                        }
                    }

            }
        }
    }else{
        printf("Não existe esse espaço na cache.\n");
    }

}

#endif
