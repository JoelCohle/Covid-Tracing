# Covid Tracing
**Team 33**

>## Assumptions:


1. People who are not quarantined can move across any number of stations on a given day.

2. If a station contains at least one positive person at a given time, then all of the people in that station will be marked as primary contacts in the future unless they test positive.

3. If a station contains at least one primary contact at a given time then all the people in that station will be marked as secondary contacts until and unless someone tests positive in which case they will be marked as the primary contacts as stated before.

4. The people who test positive will not move between stations.  


>## Instructions for input format:


1. The first line contains 3 space-separated integers **N, M, K** representing the number of stations, the number of bidirectional roads and the total number of people respectively.

2. Followed by M lines of 3 space-separated integers  **U, V, W**. that indicate there is a bidirectional road between the station number U and V of weight W.  

3. Followed by K lines containing the initial station id of each person.

4. The next 3 lines contain **L, D, X** i.e. the number of positive people on day D, and X is the number of days requested to trace back.

5. L lines after that take in the input for ids of the L positive people. 

6. For each of the X days, the code takes the input **“num”** represents the number of movements that day, followed by **“num”** queries of **“personid”** and then again U and V to indicate that the person of the given id has traveled from U to V in that day.

7. The input **“numq”** asks the number of queries the user wants to input which is naturally followed by a string input **“query”** asking for the type of query required.  

8. If the query asks for **“status”** or **“location”** of a person then it is followed by the required person’s id as the input in the next line. And if **“list”** is requested then the user has to specify which station number is the list required for in the next line. 
