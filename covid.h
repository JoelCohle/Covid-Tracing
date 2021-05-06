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
PtrtoPerson separateHash(HashTable myHT, Element x, int status, char query);

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
    double danger_value;
    Node* ptr_to_ll_of_neighbours; // pointer to the linked list of meighbours
} Station;

typedef struct Node {
    ll length; // length of the edge
    ll danger_value; // danger value of the edge
    ll station_no;
    struct Node* next; // ptr to next node
} Node;


/////// For task2 ////////

typedef struct path_info {
    ll danger_value;
    ll length;
    ll no_of_vertices_in_the_path;
    ll* path_vertices;
} path_info;

// a struct to return the danger value and the length of the removed edge
typedef struct Set {
    ll danger_value;
    ll length;
} Set;

int isConnected(Graph* G);
void GetPath (ll* previous_vertex, ll destination, path_info* path, ll* index);
path_info* dijkstra (Graph* G, ll source, ll destination);
top_three_routes (Graph* G, ll source, ll destination);

////////////////////

Graph* create_graph(ll no_of_stations, ll no_of_roads, ll total_no_of_people);
void insert_edge(Graph* G, ll source, ll destination, ll length, ll danger_value);
void insert_bidirectional_road(Graph* G, ll source, ll destination, ll length, ll danger_value);
Person* initialize_people(ll no_of_people);

Set remove_edge(Graph* G, ll source, ll destination);
Set remove_bidirectional_road(Graph* G, ll source, ll destination);



#endif