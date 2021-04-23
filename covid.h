#ifndef __COVIDTRACER_H
#define __COVIDTRACER_H

#define ll long long int

// info of the overall map
typedef struct Graph { 
    ll no_of_stations;
    ll no_of_roads;      
    ll total_no_of_people;
    Station* arr_of_stations;
} Graph;

// info of each station
typedef struct Station {
    ll no_of_people;
    ll danger_value;
    Node* ptr_to_ll_of_neighbours;
} Station;

typedef struct Node {
    ll length; // length of the edge
    ll danger_value; // danger value of the edge
    ll station_no;
    struct Node* next; // ptr to next node
} Node;

enum type_of_person {covid_positive, primary_contact, secondary_contact, safe};

// info of each person
typedef struct Person {
    ll station_no;
    enum type_of_person type;
} Person;

Graph* create_graph(ll no_of_stations, ll no_of_roads, ll total_no_of_people);
void insert_edge(Graph* G, ll source, ll destination, ll length);
void insert_bidirectional_road(Graph* G, ll source, ll destination, ll length);
Person* initialize_people(ll no_of_people);




#endif