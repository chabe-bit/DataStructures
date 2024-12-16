#pragma once 

#define STACK_MAX_SIZE 512

typedef struct
{
    int top;
    int items[STACK_MAX_SIZE];
} Stack;

void init_stack(Stack *stack)
{
    stack->top = -1;
}

int empty(Stack *stack)
{
    return stack->top == -1;  
}

int full(Stack *stack)
{
    return stack->top == STACK_MAX_SIZE - 1;
}

void push(Stack *stack, int val)
{
    if (full(stack))
        return;
    
    stack->items[++stack->top] = val;
    printf("pushed: %d\n", stack->items[stack->top]);
}

int pop(Stack *stack)
{
    if (empty(stack))
        return 1;

    int temp = stack->items[stack->top--];
    printf("popped: %d\n", temp);

    return temp;
}




