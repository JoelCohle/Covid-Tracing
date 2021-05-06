#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "covid.h"

int Update(Station S, PtrtoPerson P)
{
    int covid, prim, second;

    // just in case P is safe and goes to place with primary so update P
    for (int i = 0; i < S.no_of_people; i++)
    {
        PtrtoPerson Current = S.PeopleList->pStart[i];
        while (Current != NULL)
        {
            if (Current->type < P->type)
                P->type = Current->type;

            Current = Current->next;
        }
    }

    // Updating all people
    for (int i = 0; i < S.no_of_people; i++)
    {
        PtrtoPerson Current = S.PeopleList->pStart[i];

        while (Current != NULL)
        {
            if (Current->type - P->type > 1)
                Current->type = P->type - 1;

            Current = Current->next;
        }
    }

    // Finding the number of covid, primary and secondary people;
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
    }
    
    int safety_value = covid + (prim / 5) + (second / 10);

    return safety_value;
}

int Safety_Value(Graph *G, int S, int V, PtrtoPerson P)
{
    P->station_no = V;
    int safetyVal_S, safetyVal_V;

    safetyVal_S = Update(G->arr_of_stations[S], P);
    safetyVal_V = Update(G->arr_of_stations[V], P);

    return safetyVal_V;
}

