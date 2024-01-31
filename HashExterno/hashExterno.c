#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "lista.c"

int calculaHash(int cod, int tamBase)
{
    return (cod % tamBase);
}

void adiciona_no_hash(TMesa *mesa, FILE *hashCompartimentos, FILE *hash, int tamBase)
{
    rewind(hashCompartimentos);
    rewind(hash);

    TLista *aux;

    int posicaoNoHash = calculaHash(mesa->cod, tamBase);


    aux = leCabecalho(hash);

    //no caso da lista está vazia, apenas adiciona
    if (aux->tam == 0)
    {
        fseek(hashCompartimentos, aux->pos  , SEEK_SET);
        salvaMesa(mesa, hashCompartimentos);
        aux->tam++;
        salvaLista(aux,hash);
        return;
    }
    //caso nao esteja, tratamento de colisoes e adiciona na posição ao lado

}

void criaHash(char *nome_do_hash, int tam, FILE *mesas)
{
    FILE *hash, *hashCompartimentos;
    TLista *aux;
    TLista lista;
    TMesa mesa;
    TMesa mesaAux[15];
    mesa.cod = -1;

    if (((hash = fopen(nome_do_hash, "w+b")) == NULL) || ((hashCompartimentos = fopen("tabelaHash.dat", "w+b")) == NULL))
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {
        // cria o arquivo cm as informações de cada lista
        for (int i = 0; i <= tam; i++)
        {
            salvaMesa(&mesa, hashCompartimentos);
            lista.tam = 0;
            lista.pos = ftell(hashCompartimentos); //salva o endereço do primeiro elemento daquela lista
            lista.prox = i + 1;
            for(int j = 0; j<10 ;j++){   //10 tá aqui temporariamente 
                salvaMesa(&mesa, hashCompartimentos);
            }
            salvaLista(&lista, hash);
        }
    }
}

