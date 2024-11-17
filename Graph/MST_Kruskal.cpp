/*
Description
Given a undirected connected graph G=(V,E) where V={1,…,N}. Each edge (u,v)∈E(u,v)∈E has weight w(u,v)w(u,v). Compute minimum spanning tree of G.
Input
Line 1: N and M (1≤N,M≤10
5
) in which NN is the number of nodes and MM is the number of edges.
Line i+1 (i=1,…,M): contains 3 positive integers u, v, and w where w is the weight of edge (u,v)
Output
Write the weight of the minimum spanning tree found.
Example
Input
5 8
1 2 1
1 3 4
1 5 1
2 4 2
2 5 1
3 4 3
3 5 3
4 5 2
Output
7
*/

#include <bits/stdc++.h>
using namespace std;

#define e pair<int, pair<int, int>>
#define w first
#define v1 second.first
#define v2 second.second

const int maxnm = 100001;
int n, m;
vector<e> edges(0);
int parent[maxnm], sz[maxnm];
int res = 0;

void make_set(int v){
    parent[v] = v;
    sz[v] = 1;
}

int find_set(int v) {
    if(parent[v]==v) return v;
    else return find_set(parent[v]);
}

void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);

    if (a != b) {
        if (sz[a] > sz[b]) swap(a, b);
        sz[b] += sz[a];
        parent[a] = b;
    }
}

int main() {
    cin >> n >> m;
    for(int i=1; i<=n; ++i) make_set(i);
    for (int i = 0; i < m; ++i) {
        int tmp1, tmp2, w;
        cin >> tmp1 >> tmp2 >> w;
        edges.push_back({w, {tmp1, tmp2}});
    }
    sort(edges.begin(), edges.end());

    for (int i = 0; i < m; ++i) {
        e edge = edges[i];
        if (find_set(edge.v1) == find_set(edge.v2))
            continue;
        else {
            res += edge.w;
            union_set(edge.v1, edge.v2);
        }
    }
    cout << res;
}
