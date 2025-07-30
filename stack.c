#include "stack.h"

// messages for appropriate Stack proccess Code
const char *STACK_MESSAGES[6] = {
    "RESPONSE_INITIATED",
    "STACK_PROCESS_SUCCESSFUL",
    "STACK_PUSH_NODE_ALLOCATION_ERROR",
    "STACK_EMPTY",
    "STACK_NULL_POINTER",
    "STACK_ALREADY_INITIATED"};


Node *newNode(char data)
{
    Node *node = malloc(sizeof(Node));

    if (node != NULL)
    {
        node->data = data;
        node->nextNode = NULL;
        return node;
    }
    return NULL;
}

bool isNULL(const Stack *stack)
{
    return (stack == NULL);
}

stackResponse newResponse(stackCodes code)
{
    stackResponse response;
    response.code = code;
    response.returnValue = NO_VALUE;
    snprintf(response.message, MAX_BUFFER, "%s", STACK_MESSAGES[code]); // same as strcpy() but better since, it takes buffer into account!
    return response;
}

Stack newStack(void)
{
    Stack stack = {
        .size = 0,
        .top = NULL};
    return stack;
}

bool isEmpty(const Stack *stack)
{
    if (!isNULL(stack))
    {
        return (stack->size == 0);
    }
    return false;
}

size_t size(const Stack *stack)
{
    if (!isNULL(stack))
    {
        return stack->size;
    }
    return 0; // since even a NULL stack technically has Zero Nodes within it!
}

stackResponse peek(const Stack *stack)
{
    if (!isNULL(stack))
    {
        if (!isEmpty(stack))
        {
            stackResponse response = newResponse(STACK_PROCESS_SUCCESSFUL);
            response.returnValue = stack->top->data;
            return response;
        }
        return newResponse(STACK_EMPTY);
    }
    return newResponse(STACK_NULL_POINTER);
}

stackResponse push(Stack *stack, char data)
{
    Node *node = newNode(data);
    if (!isNULL(stack))
    {
        if (node != NULL)
        {
            if (stack->top == NULL)
            {
                stack->top = node;
            }
            else
            {
                node->nextNode = stack->top;
                stack->top = node;
            }

            stack->size++;
            return newResponse(STACK_PROCESS_SUCCESSFUL);
        }
        return newResponse(STACK_PUSH_NODE_ALLOCATION_ERROR);
    }
    return newResponse(STACK_NULL_POINTER);
}

stackResponse pop(Stack *stack)
{
    if (!isNULL(stack))
    {
        if (!isEmpty(stack))
        {
            // storing data/init for returning/popping purposes
            Node *nodeToPop = stack->top;
            char returnValue = nodeToPop->data;

            // main popping part
            stack->top = stack->top->nextNode;
            stack->size--;
            free(nodeToPop);

            stackResponse response = newResponse(STACK_PROCESS_SUCCESSFUL);
            response.returnValue = returnValue;
            return response;
        }
        return newResponse(STACK_EMPTY);
    }
    return newResponse(STACK_NULL_POINTER);
}

stackResponse destroyStack(Stack *stack)
{
    if (!isNULL(stack))
    {
        if (!isEmpty(stack))
        {
            Node *nodeToPop;
            while (!isEmpty(stack))
            {
                nodeToPop = stack->top;
                stack->top = stack->top->nextNode;
                free(nodeToPop);
                stack->size--;
            }
            return newResponse(STACK_PROCESS_SUCCESSFUL);
        }

        return newResponse(STACK_EMPTY);
    }
    return newResponse(STACK_NULL_POINTER);
}

stackResponse printStack(const Stack *stack)
{
    if (!isNULL(stack))
    {
        if (!isEmpty(stack))
        {
            int i = stack->size;
            for (Node *node = stack->top; node != NULL; node = node->nextNode)
            {
                printf("index: %i, data: %c\n", i--, node->data);
            }
            printf("\n");
            return newResponse(STACK_PROCESS_SUCCESSFUL);
        }
        return newResponse(STACK_EMPTY);
    }
    return newResponse(STACK_NULL_POINTER);
}



stackResponse reverseStack(const Stack *stack, Stack *reversedStack)
{
    if (isNULL(stack) || isNULL(reversedStack))
    {
        return newResponse(STACK_NULL_POINTER);
    }

    if (isEmpty(stack))
    {
        return newResponse(STACK_EMPTY);
    }

    if (!isEmpty(reversedStack))
    {
        return newResponse(STACK_ALREADY_INITIATED);
    }

    stackResponse response = newResponse(RESPONSE_INITIATED);

    for (Node *node = stack->top; node != NULL; node = node->nextNode)
    {
        response = push(reversedStack, node->data);
        if (response.code != STACK_PROCESS_SUCCESSFUL)
        {
            return newResponse(response.code);
        }
    }

    return newResponse(STACK_PROCESS_SUCCESSFUL);
}

// test case Example!!!

int main(void)
{
    stackResponse response = newResponse(RESPONSE_INITIATED);
    Stack stack1 = newStack();
    Stack *stack = &stack1;

    response = push(stack, 'm');

    if (response.code == STACK_PROCESS_SUCCESSFUL)
    {
        printf("The RESPONSE MESSAGE IS: %s\n", response.message);
    }

    push(stack, 'o');
    push(stack, 'y');
    push(stack, 'v');

    printStack(stack);

    response = pop(stack);

    if (response.code == STACK_PROCESS_SUCCESSFUL)
    {
        printf("The Popped Value is: %c\n", response.returnValue);
    }

    destroyStack(stack);
    printf("The Stack has been destroyed!\n");

    response = printStack(stack);

    printf("The response for Printing the Stack is: %s\n", response.message);

    response = printStack(NULL);

    printf("The repsonse for Printing a NULL stack is: %s\n", response.message);

    return 0;
}
