#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define QUANTIDADE_MAXIMA_ELEMENTOS_PILHA 100

const char* BORDER = "\n========================================================\n";

typedef struct tipoElemento
{
    int valor;

}TElemento;

typedef struct tipoPilha
{
    TElemento pilhaElementos[QUANTIDADE_MAXIMA_ELEMENTOS_PILHA];
    int topo;

}TPilha;

// ============================================================================================

void ClearBuffer()
{
	int c;
	while ( (c = getchar()) != '\n' && c != EOF ) { }
}

void Pause(char * message)
{
    if (strlen(message) > 0) printf("\n%s\n", message);
    else printf("\nPrecione Enter para continuar...\n");
    ClearBuffer();
    getc(stdin);
}

// ============================================================================================

void InicializarPilha(TPilha *pilha)
{
    pilha->topo = -1;
}

void Push(TPilha *pilha, TElemento novoElemento)
{
    pilha->topo++;
    pilha->pilhaElementos[pilha->topo].valor = novoElemento.valor;
}

TElemento Pop(TPilha *pilha)
{
    TElemento elementoTopo = pilha->pilhaElementos[pilha->topo];
    pilha->topo--;

    return elementoTopo;
}

void Empilhar(TPilha *pilha)
{
    system("clear||cls");

    if (pilha->topo < QUANTIDADE_MAXIMA_ELEMENTOS_PILHA)
    {
        TElemento novoElemento;

        printf("%s\nInforme o novo valor para a pilha: ", BORDER);
        scanf("%d", &novoElemento.valor);
        Push(pilha, novoElemento);
    }
    else
    {  
        printf("%s\nPilha cheia!\n%s", BORDER, BORDER);
        Pause("");
    }
}

void Desempilhar(TPilha *pilha)
{

    system("clear||cls");
    printf("%s\n", BORDER);

    if (pilha->topo > -1)
        printf("\nValor Desempilhado : %d\n", Pop(pilha).valor);    
    else
        printf("\nPilha vazia!\n");
    
    printf(BORDER);
    Pause("");
}

void ApresentarPilha(TPilha *pilha)
{
    system("clear||cls");
    printf("%s\n", BORDER);

    if (pilha->topo < 0)
        printf("\tPilha vazia.");
    else    
        for (int i = pilha->topo; i >= 0 ; i--)
            printf("\tÍndice %d -> valor: %d\n", i, pilha->pilhaElementos[i].valor);

    printf(BORDER);
    Pause("");
}

void ApresentarTodasPilhas(TPilha *pilha1, TPilha *pilha2)
{
    system("clear||cls");

    printf("%sPilha 1%s\n", BORDER, BORDER);
    
    if (pilha1->topo < 0)
        printf("Pilha vazia.");
    else
        for (int i = pilha1->topo; i >= 0 ; i--)
            printf("\tÍndice %d -> valor: %d\n", i, pilha1->pilhaElementos[i].valor);

    printf("%sPilha 2%s\n", BORDER, BORDER);

    if (pilha2->topo < 0)
        printf("Pilha vazia.");
    else
        for (int i = pilha2->topo; i >= 0 ; i--)
            printf("\tÍndice %d -> valor: %d\n", i, pilha2->pilhaElementos[i].valor);

    printf(BORDER);
    Pause("");
}

void MenuEmpilhar(TPilha *pilha1, TPilha *pilha2 )
{
    int op;

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Empilhar Pilha 1\n2 - Empilhar Pilha 2\n\n0 - Voltar\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");

        if (op == 1)
            Empilhar(pilha1); 
        else if (op == 2)
            Empilhar(pilha2);         

    } while (op != 0);   
}

void MenuDesempilhar(TPilha *pilha1, TPilha *pilha2)
{
    int op;

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Desempilhar Pilha 1\n2 - Desempilhar Pilha 2\n\n0 - Voltar\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");

        if (op == 1)
            Desempilhar(pilha1); 
        else if (op == 2)
            Desempilhar(pilha2);    

    } while (op != 0);   
}

bool IsEqual(TPilha *pilha1, TPilha *pilha2)
{
    if (pilha1->topo != pilha2->topo)
        return false;

    for (int i = pilha2->topo; i > -1 ; i--)
        if (pilha1->pilhaElementos[i].valor != pilha2->pilhaElementos[i].valor)
            return false;

    return true;
}

void VerificarIgualdadePilhas(TPilha *pilha1, TPilha *pilha2)
{
    bool isEqual = IsEqual(pilha1, pilha2);

    system("clear||cls");

    if (isEqual)    
        printf("%s\nAs Pilhas são iguais\n%s", BORDER, BORDER);
    else
        printf("%s\nAs Pilhas não são iguais\n%s", BORDER, BORDER);

    Pause("");
}

void MenuApresentacao(TPilha *pilha1, TPilha *pilha2)
{
    int op;

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Apresentar Pilha 1\n2 - Apresentar Pilha 2\n3 - Apresentar Ambas as Pilhas\n\n0 - Voltar\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");        

        switch(op)
        {
            case 1: ApresentarPilha(pilha1); break;
            case 2: ApresentarPilha(pilha2); break;
            case 3: ApresentarTodasPilhas(pilha1, pilha2); break;
        }

    } while (op != 0);   
}

TPilha ObterPilhaInvertida(TPilha *pilha)
{
    TPilha pilhaAux;
    InicializarPilha(&pilhaAux);

    for (int i = pilha->topo; i >= 0 ; i--)
        Push(&pilhaAux, Pop(pilha));

    return pilhaAux;
}

int main ()
{
    TPilha pilha1, pilha2;
    int op, option;

    setlocale(LC_ALL, "pt-BR");
    InicializarPilha(&pilha1);    
    InicializarPilha(&pilha2);    

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Empilhar Elementos\n2 - Desempilhar Elementos\n3 - Apresentar Pilha\n4 - Inverter Pilha\n5 - Verificar igualdade entre as pilhas\n\n0 - Sair\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");

        switch(op)
        {
            case 1: MenuEmpilhar(&pilha1, &pilha2); break;
            case 2: MenuDesempilhar(&pilha1, &pilha2); break;
            case 3: MenuApresentacao(&pilha1, &pilha2); break;
            case 4:    

                do
                {
                    system("clear||cls");
                    printf(BORDER);
                    printf("\nSelecione uma opção:\n\n1 - Inverter Pilha 1\n2 - Inverter Pilha 2\n3 - Inverter Ambas as Pilhas\n\n0 - Voltar\n");
                    printf(BORDER);
                    scanf("%d", &option);
                    system("clear||cls");        

                    switch(option)
                    {
                        case 1:
                            pilha1 = ObterPilhaInvertida(&pilha1);
                            printf("%s\nPilha invertida com sucesso!\n%s", BORDER, BORDER);
                            Pause("");
                            break;
                        case 2:
                            pilha2 = ObterPilhaInvertida(&pilha2);
                            printf("\n%sPilha invertida com sucesso!\n%s", BORDER, BORDER);
                            Pause("");
                            break;
                        case 3:
                            pilha1 = ObterPilhaInvertida(&pilha1);
                            pilha2 = ObterPilhaInvertida(&pilha2);
                            printf("\n%sPilhas invertidas com sucesso!\n%s", BORDER, BORDER);
                            Pause("");
                            break;
                    }

                } while (option != 0); break;

            case 5: VerificarIgualdadePilhas(&pilha1, &pilha2); break;
        }

    } while (op != 0);    

    return 0;
}