#include "stack.h"


Node* newNode(char data){
    Node* node = malloc(sizeof(Node));

    if(node!= NULL){
        node->data = data;
        node->nextNode = NULL;
        return node;
    }
    return NULL;
}



stackResponse newResponse(stackCodes code){
    stackResponse response  = {
        .code = code,
        .poppedData = NO_VALUE
    };
    snprintf(response.message, MAX_BUFFER, "%s", STACK_MESSAGES[code]); // same as strcpy() but better!
    return response;
}

Stack newStack(void){

    Stack stack  = {
        .size = 0,
        .top = NULL
    };

    return stack;
}


bool isEmpty(const Stack *stack){
    return (stack->size == (size_t)0);
}


size_t size(const Stack *stack){
    return stack->size;
}

char peek(const Stack *stack){
    if(!isEmpty(stack))
    {
        return stack->top->data;
    }
    return NO_VALUE;
}

stackResponse push(Stack *stack,char data){
        Node *node =  newNode(data);

        if(node != NULL){
            if(stack->top == NULL)
            {
                stack->top = node;
            }
            else{
                node->nextNode = stack->top;
                stack->top = node;
            }

            stack->size++;
            return newResponse(STACK_PROCESS_SUCCESSFUL);
        }
        return newResponse(STACK_PUSH_NODE_ALLOCATION_ERROR);
}


stackResponse pop(Stack *stack){
    if(!isEmpty(stack)){

        // storing data/init for returning/popping purposes
        Node *nodeToPop = stack->top;
        char poppedData = nodeToPop->data;

        // main popping part
        stack->top = stack->top->nextNode;
        stack->size--;
        free(nodeToPop);


        stackResponse response = newResponse(STACK_PROCESS_SUCCESSFUL);
        response.poppedData = poppedData;
        return response;
    }
    return newResponse(STACK_EMPTY);
}

stackResponse destroyStack(Stack *stack){
    if(!isEmpty(stack)){
        Node* nodeToPop;
        while(!isEmpty(stack))
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

stackResponse printStack(const Stack *stack)
{
    if(!isEmpty(stack)){
        printf("STACK: ");
        for(Node* node = stack->top ; node != NULL ; node = node->nextNode){
            printf("%c, ",node->data);
        }
        printf("\n");
        return newResponse(STACK_PROCESS_SUCCESSFUL);
    }
    return newResponse(STACK_EMPTY);
}


// test case Example!!!
/*
int main(void)
{
    stackResponse  response  = newResponse(RESPONSE_INITIATED);
    Stack stack1 = newStack();
    Stack *stack = &stack1;

    response = push(stack,'m');

    if(response.code == STACK_PROCESS_SUCCESSFUL){
        printf("The RESPONSE MESSAGE IS: %s\n",response.message);
    }

    push(stack,'o');
    push(stack,'y');
    push(stack,'v');

    printStack(stack);

    response = pop(stack);

    if(response.code == STACK_PROCESS_SUCCESSFUL){
        printf("The Popped Value is: %c\n",response.poppedData);
    }


    destroyStack(stack);
    printf("The Stack has been destroyed!\n");


    response  = printStack(stack);

    printf("The response for Printing the Stack is: %s\n",response.message);

    return 0;
}*/
