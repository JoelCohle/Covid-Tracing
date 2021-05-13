#ifndef __COVIDTRACER_H
#define __COVIDTRACER_H

#define ll long long int

#include <limits.h>
#include <float.h>

#define INFINITY DBL_MAX // to use in dijkstra
#define UNKNOWN -1

typedef struct Person * PtrtoPerson;
typedef struct sepchainHT * HashTable;
typedef long long int Element;
typedef long long int Key;
typedef long long int Vertex;
typedef struct Station Station;
typedef struct Graph Graph;
typedef struct Node Node;

enum type_of_person {covid_positive, primary_contact, secondary_contact, safe};

// info of each person
typedef struct Person {
    ll ID;
    ll station_no;
    enum type_of_person type;
    PtrtoPerson next;
} Person;

// info of the overall map
struct Graph { 
    ll no_of_stations;
    ll no_of_roads;      
    ll total_no_of_people;
    Node** arr_of_stations;
};

struct Node {
    ll length; // length of the edge
    double danger_value; // danger value of the edge
    ll station_no;
    Node* next; // ptr to next node
};

// info of each station
struct Station {
    HashTable PeopleList;
    ll station_no;
    ll no_of_people;
    double danger_value;
    Node* ptr_to_ll_of_neighbours; // pointer to the linked list of neighbours
};


///////////// Hashtable Code /////////////////////

struct sepchainHT{
    ll TableSize;
    PtrtoPerson *pStart;
};

HashTable CreateHashTable(ll TableSize);
Key Identityhash(Element x, ll n);
PtrtoPerson separateHash(HashTable myHT, Element x, int status, char query);

//////////////////////////////////////////////////

void MovePerson(Graph* G, ll personID, Station* station1, Station* station2, Person* *personlist);
double Update(Station *S, PtrtoPerson P, PtrtoPerson *person_list);

void update_danger_value_of_edges(Graph* G, Station** Stationlist);

/////// For task2 ////////

typedef struct path_info {
    double danger_value;
    ll length;
    ll no_of_vertices_in_the_path;
    ll* path_vertices;
} path_info;

// a struct to return the danger value and the length of the removed edge
typedef struct Set {
    double danger_value;
    ll length;
} Set;

int isConnected(Graph* G);
void GetPath (ll* previous_vertex, ll destination, path_info* path, ll* index);
path_info* dijkstra (Graph* G, ll source, ll destination);
void print_top_three_routes (Graph* G, ll source, ll destination);

////////////////////

Graph* create_graph(ll no_of_stations, ll no_of_roads, ll total_no_of_people);
void insert_edge(Graph* G, ll source, ll destination, ll length, double danger_value);
void insert_bidirectional_road(Graph* G, ll source, ll destination, ll length, double danger_value);
PtrtoPerson* initialize_people(ll no_of_people);

Set remove_edge(Graph* G, ll source, ll destination);
Set remove_bidirectional_road(Graph* G, ll source, ll destination);


void delete_hash_table(HashTable HT);
void delete_all_stations(Station** Stationlist, ll no_of_stations);
void delete_people(PtrtoPerson* P, ll no_of_people);
void delete_graph(Graph* G);

#endif
