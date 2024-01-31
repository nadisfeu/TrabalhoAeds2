#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "encadeamento_exterior.h"
#include "lista_compartimentos.c"


void cria_hash(char *nome_arquivo_hash, int m)
{
	FILE *hash;

	if (hash = fopen(nome_arquivo_hash, "a+") == NULL)
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {
	// Estamos usando tabela hash de tamanho 7 nos testes
	// Adicionar 7 compartimentos que nao apontam para ninguem (prox = -1)
	ListaCompartimentos *tab_hash, *tab_hash_saida;

	tab_hash = cria_compartimentos(7,
		compartimento_hash(-1),
		compartimento_hash(-1),
		compartimento_hash(-1),
		compartimento_hash(-1),
		compartimento_hash(-1),
		compartimento_hash(-1),
		compartimento_hash(-1));

	//M = 7 conforme definido no cabeçalho desse arquivo
	cria_hash(nome_arquivo_hash, m);

	tab_hash_saida = le_compartimentos(nome_arquivo_hash);

	ASSERT_EQUAL_CMP(tab_hash, tab_hash_saida, cmp_compartimentos);
	libera_compartimentos(tab_hash);
	libera_compartimentos(tab_hash_saida);


	}
	//TODO: criar a tabela hash
}

/*
int busca(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m)
{
	//TODO: Inserir aqui o codigo do algoritmo
    return INT_MAX;
}


int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int num_registros, int m)
{
	//TODO: Inserir aqui o codigo do algoritmo de insercao
    return INT_MAX;
}

int exclui(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m)
{
	//TODO: Inserir aqui o codigo do algoritmo de remocao
    return INT_MAX;
}
*/