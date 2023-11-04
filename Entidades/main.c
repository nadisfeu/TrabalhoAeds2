#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

//#include "Entidades/Headers/mesas.h"
#include "mesas.c"


int main()
{
   FILE *f;
   f = fopen("teste.dat","w"); 
   TMesa *m;
   m = mesa(123, 2, 0);
   salvaMesa(m, f);
   leMesa(f);

   return 0;
}