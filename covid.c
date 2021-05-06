#include "covid.h"
#include <stdlib.h>
#include <stdbool.h>

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
void insert_edge(Graph* G, ll source, ll destination, ll length) {
    
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
        temp->danger_value = 0; // Initialize the danger value of the edge as zero

        temp->next = G->arr_of_stations[source].ptr_to_ll_of_neighbours;
        G->arr_of_stations[source].ptr_to_ll_of_neighbours = temp;
    }
}

void insert_bidirectional_road(Graph* G, ll U, ll V, ll W) {
    insert_edge(G, U, V, W); // Insert an edge from U to V
    insert_edge(G, V, U, W); // Insert an edge from V to U
    G->no_of_roads++;
}

// Initializes an array (size = number of people) of people 
Person* initialize_people(ll no_of_people) {
    Person* P = (Person*) malloc (no_of_people * sizeof(Person));
    assert(P != NULL);

    // Initializing everyone as safe
    for (int i = 0; i < no_of_people; i++) {
        P[i].type = safe;
    }

    return P;
}

// removes the edge from source to destination
void remove_edge(Graph* G, ll source, ll destination) {
    Node* p = G->arr_of_stations[source].ptr_to_ll_of_neighbours;
    Node* t;
    while (p != NULL) {
        if (p->next->station_no == destination) {
            t = p->next;
            p->next = t->next;
            free(t);
            return;
        }

        p = p->next;
    }
}

void remove_bidirectional_road(Graph* G, ll source, ll destination) {
    remove_edge(G, source, destination);
    remove_edge(G, destination, source);
    G->no_of_roads --;
}
