#include <stdio.h>
#include <stdlib.h>
 

 
typedef int Element;
typedef float Key;

// PQueue
typedef stNodepq PQueue;
typedef stNodepq Nodepq;
struct stNodepq{
    element n;
    key k;  // Lower values indicate higher k
    Nodepq* pNext;
 
};

// Function to Enqueue according to key 
void Priority_Enqueue(PQueue** Q, element u, key P)
{
    PQueue* start = (*head);
 
    // Create new PQueue
    PQueue* temp = newNode(u, P);
 
    // Special Case: The head of list has lesser
    // k than new node. So insert new
    // node before head node and change head node.
    if ((*head)->k > P) {
 
        // Insert New PQueue before head
        temp->pNext = *head;
        (*head) = temp;
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

//Return the value at head
// the highest priority element in the queue without removing it from the queue
Element ExtractMin(PQueue** Q)
{
    return (*Q)->n;
}
 
// Function to check is list is empty
int isPQueueEmpty(PQueue** Q)
{
    return (*Q) == NULL;
}
