#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include<stdlib.h>
#include<stdio.h>

//faz o calculo do Hash para o endereço
int calculaHash(int cod, int tamBase);

//adiciona elemento na tabela e faz o tratameto de colisao
void adiciona_no_hash(TMesa *mesa, FILE *hashCompartimentos, FILE *hash, int tamBase);

//cria o hash
FILE *criaHash(char *nome_do_hash, int tam, FILE *mesas);


#endif