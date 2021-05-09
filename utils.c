#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "covid.h"

HashTable CreateHashTable(ll TableSize)
{
    ll i = 0;
    HashTable myHt;

    myHt = (HashTable)malloc(sizeof(struct sepchainHT));
    assert(myHt != NULL);

    myHt->TableSize = TableSize;
    myHt->pStart = (PtrtoPerson*)malloc(TableSize * sizeof(PtrtoPerson));
    assert(myHt->pStart != NULL);

    for (i = 0; i < TableSize; i++)
    {
        myHt->pStart[i] = (PtrtoPerson)malloc(sizeof(struct Person));
        assert(myHt->pStart[i] != NULL);

        (myHt->pStart[i])->next = NULL;
        myHt->pStart[i]->station_no = -1;
    }
    return myHt;
}

Key Identityhash(Element x, ll n)
{
    if (n)
        return x % n;
    else
        return -1;
}

PtrtoPerson separateHash(HashTable myHT, Element x, int status, char query)
{
    Key k = Identityhash(x, myHT->TableSize);
    PtrtoPerson Position = myHT->pStart[k];
    while ((Position->next != NULL) && (Position->next->ID != x))
    {
        Position = Position->next;
    }

    if (query == '+')
    {
        PtrtoPerson Temp = (PtrtoPerson)malloc(sizeof(struct Person));
        assert(Temp != NULL);
        if (Position->next != NULL && Position->next->ID == x){
            while (Position->next != NULL)
                Position = Position->next;
        }
        Position->next = Temp;
        Temp->ID = x;
        Temp->type = status;
        Temp->next = NULL;
    }

    if (query == '-')
    {
        if (Position->next == NULL)
            return NULL;
        PtrtoPerson Temp = Position->next;
        Position->next = Position->next->next;
        free(Temp);
    }
    if (Position->next == NULL && query == '?')
        return NULL;
    return Position->next;
}

#include <limits.h>
//#include <stdio.h>
//#include <stdlib.h>
 

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

