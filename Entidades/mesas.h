#ifndef MESAS_H_INCLUDED
#define MESAS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "pedidos.c"

typedef struct mesa
{
    int cod;
    int numClientes;
    double divida;
    int numeroPedidos;
    int pedidos[100];
} TMesa;

//retorna o tamanho do registro de cada funcionario
int tamanho_registro_Mesa();

//cria Funcionario

TMesa *mesa(int cod, int numClientes, double divida); 

//salva os funcionarios dentro do arquivo
void salvaMesa(TMesa *mesa, FILE *out);

// le e retorna os dados do funcionario do arquivo 
TMesa *leMesa(FILE *in);

//imprime uma unica na tela
void imprimeMesa(TMesa mesa);

void imprimeTodosMesa(FILE *in);

//Faz a leitura e calcula a divida de todos os pedidos feitos na mesa 
//void LePedidosDaMesa(FILE *log, FILE *pedidos, TMesa *m);

#endif