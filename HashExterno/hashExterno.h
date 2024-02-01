#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

//faz o calculo do Hash para o endereço
int calculaHash(int cod, int tamBase);

//adiciona elemento na tabela e faz o tratameto de colisao
void adiciona_no_hash(TMesa *mesa, FILE *hashCompartimentos, FILE *hash, int tamBase);

//cria o hash
void criaHash(char *nome_do_hash, int tam, FILE *mesas);


#endif