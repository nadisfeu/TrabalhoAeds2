#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "Utilitarios.h"

void salva_no_log(FILE *log, int comp, double time, char s[])
{
    fprintf(log, "Tipo de busca: %s", s);
    fprintf(log, "\tComparacoes: %d\t", comp);
    fprintf(log, "Tempo: %.2f\n", time);
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
    int vet[tam];
    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    shuffle(vet, tam, (tam * 10) / 100);

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
        shuffle(vet, tam, (tam * 10) / 100);
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

TFunc *BuscaSequencial(FILE *log, FILE *out, int cod, int qnt)
{
    clock_t begin, end;
    begin = clock();
    int comp = 0;

    TFunc *geral = (TFunc *)malloc(sizeof(TFunc));
    geral->cod = 0;

    for (int i = 0; i < qnt; i++)
    {
        fseek(out, tamanho_registro() * i, SEEK_SET);
        geral = le(out);
        comp++;
        if (geral->cod == cod)
        {
            end = clock();
            salva_no_log(log, comp, (double)(end - begin) / CLOCKS_PER_SEC, "Busca Sequencial Funcionario - Encontrado\t");
            return geral;
        }
    }
    end = clock();
    salva_no_log(log, comp, (double)(end - begin) / CLOCKS_PER_SEC, "Busca Sequencial Funcionario - Nao Encontrado\t");
    return geral;
}

TMesa *BuscaSequencialMesa(FILE *log, FILE *out, int cod, int qnt)
{
    clock_t begin, end;
    begin = clock();
    int comp = 0;
    TMesa *geral = (TMesa *)malloc(sizeof(TMesa));
    for (int i = 0; i < qnt; i++)
    {
        fseek(out, tamanho_registro_Mesa() * i, SEEK_SET);
        geral = leMesa(out);
        comp++;
        if (geral->cod == cod)
        {
            end = clock();
            salva_no_log(log, comp, (double)(end - begin) / CLOCKS_PER_SEC, "Busca Sequencial Mesa - Encontrado\t");
            return geral;
        }
    }
    end = clock();
    salva_no_log(log, comp, (double)(end - begin) / CLOCKS_PER_SEC, "Busca Sequencial Mesa - Nao Encontrado\t");
    return geral;
}

TPedido *BuscaSequencialPedido(FILE *log, FILE *out, int cod, int qnt)
{
    int comp = 0;
    clock_t begin, end;
    begin = clock();
    TPedido *geral = (TPedido *)malloc(sizeof(TPedido));

    for (int i = 0; i < qnt; i++)
    {
        fseek(out, tamanho_registro_Pedido() * i, SEEK_SET);
        geral = lePedido(out);
        comp++;
        if (geral->cod == cod)
        {
            end = clock();
            salva_no_log(log, comp, (double)(end - begin) / CLOCKS_PER_SEC, "Busca Sequencial Pedido - Encontrado\t");
            return geral;
        }
    }
    end = clock();
    salva_no_log(log, comp, (double)(end - begin) / CLOCKS_PER_SEC, "Busca Sequencial Pedido - Nao Encontrado\t");
    return geral;
}

TFunc *BuscaBinariaFuncionario(FILE *log, int chave, FILE *in, int inicio, int fim)
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

TMesa *BuscaBinariaMesa(FILE *log, int chave, FILE *in, int inicio, int fim)
{
    rewind(in);
    TMesa *f = NULL;
    int cod = -1;
    time_t begin = time(NULL);
    int comp = 0;

    while (inicio <= fim && cod != chave)
    {
        int meio = trunc((inicio + fim) / 2);
        fseek(in, (meio - 1) * tamanho_registro_Mesa(), SEEK_SET);
        f = leMesa(in);
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
        salva_no_log(log, comp, (end - begin), "BuscaBinaria-Mesa-Encontrado");
        return f;
    }
    else
    {
        time_t end = time(NULL);
        salva_no_log(log, comp, (end - begin), "BuscaBinaria-Mesa-Nao_Encontrado");
        return NULL;
    }
}

TPedido *BuscaBinariaPedido(FILE *log, int chave, FILE *in)
{
    rewind(in);
    TPedido *f = NULL;
    int cod = -1;
    time_t begin = time(NULL);
    int comp = 0;
    int inicio = inicioPedidos;
    int fim = fimPedidos;

    while (inicio <= fim && cod != chave)
    {
        int meio = trunc((inicio + fim) / 2);
        fseek(in, (meio - 1) * tamanho_registro_Pedido(), SEEK_SET);
        f = lePedido(in);
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
        salva_no_log(log, comp, (end - begin), "BuscaBinaria-Pedido-Encontrado");
        return f;
    }
    else
    {
        time_t end = time(NULL);
        salva_no_log(log, comp, (end - begin), "BuscaBinaria-Pedido-Nao_Encontrado");
        return NULL;
    }
}

void fazPedidoMesa(FILE *log, FILE *out, FILE *pedidos, TMesa *m, int cod)
{
    TPedido *pedido;
    // falta somar o valor do pedido na mesas
    if ((pedido = BuscaBinariaPedido(log, cod, pedidos)) == NULL)
    {
        printf("O pedido de codigo %d nao existe", cod);
        return;
    }

    rewind(out);
    TMesa *mesa;

    while ((mesa = leMesa(out)) != NULL)
    {
        if (mesa->cod == m->cod)
        {
            // Encontramos o registro desejado
            m->pedidos[m->numeroPedidos] = cod;
            m->numeroPedidos = m->numeroPedidos + 1;
            m->divida += pedido->valor;
            imprimeMesa(*m);
            fseek(out, -tamanho_registro_Mesa(), SEEK_CUR);
            fwrite(m, tamanho_registro_Mesa(), 1, out);
            printf("Pedido realizado com sucesso!\n");
            break; // Sair do loop
        }
    }
    free(mesa);
}

void insertionSort(FILE *arq, int tam)
{
    int i;
    // faz o insertion sort
    for (int j = 2; j <= tam; j++)
    {
        // posiciona o arquivo no registro j
        fseek(arq, (j - 1) * tamanho_registro(), SEEK_SET);
        TFunc *fj = le(arq);
        i = j - 1;
        // posiciona o cursor no registro i
        fseek(arq, (i - 1) * tamanho_registro(), SEEK_SET);
        TFunc *fi = le(arq);
        while ((i > 0) && (fi->cod > fj->cod))
        {
            // posiciona o cursor no registro i+1
            fseek(arq, i * tamanho_registro(), SEEK_SET);
            salva(fi, arq);
            i = i - 1;
            // lê registro i
            fseek(arq, (i - 1) * tamanho_registro(), SEEK_SET);
            fi = le(arq);
        }
        // posiciona cursor no registro i + 1
        fseek(arq, (i)*tamanho_registro(), SEEK_SET);
        // salva registro j na posição i
        salva(fj, arq);
    }
    // descarrega o buffer para ter certeza que dados foram gravados
    fflush(arq);
}

void insertionSortMesa(FILE *arq, int tam)
{
    int i;
    // faz o insertion sort
    for (int j = 2; j <= tam; j++)
    {
        // posiciona o arquivo no registro j
        fseek(arq, (j - 1) * tamanho_registro_Mesa(), SEEK_SET);
        TFunc *fj = le(arq);
        i = j - 1;
        // posiciona o cursor no registro i
        fseek(arq, (i - 1) * tamanho_registro_Mesa(), SEEK_SET);
        TFunc *fi = le(arq);
        while ((i > 0) && (fi->cod > fj->cod))
        {
            // posiciona o cursor no registro i+1
            fseek(arq, i * tamanho_registro_Mesa(), SEEK_SET);
            salva(fi, arq);
            i = i - 1;
            // lê registro i
            fseek(arq, (i - 1) * tamanho_registro_Mesa(), SEEK_SET);
            fi = le(arq);
        }
        // posiciona cursor no registro i + 1
        fseek(arq, (i)*tamanho_registro_Mesa(), SEEK_SET);
        // salva registro j na posição i
        salva(fj, arq);
    }
    // descarrega o buffer para ter certeza que dados foram gravados
    fflush(arq);
}

void selecao_subst(FILE *arq)
{

    rewind(arq);

    TFunc *funcs[qntReg];
    TFunc *funcAux = (TFunc *)malloc(sizeof(TFunc));
    int flags[qntReg];
    int flag = 0;

    char nomeParticao[20];
    int qtdParticoes = 0;
    int substituido;

    FILE *particoes;

    // salvando uma parte do registro em memoria (1) *ok
    for (int i = 0; i < qntReg; i++)
    {
        funcAux = le(arq);
        funcs[i] = funcAux;
    }

    while (le(arq) != NULL)
    {
        // volta o arquivo em um registro para nãoi ter perda
        fseek(arq, -tamanho_registro(), SEEK_CUR);

        //(7)
        // descongela todos os registros
        for (int i = 0; i < qntReg; i++)
            flags[i] = 0;

        // cria e abre nova paritcao
        qtdParticoes++;
        sprintf(nomeParticao, "particao%i.dat", qtdParticoes);
        if ((particoes = fopen(nomeParticao, "wb+")) == NULL)
            printf("Erro criar arquivo de saida\n");

        while (flag == 0)
        {
            flag = 1;

            // selecionando a menor chave do registro vetor (2) *ok
            int menor_numero = funcs[0]->cod;

            // Percorre o vetor e atualiza o menor número se encontrar um valor menor. *ok
            for (int i = 0; i < qntReg; i++)
            {
                if (funcs[i]->cod < menor_numero && flags[i] == 0)
                {
                    menor_numero = funcs[i]->cod;
                    substituido = i;
                }
            }

            //(3)
            salva(funcs[substituido], particoes);
            imprimeTodos(particoes);
            
            
            // sobreescrevendo o funcionario removido pelo próximo na array(4)
            funcAux = le(arq);
            funcs[substituido] = funcAux;

            // congelamento da posição caso o numero seja menor (5)
            if (funcAux->cod < funcs[substituido]->cod)
            {
                flags[substituido] = 1;
            }

            // verifica se ainda tem algum congelado para (6)
            // caso não tenha volta pro (2)
            for (int i = 0; i < qntReg; i++)
            {
                printf("%d", flags[i]);
                if (flags[i] == 1)
                {
                    flag = 0;
                }
            }
        }
        //(7)
        fclose(particoes);
    }
}