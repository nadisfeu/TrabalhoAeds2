#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "../Entidades/mesas.h"


typedef struct celula
{
    TMesa mesa;
    struct celula* prox;
} TCelula;

typedef struct lista
{
    int pos;
    int tam;
    int prox;
}TLista;

void salvaLista(TLista *lista, FILE *hash);
TLista *leCabecalho(FILE *in);
void imprimeCabecalho(TLista lista);
#endif