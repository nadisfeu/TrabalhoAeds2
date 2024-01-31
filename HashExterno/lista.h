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
    TCelula* primeiro;
    TCelula* ultimo;
    int usando;
    int tamanho;
}TLista;

#endif