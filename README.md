# Covid Tracing
**Team 33**

>## Assumptions:


1. Covid Positive people in the list L started making contacts on day, D - X.

2. We are required to find all contacts and other queries on the X days before day D and find the 3 safest and shortest paths at the start of day D.

3. Since all queries are BEFORE day D, we need not use the information that list L is quarantined from Day D.

4. If a station contains at least one positive person at a given time, then all of the people in that station will be marked as primary contacts in the future unless they test positive.

5. If a station contains at least one primary contact at a given time then all the people in that station will be marked as secondary contacts until and unless someone tests positive in which case they will be marked as the primary contacts as stated before. 

6. All queries on a particular day are made after all movements on said day. This is to ensure Uniformity of input.

7. The list of all Primary and Secondary Contacts in a Day are printed at the end of the Day 

>## Instructions for input format:

### Standard Input:

1. The first line contains 3 space-separated integers **N, M, K** representing the number of stations, the number of bidirectional roads and the total number of people respectively.

2. Followed by M lines of 3 space-separated integers  **U, V, W**. that indicate there is a bidirectional road between the station number U and V of weight W.  

3. Followed by K lines containing the initial station id of each person.

4. The next 3 lines contain **L, D, X** i.e. the number of positive people on day D, and X is the number of days requested to trace back.

5. L lines after that take in the input for ID's of the L positive people. 

### Input Per Day (For X Days):

1. The input **“num”** representing the number of movements that day, followed by **“num”** queries of 3 space-separated integers **“personID”**, **"U"** and **"V"** to indicate that the person of the given id has traveled from U to V in that day.

2. The input **“numq”** asks the number of queries the user wants to input which is naturally followed by a string input **“query”** asking for the type of query required.  

3. Query types: 
    *   **status**  : User inputs integer **personID**. Program Outputs status of said person.
    *   **location**: User inputs integer **personID**. Program Outputs location of said person.
    *   **list**    : User inputs integer **station_num**. Program Outputs list of all people at the station along with their status.

### Final Input:

1. User inputs 2 space-separated integers  **U, V** and program outputs top 3 safest and shortest paths between **U** and **V**.
