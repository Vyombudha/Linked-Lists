# Linked-Lists

Prototype-1-for-LinkedList-Header-File:
This has the functions for 
void insert(struct linkedList** list,char string[]);
void freeList(struct linkedList** list);
void printList(struct linkedList* list);
int searchInList(struct linkedList* list, char *string);
void deleteNode(struct linkedList** list,char *string);
 linkedLists in C



Prototype-2-for-LinkedList-Header-File:
This a complete overhaul in the Code taking from polymorhism basics from OOP and using function pointers and void pointers to make a new Type of LinkedList, to store any type of dataType the User Wants with least abstraction I could apply with my current understanding of C and skills;

The newList() takes an datatype enum as an argument. It will call a function assignFunctionPointers() to  idenditfy the right mathching datatype in the enum and, assing right function matching passed datatype.


