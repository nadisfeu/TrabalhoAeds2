#include <stdio.h>
#include <stdlib.h>

#include "interface.h"

void MSG_MENU( )
{
    system("clear");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. INSERIR");
    printf("  \n\t2. PESQUISAR");
    printf("  \n\t3. EXCLUIR");
    printf("  \n\t4. IMPRIMIR");
    printf("  \n\t5. SAIR");
}

void MENU(TMesa *mesa1)
{
    TPedido pedido;
    int opcao=0;
    //int i;
    do
    {
        MSG_MENU();
        printf("\n\nDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1: // INSERIR
            printf("\n\t >>>>>> MSG: INSIRA O PEDIDO! <<<<<<\n\n");
            lePedido(&pedido);
            salvaPedido(&pedido, mesa1);

            break;
        case 2: // PESQUISAR
            printf("\nInforme o codigo do pedido que deseja pesquisar: ");
            fflush(stdin);
            scanf("%d", &pedido.cod);

            if(Pesquisar(*mesa1, pedido) != NULL)
                printf("\nO pedido pertence mesa!\n\n");
            else
                printf("\nO pedido NAO pertemce a esta mesa!\n\n");

            break;
        case 3: // EXCLUIR
            printf("\nInforme o codigo do pedido que deseja excluir: ");
            scanf("%d", &pedido.cod);

            Excluir(mesa1, &pedido);

            if(pedido.cod != -1)
                printf("\nItem excluido com sucesso!\n");
            else
                printf("\n >>>>>Nao foi possivel excluir o pedido! Pedido NAO pertence a mesa!!<<<< \n");

            break;
        case 4: // IMPRIMIR
            printf("\n\n\t >>>>>> IMPRIMINDO AS INFORMACOES DA MESA!! <<<<<<");
            imprimeMesa(*mesa1);

            break;
        case 5:

            //system("clear");
            system("cls");
            printf("\n\n\n\t >>>>>> MSG: Saindo do MODULO...!!! <<<<<<\n");
            system("PAUSE");
            break;
        default:
            //system("clear");
            system("cls");
            printf("\n\n\n\t >>>>>> MSG: Digite uma opcao valida!!! <<<<<<\n");
            system("PAUSE");
        } // fim do bloco switch
    }
    while(opcao != 5);
}