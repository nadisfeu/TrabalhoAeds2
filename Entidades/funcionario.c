#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

#include "funcionario.h"

int tamanho_registro(){
    return sizeof(int) // cod
    + sizeof(char)*50  //nome
    + sizeof(char)*15 //cpf
    + sizeof(char)*11  //data
    + sizeof(double); // salrio
}


TFunc *funcionario (int cod, char *nome, char *cpf, char *data_nascimento, double salario){
    TFunc *func = (TFunc *)malloc(sizeof(TFunc));
    if (func) memset(func, 0, sizeof(TFunc));
    //copia valores para os campos de func
    func->cod = cod;
    strcpy(func->nome, nome);
    strcpy(func->cpf, cpf);
    strcpy(func->data_nascimento, data_nascimento);
    func->salario = salario;
    return func;
}


//salva os funcionarios dentro do arquivo
void salva(TFunc *func, FILE *out){

        fwrite(&func->cod, sizeof(int),1, out);

        fwrite(func->nome, sizeof(char), sizeof(func->nome), out);

        fwrite(func->cpf, sizeof(char),  sizeof(func->cpf), out);

        fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), out);

        fwrite(&func->salario, sizeof(double), 1, out);

}

TFunc *le(FILE *in){
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if(0 >= fread(&func->cod, sizeof(int), 1, in)){
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}

void imprime(TFunc *func){
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    printf("\nFuncionario de codigo: %d\n", func->cod);
    printf("Nome do funcionario: %s\n", func->nome);
    printf("CPF do funcionario: %s\n", func->cpf);
    printf("Data de nascimento: %s\n", func->data_nascimento);
    printf("Salario: %.2f\n", func->salario);
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

//imprime toda a base de dados
void imprimeTodos(FILE *in){
    TFunc *f;
    rewind(in);
    
    printf("Lendo arquivo de funcionarios...\n");
    
    while((f=le(in))!=NULL){
        imprime(f);
        }
    
    free(f);
    
    system("pause");
    system("cls");
}

//salva todos os funcionarios de forma ordenada
void SalvaFuncOrdenados(FILE *out, int qnt){
TFunc *f;
    for(int i = 0; i < qnt; i++){
        f= funcionario(i+1,"CaoMiudo","000.000.000-00","01/01/1980",3000);
        salva(f,out);   
    }
free(f);
}

//salva todos os funcionarios de forma desordenada
void SalvaFuncDesordenados(FILE *out, int qnt){
    srand(time(NULL));
    TFunc *f;
    for(int i = 0; i < qnt; i++){
        f= funcionario(rand() % qnt,"CaoMiudo","000.000.000-00","01/01/1980",3000);
        salva(f,out);
    }
free(f);
}
