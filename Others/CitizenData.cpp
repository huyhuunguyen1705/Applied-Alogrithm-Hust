/*
Description
CITIZEN
Given a DataBase about citizen, perform queries over this DataBase.
Input
The input consists of two blocks: the first block is the DataBase and the second block is the list of queries. Two blocks are separated by a line containing a character *.
1. The first block (DataBase about citizen) consists of lines (number of lines can be upto 100000), each line is the information about a person and is under the format:
                                   <code>  <dat_of_birth>  <fathher_code>   <mother_code>  <is_alive>  <region_code>
in which:
 <code>: the code of the person which is a string of length 7
 <date_of_birth>: the date of birth of the person and has the format YYYY-MM-DD (for example 1980-02-23), <date_of_birth> is before 3000-12-31
 <father_code> and <mother_code> is the code of father and mother: they are also strings of length 7. If the code is 0000000, then the current person does not has information about his father or mother
 <is_alive>: a character with two values: ‘Y’ means that the person is still alive, and ‘N’ means tat the current person is died.
 <region_code>: the code of the region where the person lives

2. The second block is the list of queries (number of queries can be upto 100000) over the DataBase which consists of following commands:
 NUMBER_PEOPLE: return the number of people (number of lines of the DataBase)
 NUMBER_PEOPLE_BORN_AT <date>: return the number of people having date-of-birth is equal to <date>
 MOST_ALIVE_ANCESTOR <code>: find the most ancestor (farthest in term of generation distance) of the given person <code>. Return the generation distance between the ancestor found and the given person
 NUMBER_PEOPLE_BORN_BETWEEN <from_date> <to_date>: compute the number of people having date-of-birth between <from_date> and <to_date> (<from_date> and <to_date> are under the form YYYY-MM-DD, <to_date> is before 3000-12-31)
 MAX_UNRELATED_PEOPLE: find a subset of people in which two any people of the subset do not have father/mother-children and the size of the subset is maximal. Return the size of the subset found.
The second block is terminated by a line containing ***.
Output
 Each line presents the result of the corresponding query (described above).
Example
Input
0000001 1920-08-10 0000000 0000000 Y 00002
0000002 1920-11-03 0000000 0000000 Y 00003
0000003 1948-02-13 0000001 0000002 Y 00005
0000004 1946-01-16 0000001 0000002 Y 00005
0000005 1920-11-27 0000000 0000000 Y 00005
0000006 1920-02-29 0000000 0000000 Y 00004
0000007 1948-07-18 0000005 0000006 Y 00005
0000008 1948-07-18 0000005 0000006 Y 00002
0000009 1920-03-09 0000000 0000000 Y 00005
0000010 1920-10-16 0000000 0000000 Y 00005
*
NUMBER_PEOPLE
NUMBER_PEOPLE_BORN_AT 1919-12-10
NUMBER_PEOPLE_BORN_AT 1948-07-18
MAX_UNRELATED_PEOPLE
MOST_ALIVE_ANCESTOR 0000008
MOST_ALIVE_ANCESTOR 0000001
NUMBER_PEOPLE_BORN_BETWEEN 1900-12-19 1928-11-16
NUMBER_PEOPLE_BORN_BETWEEN 1944-08-13 1977-12-15
NUMBER_PEOPLE_BORN_BETWEEN 1987-01-24 1988-06-03
***
Output
10
0
2
6
1
0
6
4
0
*/

#include <bits/stdc++.h>

using namespace std;

struct Citizen {
    string code;
    string date_of_birth;
    string father_code;
    string mother_code;
    char is_alive;
    string region_code;
};

unordered_map<string, Citizen> citizenDB;  // Database of citizens by code
unordered_map<string, vector<string>> birthdateMap;  // Birthdate to list of citizens
unordered_map<string, int> ancestorCache;  // Cache for the most distant ancestor results
unordered_map<string, vector<string>> graph;  // Adjacency list for parent-child relationships

map<string, int> BirthAtTime;
map<string, int> cumulativeBirth;

// Helper function to parse a citizen line and add it to the database
void addCitizen(const string &line) {
    istringstream iss(line);
    Citizen citizen;
    iss >> citizen.code >> citizen.date_of_birth >> citizen.father_code
        >> citizen.mother_code >> citizen.is_alive >> citizen.region_code;
    
    citizenDB[citizen.code] = citizen;
    birthdateMap[citizen.date_of_birth].push_back(citizen.code);
    BirthAtTime[citizen.date_of_birth]++;
}

// Function to build the graph for parent-child relationships
void buildGraph() {
    for (const auto &[code, citizen] : citizenDB) {
        if (citizen.father_code != "0000000") {
            graph[citizen.code].push_back(citizen.father_code);
            graph[citizen.father_code].push_back(citizen.code);
        }
        if (citizen.mother_code != "0000000") {
            graph[citizen.code].push_back(citizen.mother_code);
            graph[citizen.mother_code].push_back(citizen.code);
        }
    }
}

// Function to handle NUMBER_PEOPLE query
int numberPeople() {
    return citizenDB.size();
}

// Function to handle NUMBER_PEOPLE_BORN_AT <date> query
int numberPeopleBornAt(const string &date) {
    return birthdateMap[date].size();
}

// Recursive function to find the most distant ancestor
int findMostAliveAncestor(const string &code) {
    if (ancestorCache.find(code) != ancestorCache.end()) return ancestorCache[code];

    Citizen &person = citizenDB[code];
    if (person.father_code == "0000000" && person.mother_code == "0000000") {
        ancestorCache[code] = 0;
        return 0;
    }

    int fatherDist = (person.father_code != "0000000" && citizenDB.find(person.father_code) != citizenDB.end())
                     ? 1 + findMostAliveAncestor(person.father_code) : 0;
    int motherDist = (person.mother_code != "0000000" && citizenDB.find(person.mother_code) != citizenDB.end())
                     ? 1 + findMostAliveAncestor(person.mother_code) : 0;

    ancestorCache[code] = max(fatherDist, motherDist);
    return ancestorCache[code];
}

// Greedy algorithm to find a large independent set
int maxUnrelatedPeople() {
    unordered_set<string> included;  // Track included nodes
    unordered_set<string> visited;   // Track visited nodes

    for (const auto &[code, _] : citizenDB) {
        if (visited.find(code) == visited.end()) {  // If not visited
            // Include this person and mark their neighbors as visited
            included.insert(code);
            visited.insert(code);
            for (const string &neighbor : graph[code]) {
                visited.insert(neighbor);
            }
        }
    }
    return included.size();
}

int main() {
    string line;
    
    // Read citizens data until '*' separator
    while (getline(cin, line) && line != "*") {
        addCitizen(line);
    }

    // Build the graph after reading all citizens
    buildGraph();

    int runningTotal = 0;
    for(const auto& entry : BirthAtTime){
        runningTotal += entry.second;
        cumulativeBirth[entry.first] = runningTotal;
    }

    // Process queries
    while (getline(cin, line) && line != "***") {
        istringstream iss(line);
        string query;
        iss >> query;
        
        if (query == "NUMBER_PEOPLE") {
            cout << numberPeople() << endl;
        }
        else if (query == "NUMBER_PEOPLE_BORN_AT") {
            string date;
            iss >> date;
            cout << numberPeopleBornAt(date) << endl;
        }
        else if (query == "MOST_ALIVE_ANCESTOR") {
            string code;
            iss >> code;
            cout << findMostAliveAncestor(code) << endl;
        }
        else if (query == "NUMBER_PEOPLE_BORN_BETWEEN") {
            string fromTime, toTime;
            iss >> fromTime >> toTime;
            int res = 0;

            // Find cumulative submission up to and including `toTime`
            auto toIt = cumulativeBirth.upper_bound(toTime);
            if (toIt != cumulativeBirth.begin()) {
                --toIt; // Move to toTime
                res += toIt->second;
            }

            // Subtract cumulative submission just before `fromTime`, if applicable
            auto fromIt = cumulativeBirth.lower_bound(fromTime);
            if (fromIt != cumulativeBirth.begin()) {
                --fromIt; // Move to the largest time < fromTime
                res -= fromIt->second;
            }
            
            cout << res << endl;
        }
        else if (query == "MAX_UNRELATED_PEOPLE") {
            cout << maxUnrelatedPeople() << endl;
        }
    }

    return 0;
}