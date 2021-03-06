#include "covid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define Tablesize 101

// Prints status given Non-zero int < 4 //
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

// Prints List of all people at the sattion along with their status //
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

// Prints List of all Covid-Positive, Primary and Secondary Contacts //
void print_full_list(PtrtoPerson *P, ll K)
{
        for (ll i = 0; i < K; i++)
        {
            if (P[i]->type == primary_contact || P[i]->type == secondary_contact || P[i]->type == covid_positive)
            {
                ll status = P[i]->type;
                printf("Person %lld: ", i + 1);
                print_status(status);
            }
        }
}

int main(void)
{
    printf("\x1b[2J\x1b[1;1H");
    ll N; // Total number of stations
    ll M; // Total number of roads
    ll K; // Total number of people
    printf("Enter the number of stations, roads and people :\n");
    scanf("%lld %lld %lld", &N, &M, &K);

    Graph *G = create_graph(N, M, K); // create an empty graph

    if (M != 0){
        printf("\nEnter the List of all bidirectional roads:\n");
        printf("******************************************\n");
    }
    for (ll i = 0; i < M; i++)
    {
        ll U, V, W;
        scanf("%lld %lld %lld", &U, &V, &W);
        insert_bidirectional_road(G, U - 1, V - 1, W, 0); // In the graph G, between U and V inserts a road of length W and danger value 0
    }

    // Initialize all the stations
    Station **Stationlist = (Station **)malloc(N * sizeof(Station *));
    assert(Stationlist != NULL);
    for (ll i = 0; i < N; i++)
    {
        Stationlist[i] = (Station*)malloc(sizeof(Station));
        assert(Stationlist[i] != NULL);
        Stationlist[i]->PeopleList = CreateHashTable(Tablesize);
        Stationlist[i]->station_no = i;
    }
    
    // Initial Locations of all people
    printf("\nEnter Initial Locations of all people:\n");
    PtrtoPerson *P = initialize_people(K);
    for (ll i = 0; i < K; i++)
    {
        scanf("%lld", &P[i]->station_no);
        P[i]->ID = i + 1;
        separateHash(Stationlist[P[i]->station_no - 1]->PeopleList, P[i]->ID, safe, '+');
    }

    ////////////////////////////
    // List of Covid Positive //
    ////////////////////////////
    ll L, D, X;
    printf("\nEnter the size of list L, day the list is released(D) and number of days to calculate contacts:\n");
    scanf("%lld", &L);     // Number of people in the list
    scanf("%lld", &D);     // Day the list was released
    scanf("%lld", &X);     // Number of days before we want to find Possible contacts
    printf("\nEnter the List of all Covid Posistive people on Day %lld:\n", D);
    printf("******************************************************\n");
    for (ll i = 0; i < L; i++)
    {
        ll person;
        scanf("%lld", &person);                 // Id of the person
        if (person > K){
            printf("Person does not exist \n");         // If such a person doesnt exist
            continue;
        }
        P[person - 1]->type = covid_positive;   // Assigning covid_positive status to the person
        ll location = P[person - 1]->station_no;// Finding current Location of the person

        MovePerson(G, person, Stationlist[location - 1], Stationlist[location - 1], P);
    }
    printf("\x1b[2J\x1b[1;1H");

    ///////////////////////////////////////////////
    // Accept Movements of all people for X days //
    ///////////////////////////////////////////////
    for (ll i = 0; i < X; i++)
    {
        printf("Enter number of movements, followed by all movements on day %lld\n", D - X + i);
        printf("**************************************************************\n");
        ll num;
        scanf("%lld", &num);    // Enter number of movements
        for (ll i = 0; i < num; i++)
        {
            ll personID, U, V;
            scanf("%lld %lld %lld", &personID, &U, &V); // (PersonID, Initial_station, Final_station)
            if (P[personID-1]->station_no != U || V > N)
            {
                printf("Invalid movement \n");          // If person isn't currently in that station
                continue;
            }
            P[personID-1]->station_no = V;
            MovePerson(G, personID, Stationlist[U - 1], Stationlist[V - 1], P);
        }

        printf("Enter number of queries followed by queries\n");
        printf("*******************************************\n");
        ll numq;
        scanf("%lld", &numq);
        printf("\n\n");
        for (ll i = 0; i < numq; i++)
        {
            char query[10];
            scanf("%s", query);
            if (strcmp(query, "status") == 0)       // To find status of a given Person
            {
                ll personID;
                scanf("%lld", &personID);
                if (personID > K){
                    printf("Person does not exist \n");         // If such a person doesnt exist
                    i--;
                    continue;
                }
                printf("Person %lld is ", personID);
                int status = P[personID - 1]->type;
                print_status(status);
            }
            if (strcmp(query, "location") == 0)     // To find current location of a given Person
            {
                ll personID;
                scanf("%lld", &personID);
                if (personID > K){
                    printf("Person does not exist \n");         // If such a person doesnt exist
                    continue;
                }
                printf("Person %lld is currently at Station Number %lld\n", personID, P[personID - 1]->station_no);
            }
            if (strcmp(query, "list") == 0)         // To print list of all people at a given station
            {
                ll station_num;
                scanf("%lld", &station_num);
                if (station_num > N){
                    printf("Station does not exist \n");         // If such a person doesnt exist
                    continue;
                }
                print_list_at_station(station_num, K, P);
            }
            printf("\n");
        }
        printf("\nList of all Covid-positive, Primary and Secondary contacts on Day %lld:\n", D - X + i);
        printf("************************************************************************\n");
        print_full_list(P, K);      // To print list of all primary and secondary contacts on Day 'i' (TASK 1)
        
        printf("\nProceeding to the next day\n\n\n\n\n");
    }

    // update the danger value of all the edges before finding the safest and shortest paths
    update_danger_value_of_edges(G, Stationlist);
    
    printf("Printing the best paths to travel\n\n");

    ll source, destination;
    printf("Enter the Station number of the source and the destination: ");
    scanf("%lld %lld", &source, &destination);
    printf("\n");
    print_top_three_routes(G, source - 1, destination - 1);
    

    printf("\nWe have found all Primary and Secondary Contacts of List L of people and carried out necessary user queries\n");


    // free all the dynamically allocated memory
    for (ll i = 0; i < N; i++) {
        delete_hash_table(Stationlist[i]->PeopleList);
    }
    delete_all_stations(Stationlist, N);;
    delete_people(P, K);
    delete_graph(G);

    return 0;
}
