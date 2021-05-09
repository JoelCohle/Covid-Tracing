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

    G->arr_of_stations = (Station*) malloc (no_of_stations * sizeof(Station));
    assert(G->arr_of_stations != NULL);

    for (ll i = 0; i < no_of_stations; i++) {
        G->arr_of_stations[i].danger_value = 0;
        G->arr_of_stations[i].no_of_people = 0;
        G->arr_of_stations[i].ptr_to_ll_of_neighbours = NULL;
    }

    return G;
}

// Inserts an edge of length 'length' from 'source' to 'destination' 
void insert_edge(Graph* G, ll source, ll destination, ll length, double danger_value) {
    
    Node* temp = G->arr_of_stations[source].ptr_to_ll_of_neighbours;

    bool found = false;
    while (temp != NULL) {
        if (temp->station_no == destination) {
            found = true;
            return;
        }
        temp = temp->next;
    }

    if (!found) {
        temp = (Node*) malloc (sizeof(Node));
        assert(temp != NULL);

        temp->station_no = destination;
        temp->length = length;
        temp->danger_value = danger_value;

        temp->next = G->arr_of_stations[source].ptr_to_ll_of_neighbours;
        G->arr_of_stations[source].ptr_to_ll_of_neighbours = temp;
    }
}

void insert_bidirectional_road(Graph* G, ll U, ll V, ll W, double danger_value) {
    insert_edge(G, U, V, W, danger_value); // Insert an edge from U to V
    insert_edge(G, V, U, W, danger_value); // Insert an edge from V to U
    G->no_of_roads++;
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
    Node* p = G->arr_of_stations[source].ptr_to_ll_of_neighbours;
    Node* t;

    Set set;
    set.length = UNKNOWN;
    set.danger_value = UNKNOWN;

    while (p != NULL) {
        if (p->next->station_no == destination) {
            t = p->next;
            p->next = t->next;

            set.danger_value = t->danger_value;
            set.length = t->length;

            free(t); 

            return set;
        }
        p = p->next;
    }

    return set;
}

Set remove_bidirectional_road(Graph* G, ll source, ll destination) {
    Set set;
    set = remove_edge(G, source, destination);
    set = remove_edge(G, destination, source);
    G->no_of_roads --;
    return set;
}


void delete_graph(Graph* G) {
    for (ll i = 0; i < G->no_of_stations; i++) {
        Node* p = G->arr_of_stations[i].ptr_to_ll_of_neighbours;
        while (p != NULL) {
            

            p = p->next;
        }
    }
}
