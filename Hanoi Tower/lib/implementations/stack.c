#include "stack.h"

void push(Stack *stack, TElement newElement)
{
    stack->top++;
    stack->stackElements[stack->top].value = newElement.value;
}

TElement pop(Stack *stack)
{
    TElement topElement = stack->stackElements[stack->top];
    stack->stackElements[stack->top].value = 0;
    stack->top--;

    return topElement;
}

void initializeStack(Stack *stack)
{
    stack->stackElements[0].value = 0;
    stack->stackElements[1].value = 0;
    stack->stackElements[2].value = 0;
    stack->top = -1;
}

bool isEmpty(Stack *stack)
{
    return stack->top < 0;
}

bool isEqual(Stack *stack1, Stack *stack2)
{
    if (stack1->top != stack2->top)
        return false;

    for (int i = stack2->top; i > -1 ; i--)    
        if (stack1->stackElements[i].value != stack2->stackElements[i].value)
            return false;
    
    return true;
}

void insertAtBottom(Stack *stack, TElement elemento)
{
    if (isEmpty(stack))
        push(stack, elemento);
    else
    {
        TElement auxElement = pop(stack);
        insertAtBottom(stack, elemento);
        push(stack, auxElement);
    }    
}

void reverseStack(Stack *stack)
{
    if (!isEmpty(stack))
    {
        TElement auxElement = pop(stack);
        reverseStack(stack);
        insertAtBottom(stack, auxElement);
    }
}

bool elementExist(Stack *stack, TElement element)
{
    for (int i = stack->top; i >= 0; i--)
        if (stack->stackElements[i].value == element.value)  
            return true;
    return false;
}

void removeElement(Stack *stack, TElement element)
{
    Stack auxStack;
    TElement elementRemoved;
    initializeStack(&auxStack);

    do
    {
        elementRemoved = pop(stack);
        if (elementRemoved.value != element.value)
            push(&auxStack, elementRemoved);

    } while (elementRemoved.value != element.value && stack->top > 0);
    
    for (int i = auxStack.top; i >= 0; i--)
        push(stack, pop(&auxStack));    
}