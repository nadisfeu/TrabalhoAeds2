#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

#include "pedidos.h"

int tamanho_registro_Pedido(){
    return sizeof(int) // cod
    + sizeof(char)*30  // nome do pedido
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

//salva os Pedidos dentro do arquivo
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
    printf("\nPedido de codigo: %d\n", Pedido->cod);
    printf("Nome de pedidos %s\n", Pedido->nomePedido);
    printf("valor: %.2f\n", Pedido->valor);
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

//imprime toda a base de dados
void imprimeTodosPedido(FILE *in){
    TPedido *Pedido;
    rewind(in);
    
    printf("Lendo arquivo de Pedidos...\n");
    
    while((Pedido=lePedido(in))!=NULL){
        imprimePedido(Pedido);
        }
    
    free(Pedido);
    
    system("pause");
    system("cls");
}

void adicionaPedido(FILE *out,char nome[],int cod, double valor){
    TPedido *p = Pedido(cod,nome,valor);
    salvaPedido(p,out);
    free(p);
}

void SalvaTodosOsPedidos(FILE *out){
    adicionaPedido(out,"Cerveja Long Neck", 1, 7.34);
    adicionaPedido(out, "Vinho Rose", 2, 22.5);
    adicionaPedido(out, "Vinho Tinto", 3, 18 );
    
}