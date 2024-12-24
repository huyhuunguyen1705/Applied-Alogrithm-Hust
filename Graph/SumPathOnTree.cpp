/*
Given a tree T=(V,E) in which V={1,. . ., n} is the set of nodes. Each edge (u,v) of T has length w(u,v).
Denote f(v) the sum of length of paths from all other nodes to v. Write a program to compute max{f(1), .  . ., f(n)}.
Input
Line 1 contains a positive integer n (2 <= n <= 10^5)
Line i+1 (i=1, . . ., n): contains u, v and w in which w is the weight of the edge (u,v)
Output
Write the value max{f(1), . . , f(n}.
Example
Input
4
1 2 1
1 3 3
3 4 2
Output
13
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int> 

const int MAX = 1e5 + 5;
int n, d[MAX], subTreeSize[MAX],f[MAX];
vector<pii> adj[MAX];

// f(u) tổng độ dài đường đi từ các đỉnh khác đến u trên đồ thị
// p(u) đỉnh cha của u (là đỉnh mà từ đó thuật toán thăm u)
// d(u) tổng độ dài đường đi từ các đỉnh con cháu của u đến u
// subTreeSize[u] số lượng đỉnh con cháu của u (kể cả đỉnh uu)
// Ham dfs1 tinh d[u] va subTreeSize[u]
void  dfs1(int u, int p){
    subTreeSize[u] = 1;
    for(auto [v,w] : adj[u]){
        if(v==p) continue;
        dfs1(v,u);
        d[u] += d[v] +subTreeSize[v]*w;
        subTreeSize[u] += subTreeSize[v];
    }
}

// Ham dfs2 tinh f[v] tu f[u]
void dfs2(int u, int p){
    for(auto [v,w] : adj[u]){
        if(v==p) continue;
        int F = f[u] -(d[v] + subTreeSize[v]*w);
        f[v] = d[v] + F + (n-subTreeSize[v])*w;
        dfs2(v,u);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1; i<=n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    dfs1(1,0);
    f[1] = d[1];
    dfs2(1,0);
    int ans = INT_MIN;
    for(int i=1; i<=n; i++){
        ans = max(ans, f[i]);
    }
    cout<<ans<<'\n';
    return 0;
}


