#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include "Trabalho_mapeamento_cabeçalho.h"

/**
 *
 * @author Maykoll Rocha & Rian Carrasco Gonçalves
 * @email <maykoll.rocha422@academico.ufgd.edu.br>
 * @email <rian.goncalves064@academico.ufgd.edu.br>
 * @date  2022-09-05
 *
 */


int main()
{
    setlocale(LC_ALL,"");
    unsigned int op;
    char nome_arq[10];
    do{
        printf("--MENU--\n 1.Entre com o arquivo;\n 0.Sair;");
        do{
            scanf("%i",&op);
        }while(op > 1);

        switch(op)
        {
        case 1:
            printf("Entre com o nome do arquivo(sem o .txt): ");
            scanf("%s",nome_arq);
            strcat(nome_arq,".txt");
            ler_arquivo_escolhe_mapeamento(nome_arq);
            break;
        }
    }while(op != 0);
    return 1;
}

void ler_arquivo_escolhe_mapeamento(char nomearq[])
{
    FILE *arq = fopen(nomearq,"r");

    if(!arq)
    {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    char tamanho_r[30],tamanho_s[30],tamanho_w[30],tamnho_tag[30];
    int r,s,w,tag,aux, cont=1,num;
    fgets(tamanho_s,10,arq);
    fgets(tamanho_w,10,arq);
    fgets(tamanho_r,10,arq);
    s=floor(log2(atof(tamanho_s)));
    w=floor(log2(atof(tamanho_w)));
    r=floor(log2(atof(tamanho_r)));
    fclose(arq);
    unsigned int op;
    do{
        printf("--MENU ESCOLHA MAPEAMENTO--\n 1.Mapeamento Direto;\n 2.Mapeamento Associativo;\n 3.Mapeamento Associativo por conjunto\n 0. sair;");
        do{
            scanf("%i",&op);
        }while(op>3);

        switch(op)
        {
            case 1:mapeamento_direto(s-w,w,r);break;
            case 2:mapeamento_associativo(s-w,w);
                break;
            case 3:mapeamento_associativo_por_conjunto(s-(r+w),w,r);
                break;
        }
        system("cls");
    }while(op != 0);

    return exit(1);
}

void mapeamento_direto(int s,int w,int r)
{
    tag_cache *cache = Criando_espacos_na_caches(s-r,w,r);
    unsigned int op,num;
    float falha = 0,acerto = 0,cal_ac,cal_fa;
    while(op !=0)
    {
        printf("--Mapeamento direto--\n Tamanho da Memoria Princiapal: %0.0f\n Qual endereço quer procurar na cache: ",pow(2,s+w));
        do{
            scanf("%i",&num);
        }while(num > pow(2,s+w)-1);
        procura_cahche(s-r,r,w,num,cache,&falha,&acerto);
        cal_ac = (acerto/(falha+acerto))*100;
        cal_fa = (falha/(falha+acerto))*100;
        printf("Acertos: %0.2f % \n Falhas: %0.2f % \n",cal_ac,cal_fa);
        printf("Quer sair(aperte 0): ");
        scanf("%i",&op);
        system("cls");
    }

    limpar_alocs(cache);

    return;
}


//depois de criar adicina -1 em todos os espaço para fazer um Vazio moral
void limpa_cache(int tag,int r, int w,tag_cache *tag_new)
{

    for(int i=0;i<pow(2,tag);i++)
        for(int j=0;j<pow(2,r);j++)
            for(int p=0;p<pow(2,w);p++)
            {
                tag_new[i].linhas[j].palavras[p].numero = -1;
            }

    return;
}


/*
    Criando cache:
    Tava retornando muito erro criando todas com malloc e acontando para todos os espaços então eu crio espaço por espaço
    demora mais porem é maior seguro que ficar criando tudo ao mesmo tempo.

*/
tag_cache *Criando_espacos_na_caches (int tag, int w, int r)
{
    int aux;

    aux=pow(2,tag);
    tag_cache *tags=(tag_cache *)malloc(aux*sizeof(tag_cache));

    aux=pow(2,r);
    for(int i=0;i<pow(2,tag);i++)
        tags[i].linhas=(linha_cache *)malloc(aux*sizeof(linha_cache));


    aux=pow(2,w);
    for(int i=0;i<pow(2,tag);i++)
        for(int j=0;j<pow(2,r);j++)
            tags[i].linhas[j].palavras=(palavra_cache *)malloc(aux*sizeof(palavra_cache));


    for(int i=0;i<pow(2,tag);i++)
    {
        criando_tags(tag,i,tags);
        for(int j=0;j<pow(2,r);j++)
        {
            criando_linhas(r,i,j,tags);
            for(int k=0;k<pow(2,w);k++)
            {
                criando_palavras(tags,w,i,j,k);
            }
        }
    }

    limpa_cache(tag,r,w,tags);

     return tags;
}

// Aloca nos espaços vazios da cache
void aloca_cache(int tag,int r, int w,int num,tag_cache *tag_new)
{

    int vet_aux[tag+r+w],auxnum;
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
                            tag_new[i].linhas[j].palavras[p].numero = num;
                            return;
                        }
                    }
                }

        }
    }
}


/*
    Ideia de andar na cache depois de criar é ir um por um ate encontrar o numero na cache se não encontrar
    ele retorn pra normal
*/
void procura_cahche(int tag,int r, int w,int num,tag_cache *tag_new,float *falha,float *acerto)
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
                        if(tag_new[i].linhas[j].palavras[p].numero != -1){
                            *acerto +=1;
                            if(num != tag_new[i].linhas[j].palavras[p].numero)
                            {
                                aloca_cache(tag,r,w,num,tag_new);
                                print_acertos(tag,r, w, num,tag_new);
                                return;
                            }else{
                                print_acertos(tag,r, w, num,tag_new);
                                return;
                            }
                        }else if (p == pow(2,w) -1 ){
                                *falha +=1;
                                aloca_cache(tag,r,w,num,tag_new);
                                printf("Falha.\n");
                                return;
                            }
                        }
                    }
                }

        }
}

void print_acertos(int tag,int r, int w, int num,tag_cache *tag_new)
{
    print_loca_MC(tag,r, w, num-2,tag_new);
    print_loca_MC(tag,r, w, num-1,tag_new);
    print_loca_MC(tag,r, w, num,tag_new);
    print_loca_MC(tag,r, w, num+1,tag_new);
    print_loca_MC(tag,r, w, num+2,tag_new);

    return;
}


// daqui pra frente é apenas mapeamento associativo
void mapeamento_associativo(int tag,int w)
{
    tag_cache *cache = Criando_MA(tag,w);
    unsigned int op,num;
    float falha = 0,acerto = 0,cal_ac,cal_fa;
    while(op !=0)
    {
        printf("--Mapeamento Associativo--\n Tamanho da Memoria Princiapal: %0.0f\n Qual endereço quer procurar na cache: ",pow(2,tag+w));
        do{
            scanf("%i",&num);
        }while(num > pow(2,tag+w)-1);

        procura_MA(tag,w,num,cache,&falha,&acerto);
        cal_ac = (acerto/(falha+acerto))*100;
        cal_fa = (falha/(falha+acerto))*100;
        printf("Acertos: %0.2f %\n Falhas: %0.2f %\n",cal_ac,cal_fa);
        printf("Quer sair(aperte 0): ");
        scanf("%i",&op);
        system("cls");
    }

    liberar_MA(cache);
    return;
}


tag_cache *Criando_MA(int tag,int w)
{
    int aux;

    aux=pow(2,tag);
    tag_cache *tags=(tag_cache *)malloc(aux*sizeof(tag_cache));

    aux=pow(2,w);
    for(int i=0;i<pow(2,tag);i++)
        tags[i].palavras=(palavra_cache *)malloc(aux*sizeof(palavra_cache));

    for(int i=0;i<pow(2,tag);i++)
    {
        tags_MA(tag,i,tags);
            for(int k=0;k<pow(2,w);k++)
            {
                palavras_MA(tags,k,i,w);
            }
    }

     limpa_MA(tag,w,tags);
   return tags;
}

void procura_MA(int tag,int w,int num,tag_cache *cache,float *falha,float *acerto)
{
    int vet_aux[tag+w],vet_w[w],vet_tag[tag];
    convert_num_bin(num,vet_aux,tag+w);
    arrumar_aux_MA(vet_tag,vet_w,vet_aux,tag,w);

    int loc,mod,aux_pow;

    for(int i=0;i<pow(2,tag);i++)// anda por todas as TAG
    {
        for(int p=0;p<pow(2,w);p++)// anda por toda W
        {
            if(tranforma_vet(vet_tag,tag) == cache[i].palavras[p].numero)
            {
                loc = tranforma_vet_MA(cache[i].num_bin,cache[i].palavras[p].num_bin,tag+w,tag);
                aux_pow = pow(2,w);
                loc += num % aux_pow;
                *acerto +=1;
                print_acertos_MA(tag,w,loc,cache);
                return;
            }else if (i == (pow(2,tag)-1) && p == (pow(2,p)-1) ){
                *falha +=1;
                aloca_MA(tag,w,num,cache);
                printf("Falha.\n");
                return;
            }
        }
    }
}

void aloca_MA(int tag,int w,int num,tag_cache *cache)
{
    int vet_aux[tag+w],vet_w[w],vet_tag[tag];
    convert_num_bin(num,vet_aux,tag+w);
    arrumar_aux_MA(vet_tag,vet_w,vet_aux,tag,w);

    for(int i=0;i<pow(2,tag);i++)// anda por todas as TAG
    {
        if(cache[i].palavras[0].numero == -1)
        {
            for(int p=0;p<pow(2,w);p++)// anda por toda W
            {
                cache[i].palavras[p].numero = tranforma_vet(vet_tag,tag);
            }
            return;
        }

    }
}

void print_acertos_MA(int tag,int w,int num,tag_cache *cache)
{
    print_loca_MP(tag, w, num-2,cache);
    print_loca_MP(tag, w, num-1,cache);
    print_loca_MP(tag, w, num,cache);
    print_loca_MP(tag, w, num+1,cache);
    print_loca_MP(tag, w, num+2,cache);

}

/**MAPEAMENTO ASSOCIATIVO POR CONJUNTO**/

void mapeamento_associativo_por_conjunto(int tag,int w,int sets)
{
    tag_cache *cache = Criando_espacos_na_caches(tag,w,sets);
    /*
    Usando o mesmo de criar o mapemanto direto eu separo por linha tag e word(palavra) porem
    eu utilizo minha linha pra descobrir qual sera o conjunto da minha cache    ou seja oque é linha representa meu
    conjunto da cache
    */
    unsigned int op,num;
    float falha = 0,acerto = 0,cal_ac,cal_fa;

    while(op !=0)
    {
        printf("--Mapeamento Associativo por Conjunto--\n Tamanho da Memoria Princiapal: %0.0f|Conjunto da cache: %0.0f\n Qual endereço quer procurar na cache: ",pow(2,tag+w+sets),pow(2,sets));
        do{
            scanf("%i",&num);
        }while(num > pow(2,tag+w+sets)-1);
        procurar_associativo_conj(tag,w,sets,num,cache,&falha,&acerto);
        cal_ac = (acerto/(falha+acerto))*100;
        cal_fa = (falha/(falha+acerto))*100;
        printf("Acertos: %0.2f % \n Falhas: %0.2f % \n",cal_ac,cal_fa);
        printf("Quer sair(aperte 0): ");
        scanf("%i",&op);
        system("cls");
    }

    limpar_alocs(cache);
    getch();
    return;
}

void procurar_associativo_conj(int tag,int w, int sets,int num,tag_cache *cache,float *falha,float *acerto)
{
    /*
    a parte abaixo serve para a conversão do numero que entrei para bits e ele separa
    o que sera usado para conjunto(descobrir o conjunto) oque eu uso para tag e para palavra.
    */
    int vet_aux[tag+sets+w];
    convert_num_bin(num,vet_aux,tag+sets+w);
    int vet_w[w],vet_sets[sets],vet_tag[tag];
    arrumar_aux(vet_tag,vet_sets,vet_w,vet_aux,tag,sets,w);

    /*
    primeiro eu começo comparado o conujunto eu vejo qual conjunto ele se contra eu uso
    o conjunto que tenho e descobri o conjunto que ele faz parte;
    em seguida eu descobro a tag qual tac ele pertenci e dentro dessa tag eu checo se a cache ja chamou ela antes
    caso tenha qualquer acesso eu retorna o local como acerto e caso não é erro;
    */
    for(int i=0;i<pow(2,sets);i++)
        if(Conversor_bin(vet_sets,sets) == Conversor_bin(cache->linhas[i].num_bin,sets))
                {
                    for(int p=0;p<pow(2,sets);p++)
                        if(Conversor_bin(vet_tag,tag) == Conversor_bin(cache[p].num_bin,tag))
                        {
                            printf("Achei sets %i\n",tranforma_vet(cache->linhas[i].num_bin,sets));
                            for(int z=0;z<pow(2,w);z++)
                            {
                                 if(cache[p].linhas[i].palavras[z].numero != -1){
                                    *acerto +=1;
                                    if(num != cache[p].linhas[i].palavras[z].numero)
                                    {
                                        aloca_cache(tag,sets,w,num,cache);// a alocação é o mesmo sistema do mapeamento direto
                                        print_acertos_MPC(tag,sets, w, num,cache);
                                        return;
                                    }else{
                                        print_acertos_MPC(tag,sets, w, num,cache);
                                        return;
                                    }
                                    }else if (z == pow(2,w) -1 ){
                                    *falha +=1;
                                    aloca_cache(tag,sets,w,num,cache);
                                    printf("Falha.\n");
                                    return;
                                    }
                            }

                        }
                }
}

void print_acertos_MPC(int tag,int r, int w, int num,tag_cache *tag_new)
{
    print_loca_MPC(tag,r, w, num-2*pow(2,w+r),tag_new);
    print_loca_MPC(tag,r, w, num-1*pow(2,w+r),tag_new);
    print_loca_MPC(tag,r, w, num,tag_new);
    print_loca_MPC(tag,r, w, num+1*pow(2,w+r),tag_new);
    print_loca_MPC(tag,r, w, num+2*pow(2,w+r),tag_new);

    return;
}
