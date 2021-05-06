#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "covid.h"

int Update(Station S, PtrtoPerson P)
{
    int covid, prim, second;

    if (S.MostInfectiousType > P->type)
    {
        if (S.MostInfectiousType - P->type > 1)
        {
            S.MostInfectiousType = P->type;
            for (int i = 0; i < S.no_of_people; i++)
            {
                PtrtoPerson Current = S.PeopleList->pStart[i];
                while (Current != NULL)
                {
                    Current->type = P->type - 1;
                    Current = Current->next;
                }
            }
        }
    }

    else
    {
        if (P->type - S.MostInfectiousType > 1)
        {
            P->type = S.MostInfectiousType - 1;
        }
    }

    for (int i = 0; i < S.no_of_people; i++)
    {
        PtrtoPerson Current = S.PeopleList->pStart[i];
        while (Current != NULL)
        {
            if (Current->type == 0)
                covid++;
            if (Current->type == 1)
                prim++;
            if (Current->type == 2)
                second++;
            Current = Current->next;
        }

        int safety_value = covid + (prim / 5) + (second / 10);

        return safety_value;
    }
}

void Add(Station S, PtrtoPerson P)
{
    Key K = Identityhash(P->ID, S.no_of_people);
    PtrtoPerson Position = S.PeopleList->pStart[K]->next;
    while ((Position != NULL) && (Position->ID != P->ID))
        Position = Position->next;

    if (Position == NULL)
    {
        Position = (PtrtoPerson)malloc(sizeof(Person));
        assert(P != NULL);

        Position->next = S.PeopleList->pStart[K]->next;
        Position->ID = P->ID;
        Position->station_no = P->station_no;
        Position->type = P->type;
        S.PeopleList->pStart[K]->next = Position;
    }
    return;
}

void Delete(Station S, PtrtoPerson P)
{
    Key K;
    PtrtoPerson Search, Prev;

    K = Identityhash(P->ID, S.no_of_people);

    Search = S.PeopleList->pStart[K];

    while (Search != NULL)
    {
        if (Search->next != NULL && Search->next->ID == P->ID)
        {
            Search->next = Search->next->next;
            free(Search->next);
        }
    }
}

int Safety_Value(Graph *G, int S, int V, PtrtoPerson P)
{
    P->station_no = V;
    Add(G->arr_of_stations[V], P);
    Delete(G->arr_of_stations[S], P);

    int safetyVal_S, safetyVal_V;

    safetyVal_S = Update(G->arr_of_stations[S], P);
    safetyVal_V = Update(G->arr_of_stations[V], P);

    return safetyVal_V;
}

int main(void)
{
    return 0;
}