#include "covid.h"
#include <stdio.h>
#include <stdlib.h>

#define Tablesize 211

int main (void) {
    ll N; // Total number of stations
    ll M; // Total number of roads
    ll K; // Total number of people
    scanf("%lld %lld %lld", &N, &M, &K);

    Graph* G = create_graph(N, M, K); // create an empty graph

    for (ll i = 0; i < M; i++) {
        ll U, V, W;
        scanf("%lld %lld %lld", &U, &V, &W);
        insert_bidirectional_road(G, U, V, W); // In the graph G, between U and V inserts a road of length W
    }

    Person* P = initialize_people(K);
    // set the initial station number of people using the user input
    for (int i = 0; i < K; i++) {
        ll initial_station_number;
        scanf("%lld", &initial_station_number);
        P[i].station_no = initial_station_number;
    }

    // Initialize all the stations
    Station* *Stationlist = (Station**)malloc(N*sizeof(Station*)); 
    for (int i = 0; i < N; i++) {
        Stationlist[i]->PeopleList = CreateHashTable(Tablesize);
    }

    // Initial Positions of all people
    for(int i = 0 ; i < K ; i++)
    {
        scanf("%lld", &P[i].station_no);
        int status = safe;
        separateHash(Stationlist[i]->PeopleList, P[i].ID, status, '+');
    }

    // List of Covid Positive
    ll L, D, X;
    scanf("%lld", &L);
    for(int i = 0 ; i<L; i++)
    {
        int person;
        scanf("%lld", &person);
        P[person-1].type = covid_positive;
        scanf("%lld", &D);
        scanf("%lld", &X);
    }

    // Accept Movements of all people for X days
    for(int i = 0 ; i < X ; i++)
    {
        char query;
        printf("Enter Movement of person (Person ID, Initial Station, Final Station)? (y/n)");
        scanf("%c", &query);
        if (query == 'y'){
            ll personID, U, V;
            scanf("%lld %lld %lld", &personID, &U, &V);
            P[i].station_no = V;
            MovePerson(personID, Stationlist[U-1], Stationlist[V-1], &P);
        }
        else
        {
            continue;
        }
        
    }


    return 0;
}