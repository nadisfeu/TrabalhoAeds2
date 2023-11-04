#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// #include "Entidades/Headers/mesas.h"
#include "mesas.c"

int main()
{
    FILE *in;
    if ((in = fopen("teste.dat", "w+b")) == NULL)
    {
        printf("erro ao abrir");
        exit(1);
    }
    else
    {
        TMesa *m;
        m = mesa(123, 2, 1550);
        salvaMesa(m, in);
        rewind(in);
        m = leMesa(in);
        printf("aa");
        imprimeMesa(*m);
        return 0;
    }
}