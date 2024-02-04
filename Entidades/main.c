#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "mesas.c"
#include "funcionario.c"
#include "../Utilitarios/Utilitarios.c"
#include "interface.c"
#include "../HashExterno/hashexterno.c"

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
        TMesa *mesa1;
        criarBase(mesas, qntMesas, "mesa");
        imprimeTodosMesa(mesas);

        int vetorParaPesquisar[5] = {17, 19, 21,23, 25};

        criarBase(funcionarios, qntMesas / 3, "funcionario");

        SalvaTodosOsPedidos(pedidos);

        /*printf("Ordenando mesas por Insertionsort");
        insertionSortMesa(mesas, qntMesas);
        imprimeTodosMesa(mesas);
        */

        hashCompartimentos = criaHash(tamBase, hash);
        adiciona_todas_as_mesas_no_hash(mesas, hash, hashCompartimentos, log, tamBase);

        mesa1 = mesa(12, 0, 0);


        //faz a busca
        for (int i = 0; i < 5; i++)
        {
            mesa1->cod =  vetorParaPesquisar[i];
            mesa1 = busca_no_hash(hashCompartimentos, hash, tamBase, mesa1, log);
            imprimeMesa(*mesa1);
        }

        //exclui uma mesa
        printf("\n\n");
        mesa1->cod = vetorParaPesquisar[2];
        exclui_no_hash(hashCompartimentos,hash,tamBase,mesa1,log);
        printf("\n\n");

        //refaz a busca
        for (int i = 0; i < 5; i++)
        {
            mesa1->cod =  vetorParaPesquisar[i];
            mesa1 = busca_no_hash(hashCompartimentos, hash, tamBase, mesa1, log);

            if (mesa1->cod == -1)
                printf("\ncodigo %d nao existe mais.\n", vetorParaPesquisar[i]);
            else
                imprimeMesa(*mesa1);
        }

        fclose(pedidos);
        fclose(mesas);
        fclose(funcionarios);
    }
    return 0;
}
