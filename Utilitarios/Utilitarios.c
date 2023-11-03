#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include <math.h>

#include "Utilitarios.h"



void salva_no_log(FILE *log, int comp, int time, char s[]){
    fprintf(log, "Tipo de busca: %s", s);
    fprintf(log, "\tComparacoes: %d\t", comp);
    fprintf(log, "Tempo: %d\n", time);
}

int tamanho_arquivo(FILE *arq){
    fseek(arq, 0, SEEK_END);
    return trunc(ftell(arq)) / tamanho_registro();
}

//embaralha base de dados
void shuffle(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void criarBase(FILE *out, int tam){

    int vet[tam];
    TFunc *f;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    //shuffle(vet,tam,(tam*1)/100);

    printf("\nGerando a base de dados...\n");

    for (int i=0;i<tam;i++){
        f = funcionario(vet[i], "Aa", "000.000.000-00", "01/01/1980", i*100);
        salva(f, out);
    }

    free(f);

}

TFunc *BuscaSequencial(FILE *log, FILE *out, int cod, int qnt, char tipo[]){
    
    if(strcmp(tipo,"TFunc")){
        TFunc *geral = (TFunc *) malloc(sizeof(TFunc));
    }
    else if (strcmp(tipo, "TMesa"))
    {
        TFunc *geral = (TMesa *) malloc(sizeof(TMesa));
    }
    
    TFunc *geral = (TFunc *) malloc(sizeof(TFunc));
    geral->cod = 0;
    int comp = 0;
    time_t begin = time(NULL);
    
    for( int i = 0; i < qnt; i++){
        fseek(out, tamanho_registro()*i,SEEK_SET);
        geral = le(out);
        comp++;
        if (geral->cod == cod){
            time_t end = time(NULL);
            salva_no_log(log, comp, (end - begin), "BuscaSequencial-Encontrado");
            return geral;
        }
    }
    time_t end = time(NULL);
    salva_no_log(log, comp, end - begin, "BuscaSequencial-Nao Encontrado");
    return geral;
}

TFunc *BuscaBinaria(FILE *log, int chave, FILE *in, int inicio, int fim){
    TFunc *f = NULL;
    int cod = -1;
    time_t begin = time(NULL);
    int comp = 0;

    while (inicio <= fim && cod != chave)
    {
        int meio = trunc((inicio + fim )/2);
        fseek(in,(meio - 1) * tamanho_registro(), SEEK_SET);
        f= le(in);
        cod =f->cod;

        if (f){
            if (cod > chave)
            {
                comp++;
                fim = meio - 1;
            }
            else {
                comp++;
                inicio = meio + 1;
            }
            
        }

    }

    if (cod == chave)
    {
        time_t end = time(NULL);
        salva_no_log(log, comp, (end - begin), "BuscaBinaria-Encontrado");
        return f;
    }
    else{
    time_t end = time(NULL);
    salva_no_log(log, comp, (end - begin), "BuscaBinaria-Nao_Encontrado");
    return NULL;
    } 
}