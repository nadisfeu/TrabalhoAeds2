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
    if ((mesas = fopen("mesas.dat", "w+b")) == NULL || (pedidos = fopen("pedidos.dat", "ab")) == NULL 
    || (funcionarios = fopen("funcionarios.dat", "w+b")) == NULL || (log= fopen("log.txt", "a+")) == NULL)
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

        int qntMesas = 10;
        TMesa *mesa;
     
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

        mesa = BuscaSequencialMesa(log, mesas, 8, qntMesas);
        imprimeMesa(*mesa);
        fazPedidoMesa(mesas, mesa, 33);
        system("PAUSE");
        system("cls");
        imprimeTodosMesa(mesas);
        //mesa = BuscaSequencialMesa(log, mesas, 8, qntMesas);
        system("PAUSE");
        system("cls");
        fazPedidoMesa(mesas, mesa, 45);
        system("PAUSE");
        system("cls");
        imprimeTodosMesa(mesas);
        fazPedidoMesa(mesas, mesa, 4);
        fazPedidoMesa(mesas, mesa, 78);
        fazPedidoMesa(mesas, mesa, 5);
        imprimeTodosMesa(mesas);
        //BuscaSequencial(log,funcionarios,3,4);
        return 0;
    }
}