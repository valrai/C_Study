#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUANTITY_OF_STUDENT_GRADES 4
#define MAX_STUDENT_NAME_SIZE 100
#define MAX_QUANTITY_OF_STUDENTS 60

const char* BORDER = "\n========================================================\n";
const char* NOT_FOUND_MESSAGE = "Não foram encontrados resultados para o RA informado.";
const char* INSUFFICIENT_STORAGE_MESSAGE = "Não é possível cadastrar novos alunos, Armazenamento cheio.";

typedef struct
{
    int ra;
    char name[MAX_STUDENT_NAME_SIZE];
    float grades[MAX_QUANTITY_OF_STUDENT_GRADES+1]; 

}Student;

typedef struct List_Students
{
    Student students[MAX_QUANTITY_OF_STUDENTS];
    int lastIndex;

}LStudents;

// =======================================================================================

void ClearBuffer()
{
	int c;
	while ( (c = getchar()) != '\n' && c != EOF ) { }
}

void RemoveNewLine(char *phase)
{
    int WordSize = strlen(phase);

    if (phase[WordSize - 1] == '\n') 
        phase[WordSize - 1] = '\0';
}

void Pause(char * message)
{
    if (strlen(message) > 0) printf("\n%s\n", message);
    else printf("\nPrecione Enter para continuar...\n");
    ClearBuffer();
    getc(stdin);
}

// =======================================================================================

void InicializeStudentGrades(Student *student)
{

    for(int i = 0; MAX_QUANTITY_OF_STUDENT_GRADES >= i; i++)    
        student->grades[i] = 0;
    
}

void SetGradesAverage(LStudents* studentsList)
{
    float sum = 0;

    for (int j = 0; j < studentsList->lastIndex; j++) 
    {
        for (int i = 0; i < MAX_QUANTITY_OF_STUDENT_GRADES; i++)
            sum += studentsList->students[j].grades[i];

        if (sum > 0)
            studentsList->students[j].grades[MAX_QUANTITY_OF_STUDENT_GRADES] = (sum/MAX_QUANTITY_OF_STUDENT_GRADES);

        sum = 0;
    }
}

void PrintListStudents(LStudents studentsList)
{
    printf(BORDER);
    for(int i = 0; studentsList.lastIndex > i; i++)
    {
        printf("RA: %d\nNome: %s\n\nNota 1: %-.2f\nNota 2: %-.2f\nNota 3: %-.2f\nNota 4: %-.2f\nMedia:  %-.2f", studentsList.students[i].ra, studentsList.students[i].name, studentsList.students[i].grades[0], studentsList.students[i].grades[1], studentsList.students[i].grades[2], studentsList.students[i].grades[3], studentsList.students[i].grades[4]);
        printf(BORDER);
    }

    Pause("");
}

LStudents CopyList(LStudents studentsList)
{
    LStudents list;
    list.lastIndex = studentsList.lastIndex;

    for(int i = 0; i < studentsList.lastIndex; i++)    
        list.students[i] = studentsList.students[i];    

    return list;
}

void SwapPositions(LStudents* list, int i, int j)
{
    Student st;

    st = list->students[i];
    list->students[i] = list->students[j];
    list->students[j] = st;
}

LStudents GetListOrderByRA(LStudents studentsList)
{
    LStudents orderedList = CopyList(studentsList);

    for(int i = 1; i < orderedList.lastIndex; i++)
        for(int j = 0; j < orderedList.lastIndex - 1; j++)
            if (orderedList.students[i].ra < orderedList.students[j].ra)
                SwapPositions(&orderedList, i, j);

    return orderedList;
}

LStudents GetListOrderByName(LStudents studentsList)
{
    LStudents orderedList = CopyList(studentsList);

    for(int i = 1; i < orderedList.lastIndex; i++)
        for(int j = 0; j < orderedList.lastIndex - 1; j++)
            if (orderedList.students[i].name > orderedList.students[j].name)
                SwapPositions(&orderedList, i, j);

    return orderedList;
}

void RegisterStudents(LStudents *studentsList)
{
    Student student;

    if (studentsList->lastIndex == MAX_QUANTITY_OF_STUDENTS)
    {
        system("clear||cls");
        printf(BORDER);
        printf("\n%s\n", INSUFFICIENT_STORAGE_MESSAGE);
        printf(BORDER);
        Pause("");

        return;
    }

    printf(BORDER);
    printf("\nInforme o RA do aluno: ");
    scanf("%d", &student.ra);
    printf("Informe o nome do estudante: ");
    ClearBuffer();
    fgets(student.name, MAX_STUDENT_NAME_SIZE, stdin);
    RemoveNewLine(student.name);    
    InicializeStudentGrades(&student);

    studentsList->students[studentsList->lastIndex] = student;
    studentsList->lastIndex++;

    system("clear||cls");
    printf(BORDER);
    printf("\nAluno cadastrado com sucesso!\n");
    printf(BORDER);
    Pause("");
}

int FindStudentByRa(int studentRA, LStudents* studentsList)
{
    for(int i = 0; i < studentsList->lastIndex; i++)    
        if (studentsList->students[i].ra == studentRA)
            return i;   

    return -1;
}

LStudents FindStudentsByName(char* studentName, LStudents* studentsList)
{
    LStudents resultList;
    resultList.lastIndex = 0;

    for(int i = 0; i < studentsList->lastIndex; i++)    
        if (strcasestr(studentsList->students[i].name, studentName))
        {
            resultList.students[resultList.lastIndex] = studentsList->students[i];    
            resultList.lastIndex++;
        }

    return resultList;
}

void ReportMenu(LStudents studentsList)
{
    int option;

    do
    {
        system("clear||cls");
        printf(BORDER);
        printf("\nSelecione uma opcao:\n\n1 - Emitir  relatorio ordenado por R.A.\n2 - Emitir  relatorio ordenado por Nome\n3 - Emitir  relatorio de medias\n4 - Emitir relatorio com filtro de media\n\n0 - Voltar\n");
        printf(BORDER);
        scanf("%d", &option);
        system("clear||cls");

        switch (option)
        {
            case 1: PrintListStudents(GetListOrderByRA(studentsList)); break;
            case 2: PrintListStudents(GetListOrderByName(studentsList)); break;
            case 3: SetGradesAverage(&studentsList); PrintListStudents(GetListOrderByName(studentsList)); break;
            case 0: break;
        }

    } while (option);
    
}

void SearchByRAHandler(LStudents studentsList)
{
    Student student;
    LStudents resultList;

    system("clear||cls");
    printf(BORDER);
    printf("\nInforme o RA do aluno: ");
    scanf("%d", &student.ra);
    system("clear||cls");

    int indexResult = FindStudentByRa(student.ra, &studentsList);

    if (indexResult != -1)
    {
        resultList.students[0] = studentsList.students[indexResult];
        resultList.lastIndex++;    
        PrintListStudents(resultList);
    }
    else
    {
        printf(BORDER);
        printf("\n%s\n", NOT_FOUND_MESSAGE);
        printf(BORDER);
        Pause("");
    } 
}

void SearchByNameHandler(LStudents studentsList)
{
    Student student;
    LStudents resultList;

    system("clear||cls");
    printf(BORDER);
    printf("\nInforme o nome do aluno: ");
    ClearBuffer();
    fgets(student.name, MAX_STUDENT_NAME_SIZE, stdin);
    RemoveNewLine(student.name);
    system("clear||cls"); 

    resultList = FindStudentsByName(student.name, &studentsList);

    if (resultList.lastIndex > 0)
        PrintListStudents(resultList);
    else
    {
        printf(BORDER);
        printf("\n%s\n", NOT_FOUND_MESSAGE);
        printf(BORDER);
        Pause("");
    } 
}

void ConsultMenu(LStudents studentsList)
{
    int option;

    do
    {
        system("clear||cls");
        printf(BORDER);
        printf("\nSelecione uma opcao:\n\n1 - Buscar por RA\n2 - Buscar por Nome\n3 - Listar Todos\n\n0 - Voltar\n");
        printf(BORDER);
        scanf("%d", &option);
        system("clear||cls");

        switch (option)
        {
            case 1: SearchByRAHandler(studentsList); break;
            case 2: SearchByNameHandler(studentsList); break;
            case 3: PrintListStudents(studentsList); break;
        }

    } while (option != 0);
    
}

void RegisterStudentGrades(Student* student)
{
    int option;

    do
    {   system("clear||cls");
        printf(BORDER);
        printf("Informe qual nota deseja alterar:\n\n");
        for (int i = 0; i < MAX_QUANTITY_OF_STUDENT_GRADES; i++)
            printf("%dº Nota: %.2f\n", i+1, student->grades[i]);
        printf("\n0 - Voltar\n");
        printf(BORDER);
        scanf("%d", &option);

        if (option > 0 && option <= MAX_QUANTITY_OF_STUDENT_GRADES)
        {
            system("clear||cls");
            printf(BORDER);
            printf("Informe o valor da %dº nota: ", option);
            scanf("%f", &student->grades[option-1]);

            system("clear||cls");
            printf(BORDER);
            printf("Nota atualizada com sucesso!");
            printf(BORDER);
            Pause("");
        }

    } while (option);
}

void SetStudentGrades(LStudents* studentsList)
{
    int studentRA;

    system("clear||cls");
    printf(BORDER);
    printf("Informe o RA do aluno:");
    scanf("%d", &studentRA);

    int indexResult = FindStudentByRa(studentRA, studentsList);

    if (indexResult != -1)
        RegisterStudentGrades(&studentsList->students[indexResult]);
    else{
        system("clear||cls");
        printf(BORDER);
        printf("\n%s\n", NOT_FOUND_MESSAGE);
        printf(BORDER);
        Pause("");
    }

}

void RemoveStudent(int index, LStudents* studentsList)
{
    studentsList->lastIndex--;
    for (int i = index; i < studentsList->lastIndex; i++)
        studentsList->students[i] = studentsList->students[i+1];
        
}

void RemoveStudentHandler(LStudents* studentsList)
{
    int studentRA;
    char * message;
    system("clear||cls");
    printf(BORDER);
    printf("Informe o RA do aluno:");
    scanf("%d", &studentRA);

    int indexResult = FindStudentByRa(studentRA, studentsList);

    if (indexResult == -1)
        message = NOT_FOUND_MESSAGE;  
    else
    {
        RemoveStudent(indexResult, studentsList);
        message = "Aluno removido com sucesso!";
    }

    system("clear||cls");
    printf(BORDER);
    printf("\n%s\n", message);
    printf(BORDER);
    Pause("");
}

int main ()
{    
    LStudents studentsList;
    int option;

    studentsList.lastIndex = 0;
    system("clear||cls");

    do
    {
        printf(BORDER);
        printf("Selecione uma opcao:\n\n1 - Cadastrar Aluno\n2 - Registrar notas dos alunos\n3 - Remover Aluno\n4 - Consultar Alunos\n5 - Alterar dados Aluno\n6 - Emitir Relatorios\n\n0 - Sair\n");
        printf(BORDER);
        scanf("%d", &option);
        system("clear||cls");

        switch(option)
        {
            case 1: RegisterStudents(&studentsList); break;
            case 2: SetStudentGrades(&studentsList); break;
            case 3: RemoveStudentHandler(&studentsList); break;
            case 4: ConsultMenu(studentsList); break;
            case 5: break;
            case 6: ReportMenu(studentsList); break;
            case 0: break;
        }

    }while(option);
    
    return 0;
}