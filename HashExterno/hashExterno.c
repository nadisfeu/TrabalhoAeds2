 #include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "lista.c"

int calculaHash(int cod, int tamBase)
{
    return (tamBase % cod );
}

void adiciona_no_hash(TMesa *mesa, FILE *hashCompartimentos, FILE *hash, int tamBase)
{
    rewind(hashCompartimentos);
    rewind(hash);

    int posicaoNoHash = calculaHash(mesa->cod, tamBase);

    TLista *aux;
    TMesa *mesa1;

    fseek(hash, posicaoNoHash * tamanhoCabecalho(), SEEK_SET);
    aux = leCabecalho(hash);

    fseek(hashCompartimentos, aux->pos - tamanho_registro_Mesa(), SEEK_SET);
    
    mesa1 = leMesa(hashCompartimentos);

    // Percorre a lista até o final
    int i =0;
    while (i < 15)
    {
        if(mesa1->cod == -1)
        {   
            //salva elemnto na hashmap
            fseek(hashCompartimentos, - tamanho_registro_Mesa(), SEEK_CUR);
            salvaMesa(mesa1,hashCompartimentos);
            break;
        }
        mesa1 = leMesa(hashCompartimentos);
    }

    
    // Atualiza a lista com a nova posição do último elemento
    aux->tam++;
    fseek(hash, - tamanhoCabecalho(), SEEK_CUR);
    salvaLista(aux, hash);
}
 
FILE *criaHash( int tam, FILE *mesas, FILE *hash)
{
    FILE *hashCompartimentos;
    TLista lista;
    TMesa mesa;
    mesa.cod = -1;

    if ( ((hashCompartimentos = fopen("tabelaHash.dat", "w+b")) == NULL))
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
    return hashCompartimentos;
    }
}

