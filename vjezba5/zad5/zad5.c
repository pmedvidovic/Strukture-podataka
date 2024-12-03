#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
    double number;
    Position next;
} Element;

Position CreateElement(double number);
int InsertAfter(Position position, Position newElement);
int DeleteAfter(Position position);
int DeleteAll(Position position);
int Push(Position head, double number);
int Pop(double* Resultdestination, Position head);
int Operation(Position head, char operation);
int CalculatePostfix(double* Resultdestination, const char* filename);

int main()
{
    double result = 0;
    const char* filename = "postfix.txt";

    if (CalculatePostfix(&result, filename) == EXIT_SUCCESS)
    {
        printf("Rezultat: %0.1lf\n", result);
    }
    else
    {
        printf("Greska pri obradi datoteke: %s\n", filename);
    }

    return EXIT_SUCCESS;
}

Position CreateElement(double number)
{
    Position newElement = (Position)malloc(sizeof(Element));
    if (!newElement)
    {
        perror("Greska u alociranju memorije!");
        return NULL;
    }

    newElement->number = number;
    newElement->next = NULL;

    return newElement;
}

int InsertAfter(Position position, Position newElement)
{
    if (!position || !newElement)
    {
        return -1;
    }

    newElement->next = position->next;
    position->next = newElement;

    return EXIT_SUCCESS;
}

int DeleteAfter(Position position)
{
    Position temp = NULL;

    if (!position || !position->next)
    {
        return EXIT_SUCCESS;
    }

    temp = position->next;
    position->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}

int DeleteAll(Position head)
{
    while (head->next)
    {
        DeleteAfter(head);
    }

    return EXIT_SUCCESS;
}

int Push(Position head, double number)
{
    Position newElement = CreateElement(number);
    if (!newElement)
    {
        return -1;
    }

    return InsertAfter(head, newElement);
}

int Pop(double* Resultdestination, Position head)
{
    if (!head || !head->next)
    {
        perror("Postfix nije uredu! Provjerite datoteku.");
        return -1;
    }

    Position first = head->next;
    *Resultdestination = first->number;
    DeleteAfter(head);

    return EXIT_SUCCESS;
}

int Operation(Position head, char operation)
{
    double operand1 = 0;
    double operand2 = 0;
    double result = 0;

    if (Pop(&operand2, head) != EXIT_SUCCESS || Pop(&operand1, head) != EXIT_SUCCESS)
    {
        return -1;
    }

    switch (operation)
    {
    case '+':
        result = operand1 + operand2;
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '*':
        result = operand1 * operand2;
        break;
    case '/':
        if (operand2 == 0)
        {
            perror("Nazivnik ne smije biti nula!");
            return -2;
        }
        result = operand1 / operand2;
        break;
    default:
        perror("Ova operacija ne postoji!");
        return -3;
    }

    return Push(head, result);
}

int CalculatePostfix(double* Resultdestination, const char* filename)
{
    FILE* f = fopen(filename, "rb");
    if (!f)
    {
        perror("Greska s datotekom!");
        return -1;
    }

    fseek(f, 0, SEEK_END);
    int fileLength = ftell(f);
    rewind(f);

    char* buffer = (char*)calloc(fileLength + 1, sizeof(char));
    if (!buffer)
    {
        perror("Nemoguce alocirati memoriju!");
        fclose(f);
        return -2;
    }

    fread(buffer, sizeof(char), fileLength, f);
    fclose(f);

    char* currentBuffer = buffer;
    int status = 0;
    double number = 0;
    char operation = 0;
    int numbOfbytes = 0;
    Element head = { .number = 0, .next = NULL };

    while (strlen(currentBuffer) > 0)
    {
        status = sscanf(currentBuffer, " %lf %n", &number, &numbOfbytes);
        if (status == 1)
        {
            if (Push(&head, number) != EXIT_SUCCESS)
            {
                free(buffer);
                DeleteAll(&head);
                return -3;
            }
            currentBuffer += numbOfbytes;
        }
        else
        {
            status = sscanf(currentBuffer, " %c %n", &operation, &numbOfbytes);
            if (status == 1)
            {
                if (Operation(&head, operation) != EXIT_SUCCESS)
                {
                    free(buffer);
                    DeleteAll(&head);
                    return -4;
                }
                currentBuffer += numbOfbytes;
            }
            else
            {
                free(buffer);
                DeleteAll(&head);
                perror("Neispravan unos u datoteci!");
                return -5;
            }
        }
    }

    free(buffer);
    if (Pop(Resultdestination, &head) != EXIT_SUCCESS)
    {
        DeleteAll(&head);
        return -6;
    }

    if (head.next)
    {
        perror("Postfix nije uredu! Provjerite datoteku.");
        DeleteAll(&head);
        return -7;
    }

    return EXIT_SUCCESS;
}
