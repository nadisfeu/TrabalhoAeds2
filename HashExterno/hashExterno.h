#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

//faz o calculo do Hash para o endereço
int calculaHash(int cod, int tamBase);

//cria o hash
void criaHash(char *nome_do_hash, int tam, FILE *mesas);


#endif