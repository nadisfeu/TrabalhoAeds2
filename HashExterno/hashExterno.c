#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "hashexterno.h"
#include "lista.c"

void salva_no_log_hash(FILE *log, double time, char s[])
{
    fprintf(log, "%s", s);
    fprintf(log, "Tempo: %.2f\n", time);
}

int calculaHash(int cod, int tamBase)
{
    return (tamBase % cod);
}

void adiciona_no_hash(TMesa *mesa, FILE *hashCompartimentos, FILE *hash, int tamBase, FILE *log)
{
    clock_t begin, end;
    begin = clock();

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
    int i = 0;
    fseek(hashCompartimentos, -tamanho_registro_Mesa(), SEEK_CUR);

    while (i < (tamBase/3))
    {
        if (mesa1->cod == -1)
        {
            // salva elemnto na hashmap
            salvaMesa(mesa, hashCompartimentos); 
            break;
        }
        mesa1 = leMesa(hashCompartimentos);
        i++;
    }

    // Atualiza a lista com a nova posição do último elemento
    aux->tam++;
    fseek(hash, -tamanhoCabecalho(), SEEK_CUR);
    salvaLista(aux, hash);

    end = clock();
    salva_no_log_hash(log, (double)(end - begin) / CLOCKS_PER_SEC, "Adicionado no hash\t");
}

FILE *criaHash(int tam, FILE *hash)
{
    FILE *hashCompartimentos;
    TLista lista;
    TMesa mesa;
    mesa.cod = -1;

    if (((hashCompartimentos = fopen("tabelaHash.dat", "w+b")) == NULL))
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
            lista.pos = ftell(hashCompartimentos); // salva o endereço do primeiro elemento daquela lista
            lista.prox = i + 1;
            for (int j = 0; j < tam/3; j++)
            { // 10 tá aqui temporariamente
                salvaMesa(&mesa, hashCompartimentos);
            }
            salvaLista(&lista, hash);
        }
        return hashCompartimentos;
    }
}

TMesa *busca_no_hash(FILE *hashCompartimentos, FILE *hash, int tamBase, TMesa *mesa, FILE *log)
{
    clock_t begin, end;
    begin = clock();

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
    int i = 0; //ok
    fseek(hashCompartimentos, -tamanho_registro_Mesa(), SEEK_CUR);

    while (i < (tamBase/3))
    {
        if (mesa1->cod == mesa->cod)
        {
            end = clock();
            salva_no_log_hash(log, (double)(end - begin) / CLOCKS_PER_SEC, "Mesa encontrada!!\t");

            return mesa1;
            break;
        }
        mesa1 = leMesa(hashCompartimentos);
        i++;
    }

    end = clock();
    salva_no_log_hash(log, (double)(end - begin) / CLOCKS_PER_SEC, "Mesa nao encontrada!!\t");
    mesa1->cod = -1;

    return mesa1;
}

void exclui_no_hash(FILE *hashCompartimentos, FILE *hash, int tamBase, TMesa *mesa, FILE *log)
{
    clock_t begin, end;
    begin = clock();

    TLista *aux;
    TMesa *mesa1;

    mesa1 = busca_no_hash(hashCompartimentos, hash, tamBase, mesa, log);

    if (mesa1==NULL){
        printf("NÃO EXISTE MESA A SER EXCLUIDA COM ESSE CODIGO");
        end = clock();
        salva_no_log_hash(log, (double)(end - begin) / CLOCKS_PER_SEC, "A messa nao pode ser excluida pois nao existe!!\t");
        return;
    }

    rewind(hashCompartimentos);
    rewind(hash);

    int posicaoNoHash = calculaHash(mesa->cod, tamBase);

    fseek(hash, posicaoNoHash * tamanhoCabecalho(), SEEK_SET);
    aux = leCabecalho(hash);

    fseek(hashCompartimentos, aux->pos - tamanho_registro_Mesa(), SEEK_SET);

    mesa1 = leMesa(hashCompartimentos);

    // Percorre a lista até o final
    int i = 0; //ok
    fseek(hashCompartimentos, -tamanho_registro_Mesa(), SEEK_CUR);

    while (i < (tamBase/3))
    {
        if (mesa1->cod == mesa->cod)
        {
            mesa1->cod=-1;
            salvaMesa(mesa1, hashCompartimentos);
            break;
        }
        mesa1 = leMesa(hashCompartimentos);
        i++;
    }

    printf("MESA EXCLUIDA COM SUCESSO!");

    end = clock();
    salva_no_log_hash(log, (double)(end - begin) / CLOCKS_PER_SEC, "Mesa excluida!!\t");

}

void adiciona_todas_as_mesas_no_hash(FILE *mesas, FILE *hash, FILE *hashCompartimentos, FILE * log, int tamBase){
    
    rewind(mesas);

    TMesa *mesa;
    
    while (!feof(mesas))
    {
        mesa = leMesa(mesas);
        if (mesa == NULL)
            break;   
        adiciona_no_hash(mesa,hashCompartimentos,hash,tamBase,log);
    }
}

