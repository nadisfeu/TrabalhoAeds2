# ifndef INTERFACE_H_INCLUDED
# define INTERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "funcionario.h"
#include "mesas.h"
#include "pedidos.h"


void MSG_MENU(); // MENSAGEM PARA EXIBIR O MENU PRINCIPAL

void MENU(FILE *mesas, FILE *pedidos, FILE *funcionarios, FILE *log, FILE *hashCompartimentos, FILE *hash, int tamBase, int qntMesas);// MÓDULO DE MENU

# endif // INTERFACE_H_INCLUDED