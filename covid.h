#ifndef __COVIDTRACER_H
#define __COVIDTRACER_H

#define ll long long int

#include <limits.h>

#define INFINITY LLONG_MAX // to use in dijkstra
#define UNKNOWN -1

///////////// Hashtable Code /////////////////////

typedef struct sepchainHT * HashTable;
typedef struct Person * PtrtoPerson;
typedef long long int Element;
typedef int Key;
typedef long long int Vertex;

struct sepchainHT{
    int TableSize;
    PtrtoPerson *pStart;
};

HashTable CreateHashTable(int TableSize);
Key Identityhash(Element x, int n);
int separateHash(HashTable myHT, Element x, int status, char query);

//////////////////////////////////////////////////

void MovePerson(int personID, Station* station1, Station* station2, Person* *personlist);

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
    Node* ptr_to_ll_of_neighbours; // pointer to the linked list of meighbours
} Station;

typedef struct Node {
    ll length; // length of the edge
    ll danger_value; // danger value of the edge
    ll station_no;
    struct Node* next; // ptr to next node
} Node;


/////// For Dijkstra ////////

typedef struct linkedlistNode_for_SPTable_PreviousVertex {
    ll station_no;
    struct linkedlistNode_for_SPTable_PreviousVertex* next;
} ll_node;

typedef struct stSPTable {
    int *pKnown;
    double *pdistance_to_source;
    ll_node** pPrevious_vertex;
} SPTable;

////////////////////

Graph* create_graph(ll no_of_stations, ll no_of_roads, ll total_no_of_people);
void insert_edge(Graph* G, ll source, ll destination, ll length);
void insert_bidirectional_road(Graph* G, ll source, ll destination, ll length);
Person* initialize_people(ll no_of_people);




#endif