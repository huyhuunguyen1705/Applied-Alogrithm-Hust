/*
Cho cây T trong đó V={1,2,...,n} là tập đỉnh và E là tập cạnh. TÍnh số Q cách phân hoạch tập cạnh E thành 2 tập con E1, E2:
- Các cạnh thuộc E1 lập thành một cây con của T
- Các cạnh thuộc E2 cũng lập thành một cây con của T
Input:
- Dòng đầu tiên chứa số nguyên dương n (2≤n≤1000)
- n-1 dòng tiếp theo, mỗi dòng chứa 2 số nguyên dương u, v (1≤u,v≤n) là 2 đầu mút của cạnh thứ i trong tập cạnh E
Output:
- In ra số Q cần tìm mod 10000
Example:
Input:
5
2 4
4 5
2 1
5 3
Output:
3
*/

// Wrong
#include <bits/stdc++.h>

using namespace std;

const int MOD = 10000;
int n;
vector<pair<int, int>> edges;

// Union-Find structure
vector<int> parent;

void initUnionFind(int size) {
    parent.resize(size + 1);
    for (int i = 1; i <= size; ++i) {
        parent[i] = i;
    }
}

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);  // Path compression
    }
    return parent[u];
}

bool unionSets(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU == rootV) return false;  // Cycle detected
    parent[rootV] = rootU;
    return true;
}

bool isValidTree(const set<int>& edgeIndices) {
    if (edgeIndices.size() != n - 1) return false;

    initUnionFind(n);
    for (int index : edgeIndices) {
        int u = edges[index].first;
        int v = edges[index].second;
        if (!unionSets(u, v)) return false;  // Cycle detected
    }

    // Check connectivity
    int root = find(1);
    for (int i = 2; i <= n; ++i) {
        if (find(i) != root) return false;  // Not connected
    }
    return true;
}

int main() {
    cin >> n;
    edges.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    int totalWays = 0;
    int totalSubsets = (1 << (n - 1));  // 2^(n-1) subsets

    for (int mask = 1; mask < totalSubsets - 1; ++mask) {  // Exclude empty and full set
        set<int> E1, E2;
        for (int i = 0; i < n - 1; ++i) {
            if (mask & (1 << i)) {
                E1.insert(i);
            } else {
                E2.insert(i);
            }
        }

        if (isValidTree(E1) && isValidTree(E2)) {
            totalWays = (totalWays + 1) % MOD;
        }
    }

    cout << totalWays << endl;
    return 0;
}
