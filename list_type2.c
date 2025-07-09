#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "list_type2.h"


/* Test Use Case for the LinkedList */

// int main()
// {
//     linkedList list1 = newList(STRING);
//     insertToList(&list1, "VYOM1");
//     insertToList(&list1, "VYOM2");
//     insertToList(&list1, "VYOM3");
//     insertToList(&list1, "VYOM4");
//     insertToList(&list1, "VYOM5");
//     printf("The List Before Removing any Node :\n");
//     printList(list1);
//     deleteNode(&list1, "VYOM");
//     printf("The List After Deletion is :\n");
//     printList(list1);
//     deleteNode(&list1, "VYOM2");
//     printf("The List After Deletion is :\n");
//     printList(list1);

//     freeList(&list1);
//     return 0;
// }

/* Function to CreateNewList */
linkedList newList(datatypes type)
{
    linkedList list;
    list.currentType = type;
    list.head = NULL;
    list.tail = NULL;
    assignFunctionPointers(&list); // Will dynamically assign DataType Appropriate Functions Pointers

    return list;
}

void insertToList(linkedList *list, ...)
{
    va_list arg;
    va_start(arg, list);

    node *newNode = malloc(sizeof(node));

    if (newNode == NULL)
    {
        printf("\n\nError in Allocating Memory for Node of Value\n\n");
        exit(EXIT_FAILURE);
    }

    newNode->next = NULL;
    list->insertNode(newNode, arg); // Will assign Passed Value dynamically
    va_end(arg);

    if (list->head == NULL) //  If Head null is Null, Both tail and head will become the newNode
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode; // The tail will point to the newNode
        list->tail = newNode;       //  The newNode will become the tail
    }
}

void deleteNode(linkedList *list, ...)
{
    va_list arg;
    va_start(arg, list);

    if (list->head == NULL)
    {
        printf("\n\nThe Given List is Empty!, Cannot Delete Any Node!\n\n");
    }
    else
    {
        list->removeNode(list, arg);
    }
}

void printList(linkedList list)
{
    int currentIndex = 0;
    node *currentNode = list.head;
    if (currentNode == NULL)
    {
        printf("\nThe List is Empty!\n");
    }
    else
    {
        while (currentNode != NULL)
        {
            printf("Index: %i, ", currentIndex++);
            printf("Value: ");
            list.printNode(currentNode);
            printf("\n");
            currentNode = currentNode->next;
        }
    }
}

void freeList(linkedList *list)
{
    node *currentNode = list->head, *temp;

    while (currentNode != NULL)
    {
        temp = currentNode;
        currentNode = currentNode->next;
        free(temp->data);
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
}

/* Function to assgin function pointers to each Function*/
void assignFunctionPointers(linkedList *list)
{
    switch (list->currentType)
    {
    case INT:
        list->insertNode = insertNodeInt;
        list->printNode = PrintInt;
        list->removeNode = removeNodeInt;
        break;
    case CHAR:
        list->insertNode = insertNodeChar;
        list->printNode = PrintChar;
        list->removeNode = removeNodeChar;
        break;
    case STRING:
        list->insertNode = insertNodeString;
        list->printNode = PrintString;
        list->removeNode = removeNodeString;
        break;
    case FLOAT:
        list->insertNode = insertNodeFloat;
        list->printNode = PrintFloat;
        list->removeNode = removeNodeFloat;
        break;
    default:
        break;
    }
}

/* Function For Integer type LinkedList */
void PrintInt(node *currentNode)
{
    printf("%d", *(int *)currentNode->data);
}

void insertNodeInt(node *currentNode, va_list arg)
{

    int num_int = va_arg(arg, int);
    currentNode->data = malloc(sizeof(int));
    if (currentNode->data == NULL)
    {
        printf("\n\nError in Memory ALlocation for INT, %d\n\n", num_int);
        exit(EXIT_FAILURE);
    }
    *(int *)currentNode->data = num_int;
}

void removeNodeInt(linkedList *list, va_list arg)
{
    int num_int = va_arg(arg, int);
    node *currentNode = list->head;
    node *prev = NULL;

    if (*(int *)currentNode->data == num_int) // if value in head node
    {
        if (currentNode == list->tail) // if it is a single Node List
        {
            free(currentNode->data);
            free(currentNode); // make The head and tail point to NULL to avoid errors
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            list->head = currentNode->next; // head node will point to the it's nextNode
            free(currentNode->data);
            free(currentNode);
        }
        return;
    }

    while (currentNode != NULL)
    {
        if (*(int *)currentNode->data == num_int)
        {
            if (currentNode == list->tail)
            {
                list->tail = prev; // make previous Node the  the tail node
            }
            else
            {
                prev->next = currentNode->next; // the previous node will point to the next Node
            }
            free(currentNode->data);
            free(currentNode);
            return;
        }
        prev = currentNode;
        currentNode = currentNode->next;
    }
    printf("\n\nThe Node of Value %i was not found in the Given LinkedList1!\n\n", num_int);
}

/* Function For Character type LinkedList */
void PrintChar(node *curretnNode)
{
    printf("%c", *(char *)curretnNode->data);
}

void insertNodeChar(node *currentNode, va_list arg)
{
    char ch = (char)va_arg(arg, int);
    currentNode->data = malloc(sizeof(char));
    if (currentNode->data == NULL)
    {
        printf("\n\nError in Memory ALlocation for CHAR, %c\n\n", ch);
        exit(EXIT_FAILURE);
    }
    *(char *)currentNode->data = ch;
}

void removeNodeChar(linkedList *list, va_list arg)
{
    char ch = (char)va_arg(arg, int);
    node *currentNode = list->head;
    node *prev = NULL;

    if (*(char *)currentNode->data == ch) // if value in head node
    {
        if (currentNode == list->tail) // if it is a single Node List
        {
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            list->head = currentNode->next; // head node will point to the it's nextNode
        }
        free(currentNode->data);
        free(currentNode);
        return;
    }

    while (currentNode != NULL)
    {
        if (*(char *)currentNode->data == ch)
        {
            if (currentNode == list->tail)
            {
                list->tail = prev; // make previous Node the  the tail node
            }
            else
            {
                prev->next = currentNode->next; // the previous node will point to the next Node
            }
            free(currentNode->data);
            free(currentNode);
            return;
        }
        prev = currentNode;
        currentNode = currentNode->next;
    }
    printf("\n\nThe Node of Value %c was not found in the Given LinkedList1!\n\n", ch);
}

/* Function For String type LinkedList */
void PrintString(node *currentNode)
{
    printf("%s", (char *)currentNode->data);
}

void insertNodeString(node *currentNode, va_list arg)
{
    char *str = va_arg(arg, char *);
    currentNode->data = malloc(sizeof(char) * (strlen(str) + 1));
    if (currentNode->data == NULL)
    {
        printf("\n\nError in Memory ALlocation for STRING, %s\n\n", str);
        exit(EXIT_FAILURE);
    }
    strcpy((char *)currentNode->data, str);
}

void removeNodeString(linkedList *list, va_list arg)
{
    char *str = va_arg(arg, char *);
    node *currentNode = list->head;
    node *prev = NULL;
    if (strcmp((char *)currentNode->data, str) == 0) // if value in head node
    {
        if (currentNode == list->tail) // if it is a single Node List
        {
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            list->head = currentNode->next; // head node will point to the it's nextNode
        }
        free(currentNode->data);
        free(currentNode);
        return;
    }

    while (currentNode != NULL)
    {
        if (strcmp((char *)currentNode->data, str) == 0)
        {
            if (currentNode == list->tail)
            {
                list->tail = prev; // make previous Node the  the tail node
            }
            else
            {
                prev->next = currentNode->next; // the previous node will point to the next Node
            }
            free(currentNode->data);
            free(currentNode);
            return;
        }
        prev = currentNode;
        currentNode = currentNode->next;
    }
    printf("\n\nThe Node of Value %s was not found in the Given LinkedList1!\n\n", str);
}

/* Function For Character type LinkedList */
void PrintFloat(node *currentNode)
{
    printf("%.2f", *(float *)currentNode->data);
}

void insertNodeFloat(node *currentNode, va_list arg)
{
    float num_flt = (float)va_arg(arg, double);
    currentNode->data = malloc(sizeof(float));
    if (currentNode->data == NULL)
    {
        printf("\n\nError in Memory ALlocation for FLOAT, %.2f\n\n", num_flt);
        exit(EXIT_FAILURE);
    }
    *(float *)currentNode->data = num_flt;
}

void removeNodeFloat(linkedList *list, va_list arg)
{
    float num_flt = (float)va_arg(arg, double);
    node *currentNode = list->head;
    node *prev = NULL;

    if (*(float *)currentNode->data == num_flt) // if value in head node
    {
        if (currentNode == list->tail) // if it is a single Node List
        {
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            list->head = currentNode->next; // head node will point to the it's nextNode
        }
        free(currentNode->data);
        free(currentNode);
        return;
    }

    while (currentNode != NULL)
    {
        if (*(float *)currentNode->data == num_flt)
        {
            if (currentNode == list->tail)
            {
                list->tail = prev; // make previous Node the  the tail node
            }
            else
            {
                prev->next = currentNode->next; // the previous node will point to the next Node
            }
            free(currentNode->data);
            free(currentNode);
            return;
        }
        prev = currentNode;
        currentNode = currentNode->next;
    }
    printf("\n\nThe Node of Value %.2f was not found in the Given LinkedList1!\n\n", num_flt);
}
