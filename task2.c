#include "covid.h"
#include "queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


// prints top 3 safest and shortest routes from source to destination
void print_top_three_routes (Graph* G, ll source, ll destination) {

    // find the 1st safest path by dijkstra
    path_info* safest_path_1 = dijkstra(G, source, destination);


    // find the second safest path by removing the edges in the 1st safest path from the graph and run dijkstra with one of the edge removed everytime
    path_info* safest_path_2;
    safest_path_2->danger_value = INFINITY;
    path_info* temp;

    ll n = safest_path_1->no_of_vertices_in_the_path;
    for (ll i = 0; i < n - 1; i++) {
        // remove the edge but store the length and danger value of the removed edge because we'll need it when adding the edge back
        Set deleted_road = remove_bidirectional_road(G, safest_path_1->path_vertices[i], safest_path_1->path_vertices[i + 1]);

        // run dijkstra only if the graph is connected after removing an edge
        // else just insert the edge back and continue to next iteration
        if (isConnected(G) == 1) {
            // store the safest path obtained by removing the edge between i and i + 1 in temp
            temp = dijkstra(G, source, destination);
            
            // update safest_path_2 only if temp's danger value is less than the danger value(s) of previous temp(s)
            if (temp->danger_value < safest_path_2->danger_value) {
                safest_path_2 = temp;
            }
        }

        // insert the edge back
        insert_bidirectional_road(G, safest_path_1->path_vertices[i], safest_path_1->path_vertices[i + 1], deleted_road.length, deleted_road.danger_value);
    }


    // to find the 3rd safest path, remove two edges and run dijkstra
    // one edge from 1st safest path and another from 2nd safest path
    // if there are n vertices in 1st safest path and m vertices in 2nd safest path, then dijkstra will be run (n - 1)(m - 1) times (in worst case) to find the 3rd safest path

    path_info* safest_path_3;
    safest_path_3->danger_value = INFINITY;

    ll m = safest_path_2->no_of_vertices_in_the_path;
    for (ll i = 0; i < n - 1; i++) {
        Set deleted_road_1 = remove_bidirectional_road(G, safest_path_1->path_vertices[i], safest_path_1->path_vertices[i + 1]);
        
        if (isConnected(G) == 1) {   
            for (ll j = 0; j < m - 1; j++) {
                Set deleted_road_2 = remove_bidirectional_road(G, safest_path_2->path_vertices[j], safest_path_2->path_vertices[j + 1]);
                
                if (isConnected(G) == 1) {
                    temp = dijkstra(G, source, destination);

                    if (temp->danger_value < safest_path_3->danger_value) {
                        safest_path_3 = temp;
                    }
                }
                
                // remove_bidirectional_road will give UNKNOWN danger value and length if the road to be deleted does't exist
                // (this happens if the edge has been deleted when we're removing the first road)
                // don't add the edge back if this has happend, because no road have been deleted
                if (deleted_road_2.danger_value != UNKNOWN && deleted_road_2.length != UNKNOWN) {
                    insert_bidirectional_road(G, safest_path_2->path_vertices[j], safest_path_2->path_vertices[j + 1], deleted_road_2.length, deleted_road_2.danger_value);
                }
            }
        }

        insert_bidirectional_road(G, safest_path_1->path_vertices[i], safest_path_1->path_vertices[i + 1], deleted_road_1.length, deleted_road_1.length);
    }
    

    // now we have the 3 safest paths
    // we sort it based on length (only if some of them have same danger values)

    for (int i = 0; i < 2; i++) {
        if (safest_path_1->danger_value == safest_path_2->danger_value) {
            if (safest_path_2->length < safest_path_1->length) {
                temp = safest_path_2;
                safest_path_2 = safest_path_1;
                safest_path_1 = temp;
            }
        }
        if (safest_path_2->danger_value == safest_path_3->danger_value) {
            if (safest_path_3->length < safest_path_2->length) {
                temp = safest_path_3;
                safest_path_3 = safest_path_2;
                safest_path_2 = temp;
            }
        }
    }

    // print the top 3 safest and shortest paths

    printf("Best path: ");
    for (ll i = 0; i < safest_path_1->no_of_vertices_in_the_path; i++) {
        printf("%lld ", safest_path_1->path_vertices[i]);
    }
    printf("\nLength: %lld\n", safest_path_1->length);
    printf("Danger value: %lld\n", safest_path_1->danger_value);


    printf("2nd best path: ");
    for (ll i = 0; i < safest_path_2->no_of_vertices_in_the_path; i++) {
        printf("%lld ", safest_path_2->path_vertices[i]);
    }
    printf("\nLength: %lld\n", safest_path_2->length);
    printf("Danger value: %lld\n", safest_path_2->danger_value);


    printf("3rd best path: ");
    for (ll i = 0; i < safest_path_3->no_of_vertices_in_the_path; i++) {
        printf("%lld ", safest_path_3->path_vertices[i]);
    }
    printf("\nLength: %lld\n", safest_path_3->length);
    printf("Danger value: %lld\n", safest_path_3->danger_value);


    // free the dynamically allocated memory
    free(safest_path_1->path_vertices);
    free(safest_path_1);
    free(safest_path_2->path_vertices);
    free(safest_path_2);
    free(safest_path_3->path_vertices);
    free(safest_path_3);

    return;
}



path_info* dijkstra (Graph* G, ll source, ll destination) {
    ll n = G->no_of_stations;

    ll previous_vertex[n];
    int isKnown[n];
    ll distance_to_source[n];

    for (ll i = 0; i < n; i++) {
        previous_vertex[i] = UNKNOWN;
        isKnown[i] = 0;
        distance_to_source[i] = INFINITY;
    }
    distance_to_source[source] = 0;

    PQueue* Q = CreateEmptyPriorityQueue();
    for (ll i = 0; i < n; i++) {
        Priority_Enqueue(Q, (Element) i, (Key) distance_to_source[i]);
    }

    while (!IsPQueueEmpty(Q)) {
        ll u = ExtractMin(Q);
        isKnown[u] = 1;

        Node* temp = G->arr_of_stations[u].ptr_to_ll_of_neighbours;
        while (temp != NULL) {
            ll v = temp->station_no;
            if (isKnown[v] == 0 && distance_to_source[u] != INFINITY) {
                if (distance_to_source[u] + temp->danger_value < distance_to_source[v]) {
                    distance_to_source[v] = distance_to_source[u] + temp->danger_value;
                    previous_vertex[v] = u;
                    DecreaseKey(Q, v, distance_to_source[v]);
                }
            }
            temp = temp->next;
        }
    }

    path_info* path = (path_info*) malloc (sizeof(path_info));
    assert(path != NULL);
    path->path_vertices = (ll*) malloc (n * sizeof(ll));
    assert(path->path_vertices != NULL);

    ll index = 0;
    // get the path using the previous_vertex array 
    GetPath(previous_vertex, destination, path, &index);

    path->length = distance_to_source[destination];

    // find the danger value of the path
    path->danger_value = 0;
    for (ll i = 0; i < path->no_of_vertices_in_the_path; i++) {
        Node* p = G->arr_of_stations[source].ptr_to_ll_of_neighbours;
        while (p != NULL) {
            if (p->station_no == destination) {
                (path->danger_value) += (p->danger_value);
            }
            p = p->next;
        }
    }

    return path;
}

void GetPath (ll* previous_vertex, ll destination, path_info* path, ll* index) {
    if (previous_vertex[destination] != UNKNOWN) {
        GetPath(previous_vertex, previous_vertex[destination], path, *index);
    }

    path->path_vertices[(*index)++] = destination;
    path->no_of_vertices_in_the_path++;
    return;
}


// returns 1 if the graph is connected, else 0. (undirected graph)
int isConnected(Graph* G) {
    for (ll i = 0; i < G->no_of_stations; i++) {
        if (G->arr_of_stations[i].ptr_to_ll_of_neighbours == NULL) {
            return 0;
        }
    }

    return 1;
}
