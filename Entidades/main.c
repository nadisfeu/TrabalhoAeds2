#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// #include "Entidades/Headers/mesas.h"
#include "mesas.c"
#include "funcionario.c"
#include "../Utilitarios/Utilitarios.c"
#include "interface.c"

int main()
{/*
    FILE *mesas, *pedidos, *funcionarios, *log;
    if ((mesas = fopen("mesas.dat", "w+b")) == NULL || (pedidos = fopen("pedidos.dat", "w+b")) == NULL || (funcionarios = fopen("funcionarios.dat", "w+b")) == NULL || (log = fopen("log.txt", "a+")) == NULL)
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {
       
        criarBase(mesas, qntMesas, "mesa");
        //imprimeTodosMesa(mesas);

        criarBase(funcionarios, qntMesas / 3, "funcionario");
        //imprimeTodos(funcionarios);
        
 
        SalvaTodosOsPedidos(pedidos);
        //imprimeTodosPedido(pedidos);

        printf("Ordenando mesas por Insertionsort");
        insertionSortMesa(mesas, qntMesas);
        imprimeTodosMesa(mesas);

        MENU(mesas, pedidos, funcionarios, log, qntMesas);

        fclose(pedidos);
        fclose(mesas);
        fclose(funcionarios);
        */
        int qntMesas = 300;

        return 0;
}
