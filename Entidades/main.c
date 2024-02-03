#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// #include "Entidades/Headers/mesas.h"
#include "mesas.c"
#include "funcionario.c"
#include "../Utilitarios/Utilitarios.c"
#include "interface.c"
#include "../HashExterno/hashExterno.c"
#include "../HashExterno/lista.c"

int main()
{
    FILE *mesas, *pedidos, *funcionarios, *log;
    FILE *hash;
    FILE *hashCompartimentos;


    if ((mesas = fopen("mesas.dat", "w+b")) == NULL ||
        (pedidos = fopen("pedidos.dat", "w+b")) == NULL ||
        (funcionarios = fopen("funcionarios.dat", "w+b")) == NULL ||
        (log = fopen("log.txt", "a+")) == NULL ||
        (hash = fopen("hashmap.dat", "w+b")) == NULL)
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {

        int qntMesas = 30;
        int tamBase = qntMesas - 1;

        criarBase(mesas, qntMesas, "mesa");
        imprimeTodosMesa(mesas);

        criarBase(funcionarios, qntMesas / 3, "funcionario");
        // imprimeTodos(funcionarios);

        SalvaTodosOsPedidos(pedidos);
        // imprimeTodosPedido(pedidos);
        /*printf("Ordenando mesas por Insertionsort");
        insertionSortMesa(mesas, qntMesas);
        imprimeTodosMesa(mesas);
        */

        hashCompartimentos = criaHash(tamBase, hash);
        adiciona_todas_as_mesas_no_hash(mesas, hash, hashCompartimentos, log, tamBase);


        MENU(mesas, pedidos, funcionarios, log,hashCompartimentos, hash,tamBase, qntMesas);
        
        /*
        adiciona_no_hash(mesa1, hashCompartimentos, hash, 30 - 1, log);

        mesa1 = busca_no_hash(hashCompartimentos, hash, 30 - 1, mesa1, log);

        exclui_no_hash(hashCompartimentos, hash, 30 - 1, mesa1, log);

        mesa1 = busca_no_hash(hashCompartimentos, hash, 30 - 1, mesa1, log);
        */

        fclose(pedidos);
        fclose(mesas);
        fclose(funcionarios);
    }
    return 0;
}
