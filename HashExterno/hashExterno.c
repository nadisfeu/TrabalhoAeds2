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

    int posicaoNoHash = calculaHash(mesa->cod, tamBase);

    TLista lista;
    TLista *aux = leCabecalho(hash);
    fseek(hashCompartimentos, aux[posicaoNoHash].pos, SEEK_SET);
    fread(&lista, sizeof(TLista), 1, hash);

    // Percorre a lista até o final
    while (lista.prox != -1)
    {
        fseek(hashCompartimentos, lista.prox, SEEK_SET);
        fread(&lista, sizeof(TLista), 1, hash);
    }

    // Cria um novo elemento na lista
    fseek(hashCompartimentos, ftell(hashCompartimentos), SEEK_SET);
    salvaMesa(mesa, hashCompartimentos);
    
    // Atualiza a lista com a nova posição do último elemento
    lista.prox = ftell(hashCompartimentos);
    lista.tam++;
    fseek(hashCompartimentos, aux[posicaoNoHash].pos, SEEK_SET);
    fwrite(&lista, sizeof(TLista), 1, hash);

    // Atualiza o cabeçalho do arquivo
    aux[posicaoNoHash].tam++;
    fseek(hash, 0, SEEK_SET);
    fwrite(aux, sizeof(TLista), tamBase, hash);
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

