
#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 300
#define NO_VALUE "<NO_VALUE>"

typedef enum STACK_CODES
{
    STACK_EMPTY,
    MEMORY_ERROR_NODE,
    MEMORY_ERROR_VALUE,
    SUCCESS
} STACK_CODES;

typedef struct STACK_REPORT
{
    char value[MAX_STRING_SIZE];
    STACK_CODES code;
} STACK_REPORT;

typedef struct Node
{
    char value[MAX_STRING_SIZE];
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
    unsigned int size;
} Stack;

// Funtions With the stack reporting Struct:
void setStatus(STACK_REPORT *report, STACK_CODES code, const char *value);
void checkError(STACK_REPORT *report);

// Functions With the Stack Strcut itself:
Node *newNode(const char *valueToAssign, STACK_REPORT *report);
Stack newStack();
void push(Stack *stack, const char *valueToPush, STACK_REPORT *report);
char *pop(Stack *stack, STACK_REPORT *report);
void peek(Stack *stack, STACK_REPORT *report);
bool isEmpty(Stack *stack);
void printStack(Stack *stack, STACK_REPORT *report);
void destroyStack(Stack *stack, STACK_REPORT *report);
Stack reverseStack(Stack *stack, STACK_REPORT *report);

#endif