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
    if ((mesas = fopen("mesas.dat", "w+b")) == NULL || (pedidos = fopen("pedidos.dat", "w+b")) == NULL 
    || (funcionarios = fopen("funcionarios.dat", "w+b")) == NULL || (log= fopen("log.txt", "a+")) == NULL)
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {
        int qntMesas = 30;
        criarBase(mesas, qntMesas,"mesa");
        imprimeTodosMesa(mesas);
        
        criarBase(funcionarios, qntMesas/3, "funcionario");
        imprimeTodos(funcionarios);
        
        SalvaTodosOsPedidos(pedidos);
        imprimeTodosPedido(pedidos);
        
        MENU(mesas,pedidos,funcionarios,log,qntMesas);

        // fprintf(log, "\nTeste com arquivos de Base %d, Busca Sequencial: \n", qntMesas);
        // //imprimeTodosMesa(mesas);

        // // mesa = BuscaBinariaMesa(log,3,mesas,1,10);
        // // fazPedidoMesa(log,mesas,pedidos,mesa,2);
        // // imprimeTodosMesa(mesas);

        // for (int i = 0; i < 10; i++)
        // {
        //     BuscaBinariaMesa(log,cod[i],mesas,1,qntMesas);
        // }
        

        /*
        imprimeTodosPedido(pedidos);
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
        */
        return 0;

    }
}