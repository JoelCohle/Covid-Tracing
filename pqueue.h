#ifndef __PQUEUE_H
#define __PQUEUE_H

#define ll long long int

typedef struct PQueue PQueue; // Priority Queue using Min Heaps
typedef struct pq_node pq_node; // Node in Priority Queue

typedef long long int Element;
typedef long long int Key;


struct PQueue {
    pq_node* arr;
    ll size; // number of elements present
    ll capacity; // maximum possible number of elements
};

struct pq_node {
    Element n;
    Key k;
};

PQueue* CreateEmptyPriorityQueue();
void Priority_Enqueue(PQueue* Q, Element u, Key k);
int IsPQueueEmpty(PQueue* Q);
Element ExtractMin(PQueue* Q);
void DecreaseKey(PQueue* Q, Element u, Key new_decreased_key);
void delete_pqueue(PQueue* Q);

#endif
