#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// #include "Entidades/Headers/mesas.h"
#include "mesas.c"
#include "funcionario.c"
#include "../Utilitarios/Utilitarios.c"

int main()
{
    FILE *mesas, *pedidos, *funcionarios, *log;
    if ((mesas = fopen("../output/mesas.dat", "w+b")) == NULL || (pedidos = fopen("../output/pedidos.dat", "a+b")) == NULL 
    || (funcionarios = fopen("../output/funcionarios.dat", "w+b")) == NULL || (log= fopen("../output/log.txt", "a+")) == NULL)
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {
    /*  FILE *a;
        a = fopen("teste.dat","w+b");
        TMesa *m;
        m = mesa(123, 2, 1550);
        salvaMesa(m, a);
        rewind(a);
        m = leMesa(a);
        printf("aa");
        imprimeMesa(*m); */

        int qntMesas = 50;
     
        criarBase(mesas, qntMesas,"mesa");
        imprimeTodosMesa(mesas);
        
        criarBase(funcionarios, qntMesas/4, "funcionario");
        imprimeTodos(funcionarios);

        /*
        criarBase(pedidos,6,"pedido");
        imprimeTodosPedido(pedidos);
        */
        
        adicionaPedido( pedidos, "cha", 21, 12.2);
        imprimeTodosPedido( pedidos);

        BuscaSequencialMesa(log, mesas, 2, 10);
        BuscaSequencial(log,funcionarios,3,4);
        return 0;
    }
}