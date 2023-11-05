#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "Utilitarios.h"

void salva_no_log(FILE *log, int comp, int time, char s[])
{
    fprintf(log, "Tipo de busca: %s", s);
    fprintf(log, "\tComparacoes: %d\t", comp);
    fprintf(log, "Tempo: %d\n", time);
}

int tamanho_arquivo(FILE *arq)
{
    fseek(arq, 0, SEEK_END);
    return trunc(ftell(arq)) / tamanho_registro();
}

void shuffle(int *vet, int MAX, int MIN)
{
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--)
    {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void criarBase(FILE *out, int tam, char *tipo)
{
    int resultado;
    int vet[tam];
    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    // shuffle(vet,tam,(tam*1)/100);

    resultado = strcmp(tipo, "mesa");

    if (strcmp(tipo, "mesa") == 0)
    {
        printf("\nGerando a base de dados da Mesa...\n");
        TMesa *f;
        for (int i = 0; i < tam; i++)
        {
            f = mesa(vet[i], (rand() % 10 + 1), 100);
            salvaMesa(f, out);
        }

        free(f);
    }
    else if (strcmp(tipo, "funcionario") == 0)
    {
        printf("\nGerando a base de dados de Funcionarios...\n");
        TFunc *f;
        for (int i = 0; i < tam; i++)
        {
            f = funcionario(vet[i], "Julio", "889.785.521-09", "22/10/2003", (i + 1) * 1000 + ((i - 1) * 231));
            salva(f, out);
        }

        free(f);
    }
    else if (strcmp(tipo, "pedido") == 0)
    {
        printf("\nGerando a base de dados de Pedidos...\n");
        TPedido *f;
        for (int i = 0; i < tam; i++)
        {
            f = Pedido(vet[i], "Cerveja Artesanal", 25.5);
            salvaPedido(f, out);
        }

        free(f);
    }
    else
        printf("ERRO AO DEFINIR O TIPO");
}

TFunc *BuscaSequencial(FILE *log, FILE *out, int cod, int qnt, char *tipo)
{
    if (strcmp(tipo, "funcionario") == 0)
    {
        TFunc *geral = (TFunc *)malloc(sizeof(TFunc));
        geral->cod = 0;
        int comp = 0;
        time_t begin = time(NULL);

        for (int i = 0; i < qnt; i++)
        {
            fseek(out, tamanho_registro() * i, SEEK_SET);
            geral = le(out);
            comp++;
            if (geral->cod == cod)
            {
                time_t end = time(NULL);
                salva_no_log(log, comp, (end - begin), "Busca Sequencial Funcionario - Encontrado\t");
                return geral;
            }
        }
        time_t end = time(NULL);
        salva_no_log(log, comp, end - begin, "Busca Sequencial Funcionario - Nao Encontrado\t");
        return geral;
    }
    else if (tipo, "mesa")
    {
        TMesa *geral = (TMesa *)malloc(sizeof(TMesa));
        geral->cod = 0;
        int comp = 0;
        time_t begin = time(NULL);

        for (int i = 0; i < qnt; i++)
        {
            fseek(out, tamanho_registro_Mesa() * i, SEEK_SET);
            geral = leMesa(out);
            comp++;
            if (geral->cod == cod)
            {
                time_t end = time(NULL);
                salva_no_log(log, comp, (end - begin), "Busca Sequencial Mesa - Encontrado\t");
                return geral;
            }
        }
        time_t end = time(NULL);
        salva_no_log(log, comp, end - begin, "Busca Sequencial Mesa - Nao Encontrado\t");
        return geral;
    }
    else if (strcmp(tipo,"pedido") == 0)
    {
       
    }
    
}

/*
TFunc *BuscaBinaria(FILE *log, int chave, FILE *in, int inicio, int fim)
{
    TFunc *f = NULL;
    int cod = -1;
    time_t begin = time(NULL);
    int comp = 0;

    while (inicio <= fim && cod != chave)
    {
        int meio = trunc((inicio + fim) / 2);
        fseek(in, (meio - 1) * tamanho_registro(), SEEK_SET);
        f = le(in);
        cod = f->cod;

        if (f)
        {
            if (cod > chave)
            {
                comp++;
                fim = meio - 1;
            }
            else
            {
                comp++;
                inicio = meio + 1;
            }
        }
    }

    if (cod == chave)
    {
        time_t end = time(NULL);
        salva_no_log(log, comp, (end - begin), "BuscaBinaria-Encontrado");
        return f;
    }
    else
    {
        time_t end = time(NULL);
        salva_no_log(log, comp, (end - begin), "BuscaBinaria-Nao_Encontrado");
        return NULL;
    }
}
*/