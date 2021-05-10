#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "covid.h"


void MovePerson(Graph* G, ll personID, Station* station1, Station* station2, PtrtoPerson *person_list)
{
    /*********************************/
    /* Deleting Person from station1 */
    /*********************************/
    separateHash(station1->PeopleList, personID, person_list[personID-1]->type, '-');
    // Updating danger value of station 1
    if (person_list[personID-1]->type == covid_positive)
        station1->danger_value--;
    if (person_list[personID-1]->type == primary_contact)
        station1->danger_value -= 1/5;
    if (person_list[personID-1]->type == secondary_contact)
        station1->danger_value -= 1/10;
    station1->no_of_people--;

    //**************************//
    //Adding person to station2 //
    //**************************//
    PtrtoPerson person = separateHash(station2->PeopleList, personID, person_list[personID-1]->type, '+');
    double danger_value = Update(station2, person, person_list);    // Updating status of all people in Station 2
    station2->no_of_people++;
    station2->danger_value = danger_value;
    

    update_danger_value_of_edge(G, station1, station2);
}

double Update(Station *S, PtrtoPerson P, PtrtoPerson *person_list)
{
    ll covid = 0, prim = 0, second = 0;

    // Iterating through the hashtable to update status of all people in it
    for (ll i = 0; i < S->PeopleList->TableSize; i++)
    {
        PtrtoPerson Current = S->PeopleList->pStart[i]->next; // first person at index i
        while (Current != NULL)
        {

            //******************************************************************//
            // If person being inserted is less infectious than current person, //
            // we update new person's status in the hashtable and break, since  //
            // everyone already has status >= new person's status               //
            //******************************************************************//
            if (Current->type < P->type){
                Key k = Identityhash(P->ID, S->PeopleList->TableSize);
                PtrtoPerson Position = S->PeopleList->pStart[k];
                while ((Position->next != NULL) && (Position->next->ID != P->ID)){
                    Position = Position->next;
                }
                if (Position->next->ID == P->ID){
                    Position->next->type = Current->type + 1;
                    person_list[P->ID-1]->type = Current->type + 1;
                }
                goto L1;
            }

            //*****************************************************************//
            // If current person is less infectious than new person, we update //
            // current person's status and continue                            //
            //*****************************************************************// 
            if (Current->type - P->type > 1){
                Current->type = P->type + 1;
                person_list[Current->ID - 1]->type = P->type + 1;
            }

            //******************************************************************//
            // If current person has the same status as the new person, everyone//
            // in the station remains unaffected so we break                    //
            //******************************************************************//
            if (Current->type == P->type && Current->ID != P->ID)
                goto L1;

            Current = Current->next;
        }
    }

    L1:

    // Finding the number of covid, primary and secondary people after updating everyone's status // 
    for (ll i = 0; i < S->PeopleList->TableSize; i++)
    {
        PtrtoPerson Current = S->PeopleList->pStart[i]->next;
        while (Current != NULL)
        {
            if (Current->type == 0)
                covid++;
            if (Current->type == 1)
                prim++;
            if (Current->type == 2)
                second++;
            Current = Current->next;
        }
    }
    
    // Calculating danger value of the station from number of positive, primary and secondary people //
    double danger_value = (double)covid + ((double)prim / 5) + ((double)second / 10);

    return danger_value;
}


void update_danger_value_of_edge(Graph* G, Station* s1, Station* s2) {
    Node* p = G->arr_of_stations[s1->station_no];
    while (p != NULL) {
        if (p->station_no == s2->station_no) {
            p->danger_value = (s1->danger_value) + (s2->danger_value);
            break;
        }
        p = p->next;
    }

    p = G->arr_of_stations[s2->station_no];
    while (p != NULL) {
        if (p->station_no == s1->station_no) {
            p->danger_value = (s1->danger_value) + (s2->danger_value);
            break;
        }
        p = p->next;
    }

    return;
}