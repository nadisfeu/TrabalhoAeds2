#include "lista.h"

#include<stdio.h>
#include<stdlib.h>

void salvaLista(TLista *lista, FILE *hash){
    fwrite(&lista->tam, sizeof(int),1,hash);
    fwrite(&lista->pos, sizeof(int),1,hash);
    fwrite(&lista->prox, sizeof(int),1,hash);
}

TLista *leCabecalho(FILE *in ){
    TLista *lista = (TLista *)malloc(sizeof(TLista));
    /*
    if (0 >= fread(&lista->pos, sizeof(int), 1, in))
    {
        free(mesa);
        return NULL;
    }
    */
    fread(&lista->tam, sizeof(int), 1, in);
    fread(&lista->pos, sizeof(int), 1, in);
    fread(&lista->prox, sizeof(int), 1, in);
   
    return lista;
}

void imprimeCabecalho(TLista lista){
    printf("\nTamanho da lista: %d\n", lista.tam);
    printf("posicao da lista: %d\n", lista.pos);
    printf("proxima lista: %d\n", lista.prox);
}

int tamanhoCabecalho(){
    return sizeof(int) + sizeof(int) + sizeof(int);
}
