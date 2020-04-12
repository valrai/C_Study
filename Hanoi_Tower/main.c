#include <stdio.h>
#include "./lib//headers/interface.h"

int main()
{
    Stack stackA, stackB, stackC;

    inicializeGame(&stackA, &stackB, &stackC);
    mainMenu(&stackA, &stackB, &stackC);

    return 0;
}
