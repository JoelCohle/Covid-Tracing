#include "covid.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Creates an empty graph with the given info and returns a pointer to the graph
Graph* create_graph(ll no_of_stations, ll no_of_roads, ll total_no_of_people) {
    Graph* G = (Graph*) malloc (sizeof(Graph));
    assert (G != NULL);
    
    G->no_of_stations = no_of_stations;
    G->no_of_roads = no_of_roads;
    G->total_no_of_people = total_no_of_people;

    G->arr_of_stations = (Node**) malloc (no_of_stations * sizeof(Node*));
    assert(G->arr_of_stations != NULL);

    for (ll i = 0; i < no_of_stations; i++) {
        G->arr_of_stations[i] = NULL;
    }

    return G;
}

// Inserts an edge of length 'length' from 'source' to 'destination' 
void insert_edge(Graph* G, ll source, ll destination, ll length, double danger_value) {
    
    Node* temp = G->arr_of_stations[source];

    bool found = false;
    while (temp != NULL) {
        if (temp->station_no == destination) {
            found = true;
            return;
        }
        temp = temp->next;
    }
    
    if (!found) {
        Node* p = (Node*) malloc (sizeof(Node));        
        assert(p != NULL);

        p->station_no = destination;
        p->length = length;
        p->danger_value = danger_value;

        p->next = G->arr_of_stations[source];
        G->arr_of_stations[source] = p;
    }
}

void insert_bidirectional_road(Graph* G, ll U, ll V, ll W, double danger_value) {
    insert_edge(G, U, V, W, danger_value); // Insert an edge from U to V
    insert_edge(G, V, U, W, danger_value); // Insert an edge from V to U
}

// Initializes an array (size = number of people) of people 
PtrtoPerson* initialize_people(ll no_of_people) {
    PtrtoPerson* P = (PtrtoPerson*) malloc (no_of_people * sizeof(PtrtoPerson));
    assert(P != NULL);

    // Initializing everyone as safe
    for (int i = 0; i < no_of_people; i++) {
        P[i] = (Person*) malloc (sizeof(Person));
        assert(P != NULL);
        P[i]->type = safe;
    }

    return P;
}

// removes the edge from source to destination and returns the danger value and the length of the removed edge
Set remove_edge(Graph* G, ll source, ll destination) {
    Node* p = G->arr_of_stations[source];
    Node* t = p;

    Set set;
    set.length = UNKNOWN;
    set.danger_value = UNKNOWN;

    if (p != NULL && p->station_no == destination) {
        set.length = p->length;
        set.danger_value = p->danger_value;
        G->arr_of_stations[source] = p->next;
        free(p);

        return set;
    }

    while (p != NULL && p->station_no != destination) {
        p = p->next;
    }
    while (t != NULL && t->next != p) {
        t = t->next;
    }

    t->next = p->next;
    set.length = p->length;
    set.danger_value = p->danger_value;
    free(p);

    return set;
}

Set remove_bidirectional_road(Graph* G, ll source, ll destination) {
    Set set;
    set = remove_edge(G, source, destination);
    set = remove_edge(G, destination, source);
    // G->no_of_roads --;
    return set;
}


void delete_all_stations(Station** Stationlist, ll no_of_stations) {
    for (ll i = 0; i < no_of_stations; i++) {
        free(Stationlist[i]);
    }
    free(Stationlist);
}

void delete_people(PtrtoPerson* P, ll no_of_people) {
    for (ll i = 0; i < no_of_people; i++) {
        free(P[i]);
    }
    free(P);
}

void delete_graph(Graph* G) {
    Node* p, *t;
    for (ll i = 0; i < G->no_of_stations; i++) {
        Node* p = G->arr_of_stations[i];
        while (p != NULL) {
            t = p;
            p = p->next;
            free(t);
        }
    }

    free(G->arr_of_stations);

    free(G);
}