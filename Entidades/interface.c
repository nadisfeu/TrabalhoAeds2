#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "hashExterno.c"

//adicionar funções de hash na interface 
void MSG_MENU()
{
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t1. ADICIONAR PEDIDOS A UMA MESA");
    printf("  \n\t2. BUSCAR FUNCIONARIOS SEQUENCIAL NAS PARTICOES");
    printf("  \n\t3. EXIBIR INFORMACOES SOBRE A MESA NO HASH");
    printf("  \n\t4. EXCLUIR A MESA NO HASH");
    printf("  \n\t5. SAIR");
}

void MENU(FILE *mesas, FILE *pedidos, FILE *funcionarios, FILE *log, FILE *hashCompartimentos, FILE *hash, int tamBase, int qntMesas)
{
    TMesa *mesa1;
    // TPedido *pedido;
    TFunc *func;
    int opcao = 0;
    int aux;
    int c = 1;
    char* nomeParticao = "particao1.dat";
    int qtdParticoes;
    qtdParticoes = selecao_subst2(funcionarios, qntMesas /3);
    FILE *AUX;
    

    do
    {
        MSG_MENU();
        printf("\n\nDigite uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1: // INSERIR PEDIDO EM MESA
            printf("\nDIGITE O CODIGO MESA DESEJA ADICIONAR O PEDIDO\n");
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
            c = 1;
            printf("%d", qtdParticoes);

            while (c != qtdParticoes)
            {
                
                sprintf(nomeParticao, "particao%i.dat", c);
                if ((AUX = fopen(nomeParticao, "w+b")) == NULL){
                    printf("Erro criar arquivo de saida\n");
                    break;
                }
                printf("%d", c);
                imprimeTodos(AUX);
                func = BuscaSequencial(log, AUX, aux, tamanho_arquivo(AUX));

                if (func != NULL)
                    imprime(func);
                else
                {
                    c++;
                    printf("\nO funcionario NAO existe nessa partição!\n\n");
                }
                printf("\nO funcionario NAO existe!\n\n");
            }
            system("PAUSE");
            break;

        case 3: // IMPRIMIR
            printf("\n DIGITE O CODIGO DA MESA VOCE DESEJA OBTER AS INFORMACOES:");
            fflush(stdin);
            scanf("%d", &aux);
            mesa1->cod = aux;
            mesa1 = busca_no_hash(hashCompartimentos, hash, tamBase, mesa1, log);
            printf("\n\t >>>>>> IMPRIMINDO AS INFORMACOES DA MESA!! <<<<<<\n");

            if (mesa1 != NULL)
            {
                imprimeMesa(*mesa1);
                LePedidosDaMesa(log, pedidos, mesa1);
            }
            else
            {
                printf("Digite um codigo de mesa valido!");
            }
            system("PAUSE");

            break;
        case 4:
            printf("\n DIGITE O CODIGO DA MESA VOCE DESEJA EXCLUIR: ");
            fflush(stdin);
            scanf("%d", &aux);
            mesa1->cod = aux;
            exclui_no_hash(hashCompartimentos, hash, tamBase, mesa1, log);
        
        case 5:
            system("cls");
            printf("\n\n\n\t >>>>>> MSG: Saindo do MODULO...!!! <<<<<<\n");
            system("PAUSE");
            break;
        default:
            // system("clear");
            system("cls");
            printf("\n\n\n\t >>>>>> MSG: Digite uma opcao valida!!! <<<<<<\n");
            system("PAUSE");
        } // fim do bloco switch
    } while (opcao != 4);
}