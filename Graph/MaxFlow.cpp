/*
Given a network G = (V, E) which is a directed weighted graph. Node s is the source and node t is the target. c(u,v) is the capacity of the arc (u,v). Find the maximum flow on G.
Input
•Line 1: two positive integers N and M (1 <= N <= 10^4, 1 <= M <= 10^6)
•Line 2: contains 2 positive integers s and t
•Line i+2 (I = 1,. . ., M): contains two positive integers u and v which are endpoints of ith arc and the maximun capacity of the arc
Output
Write the value of the max-flow found
Example
Input
7 12
6 7
1 7 7
2 3 6
2 5 6
3 1 6
3 7 11
4 1 7
4 2 4
4 5 5
5 1 4
5 3 4
6 2 8
6 4 10
Output
17  
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX  = 1e3 + 5;

int f[MAX][MAX], c[MAX][MAX];
int n, m, source, sink, tmp1,tmp2; 
bool visited[MAX];
int  trace[MAX];

void bfs(int source, int sink){
    memset(visited, 0, sizeof(visited)); // vì các đường đi có thể trùng node, nên phải reset visited
    memset(trace, 0, sizeof(trace));
    queue<int> q;
    q.push(source);
    visited[source] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v=1; v<=n; v++){
            if(!visited[v] && f[u][v] < c[u][v]){ // Không thăm lại các node đã thăm hoặc các đường đã đầy
                q.push(v);
                visited[v] = true;
                trace[v] = u;
            }
            if(visited[sink]) return;
        }
    }
}

bool existAugPath(int source, int sink){
    bfs(source, sink);
    return visited[sink]; // if there is a path from s to t
}

void increaseFlow(int source, int sink){
    int minCapacity = INT_MAX;
    int v = sink;
    int prev = -1;
    while(v!=source){
        // find minCapacity
        prev = trace[v];
        minCapacity = min(minCapacity, c[prev][v] - f[prev][v]);
        v = prev;
    }
    v = sink;
    while(v!= source){
        prev = trace[v];
        f[prev][v] += minCapacity;
        f[v][prev] -= minCapacity;
        v = prev;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>source>>sink;
    int tmp1, tmp2;
    memset(f, 0, sizeof(f));
    for(int i=0; i<m; i++){
        cin>>tmp1>>tmp2;
        cin>>c[tmp1][tmp2];
    }
    while(existAugPath(source, sink)){ // Quá trình này dừng khi không còn đường tăng luồng nữa
        increaseFlow(source, sink);
    }
    int res = 0;
    for(int i=1; i<=n ;i++){
        res += f[source][i];
    }
    cout<< res;
}