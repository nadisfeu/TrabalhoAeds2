#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

#include "Entidades/Headers/clientes.h"

int tamanho_registro(){
    return sizeof(int) // cod
    + sizeof(char)*50  //nome
    + sizeof(char)*15 //cpf
    + sizeof(char)*11  //data
    + sizeof(double); // divida
}


TCliente *clienteionario (int cod, char *nome, char *cpf, char *data_nascimento, double divida){
    TCliente *cliente = (TCliente *)malloc(sizeof(TCliente));
    if (cliente) memset(cliente, 0, sizeof(TCliente));
    //copia valores para os campos de cliente
    cliente->cod = cod;
    strcpy(cliente->nome, nome);
    strcpy(cliente->cpf, cpf);
    strcpy(cliente->data_nascimento, data_nascimento);
    cliente->divida = divida;
    return cliente;
}


//salva os clienteionarios dentro do arquivo
void salva(TCliente *cliente, FILE *out){

        fwrite(&cliente->cod, sizeof(int),1, out);

        fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);

        fwrite(cliente->cpf, sizeof(char),  sizeof(cliente->cpf), out);

        fwrite(cliente->data_nascimento, sizeof(char), sizeof(cliente->data_nascimento), out);

        fwrite(&cliente->divida, sizeof(double), 1, out);

}

TCliente *le(FILE *in){
    TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));
    if(0 >= fread(&cliente->cod, sizeof(int), 1, in)){
        free(cliente);
        return NULL;
    }
    fread(cliente->nome, sizeof(char), sizeof(cliente->nome), in);
    fread(cliente->cpf, sizeof(char), sizeof(cliente->cpf), in);
    fread(cliente->data_nascimento, sizeof(char), sizeof(cliente->data_nascimento), in);
    fread(&cliente->divida, sizeof(double), 1, in);
    return cliente;
}

void imprime(TCliente *cliente){
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    printf("\nclienteionario de codigo: %d\n", cliente->cod);
    printf("Nome do clienteionario: %s\n", cliente->nome);
    printf("CPF do clienteionario: %s\n", cliente->cpf);
    printf("Data de nascimento: %s\n", cliente->data_nascimento);
    printf("divida: %.2f\n", cliente->divida);
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

//imprime toda a base de dados
void imprimeTodos(FILE *in){
    TCliente *f;
    rewind(in);
    
    printf("Lendo arquivo de clienteionarios...\n");
    
    while((f=le(in))!=NULL){
        imprime(f);
        }
    
    free(f);
    
    system("pause");
    system("cls");
}

//salva todos os clienteionarios de forma ordenada
void SalvaclienteOrdenados(FILE *out, int qnt){
TCliente *f;
    for(int i = 0; i < qnt; i++){
        f= clienteionario(i+1,"CaoMiudo","000.000.000-00","01/01/1980",3000);
        salva(f,out);   
    }
free(f);
}

//salva todos os clienteionarios de forma desordenada
void SalvaclienteDesordenados(FILE *out, int qnt){
    srand(time(NULL));
    TCliente *f;
    for(int i = 0; i < qnt; i++){
        f= clienteionario(rand() % qnt,"CaoMiudo","000.000.000-00","01/01/1980",3000);
        salva(f,out);
    }
free(f);
}
