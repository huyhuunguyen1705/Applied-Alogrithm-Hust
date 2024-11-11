/*
Description
Given undirected graph G = (V,E) in which V = {1, 2, ..., n} is the set of nodes, and E is the set of m edges.
Write a program that computes the sequence of nodes visited using a BFS algorithm (the nodes are considered in a lexicographic order)

Input
Line 1: contains 2 integers n and m which are the number of nodes and the number of edges
Line i+1 (i = 1, ..., m): contains 2 positive integers u and v which are the end points of the ith edge

Output
Write the sequence of nodes visited by a BFS procedure (nodes a are separated by a SPACE character)
Example

Input
6 7
2 4
1 3
3 4
5 6
1 2
3 5
2 3

Output
1 2 3 4 5 6
*/

#include<bits/stdc++.h>
using namespace std;

int n, m;

void bfs(vector< priority_queue <int, vector<int>, greater<int>> > adj) {
    queue<int> Q;
    vector<bool> visited(adj.size());
    for(int i=1; i<=n; i++){ // có dòng for này xử lí th có nhiều tp liên thông
        if(!visited[i]) Q.push(i);
        while (!Q.empty()) {
            int u=Q.front();
            if (!visited[u]){
                visited[u] = true;
                std::cout<< u << " ";
            }
            if (!adj[u].empty()){
                int v=adj[u].top(); adj[u].pop();
                if(!visited[v]){
                    Q.push(v);
                }
            }else Q.pop();
        }
    }
}

int main(){
    cin>>n>>m;
    vector<priority_queue <int, vector<int>, greater<int>> > adj;
    adj.resize(n + 1);
    for(int i=0; i<m; i++){
        int u,v;
        cin>>u>>v;
        adj[u].push(v);
        adj[v].push(u);
    }
    bfs(adj);
}