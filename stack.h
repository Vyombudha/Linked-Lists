#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BUFFER 257
#define NO_VALUE '\0'

// enums based codes to handle stack proccess!
typedef enum
{
    RESPONSE_INITIATED = 0,
    STACK_PROCESS_SUCCESSFUL = 1,
    STACK_PUSH_NODE_ALLOCATION_ERROR = 2,
    STACK_EMPTY = 3,
    STACK_NULL_POINTER = 4,
    STACK_ALREADY_INITIATED = 5
} stackCodes;

extern const char *STACK_MESSAGES[6];


// A struct to handle Struct Prccess Codes  and Return Values!
typedef struct
{
    stackCodes code;
    char returnValue;
    char message[MAX_BUFFER];
} stackResponse;

typedef struct Node
{
    char data;
    struct Node *nextNode;
} Node;

typedef struct
{
    size_t size;
    Node *top;
} Stack;

// Functions for Response struct!
stackResponse newResponse(stackCodes code);

// Functions for handling Stack Operations!
Node *newNode(char data);
Stack newStack(void);
stackResponse push(Stack *stack, char data);
stackResponse pop(Stack *stack);
stackResponse printStack(const Stack *stack);
stackResponse destroyStack(Stack *stack);
stackResponse peek(const Stack *stack);

// Helper Functions for Stack!
bool isNULL(const Stack *stack);
bool isEmpty(const Stack *stack);
size_t size(const Stack *stack);

#endif // STACK_H
