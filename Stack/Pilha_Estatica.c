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

bool EstaVazia(TPilha *pilha)
{
    return pilha->topo < 0;
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

    if (!EstaVazia(pilha))
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

    if (EstaVazia(pilha))
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
    
    if (EstaVazia(pilha1))
        printf("Pilha vazia.");
    else
        for (int i = pilha1->topo; i >= 0 ; i--)
            printf("\tÍndice %d -> valor: %d\n", i, pilha1->pilhaElementos[i].valor);

    printf("%sPilha 2%s\n", BORDER, BORDER);

    if (EstaVazia(pilha2))
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

    for (int i = pilha2->topo; i >= 0 ; i--)
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

void EmpilharNoFundo(TPilha *pilha, TElemento elemento)
{
    if (EstaVazia(pilha))
        Push(pilha, elemento);
    else
    {
        TElemento elementoAux = Pop(pilha);
        EmpilharNoFundo(pilha, elemento);
        Push(pilha, elementoAux);
    }    
}

void InverterPilha(TPilha *pilha)
{
    if (!EstaVazia(pilha))
    {
        TElemento elementoAux = Pop(pilha);
        InverterPilha(pilha);
        EmpilharNoFundo(pilha, elementoAux);
    }
}

bool ElementoExisteNaPilha(TPilha *pilha, TElemento elemento)
{
    for (int i = pilha->topo; i >= 0; i--)
        if (pilha->pilhaElementos[i].valor == elemento.valor)  
            return true;
    return false;
}

void RemoverElemento(TPilha *pilha, TElemento elemento)
{
    TPilha pilhaAux;
    TElemento elementoRemovido;
    InicializarPilha(&pilhaAux);

    do
    {
        elementoRemovido = Pop(pilha);
        if (elementoRemovido.valor != elemento.valor)
            Push(&pilhaAux, elementoRemovido);

    } while (elementoRemovido.valor != elemento.valor && pilha->topo > 0);
    
    for (int i = pilhaAux.topo; i >= 0; i--)
        Push(pilha, Pop(&pilhaAux));    
}

void MenuRemoverElemento(TPilha *pilha1, TPilha *pilha2)
{
    int op;
    TElemento elemento;

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Remover elemento da Pilha 1\n2 - Remover elemento da Pilha 2\n\n0 - Voltar\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");        

        if (op == 0) break;
        
        printf("%s\nInforme o valor que deseja remover: ", BORDER);
        scanf("%d", &elemento.valor);

        if (op == 1)        
            if (ElementoExisteNaPilha(pilha1, elemento))
            {
                RemoverElemento(pilha1, elemento);
                system("clear||cls");
                printf("%s\n Valor removido com sucesso!\n%s", BORDER, BORDER); 
            }
            else
            {
                system("clear||cls");
                printf("%s\n Valor não está presente na pilha.\n%s", BORDER, BORDER); 
            }
        
        else if (op == 2)
            if (ElementoExisteNaPilha(pilha2, elemento))
            {
                RemoverElemento(pilha2, elemento);
                system("clear||cls");
                printf("%s\n Valor removido com sucesso!\n%s", BORDER, BORDER); 
            }
            else
            {
                system("clear||cls");
                printf("%s\n Valor não está presente na pilha.\n%s", BORDER, BORDER); 
            }    

        Pause("");        

    }while(op != 0);
    
}

void MenuInvercao(TPilha *pilha1, TPilha *pilha2)
{
    int op;

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Inverter Pilha 1\n2 - Inverter Pilha 2\n3 - Inverter Ambas as Pilhas\n\n0 - Voltar\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");        

        switch(op)
        {
            case 1:
                InverterPilha(pilha1);
                printf("%s\nPilha invertida com sucesso!\n%s", BORDER, BORDER);
                Pause("");
                break;
            case 2:
                InverterPilha(pilha2);
                printf("%s\nPilha invertida com sucesso!\n%s", BORDER, BORDER);
                Pause("");
                break;
            case 3:
                InverterPilha(pilha1);
                InverterPilha(pilha2);
                printf("%s\nPilhas invertidas com sucesso!\n%s", BORDER, BORDER);
                Pause("");
                break;
        }

    } while (op != 0);
}

int main ()
{
    TPilha pilha1, pilha2;
    int op;

    setlocale(LC_ALL, "pt-BR");
    InicializarPilha(&pilha1);    
    InicializarPilha(&pilha2);    

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Empilhar Elementos\n2 - Desempilhar Elementos\n3 - Apresentar Pilha\n4 - Inverter Pilha\n5 - Verificar igualdade entre as pilhas\n6 - Remover elemento por valor\n\n0 - Sair\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");

        switch(op)
        {
            case 1: MenuEmpilhar(&pilha1, &pilha2); break;
            case 2: MenuDesempilhar(&pilha1, &pilha2); break;
            case 3: MenuApresentacao(&pilha1, &pilha2); break;
            case 4: MenuInvercao(&pilha1, &pilha2); break;
            case 5: VerificarIgualdadePilhas(&pilha1, &pilha2); break;
            case 6: MenuRemoverElemento(&pilha1, &pilha2); break;

        }

    } while (op != 0);    

    return 0;
}