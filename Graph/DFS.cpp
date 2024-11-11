/*
Description
Given a undirected graph =(V,E) in which V = {1,2,..,n} is the set of nodes. Write a program that visit nodes of G by a DFS (consider a lexicorgraphic order of nodes).
Input
Line 1: contains 2 integers n and m (1 <= n,m <= 100000)
Line i+1: contains u and v which are two end-points of the ith edge

Output
Sequence of nodes visited by DFS
Example
Input
7 12
1 2
1 3
2 3
2 4
2 7
3 5 
3 7
4 5
4 6
4 7
5 6
5 7 
Output
1 2 3 5 4 6 7
*/

#include<bits/stdc++.h>
using namespace std;

void dfs(std::vector< std::list<int> > adj) {
    std::stack<int> S;
    std::vector<bool> visited(adj.size());
    S.push(1); // Bắt đầu từ đỉnh số 1
    while (!S.empty()) {
        int u=S.top();
        if (!visited[u]){
            visited[u] = true;
            std::cout<< u << std::endl;
        }
        if (!adj[u].empty()){
            int v=adj[u].front(); adj[u].pop_front();
            if(!visited[v]){
                S.push(v);
            }
        }else { S.pop();}
    }
}

int main(){
    int n, m;
    cin>>n>>m;
    vector< list<int> > adj;
    adj.resize(n + 1);
    int u,v;
    for(int i=0; i<m; i++){
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(adj);
}
