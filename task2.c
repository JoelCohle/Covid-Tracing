#include "covid.h"
#include "queue.h"
#include <stdlib.h>
#include <assert.h>

void delete_list (ll_node* p) {
    ll_node* t;
    while (p != NULL) {
        t = p;
        p = p->next;
        free(t);
    }
}

SPTable* Dijkstra (Graph* G) {
    ll n = G->no_of_stations;

    SPTable* table = (SPTable*) malloc (sizeof(SPTable));
    assert(table != NULL);

    table->pKnown = (int*) malloc (n * sizeof(int));
    assert(table->pKnown != NULL);
    table->pdistance_to_source = (double*) malloc (n * sizeof(double));
    assert(table->pdistance_to_source != NULL);
    table->pPrevious_vertex = (ll_node**) malloc (n * sizeof(ll_node*));
    assert(table->pPrevious_vertex != NULL);

    for (ll i = 0; i < n; i++) {
        table->pPrevious_vertex[i] = (ll_node*) malloc (sizeof(ll_node));
        assert(table->pPrevious_vertex[i] != NULL);

        table->pPrevious_vertex[i]->station_no = UNKNOWN;
        table->pPrevious_vertex[i]->next = NULL;
    }

    for (ll i = 0; i < n; i++) {
        table->pKnown[i] = 0;
        table->pdistance_to_source[i] = INFINITY;
    }
    table->pdistance_to_source[0] = 0;

    PQueue* Q = CreateEmptyPriorityQueue();
    for (ll i = 0; i < n; i++) {
        Priority_Enqueue(Q, i, table->pdistance_to_source[i]);
    }

    while (!IsPQueueEmpty(Q)) {
        ll u = ExtractMin(Q);

        table->pKnown[u] = 1;
        Node* temp = G->arr_of_stations[u].ptr_to_ll_of_neighbours;

        while (temp != NULL) {
            ll v = temp->station_no;
            if (table->pKnown[v] == 0) {
                if (table->pdistance_to_source[u] + temp->danger_value < table->pdistance_to_source[v]) {
                    table->pdistance_to_source[v] = table->pdistance_to_source[u] + temp->danger_value;
                    
                    delete_list(table->pPrevious_vertex[v]);
                    
                    ll_node* new_node = (ll_node*) malloc (sizeof(ll_node));
                    assert(new_node != NULL);

                    table->pPrevious_vertex[v] = new_node;

                    DecreaseKey(Q, v, table->pdistance_to_source[v]);
                }
                else if (table->pdistance_to_source[u] + temp->danger_value == table->pdistance_to_source[v]) {
                    ll_node* new_node = (ll_node*) malloc (sizeof(ll_node));
                    assert(new_node != NULL);

                    new_node->station_no = u;
                    new_node->next = table->pPrevious_vertex[v];
                    table->pPrevious_vertex[v] = new_node;
                }
            }
            temp = temp->next;
        }
    }

    return table;
}

top_three_shortest_routes (Graph* G, ll source, ll destination) {

}
