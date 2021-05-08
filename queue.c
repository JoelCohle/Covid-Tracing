#include <stdio.h>
#include <stdlib.h>
 
typedef int Element;
typedef float Key;

// PQueue
typedef stNodepq PQueue;
typedef stNodepq Nodepq;

struct stNodepq{
    Element n;
    Key k;  // Lower values indicate higher k
    Nodepq* pNext;
 
};

PQueue* CreateEmptyPriorityQueue()
{
    PQueue* temp = (PQueue*)malloc(sizeof(PQueue));
    temp->n = NULL;
    temp->k = NULL;
    temp->pNext = NULL;
 
    return temp;
}

// Function to Create A New PQueue
PQueue* newNode(Element u, Key P)
{
    PQueue* temp = (PQueue*)malloc(sizeof(PQueue));
    temp->n = u;
    temp->k = P;
    temp->pNext = NULL;
 
    return temp;
}

// Removes the Element with the
// highest k form the list
void pop(PQueue** Q)
{
    PQueue* temp = *Q;
    (*Q) = (*Q)->pNext;
    free(temp);
}

//Return the value at Q
// the highest priority element in the queue without removing it from the queue
Element ExtractMin(PQueue** Q)
{
    return (*Q)->n;
    pop(Q);
}
  
// Function to Enqueue according to Key
void Priority_Enqueue(PQueue** Q, Element u, Key P)
{
    PQueue* start = (*Q);
 
    // Create new PQueue
    PQueue* temp = newNode(u, P);
 
    // Special Case: The Q of list has lesser
    // k than new node. So insert new
    // node before Q node and change Q node.
    if ((*Q)->k > P) {
 
        // Insert New PQueue before Q
        temp->pNext = *Q;
        (*Q) = temp;
    }
    else {
 
        // Traverse the list and find a
        // position to insert new node
        while (start->pNext != NULL &&
            start->pNext->k < P) {
            start = start->pNext;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->pNext = start->pNext;
        start->pNext = temp;
    }
}
 
 
// Function to check is list is empty
int isPQueueEmpty(PQueue** Q)
{
    return (*Q) == NULL;
}
