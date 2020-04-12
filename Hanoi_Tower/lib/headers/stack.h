#ifndef _STACK_
#define _STACK_
#define _MAX_STACK_SIZE_ 3

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct 
{
    int value;

}TElement;

typedef struct 
{
    TElement stackElements[_MAX_STACK_SIZE_];
    int top;

}Stack;


void push(Stack *stack, TElement newElement);
TElement pop(Stack *stack);
void initializeStack(Stack *stack);
bool isEmpty(Stack *stack);
bool isEqual(Stack *stack1, Stack *stack2);
void insertAtBottom(Stack *stack, TElement elemento);
void reverseStack(Stack *stack);
bool elementExist(Stack *stack, TElement element);
void removeElement(Stack *stack, TElement element);

#endif