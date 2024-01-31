#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "lista.c"

int calculaHash(int cod, int tamBase)
{
    return (cod % tamBase);
}

void criaHash(char *nome_do_hash, int tam, FILE *mesas)
{
    FILE *hash, *hashCompartimentos;
    TLista *aux;
    TLista lista;
    TMesa mesa;
    TMesa mesaAux[15];
    mesa.cod = -1;

    if (((hash = fopen(nome_do_hash, "w+b")) == NULL))
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {
        //cria o arquivo com as informações de cada lista
        for (int i = 0; i < tam; i++)
        {
            lista.tam = -1;
            lista.pos = i;
            lista.prox = i + 1;
            salvaLista(&lista, hash);
        }
        
    }
}

// cria uma tabela preenchida com os códigos iguais a -1, depois faz os calculos.