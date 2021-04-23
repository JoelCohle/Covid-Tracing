#include "covid.h"
#include <stdio.h>

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



    return 0;
}