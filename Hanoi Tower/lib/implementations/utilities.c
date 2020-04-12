#include "../headers/utilities.h"

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