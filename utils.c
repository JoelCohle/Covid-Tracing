#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "covid.h"

HashTable CreateHashTable(int TableSize)
{
    int i = 0;
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

Key Identityhash(Element x, int n)
{
    if (n)
        return x % n;
    else
        return -1;
}

int separateHash(HashTable myHT, Element x, int status, char query)
{
    Key k = Identityhash(x, myHT->TableSize);
    PtrtoPerson Position = myHT->pStart[k];
    int count = 0;
    while ((Position->next != NULL) && (Position->next->ID != x))
    {
        Position = Position->next;
        count++;
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
            return -1;
        PtrtoPerson Temp = Position->next;
        Position->next = Position->next->next;
        free(Temp);
    }
    if (Position->next == NULL && query == '?')
        return -1;
    return count;
}