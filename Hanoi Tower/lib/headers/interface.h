#ifndef _GRAPHICS_
#define _GRAPHICS_

#define _MAX_MESSAGE_SIZE_ 100
#define _BORDER_ "============================================================================"

#include "stack.h"
#include "game.h"
#include "utilities.h"
#include <string.h>


void printStack(Stack *stack, char stackName);
void playMenu(char* message, Stack *stackA, Stack *stackB, Stack *stackC);
void printAllStacks(Stack *stackA, Stack *stackB, Stack *stackC);
void mainMenu(Stack *stackA, Stack *stackB, Stack *stackC);

#endif