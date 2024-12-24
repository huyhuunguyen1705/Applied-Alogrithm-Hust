/*
Given a undirected graph G=(V,E) where V={1,. . .,N} is the number of nodes and the set E has M edges.
Compute the number of connected components of G.
Input
Line 1: two positive integers N and M (1 <= N <= 10^5, 1 <= M <= 10^5)
Line i+1 (i=1, . . .,M): contains two positive integers u and v which are endpoints of ith edge
Output
Write the number of connected components of G.
Example
Input
8 8
1 2
1 7
1 8
2 7
4 5
4 6
5 6
7 8

Output
3
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;

int n,m;
vector<vector<int>> edges(MAX, vector<int>(0));
int component[MAX];
int num_component = 0;

void dfs(int vertex){
    if(component[vertex]) return;
    component[vertex] = num_component;
    for(int i:edges[vertex]){
        dfs(i);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for(int i=1;i<=n;i++) component[i]=0;
    for(int i=1;i<=n;i++){
        if(!component[i]){
            ++num_component;
            dfs(i);
        }
    }
    cout<<num_component<<'\n';
}
