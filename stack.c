#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

void setStatus(STACK_REPORT *report, STACK_CODES code, const char *value)
{
    if (strlen(value) + 1 > MAX_STRING_SIZE)
    {
        report->code = code;
        strcpy(report->value, NO_VALUE);
        return;
    }

    strcpy(report->value, value); // only strcpy when value's size is < MAX_STRING_SIZE , So no buffer overhead!
    report->code = code;
}

void checkError(STACK_REPORT *report)
{
    switch (report->code)
    {
    case SUCCESS:
        // Nothing to Print As Success Denotes Nothing to report on!
        break;
    case MEMORY_ERROR_NODE:
        printf("\n There is Error in Allocating Memory for the Node itself when valueToPush was '%s'  in the Stack!, Try to free() more space before allocating new Nodes!\n", report->value);
        break;
    case MEMORY_ERROR_VALUE:
        printf("\nThe Value  which you entered for push in the Stack had a buffer size greater than MAX_STRING_SIZE of  300 bytes (including '/0' Character), Use Smaller Buffer Inputs!\n");
        break;
    case STACK_EMPTY:
        printf("\nThe Stack is Empty, Try Using Non Empty Stacks!\n");
        break;
    default:
        break;
    }
}

Node *newNode(const char *valueToAssign, STACK_REPORT *report)
{

    if ((strlen(valueToAssign)) + 1 > MAX_STRING_SIZE)
    {
        setStatus(report, MEMORY_ERROR_VALUE, NO_VALUE);
        return NULL;
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL)
    {
        setStatus(report, MEMORY_ERROR_NODE, valueToAssign);
        return NULL;
    }

    strcpy(node->value, valueToAssign); // only strcpy when valueToAssign's size is < MAX_STRING_SIZE , So no buffer overhead!
    node->next = NULL;

    setStatus(report, SUCCESS, valueToAssign);

    return node;
}

Stack newStack()
{
    Stack stack;

    stack.top = NULL;
    stack.size = 0;

    return stack;
}

void push(Stack *stack, const char *valueToPush, STACK_REPORT *report)
{
    Node *node = newNode(valueToPush, report);
    if (node != NULL)
    {
        if (stack->top == NULL)
        {
            stack->top = node;
        }
        else
        {
            node->next = stack->top;
            stack->top = node;
        }
        stack->size++;
        return;
    }
}

char *pop(Stack *stack, STACK_REPORT *report)
{
    Node *nodeToPop = stack->top;

    if (nodeToPop == NULL)
    {
        setStatus(report, STACK_EMPTY, NO_VALUE);
    }
    else
    {

        setStatus(report, SUCCESS, nodeToPop->value);

        stack->top = nodeToPop->next;
        stack->size--;

        free(nodeToPop);
        nodeToPop = NULL;
    }
    return report->value; // This will return NO_VALUE if the pop() was unsuccessful else the poppedValue by returning pointer to the report->value;
}

void peek(Stack *stack, STACK_REPORT *report)
{
    if (stack->top == NULL)
    {
        setStatus(report, STACK_EMPTY, NO_VALUE);
        return;
    }
    setStatus(report, SUCCESS, stack->top->value);
}

bool isEmpty(Stack *stack)
{
    return (stack->top == NULL);
}

void printStack(Stack *stack, STACK_REPORT *report)
{

    if (stack->top == NULL)
    {
        setStatus(report, STACK_EMPTY, NO_VALUE);
        return;
    }

    setStatus(report, SUCCESS, NO_VALUE);

    unsigned int index = 0;
    Node *currentNode = stack->top;

    while (currentNode != NULL)
    {
        printf("index: %d, %s\n", index++, currentNode->value);
        currentNode = currentNode->next;
    }
}

void destroyStack(Stack *stack, STACK_REPORT *report)
{
    while (!isEmpty(stack))
    {
        pop(stack, report);
    }
    setStatus(report, SUCCESS, NO_VALUE);
}

Stack reverseStack(Stack *stack, STACK_REPORT *report)
{
    Stack stack_rev = newStack();
    STACK_REPORT report_rev;
    if (!isEmpty(stack))
    {
        while (!isEmpty(stack))
        {
            pop(stack, report);
            push(&stack_rev, report->value, &report_rev);
            checkError(&report_rev);
        }
        setStatus(report, SUCCESS, NO_VALUE);
    }
    return stack_rev; // This will be a Empty Stack if the original Stack was empty so, No change! else, it will become reverse of original Stack,
}

// General use Example
int main()
{
    Stack stack1 = newStack();
    STACK_REPORT report;

    printf("The List is:\n");
    printStack(&stack1, &report);
    checkError(&report); // optional check!

    char *value = pop(&stack1, &report);
    printf("The popped Value is: %s\n", value);
    checkError(&report); // optional Check!

    destroyStack(&stack1, &report);

    if (isEmpty(&stack1))
    {
        printf("The stack1 is now Empty!\n");
    }
    else
    {
        printf("The stack1 is still not Empty\n");
    }

    printStack(&stack1, &report);
    checkError(&report);

    return 0;
}