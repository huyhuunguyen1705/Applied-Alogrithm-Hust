/*
Description
The data about bank transactions consists of a sequence of transactions: the information of each transaction has the following format:
                                                                    <from_account>   <to_account>   <money>   <time_point>   <atm>
In which:
•	<from_account>: the account from which money is transferred (which is a string of length from 6 to 20 )
•	<to_account>: the account which receives money in the transaction (which is a string of length from 6 to 20)
•	<money>: amount of money transferred in the transaction (which is an integer from 1 to 10000)
•	<time_point>: the time point at which the transaction is performed, it is a string under the format HH:MM:SS  (hour: minute: second)
•	<atm>: the code of the ATM where the transaction is taken (a string of length from 3 to 10)
Example: T00112233445 T001234002 2000 08:36:25 BIDV (at the ATM BIDV, account T00112233445 transfers 2000$ to account T001234002 at time point 08:36:25 (08 hour, 36 minutes, 25 seconds) 
A transaction cycle of length k starting from account a1 is defined to be a sequence of distinct account a1, a2, …, ak  in which there are transactions from account a1 to a2, from a2 to a3, …, from ak to a1.
Write a program that process the following queries: 
?number_transactions: compute the total number of transactions of the data
?total_money_transaction: compute the total amount of money of transactions  
?list_sorted_accounts: compute the sequence of bank accounts (including sending and receiving accounts) appearing in the transaction (sorted in an increasing (alphabetical) order)  
?total_money_transaction_from <account>: compute the total amount of money transferred from the account <account>  
?inspect_cycle <account> k : return 1 if there is a transaction cycle of length k, starting from <account>, and return 0, otherwise
Input (stdin)
The input consists of 2 blocks of information: the data block and the query block
•	The data block consists of lines:
o	Each line contains the information about a transaction described above
o	The data is terminated by a line containing #
•	The query block consists of lines:
o	Each line is a query described above
o	The query block is terminated by a line containing #

Output (stdout)
•	Print to stdout (in each line) the result of each query described above

Example
Input
T000010010 T000010020 1000 10:20:30 ATM1
T000010010 T000010030 2000 10:02:30 ATM2
T000010010 T000010040 1500 09:23:30 ATM1
T000010020 T000010030 3000 08:20:31 ATM1
T000010030 T000010010 4000 12:40:00 ATM2
T000010040 T000010010 2000 10:30:00 ATM1
T000010020 T000010040 3000 08:20:31 ATM1
T000010040 T000010030 2000 11:30:00 ATM1
T000010040 T000010030 1000 18:30:00 ATM1
#
?number_transactions
?total_money_transaction
?list_sorted_accounts
?total_money_transaction_from T000010010
?inspect_cycle T000010010 3
#
Output
9
19500
T000010010 T000010020 T000010030 T000010040
4500
1
*/

#include<bits/stdc++.h>

using namespace std;

// Transaction struct
struct Transaction {
    string from_account;
    string to_account;
    int money;
    string time_point;
    string atm;
};

// Global variables
vector<Transaction> transactions;
map<string, int> total_money_from_account;
map<string, vector<string>> adjacency_list;
set<string> accounts;

// Helper function to parse each transaction
Transaction parseTransaction(const string& line) {
    stringstream ss(line);
    Transaction txn;
    ss >> txn.from_account >> txn.to_account >> txn.money >> txn.time_point >> txn.atm;
    return txn;
}

// Build adjacency list for cycle detection
void buildAdjacencyList() {
    for (const auto& txn : transactions) {
        adjacency_list[txn.from_account].push_back(txn.to_account);
        accounts.insert(txn.from_account);
        accounts.insert(txn.to_account);
        total_money_from_account[txn.from_account] += txn.money;
    }
}

// DFS function to detect cycle of length k
bool dfs(const string& start, const string& current, int k, int depth, set<string>& visited) {
    if (depth == k) return current == start;
    visited.insert(current);
    
    for (const string& neighbor : adjacency_list[current]) {
        if (visited.find(neighbor) == visited.end() || (depth == k - 1 && neighbor == start)) {
            if (dfs(start, neighbor, k, depth + 1, visited)) {
                return true;
            }
        }
    }
    
    visited.erase(current);
    return false;
}

// Function to process queries
void processQueries(const vector<string>& queries) {
    for (const auto& query : queries) {
        if (query == "?number_transactions") {
            cout << transactions.size() << endl;
        } 
        else if (query == "?total_money_transaction") {
            int total_money = 0;
            for (const auto& txn : transactions) {
                total_money += txn.money;
            }
            cout << total_money << endl;
        } 
        else if (query == "?list_sorted_accounts") {
            for (const auto& account : accounts) {
                cout << account << " ";
            }
            cout << endl;
        } 
        else if (query.rfind("?total_money_transaction_from", 0) == 0) {
            string account = query.substr(30);
            cout << total_money_from_account[account] << endl;
        } 
        else if (query.rfind("?inspect_cycle", 0) == 0) {
            stringstream ss(query);
            string command, account;
            int k;
            ss >> command >> account >> k;
            set<string> visited;
            cout << (dfs(account, account, k, 0, visited) ? 1 : 0) << endl;
        }
    }
}

int main() {
    string line;
    // Read transactions data
    while (getline(cin, line) && line != "#") {
        transactions.push_back(parseTransaction(line));
    }
    buildAdjacencyList();

    // Read queries
    vector<string> queries;
    while (getline(cin, line) && line != "#") {
        queries.push_back(line);
    }
    
    // Process each query
    processQueries(queries);

    return 0;
}