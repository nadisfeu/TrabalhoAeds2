#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int calculaHash(int cod, int tamBase){
    return (cod % tamBase);
}


