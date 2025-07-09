#ifndef LIST_TYPE2_H
#define LIST_TYPE2_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


typedef enum 
{
    INT,
    CHAR,
    STRING,
    FLOAT
} datatypes;


/* The node struct to Store data union 'value' and pointer to next node */
typedef struct node
{
    void* data;
    struct node *next;
} node;

/* The linkedList struct to Containerise the currentNode using head and tail nodes and Handle Type checking using function pointers */
typedef struct linkedList
{
    node *head;
    node *tail;
    datatypes currentType;

    void (*printNode)(node *currentNode);
    void (*insertNode)(node *currentNode, va_list arg);
    void (*removeNode)(struct linkedList* list,va_list arg);
} linkedList;

/* Function to CreateNewList based on dataType enum Passed */
linkedList newList(datatypes type);

void insertToList(linkedList *list, ...);
void deleteNode(linkedList *list,...);
void printList(linkedList list);
void freeList(linkedList* list);


/* Function to assgin Functions to Each List */
void assignFunctionPointers(linkedList *list);



/* Function For Integer type LinkedList */
void PrintInt(node *currentNode);
void insertNodeInt(node *currentNode, va_list arg);
void removeNodeInt(linkedList* list,va_list arg);

/* Function For Character type LinkedList */
void PrintChar(node *currentNode);
void insertNodeChar(node *currentNode, va_list arg);
void removeNodeChar(linkedList* list,va_list arg);

/* Function For String type LinkedList */
void PrintString(node *currentNode);
void insertNodeString(node *currentNode, va_list arg);
void removeNodeString(linkedList* list,va_list arg);

/* Function For Character type LinkedList */
void PrintFloat(node *curentNode);
void insertNodeFloat(node *currentNode, va_list arg);
void removeNodeFloat(linkedList* list,va_list arg);


#endif
