#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// #include "Entidades/Headers/mesas.h"
#include "mesas.c"
#include "funcionario.c"
#include "../Utilitarios/Utilitarios.c"
#include "interface.c"
#include "../hashExterno/hashExterno.c"
#include "../hashExterno/lista.h"

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
        FILE *hashCompartimentos;
        int qntMesas = 30;

        criarBase(mesas, qntMesas, "mesa");
        // imprimeTodosMesa(mesas);

        criarBase(funcionarios, qntMesas / 3, "funcionario");
        // imprimeTodos(funcionarios);

        SalvaTodosOsPedidos(pedidos);
        // imprimeTodosPedido(pedidos);
        /*printf("Ordenando mesas por Insertionsort");
        insertionSortMesa(mesas, qntMesas);
        imprimeTodosMesa(mesas);
        */
        
        TMesa *mesa1;
        mesa1 = mesa(23,2,230);
        
        FILE *hash;
        if ((hash = fopen("hashmap.dat", "w+b")) == NULL )
    {
        printf("erro ao abrir");
        exit(1);
    }
        
        hashCompartimentos = criaHash( 30 - 1, hash);
      
        adiciona_no_hash(mesa1,hashCompartimentos,hash,30 -1);

        mesa1 = busca_no_hash(hashCompartimentos, hash, 30 -1, mesa1);

        // MENU(mesas, pedidos, funcionarios, log, qntMesas);

        fclose(pedidos);
        fclose(mesas);
        fclose(funcionarios);
    }
    return 0;
}

