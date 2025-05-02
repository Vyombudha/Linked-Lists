#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char string[256];
    struct Node *next;
};


struct linkedList
{
    struct Node *head;
    struct Node *finalNode;
};

struct Node* createNode(char string[])
{
    struct Node* newNode = malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Error in allocating Memory for node with string %s\n",string);
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->string,string);
    newNode->next =  NULL;
    return newNode;
}

void insert(struct linkedList** list,char string[])
{
    struct Node* node = createNode(string);
    if(node == NULL)
    {
        printf("Error in memory allocation for Node!\n");
        exit(EXIT_FAILURE);
    }

    if((*list)->head == NULL)
    {
        (*list)->head  = node;
        (*list)->finalNode = node;
    }
    else
    {
        (*list)->finalNode->next = node;
        (*list)->finalNode = node;
    }
}

void printList(struct linkedList* list)
{
    int i = 0 ;
    struct Node* temp  = list->head;
    while(temp!=NULL)
    {
        printf("Index: %d, Value: %s\n",i,temp->string);
        i++;
        temp =  temp->next;
    }
}

struct linkedList* createList()
{
    struct linkedList* list  = malloc(sizeof(struct linkedList));
    if(list == NULL)
    {
        printf("Error in memory allocation for Linked List!\n");
        exit(EXIT_FAILURE);
    }
    list->head  = NULL;
    list->finalNode = NULL;
    return list;
}

void freeList(struct linkedList** list)
{
    struct Node* temp = (*list)->head,*currentNode;
    while(temp != NULL)
    {
        currentNode = temp;
        temp = temp->next;
        free(currentNode);
    }
    free(*list);
    *list = NULL;
}


int searchInList(struct linkedList *list, char *string)
{
    int index = 0;
    struct Node *temp = list->head;
    while (temp != NULL)
    {
        if (strcmp(temp->string, string) == 0)
        {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1;
}


void deleteNode(struct linkedList** list,char *string)
{
    struct Node* temp = (*list)->head , *prev =NULL;

    if(temp == NULL)
    {
        printf("\nThe List is empty!\nTry again with a non empty List\n");
        return;
    }

    if(strcmp(temp->string,string) == 0)
    {
        (*list)->head = temp->next;
        free(temp);
        return;
    }

    while(temp != NULL)
    {
        if(strcmp(temp->string,string) == 0)
        {
            printf("\n%s was found in the List and has benn deleted!\n",string);
            prev->next = temp->next;
            free(temp);
            return;
        }
        prev = temp ; 
        temp = temp->next;
    }

    printf("\n%s was not found in the List!\n",string);
}
