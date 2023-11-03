#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct Cliente
{
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double divida;
} TCliente;

//retorna o tamanho do registro de cada funcionario
int tamanho_registro();

//cria Funcionario

TCliente *cliente(int cod, char *nome, char *cpf, char *data_nascimento, double divida); 

//salva os funcionarios dentro do arquivo
void salvaCliente(TCliente *cliente, FILE *out);

// le e retorna os dados do funcionario do arquivo 
TCliente *leCliente(FILE *in);

//imprime um unico funcionario na tela
void imprimeCliente(TCliente *cliente);

void imprimeTodosCliente(FILE *in);

void SalvaClienteOrdenados(FILE *out, int qnt);

void SalvaClienteDesordenados(FILE *out, int qnt);

#endif