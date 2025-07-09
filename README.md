# LinkedList Library in C

This repository contains three implementations of linked lists in C, developed as a learning project to explore data structures and advanced C concepts. Each prototype demonstrates different approaches to linked list design, from simple string storage to generic data handling and stack-based operations.

Prototype 1 (list_type1): A basic linked list for strings.
Prototype 2 (list_type2): A generic linked list supporting multiple data types using function pointers.
Prototype 3 (stack): A stack implemented as a linked list with robust error handling.

This repo is primarily for personal use and experimentation, with clear documentation to aid understanding and future reference.
Features
Prototype 1: String-Based Linked List

Stores strings (up to 256 characters) in a singly linked list.
Operations:
insert: Adds a string to the end of the list (O(1) with tail pointer).
deleteNode: Removes a node by string value.
searchInList: Returns the index of a string or -1 if not found.
printList: Displays the list with indices.
freeList: Frees all memory.


Basic error handling for memory allocation failures.
Ideal for learning linked list fundamentals.

Prototype 2: Generic Linked List

Supports multiple data types (INT, CHAR, STRING, FLOAT) using void pointers and function pointers for polymorphic behavior.
Uses an enum (datatypes) to specify the data type when creating a list with newList.
Operations:
insertToList: Adds a value of the specified type.
deleteNode: Removes a node by value.
printList: Prints the list using type-specific formatting.
freeList: Frees all memory.


Dynamically assigns function pointers (e.g., printNode, insertNode) based on the data type.
Error handling for memory allocation and empty lists.
Advanced design for flexibility, inspired by OOP polymorphism.

Prototype 3: Stack Implementation

A stack built on a linked list, storing strings (up to 300 characters).
Operations:
push: Adds a string to the top.
pop: Removes and returns the top string.
peek: Views the top string without removing it.
printStack: Displays the stack.
destroyStack: Frees all memory.
reverseStack: Reverses the stack (destructive).


Robust error handling using STACK_REPORT struct and STACK_CODES enum for memory errors, empty stack, and oversized strings.
Suitable for learning stack operations and error handling in C.

Installation

Clone the repository:
git clone https://github.com/your-username/Linked-Lists.git
cd Linked-Lists


Compile each prototype using gcc:
gcc -o list_type1 list_type1.c
gcc -o list_type2 list_type2.c
gcc -o stack stack.c


Run the executables:
./list_type1
./list_type2
./stack



Note: Add a main function to list_type1.c or list_type2.c if not present, or use the examples below.
Usage
Prototype 1: String-Based Linked List
Example usage in a main function:
#include "list_type1.h"

int main() {
    struct linkedList *list = createList();

    insert(&list, "Apple");
    insert(&list, "Banana");
    insert(&list, "Cherry");

    printList(list);

    int index = searchInList(list, "Banana");
    printf("Banana found at index: %d\n", index);

    deleteNode(&list, "Banana");
    printList(list);

    freeList(&list);
    return 0;
}

Output:
Index: 0, Value: Apple
Index: 1, Value: Banana
Index: 2, Value: Cherry
Banana found at index: 1
Banana was found in the List and has been deleted!
Index: 0, Value: Apple
Index: 1, Value: Cherry

Prototype 2: Generic Linked List
Example usage for a string-based list (adapt for INT, CHAR, or FLOAT):
#include "list_type2.h"

int main() {
    linkedList list = newList(STRING);

    insertToList(&list, "Vyom1");
    insertToList(&list, "Vyom2");
    insertToList(&list, "Vyom3");

    printList(list);

    deleteNode(&list, "Vyom2");
    printList(list);

    freeList(&list);
    return 0;
}

Output:
Index: 0, Value: Vyom1
Index: 1, Value: Vyom2
Index: 2, Value: Vyom3
Index: 0, Value: Vyom1
Index: 1, Value: Vyom3

Prototype 3: Stack Implementation
Example usage for the stack:
#include "stack.h"

int main() {
    Stack stack = newStack();
    STACK_REPORT report;

    push(&stack, "Vyom1", &report);
    push(&stack, "Vyom2", &report);
    printStack(&stack, &report);

    char *value = pop(&stack, &report);
    printf("Popped: %s\n", value);

    destroyStack(&stack, &report);
    return 0;
}

Output:
index: 0, Vyom2
index: 1, Vyom1
Popped: Vyom2

Error Handling

Prototype 1: Checks for memory allocation failures and empty lists, exiting with error messages on failure.
Prototype 2: Handles memory allocation errors and empty lists, with type-specific error messages (e.g., “Error in Memory ALlocation for STRING”).
Prototype 3: Uses a STACK_REPORT struct and STACK_CODES enum for detailed error reporting (e.g., empty stack, memory errors, oversized strings).

Project Structure

list_type1.h, list_type1.c: String-based linked list.
list_type2.h, list_type2.c: Generic linked list with function pointers.
stack.h, stack.c: Stack implementation.
README.md: This documentation.
