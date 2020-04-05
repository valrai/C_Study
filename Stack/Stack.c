#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define MAX_AMOUNT_OF_ELEMENTS 100

const char* BORDER = "\n========================================================\n";

typedef struct 
{
    int value;

}TElement;

typedef struct 
{
    TElement stackElements[MAX_AMOUNT_OF_ELEMENTS];
    int top;

}Stack;

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

void InitializeStack(Stack *stack)
{
    stack->top = -1;
}

bool IsEmpty(Stack *stack)
{
    return stack->top < 0;
}

void Push(Stack *stack, TElement newElement)
{
    stack->top++;
    stack->stackElements[stack->top].value = newElement.value;
}

TElement Pop(Stack *stack)
{
    TElement topElement = stack->stackElements[stack->top];
    stack->top--;

    return topElement;
}

void StackUp(Stack *stack)
{
    system("clear||cls");

    if (stack->top < MAX_AMOUNT_OF_ELEMENTS)
    {
        TElement newElement;

        printf("%s\nInforme o novo valor para a pilha: ", BORDER);
        scanf("%d", &newElement.value);
        Push(stack, newElement);
    }
    else
    {  
        printf("%s\nPilha cheia!\n%s", BORDER, BORDER);
        Pause("");
    }
}

void Unstack(Stack *stack)
{

    system("clear||cls");
    printf("%s\n", BORDER);

    if (stack->top > -1)
        printf("\nValor Desempilhado : %d\n", Pop(stack).value);    
    else
        printf("\n Pilha vazia!\n");
    
    printf(BORDER);
    Pause("");
}

void ShowStack(Stack *stack)
{
    system("clear||cls");
    printf("%s\n", BORDER);

    if (stack->top < 0)
        printf("\nPilha vazia.");
    else    
        for (int i = stack->top; i >= 0 ; i--)
            printf("\tÍndice %d -> valor: %d\n", i, stack->stackElements[i].value);

    printf(BORDER);
    Pause("");
}

void ShowAllStacks(Stack *stack1, Stack *stack2)
{
    system("clear||cls");

    printf("%spilha 1%s\n", BORDER, BORDER);
    
    if (stack1->top < 0)
        printf("pilha vazia.");
    else
        for (int i = stack1->top; i >= 0 ; i--)
            printf("\tÍndice %d -> valor: %d\n", i, stack1->stackElements[i].value);

    printf("%spilha 2%s\n", BORDER, BORDER);

    if (stack2->top < 0)
        printf("pilha vazia.");
    else
        for (int i = stack2->top; i >= 0 ; i--)
            printf("\tÍndice %d -> valor: %d\n", i, stack2->stackElements[i].value);

    printf(BORDER);
    Pause("");
}

void StackMenu(Stack *stack1, Stack *stack2 )
{
    int op;

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Empilhar pilha 1\n2 - Empilhar pilha 2\n\n0 - Voltar\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");

        if (op == 1)
            StackUp(stack1); 
        else if (op == 2)
            StackUp(stack2);         

    } while (op != 0);   
}

void UnstackMenu(Stack *stack1, Stack *stack2)
{
    int op;

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Desempilhar pilha 1\n2 - Desempilhar pilha 2\n\n0 - Voltar\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");

        if (op == 1)
            Unstack(stack1); 
        else if (op == 2)
            Unstack(stack2);    

    } while (op != 0);   
}

bool IsEqual(Stack *stack1, Stack *stack2)
{
    if (stack1->top != stack2->top)
        return false;

    for (int i = stack2->top; i > -1 ; i--)
        if (stack1->stackElements[i].value != stack2->stackElements[i].value)
            return false;

    return true;
}

void CheckStacksEquality(Stack *stack1, Stack *stack2)
{
    bool isEqual = IsEqual(stack1, stack2);

    system("clear||cls");

    if (isEqual)    
        printf("%s\nAs pilhas são iguais\n%s", BORDER, BORDER);
    else
        printf("%s\nAs pilhas não são iguais\n%s", BORDER, BORDER);

    Pause("");
}

void PresentationMenu(Stack *stack1, Stack *stack2)
{
    int op;

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Apresentar pilha 1\n2 - Apresentar pilha 2\n3 - Apresentar Ambas as pilhas\n\n0 - Voltar\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");        

        switch(op)
        {
            case 1: ShowStack(stack1); break;
            case 2: ShowStack(stack2); break;
            case 3: ShowAllStacks(stack1, stack2); break;
        }

    } while (op != 0);   
}

void InsertAtBottom(Stack *stack, TElement elemento)
{
    if (IsEmpty(stack))
        Push(stack, elemento);
    else
    {
        TElement auxElement = Pop(stack);
        InsertAtBottom(stack, elemento);
        Push(stack, auxElement);
    }
    
}

void ReverseStack(Stack *stack)
{
    if (!IsEmpty(stack))
    {
        TElement auxElement = Pop(stack);
        ReverseStack(stack);
        InsertAtBottom(stack, auxElement);
    }
}

void ReverseStackMenu(Stack *stack1, Stack *stack2)
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
                ReverseStack(stack1);
                printf("%s\nPilha invertida com sucesso!\n%s", BORDER, BORDER);
                Pause("");
                break;
            case 2:
                ReverseStack(stack2);
                printf("%s\nPilha invertida com sucesso!\n%s", BORDER, BORDER);
                Pause("");
                break;
            case 3:
                ReverseStack(stack1);
                ReverseStack(stack2);
                printf("%s\nPilhas invertidas com sucesso!\n%s", BORDER, BORDER);
                Pause("");
                break;
        }

    } while (op != 0);
}

int main ()
{
    Stack stack1, stack2;
    int op;

    setlocale(LC_ALL, "pt-BR");
    InitializeStack(&stack1);    
    InitializeStack(&stack2);    

    do
    {
        system("clear||cls");
        printf("%s\nSelecione uma opção:\n\n1 - Empilhar Elementos\n2 - Desempilhar Elementos\n3 - Apresentar pilha\n4 - Inverter pilha\n5 - Verificar igualdade entre as pilhas\n\n0 - Sair\n%s", BORDER, BORDER);
        scanf("%d", &op);
        system("clear||cls");

        switch(op)
        {
            case 1: StackMenu(&stack1, &stack2); break;
            case 2: UnstackMenu(&stack1, &stack2); break;
            case 3: PresentationMenu(&stack1, &stack2); break;
            case 4: ReverseStackMenu(&stack1, &stack2); break;
            case 5: CheckStacksEquality(&stack1, &stack2); break;
        }

    } while (op != 0);    

    return 0;
}