#include "pqueue.h"
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

PQueue* CreateEmptyPriorityQueue (ll capacity) {
    PQueue* Q = (PQueue*) malloc (sizeof(PQueue));
    assert(Q != NULL);

    Q->size = 0;
    Q->capacity = capacity;
    Q->arr = (pq_node*) malloc (capacity * sizeof(pq_node));
    assert(Q->arr != NULL);

    for (ll i = 0; i < capacity; i++) {
        Q->arr[i].k = LLONG_MAX;
    }

    return Q;
}

void swap(pq_node* x, pq_node* y) {
    pq_node z = *x;
    *x = *y;
    *y = z;
}

ll parent(ll i) {
    return (i - 1) / 2;
}

ll leftChild(ll i) {
    return 2 * i + 1;
}

ll rightChild(ll i) {
    return 2 * i + 2;
}

void shiftUp(PQueue* Q, ll i) {
    while (i > 0 && Q->arr[parent(i)].k > Q->arr[i].k) {
        swap(&Q->arr[parent(i)], &Q->arr[i]);
        i = parent(i);
    }
}

void shiftDown(PQueue* Q, ll i) {
    ll minIndex = i;

    ll l = leftChild(i);
    ll r = rightChild(i);

    if (l <= Q->size && Q->arr[l].k < Q->arr[minIndex].k) {
        minIndex = l;
    }

    if (r <= Q->size && Q->arr[r].k < Q->arr[minIndex].k) {
        minIndex = r;
    }

    if (i != minIndex) {
        swap(&Q->arr[i], &Q->arr[minIndex]);
        shiftDown(Q, minIndex);
    }
}

void Priority_Enqueue(PQueue* Q, Element u, Key k) {
    Q->size++;
    ll i = Q->size;
    Q->arr[i].n = u;
    Q->arr[i].k = k;

    shiftUp(Q, i);
}

ll ExtractMin(PQueue* Q) {
    ll result = Q->arr[0].n;

    Q->arr[0] = Q->arr[Q->size];
    Q->size--;

    shiftDown(Q, 0);

    return result;
}

void DecreaseKey(PQueue* Q, Element u, Key new_decreased_key) {
    // find the index of u in the heap
    ll i = 0;
    while (i < Q->size) {
        if (Q->arr[i].n == u) {
            break;
        }
        i++;
    }

    // update its key
    Q->arr[i].k = new_decreased_key;

    // heapify
    if (Q->arr[i].k < Q->arr[parent(i)].k) {
        shiftUp(Q, i);
    }
    else if (Q->arr[i].k > Q->arr[leftChild(i)].k || Q->arr[i].k > Q->arr[rightChild(i)].k) {
        shiftDown(Q, i);
    }

    return;
}

int IsPQueueEmpty(PQueue* Q) {
    if (Q->size > 0) {
        return 0;
    }
    else {
        return 1;
    }
}

void delete_pqueue(PQueue* Q) {
    free(Q->arr);
    free(Q);
}
