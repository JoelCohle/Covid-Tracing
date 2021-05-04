#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 

struct Stack {
    int top;
   unsigned capacity;
    int* array;
};
 

struct Stack* makeStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 

int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
 

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
 

void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    
}
 
int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}
 
int peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}
 

int main()
{

    int i; 

    scanf("%d",&i ); 
    struct Stack* stack = makeStack(i);
 
    return 0;
}
