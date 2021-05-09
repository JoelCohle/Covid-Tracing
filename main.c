#include "covid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define Tablesize 211

void print_status(int status)
{
    if (status == 0)
        printf("Covid-Positive\n");
    if (status == 1)
        printf("Primary Contact\n");
    if (status == 2)
        printf("Secondary Contact\n");
    if (status == 3)
        printf("Safe\n");
    return;
}

void print_list_at_station(ll station_num, ll N, PtrtoPerson *person_list)
{
    printf("List of People at the station with their statuses:\n");
    for (ll i = 0; i < N; i++)
    {
        if (person_list[i]->station_no == station_num)
        {
            ll status = person_list[i]->type;
            printf("Person %lld: ", i + 1);
            print_status(status);
        }
    }
}

void print_full_list(PtrtoPerson *P, ll K)
{
    printf("List of Primary and Secondary Contacts:\n");
        for (ll i = 0; i < K; i++)
        {
            if (P[i]->type == primary_contact || P[i]->type == secondary_contact)
            {
                ll status = P[i]->type;
                printf("Person %lld: ", i + 1);
                print_status(status);
            }
        }
}

int main(void)
{
    ll N; // Total number of stations
    ll M; // Total number of roads
    ll K; // Total number of people
    scanf("%lld %lld %lld", &N, &M, &K);


    Graph *G = create_graph(N, M, K); // create an empty graph

    for (ll i = 0; i < M; i++)
    {
        ll U, V, W;
        scanf("%lld %lld %lld", &U, &V, &W);
        insert_bidirectional_road(G, U, V, W, 0); // In the graph G, between U and V inserts a road of length W and danger value 0
    }


    //Initialize all the stations
    Station **Stationlist = (Station **)malloc(N * sizeof(Station *));
    assert(Stationlist != NULL);
    for (ll i = 0; i < N; i++)
    {
        Stationlist[i] = (Station*)malloc(sizeof(Station));
        Stationlist[i]->PeopleList = CreateHashTable(Tablesize);
    }

    // HashTable myHT = CreateHashTable(Tablesize);
    // separateHash(myHT, 3, safe, '+');
    
    PtrtoPerson *P = initialize_people(K);
    for (ll i = 0; i < K; i++)
    {
        scanf("%lld", &P[i]->station_no);
        P[i]->ID = i + 1;
        separateHash(Stationlist[P[i]->station_no - 1]->PeopleList, P[i]->ID, safe, '+');
    }

    //List of Covid Positive

    ll L, D, X;
    scanf("%lld", &L);
    scanf("%lld", &D);
    scanf("%lld", &X);
    for (ll i = 0; i < L; i++)
    {
        ll person;
        scanf("%lld", &person);
        if (person > K){
            printf("Invalid Entry \n");
            continue;
        }
        P[person - 1]->type = covid_positive;
        ll location = P[person - 1]->station_no;

        MovePerson(person, Stationlist[location - 1], Stationlist[location - 1], P);
    }

    // Accept Movements of all people for X days

    for (ll i = 0; i < X; i++)
    {
        printf("Enter all movements on day %lld\n", i + 1);
        ll num;
        scanf("%lld", &num);
        for (ll i = 0; i < num; i++)
        {
            ll personID, U, V;
            scanf("%lld %lld %lld", &personID, &U, &V);
            if (P[personID-1]->station_no != U){
                printf("Invalid movement \n");
                continue;
            }
            P[personID-1]->station_no = V;
            MovePerson(personID, Stationlist[U - 1], Stationlist[V - 1], P);
        }

        printf("Enter number of queries\n");
        ll numq;
        scanf("%lld", &numq);
        for (ll i = 0; i < numq; i++)
        {
            char query[10];
            scanf("%s", query);
            if (strcmp(query, "status") == 0)
            {
                ll personID;
                scanf("%lld", &personID);
                int status = P[personID - 1]->type;
                print_status(status);
            }
            if (strcmp(query, "location") == 0)
            {
                ll personID;
                scanf("%lld", &personID);
                printf("Station Number %lld\n", P[personID - 1]->station_no);
            }
            if (strcmp(query, "list") == 0)
            {
                ll station_num;
                scanf("%lld", &station_num);
                print_list_at_station(station_num, K, P);
            }
        }
        print_full_list(P, K);
        
        printf("Proceeding to the next day\n");
    }

    return 0;
}
