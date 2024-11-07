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