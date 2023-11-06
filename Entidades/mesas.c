#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

//#include "Entidades/Headers/mesas.h"
#include "mesas.h"

int tamanho_registro_Mesa(){
    return sizeof(int) // cod
    + sizeof(int)     // numClientes
    + sizeof(double) // divida
    + sizeof(int)
    + sizeof(int)*100; //pedidos
}


TMesa *mesa(int cod, int numClientes, double divida){
    TMesa *mesa = (TMesa *)malloc(sizeof(TMesa));
    if (mesa) memset(mesa, 0, sizeof(TMesa));
    //copia valores para os campos de mesa
    mesa->cod = cod;
    mesa->numClientes = numClientes;
    mesa->divida = divida;
    mesa->numeroPedidos = 0;
    
    return mesa;
}


//salva os mesaionarios dentro do arquivo
void salvaMesa(TMesa *mesa, FILE *out){
        fwrite(&mesa->cod, sizeof(int),1, out);
        fwrite(&mesa->numClientes, sizeof(int),1, out);
        fwrite(&mesa->divida, sizeof(double), 1, out);
        fwrite(&mesa->numeroPedidos, sizeof(int),1, out);
        fwrite(mesa->pedidos, sizeof(int),100, out);
}


TMesa *leMesa(FILE *in){ 
    TMesa *mesa = (TMesa *) malloc(sizeof(TMesa));
    if(0 >= fread(&mesa->cod, sizeof(int), 1, in)){
        free(mesa);
        return NULL;
    }
    fread(&mesa->numClientes, sizeof(int), 1, in);
    fread(&mesa->divida, sizeof(double), 1, in);
    fread(&mesa->numeroPedidos, sizeof(int),1, in);
    fread(mesa->pedidos,sizeof(int),100,in);
    return mesa;
}

void imprimeMesa(TMesa mesa){
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    printf("\nMesa de codigo: %d\n", mesa.cod);
    printf("Numero de Clientes %d\n", mesa.numClientes);
    printf("divida: %.2f\n", mesa.divida);
    printf("Numero de pedidos: %d ", mesa.numeroPedidos);
    printf("Lista de pedidos:\t");
    for (int i = 0; i < mesa.numeroPedidos; i++)
        printf("%d\t", mesa.pedidos[i]);
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

//imprime toda a base de dados
void imprimeTodosMesa(FILE *in){
    TMesa *mesa;
    rewind(in);
    
    printf("Lendo arquivo de mesa...\n");
    
    while((mesa=leMesa(in))!=NULL){
        imprimeMesa(*mesa);
        }
    
    free(mesa);
    
    system("pause");
    system("cls");
}

void fazPedidoMesa(TMesa *m, int cod){
    m->pedidos[m->numeroPedidos] = cod;
    m->numeroPedidos++;
}
