#include "covid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_list_at_station(int station_num, int N, PtrtoPerson *person_list)
{
    printf("List of People at the station with their statuses:\n");
    for (int i = 0; i < N; i++)
    {
        if (person_list[i]->station_no == station_num)
        {
            int status = person_list[i]->type;
            printf("Person %d: ", i + 1);
            print_status(status);
        }
    }
}

void print_full_list(PtrtoPerson *P, int K)
{
    printf("List of People at the station with their statuses:\n");
        for (int i = 0; i < K; i++)
        {
            if (P[i]->type == primary_contact || P[i]->type == secondary_contact)
            {
                int status = P[i]->type;
                printf("Person %d: ", i + 1);
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

    Person *P = initialize_people(K);
    // set the initial station number of people using the user input
    for (int i = 0; i < K; i++)
    {
        ll initial_station_number;
        scanf("%lld", &initial_station_number);
        P[i].station_no = initial_station_number;
        P[i].ID = i + 1;
    }

    // Initialize all the stations
    Station **Stationlist = (Station **)malloc(N * sizeof(Station *));
    for (int i = 0; i < N; i++)
    {
        Stationlist[i]->PeopleList = CreateHashTable(Tablesize);
    }

    // Initial Positions of all people
    for (int i = 0; i < K; i++)
    {
        scanf("%lld", &P[i].station_no);
        int status = safe;
        separateHash(Stationlist[i]->PeopleList, P[i].ID, status, '+');
    }

    // List of Covid Positive
    ll L, D, X;
    scanf("%lld", &L);
    for (int i = 0; i < L; i++)
    {
        int person;
        scanf("%lld", &person);
        P[person - 1].type = covid_positive;
        scanf("%lld", &D);
        scanf("%lld", &X);
        Station* station = Stationlist[P[i].station_no - 1];
        MovePerson(person, station, station, &P);
    }

    // Accept Movements of all people for X days
    for (int i = 0; i < X; i++)
    {
        printf("Enter all movements on day %d\n", i + 1);
        int num;
        scanf("%d", &num);
        for (int i = 0; i < num; i++)
        {
            ll personID, U, V;
            scanf("%lld %lld %lld", &personID, &U, &V);
            P[i].station_no = V;
            MovePerson(personID, Stationlist[U - 1], Stationlist[V - 1], &P);
        }

        printf("Enter number of queries\n");
        int numq;
        scanf("%d", &numq);
        for (int i = 0; i < numq; i++)
        {
            char query[10];
            scanf("%s", query);
            if (strcmp(query, "status") == 0)
            {
                int personID;
                scanf("%d", &personID);
                int status = P[personID - 1].type;
                print_status(status);
            }
            if (strcmp(query, "location") == 0)
            {
                int personID;
                scanf("%d", &personID);
                printf("Station Number %d\n", P[personID - 1].station_no);
            }
            if (strcmp(query, "list") == 0)
            {
                int station_num;
                scanf("%d", &station_num);
                print_list_at_station(station_num, K, &P);
            }
        }
        print_full_list(&P, K);
        
        printf("Proceeding to the next day\n");
    }

    return 0;
}