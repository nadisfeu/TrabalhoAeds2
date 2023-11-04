#ifndef PedidoS_H_INCLUDED
#define PedidoS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct Pedido
{   int cod;
    char nomePedido[30];
    double valor;
} TPedido;

//retorna o tamanho do registro de cada funcionario
int tamanho_registro_Pedido();

//cria Funcionario

TPedido *Pedido(int cod,char nome[], double valor); 

//salva os funcionarios dentro do arquivo
void salvaPedido(TPedido *Pedido, FILE *out);

// le e retorna os dados do funcionario do arquivo 
TPedido *lePedido(FILE *in);

//imprime um unico funcionario na tela
void imprimePedido(TPedido *Pedido);

void imprimeTodosPedido(FILE *in);

void salvaPedidoOrdenados(FILE *out, int qnt);

void salvaPedidoDesordenados(FILE *out, int qnt);

#endif