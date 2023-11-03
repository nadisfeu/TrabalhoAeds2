#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct Funcionario
{
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

//retorna o tamanho do registro de cada funcionario
int tamanho_registro();

//cria Funcionario

TFunc *funcionario (int cod, char *nome, char *cpf, char *data_nascimento, double salario); 

//salva os funcionarios dentro do arquivo
void salva(TFunc *func, FILE *out);

// le e retorna os dados do funcionario do arquivo 
TFunc *le(FILE *in);

//imprime um unico funcionario na tela
void imprime(TFunc *func);

void imprimeTodos(FILE *in);

void SalvaFuncOrdenados(FILE *out, int qnt);

// salva os funcianrios de forma desordenada
void SalvaFuncDesordenados(FILE *out, int qnt);

#endif