#ifndef __COVIDTRACER_H
#define __COVIDTRACER_H

#define ll long long int

typedef struct sepchainHT * HashTable;
typedef struct Person * PtrtoPerson;
typedef long long int Element;
typedef int Key;

struct sepchainHT{
    int TableSize;
    PtrtoPerson *pStart;
};

HashTable CreateHashTable(int TableSize);
Key Identityhash(Element x, int n);
int separateHash(HashTable myHT, Element x, int status, char query);

enum type_of_person {covid_positive, primary_contact, secondary_contact, safe};

// info of each person
typedef struct Person {
    ll ID;
    ll station_no;
    enum type_of_person type;
    PtrtoPerson next;
} Person;

// info of the overall map
typedef struct Graph { 
    ll no_of_stations;
    ll no_of_roads;      
    ll total_no_of_people;
    Station* arr_of_stations;
} Graph;

// info of each station
typedef struct Station {
    HashTable PeopleList;
    ll no_of_people;
    ll danger_value;
    enum type_of_person MostInfectiousType;
    Node* ptr_to_ll_of_neighbours;
} Station;

typedef struct Node {
    ll length; // length of the edge
    ll danger_value; // danger value of the edge
    ll station_no;
    struct Node* next; // ptr to next node
} Node;


Graph* create_graph(ll no_of_stations, ll no_of_roads, ll total_no_of_people);
void insert_edge(Graph* G, ll source, ll destination, ll length);
void insert_bidirectional_road(Graph* G, ll source, ll destination, ll length);
Person* initialize_people(ll no_of_people);




#endif