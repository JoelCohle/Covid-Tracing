#include "covid.h"

void MovePerson(int personID, Station* station1, Station* station2, Person* *person_list)
{
    separateHash(station1, personID, person_list[personID-1]->type, '-');
    separateHash(station2, personID, person_list[personID-1]->type, '+');
    update_status(station2, personID, person_list);
}