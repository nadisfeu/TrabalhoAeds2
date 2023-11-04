#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

#include "pedidos.h"

int tamanho_registro_Pedido(){
    return sizeof(int) // cod
    + sizeof(char)*30
    + sizeof(double) ; // valor
}


TPedido *Pedido(int cod,char nome[], double valor){
    TPedido *Pedido = (TPedido *)malloc(sizeof(TPedido));
    if (Pedido) memset(Pedido, 0, sizeof(TPedido));
    //copia valores para os campos de Pedido
    Pedido->cod = cod;
    strcpy(Pedido->nomePedido, nome);
    Pedido->valor = valor;
    return Pedido;
}


//salva os Pedidoionarios dentro do arquivo
void salvaPedido(TPedido *Pedido, FILE *out){

        fwrite(&Pedido->cod, sizeof(int),1, out);

        fwrite(Pedido->nomePedido, sizeof(char)*30,1, out);

        fwrite(&Pedido->valor, sizeof(double), 1, out);

}

TPedido *lePedido(FILE *in){
    TPedido *Pedido = (TPedido *) malloc(sizeof(TPedido));
    if(0 >= fread(&Pedido->cod, sizeof(int), 1, in)){
        free(Pedido);
        return NULL;
    }
    fread(Pedido->nomePedido, sizeof(char)*30, 1, in);
    fread(&Pedido->valor, sizeof(double), 1, in);
    return Pedido;
}

void imprimePedido(TPedido *Pedido){
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    printf("\nPedidoionario de codigo: %d\n", Pedido->cod);
    printf("Numero de Clientes %s\n", Pedido->nomePedido);
    printf("valor: %.2f\n", Pedido->valor);
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

//imprime toda a base de dados
void imprimeTodosPedido(FILE *in){
    TPedido *Pedido;
    rewind(in);
    
    printf("Lendo arquivo de Pedidoionarios...\n");
    
    while((Pedido=lePedido(in))!=NULL){
        imprimePedido(Pedido);
        }
    
    free(Pedido);
    
    system("pause");
    system("cls");
}

/*
//salva todos os Pedidoionarios de forma ordenada
void salvaPedidoOrdenados(FILE *out, int qnt){
TPedido *f;
    for(int i = 0; i < qnt; i++){
        f= Pedidoionario(i+1,"CaoMiudo","000.000.000-00","01/01/1980",3000);
        salva(f,out);   
    }
free(f);
}

//salva todos os Pedidoionarios de forma desordenada
void salvaPedidoDesordenados(FILE *out, int qnt){
    srand(time(NULL));
    TPedido *f;
    for(int i = 0; i < qnt; i++){
        f= Pedidoionario(rand() % qnt,"CaoMiudo","000.000.000-00","01/01/1980",3000);
        salva(f,out);
    }
free(f);
}
*/