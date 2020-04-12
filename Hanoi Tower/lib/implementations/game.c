#include "stack.h"

void inicializeStackA(Stack *stackA)
{
    TElement element;
    stackA->top = -1;

    for (int i = _MAX_STACK_SIZE_; i > 0; i--)
    {
        element.value = i;
        push(stackA, element);
    }   
} 
    
char* makePlay(Stack *sourceStack, Stack *targetStack)
{
    if (sourceStack->top < 0)
        return "Jogada ilegal! O pino de origem está vazio.";

    if (targetStack->top >= 0)
        if (sourceStack->stackElements[sourceStack->top].value > targetStack->stackElements[targetStack->top].value)
            return "Jogada ilegal! os discos devem ser posicionados em ordem crescente.";
    
    push(targetStack, pop(sourceStack));    
    return "";    
}

bool gameIsOver(Stack *stackB, Stack *stackC)
{
    return stackB->top == (_MAX_STACK_SIZE_ - 1) || stackC->top == (_MAX_STACK_SIZE_ - 1);
}

void inicializeGame(Stack *stackA, Stack *stackB, Stack *stackC)
{
    inicializeStackA(stackA);
    initializeStack(stackB);
    initializeStack(stackC);
}   
