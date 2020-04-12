#ifndef _GAME_
#define _GAME_

#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void inicializeStackA(Stack *stackA);
bool gameIsOver(Stack *stackB, Stack *stackC);
void inicializeGame(Stack *stackA, Stack *stackB, Stack *stackC);
char* makePlay(Stack *sourceStack, Stack *targetStack);

#endif