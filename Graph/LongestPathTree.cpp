/*
Given a undirected tree G = (V, E) in which V = {1,…,N} is the set of nodes. Each edge (u,v) in E has weight w(u,v).
The length of a path is defined to be the sum of weights of edges of this path. Find the longest elementary path on G.
Input
Line 1: positive integer N (1 <= N <= 10^5)
Line i + 1 ($i = 1,…,N-1$): positive integers $u, v, w$ in which $w$ is the weight of edge $(u,v)$ (1 ≤ w ≤ 100)
Output
The weight of the longest path on the given tree
Example
Input
6 
1 3 3
1 6 2 
2 6 5 
4 5 2
4 6 1
Output
10
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first;
#define se second;

const int MAX = 1e5 + 5;
int n; 
vector<pii> adj[MAX];
int d[MAX];

void init() {
    for (int v = 1; v <= n; v++) {
        d[v] = -1;
    }
}

void dfs(int u){
    for(auto x: adj[u]){
        if(d[x.first]<0){ // Vì đây là cây nên mỗi đỉnh trừ nút gốc chỉ có thể được thăm bởi 1 đỉnh duy nhất
            d[x.first] = d[u] + x.second;
            dfs(x.first);
        }
    }
}

void solve(){
    init();

    int s=3;
    d[s] = 0;
    dfs(s);

    int x;
    int max_dist = INT_MIN;
    for(int i=1; i<=n; i++){
        if(d[i]>max_dist){
            max_dist = d[i];
            x = i;
        }
    }

    init();
    d[x] = 0;
    dfs(x);

    int y;
    max_dist = INT_MIN;
    for(int i=1; i<=n; i++){
        if(d[i]>max_dist){
            max_dist = d[i];
            y = i;
        }
    }

    cout<<max_dist<<'\n';
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for(int i=1; i<=n-1; i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    solve();
    return 0;
}