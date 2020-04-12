#include "../headers/interface.h"

void printStack(Stack *stack, char stackName)
{
    int value1 = stack->stackElements[2].value, value2 = stack->stackElements[1].value, value3 = stack->stackElements[0].value;

    if (value1 == 1 && value2 == 2 && value3 == 3)
    {
        printf("\n  %c)       __         \n", stackName);   
        printf("          |  |          \n");            
        printf("         _|__|_         \n");         
        printf("       _(______)_       \n");          
        printf("     _(__________)_     \n");             
        printf(" ___(______________)___ \n");  
        printf("|______________________|\n");  
    }
    else if (value1 == 0 && value2 == 0 && value3 == 0)
    {
        printf("\n  %c)       __           \n", stackName);        
        printf("          |  |          \n");        
        printf("          |  |          \n");            
        printf("          |  |          \n");           
        printf("          |  |          \n");          
        printf(" _________|__|_________ \n");                
        printf("|______________________|\n");   
    }
    else if (value1 == 0 && value2 == 2 && value3 == 3)
    {
        printf("\n  %c)       __           \n", stackName);      
        printf("          |  |          \n");       
        printf("          |  |          \n");       
        printf("       ___|__|___       \n");         
        printf("     _(__________)_     \n");           
        printf(" ___(______________)___ \n");            
        printf("|______________________|\n");     
    }
    else if (value1 == 0 && value2 == 0 && value3 == 3)
    {
        printf("\n  %c)       __           \n", stackName);        
        printf("          |  |          \n");        
        printf("          |  |          \n");          
        printf("          |  |          \n");     
        printf("     _____|__|_____     \n");           
        printf(" ___(______________)___ \n");             
        printf("|______________________|\n");     
    }
    else if (value1 == 0 && value2 == 1 && value3 == 3)
    {
        printf("\n  %c)       __           \n", stackName);      
        printf("          |  |          \n");                              
        printf("          |  |          \n");         
        printf("          |  |          \n");             
        printf("         _|__|_         \n");         
        printf("     ___(______)___     \n");              
        printf(" ___(______________)___ \n");   
        printf("|______________________|\n");      
    }
    else if (value1 == 0 && value2 == 1 && value3 == 2)
    {
        printf("\n  %c)       __           \n", stackName);                 
        printf("          |  |          \n");        
        printf("          |  |          \n");                          
        printf("          |  |          \n");           
        printf("         _|__|_         \n");                
        printf("       _(______)_       \n");               
        printf(" _____(__________)_____ \n");                   
        printf("|______________________|\n");       
    }    
    else if (value1 == 0 && value2 == 0 && value3 == 1)
    {
        printf("\n  %c)       __           \n", stackName);                  
        printf("          |  |          \n");        
        printf("          |  |          \n");
        printf("          |  |          \n");                           
        printf("          |  |          \n");           
        printf("         _|__|_         \n");                
        printf(" _______(______)_______ \n");               
        printf("|______________________|\n");        
    }    
    else if (value1 == 0 && value2 == 0 && value3 == 2)
    {
        printf("\n  %c)       __           \n", stackName);                  
        printf("          |  |          \n");        
        printf("          |  |          \n");                          
        printf("          |  |          \n");                          
        printf("          |  |          \n");           
        printf("       ___|__|___       \n");                
        printf(" _____(__________)_____ \n");                   
        printf("|______________________|\n");          
    }    
}

void playMenu(char* message, Stack *stackA, Stack *stackB, Stack *stackC)
{
    Stack *sourceStack, *targetStack;
    int op;

    do
    {
        system("clear||cls");
        printf("\n%s\n\nSelecione o pino de origem:\n\n1 - Pino A\n2 - Pino B\n3 - Pino C\n\n0 - Voltar\n\n%s\n", _BORDER_, _BORDER_);
        scanf("%d", &op);
        system("clear||cls");

        switch (op)
        {
            case 1: sourceStack = stackA; break;
            case 2: sourceStack = stackB; break;
            case 3: sourceStack = stackC; break;
            case 0: return;
        }            

    } while (op < 0 || op > 3); 

    int sourceOption = op;

    do
    {   
        switch (sourceOption)
        {
            case 1:

                printf("\n%s\n\nSelecione o pino de destino:\n\n1 - Pino B\n2 - Pino C\n\n0 - Voltar\n\n%s\n", _BORDER_, _BORDER_);
                scanf("%d", &op);
                if (op == 1)
                    targetStack = stackB;
                else if (op == 2)
                    targetStack = stackC;
                break;

            case 2:

                printf("\n%s\n\nSelecione o pino de destino:\n\n1 - Pino A\n2 - Pino C\n\n0 - Voltar\n\n%s\n", _BORDER_, _BORDER_);
                scanf("%d", &op);
                if (op == 1)
                    targetStack = stackA;
                else if (op == 2)
                    targetStack = stackC;   
                break;

            case 3:

                printf("\n%s\n\nSelecione o pino de destino:\n\n1 - Pino A\n2 - Pino B\n\n0 - Voltar\n\n%s\n", _BORDER_, _BORDER_);
                scanf("%d", &op);
                if (op == 1)
                    targetStack = stackA;
                else if (op == 2)
                    targetStack = stackB;   
                break;
        }        
        
        system("clear||cls");            

    } while (op < 0 || op > 3); 

    strcpy(message, makePlay(sourceStack, targetStack));
}


void printAllStacks(Stack *stackA, Stack *stackB, Stack *stackC)
{
    printf("%s\n", _BORDER_);
    printStack(stackA, 'A');
    printStack(stackB, 'B');
    printStack(stackC, 'C');
}

void mainMenu(Stack *stackA, Stack *stackB, Stack *stackC)
{
    int op, numberOfPlays = 0;
    char message[_MAX_MESSAGE_SIZE_];
    message[0] = '\0';

    do
    {
        system("clear||cls");
        printAllStacks(stackA, stackB, stackC);
        printf("\n%s\n\nSelecione uma opção:\n\n1 - Realizar jogada\n\n0 - Sair\n\n%s\n", _BORDER_, _BORDER_);
        scanf("%d", &op);
        system("clear||cls");

        if (op == 1)
        {
            playMenu(message, stackA, stackB, stackC);   
            numberOfPlays++;
        }

        system("clear||cls");
        if (gameIsOver(stackB, stackC))
        {
            printf("%s\n\t\tVocê Ganhou com %d jogadas!\n%s\n", _BORDER_, numberOfPlays, _BORDER_);
            inicializeGame(stackA, stackB, stackC);
            numberOfPlays = 0;
            Pause("");
        }
        else if(strlen(message) > 0)
        {
            printf("%s\n%s\n%s\n", _BORDER_, message, _BORDER_);                
            Pause("");
        }
        message[0] = '\0';

    } while (op != 0);     
}
