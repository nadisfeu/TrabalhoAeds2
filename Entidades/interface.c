#include <stdio.h>
#include <stdlib.h>

#include "interface.h"

void MSG_MENU()
{
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. Fazer pedido em mesa");
    printf("  \n\t2. Busca funcionario sequencial (estao desordenados)");
    printf("  \n\t3. EXCLUIR");
    printf("  \n\t4. IMPRIMIR");
    printf("  \n\t5. SAIR");
}

void MENU(FILE *mesas, FILE *pedidos, FILE *funcionarios, FILE *log, int qntMesas)
{
    TMesa *mesa1;
    TPedido *pedido;
    TFunc *func;
    int opcao = 0;
    int aux;
    do
    {
        MSG_MENU();
        printf("\n\nDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1: // INSERIR PEDIDO EM MESA
            printf("\nEM QUAL MESA DESEJA ADICIONAR O EU PEDIDO?\n");
            fflush(stdin);
            scanf("%d", &aux);
            mesa1 = BuscaBinariaMesa(log, aux, mesas, (qntMesas - (qntMesas - 1)), qntMesas);

            if (mesa1 != NULL)
            {
                imprimeTodosPedido(pedidos);
                printf("Digite o codigo do pedido que deseja fazer:\n");
                fflush(stdin);
                scanf("%d", &aux);
                fazPedidoMesa(log, mesas, pedidos, mesa1, aux);
                printf("Pedido feito com sucesso!\n");
            }
            else
            {
                printf("Digite um codigo de mesa valido!");
            }
            system("PAUSE");
            break;
        case 2: // PESQUISAR
            printf("\nInforme o codigo do funcionario que deseja pesquisar: ");
            fflush(stdin);
            scanf("%d", &aux);

            func = BuscaSequencial(log,funcionarios,aux,qntMesas/3); 
            if (func != NULL)
                imprime(func);
            else
                printf("\nO funcionario NAO existe!\n\n");
            system("PAUSE");
            break;
        // case 3: // EXCLUIR
        //     printf("\nInforme o codigo do pedido que deseja excluir: ");
        //     scanf("%d", &pedido.cod);

        //     Excluir(mesa1, &pedido);

        //     if (pedido.cod != -1)
        //         printf("\nItem excluido com sucesso!\n");
        //     else
        //         printf("\n >>>>>Nao foi possivel excluir o pedido! Pedido NAO pertence a mesa!!<<<< \n");

        //     break;
        // case 4: // IMPRIMIR
        //     printf("\n\n\t >>>>>> IMPRIMINDO AS INFORMACOES DA MESA!! <<<<<<");
        //     imprimeMesa(*mesa1);

        //     break;
        // case 5:

        //     // system("clear");
        //     system("cls");
        //     printf("\n\n\n\t >>>>>> MSG: Saindo do MODULO...!!! <<<<<<\n");
        //     system("PAUSE");
        //     break;
        default:
            // system("clear");
            system("cls");
            printf("\n\n\n\t >>>>>> MSG: Digite uma opcao valida!!! <<<<<<\n");
            system("PAUSE");
        } // fim do bloco switch
    } while (opcao != 5);
}