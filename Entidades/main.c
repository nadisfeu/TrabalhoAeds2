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
    if ((mesas = fopen("mesas.dat", "w+b")) == NULL || (pedidos = fopen("pedidos.dat", "w+b")) == NULL 
    || (funcionarios = fopen("funcionarios.dat", "w+b")) == NULL || (log= fopen("log.txt", "w+")) == NULL)
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
     
        criarBase(mesas, 10,"mesa");
        imprimeTodosMesa(mesas);
        
        criarBase(funcionarios, 4, "funcionario");
        imprimeTodos(funcionarios);

        criarBase(pedidos,6,"pedido");
        imprimeTodosPedido(pedidos);

        return 0;
    }
}