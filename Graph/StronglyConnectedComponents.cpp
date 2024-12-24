/*
Given a directed graph G=(V,E) where V={1,. . ., N} is the number of nodes and the set E has M arcs. Compute number of strongly connected components of G
Input
Line 1: two positive integers N and M (1 <= N <= 10^5, 1 <= M <= 10^6)
Line i+1 (i=1,. . ., M\): contains two positive integers u and v which are endpoints of ith arc
Output
Write the number of strongly connected components of G
Example
Input
8 13
1 2
1 8
2 3
2 6
3 6
4 3
4 6
5 4
6 5
7 1
7 2
7 6
8 7
Output
3
*/

#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 5;
const int maxM = 1e6 + 5;

int n,m;
int timeDfs = 0, scc_count = 0;
int num[maxN], low[maxN];
bool inStack[maxN]; // Used to check if a node is currently in the stack
vector<int> adj[maxN];
stack<int> st;

void dfs(int u){
    num[u] = low[u] = ++ timeDfs;
    inStack[u] = true;
    st.push(u);
    for(int v:adj[u]){
        if(!num[v]){
            // if v is not visited yet, run dfs on it
            dfs(v);
            low[u] = min(low[u], low[v]);
        }else if(inStack[v]){
            // If v is visited and is in the stack, it means that v is an ancestor of u
            low[u] = min(low[u], num[v]);
        }
    }
    // If u is the root of a SCC, pop all elements in the stack until u is popped
    if(num[u] == low[u]){
        scc_count ++;
        while(st.top() != u){
            inStack[st.top()] = false;
            st.pop();
        }
        inStack[u] = false;
        st.pop();
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    // run the graph
    for(int i=1; i<=m; i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    // Run DFS for each unvisited node
    for(int i=1; i<=n; i++){
        if(!num[i]) dfs(i);
    }
    cout<< scc_count <<endl;
    return 0;
}