#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "lista.h"

int calculaHash(int cod, int tamBase){
    return (cod % tamBase);
}

void criaHash(char *nome_do_hash, int tam){
    FILE *hash;
    TLista aux[tam];

	if ((hash = fopen(nome_do_hash, "w+b")) == NULL)
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {

        for(int i = 0; i<tam; i++){
            aux[i].usando = -1;
        }
        fwrite(&aux, sizeof(TLista),1,hash);
    }
}
