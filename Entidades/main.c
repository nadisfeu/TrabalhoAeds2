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
{
    FILE *mesas, *pedidos, *funcionarios, *log;
    if ((mesas = fopen("mesas.dat", "w+b")) == NULL || (pedidos = fopen("pedidos.dat", "w+b")) == NULL || (funcionarios = fopen("funcionarios.dat", "w+b")) == NULL || (log = fopen("log.txt", "a+")) == NULL)
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {
        int qntMesas = 300;
        criarBase(mesas, qntMesas, "mesa");
        //imprimeTodosMesa(mesas);

        criarBase(funcionarios, qntMesas / 3, "funcionario");
        //imprimeTodos(funcionarios);
        
        selecao_subst(funcionarios, qntMesas /3);


        // SalvaTodosOsPedidos(pedidos);
        // imprimeTodosPedido(pedidos);

        // Ordena os funcionarios usando a  tecnica de insertions sort
        //printf("\nOrdenando funcionarios por Insertionsort\n");
        //insertionSort(funcionarios, qntMesas / 3);
        //imprimeTodos(funcionarios);

        //printf("Ordenando funcionarios por Insertionsort");
        //insertionSortMesa(mesas, qntMesas);
        //imprimeTodosMesa(mesas);

        // MENU(mesas, pedidos, funcionarios, log, qntMesas);

        fclose(pedidos);
        fclose(mesas);
        fclose(funcionarios);

        return 0;
    }
}
