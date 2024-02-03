#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include<stdlib.h>
#include<stdio.h>

void salva_no_log_hash(FILE *log, double time, char s[]);

//faz o calculo do Hash para o endereço
int calculaHash(int cod, int tamBase);

//adiciona elemento na tabela e faz o tratameto de colisao
void adiciona_no_hash(TMesa *mesa, FILE *hashCompartimentos, FILE *hash, int tamBase, FILE *log);

//cria o hash
FILE *criaHash(int tam, FILE *hash);

TMesa *busca_no_hash(FILE *hashCompartimentos, FILE *hash, int tamBase, TMesa *mesa, FILE *log);

void exclui_no_hash(FILE *hashCompartimentos, FILE *hash, int tamBase, TMesa *mesa, FILE *log);

#endif