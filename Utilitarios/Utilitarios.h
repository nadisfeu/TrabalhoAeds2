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

TFunc *BuscaBinaria(FILE *log, int chave, FILE *in, int inicio, int fim);

#endif