#ifndef UTILITARIOS_H_INCLUDED
#define UTILITARIOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

#include "../Entidades/funcionario.h"
#include "../Entidades/mesas.h"
#include "../Entidades/pedidos.h"

void salva_no_log(FILE *log, int comp, double time, char s[]);

int tamanho_arquivo(FILE *arq);

// embaralha base de dados
void shuffle(int *vet,int MAX,int MIN);

// Tipos validos: funcionario, pedido, mesa
// verifica o tipo e cria a base desejada
void criarBase(FILE *out, int tam, char *tipo);

// Tipos validos: funcionario, pedido, mesa
TFunc *BuscaSequencial(FILE *log, FILE *out, int cod, int qnt);

TMesa *BuscaSequencialMesa(FILE *log, FILE *out, int cod, int qnt);

TPedido *BuscaSequencialPedido(FILE *log, FILE *out, int cod, int qnt);

//Realiza a busca binaria por um funcionario
TFunc *BuscaBinariaFuncionario(FILE *log, int chave, FILE *in, int inicio, int fim);
//realiza a busca binaria por uma mesa 
TMesa *BuscaBinariaMesa(FILE *log, int chave, FILE *in, int inicio, int fim);

//Realiza a busca binaria por um Pedido
TPedido *BuscaBinariaPedido(FILE *log, int chave, FILE *in);

//adiciona na mesa o codigo de mais um pedido realizado
void fazPedidoMesa(FILE *log,FILE *out,FILE *pedidos, TMesa *m, int cod);


//METODOS DE ORDENCAO

//Função insertion sort em disco para os funcionarios.
void insertionSort(FILE *arq, int tam);

//Função insertion sort em disco para as mesas.
void insertionSortMesa(FILE *arq, int tam);
#endif