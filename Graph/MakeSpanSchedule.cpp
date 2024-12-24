/*
A project has n tasks 1,. . ., n. Task i has duration d(i) to be completed (i=1,. . ., n). There are precedence constraints between tasks represented by a set Q of pairs: for each (i,j)  in Q, task j cannot be started before the completion of task i. Compute the earliest completion time  of the project.
Input
Line 1: contains n and m (1 <= n <= 10^4, 1 <= m <= 200000)
Line 2: contains d(1),. . ., d(n) (1 <= d(i) <= 1000)
Line i+3 (i=1,. . ., m) : contains i and j : task j cannot be started to execute before the completion of task i
Output
Write the earliest completion time of the project.
Example
Input
9 13
5 3 1 2 6 4 3 1 4
1 3
1 5
1 6
2 1
2 3
3 5
4 1
4 2
4 6
5 8
7 9
9 5
9 8

Output
18
*/

#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e4 + 5;
const int maxM = 2e5 + 5;

int n,m;
int res[maxN]; 
int d[maxN]; // the duration of task i
vector<vector<int>> edges(maxN, vector<int>(0)); // the graph


void dfs(int u){
    if(!res[u]){
        for(int v:edges[u]){
            dfs(v);
            res[u] = max(res[u], res[v]);
        }
        res[u] += d[u];
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for(int i=1; i<=n; i++) cin>>d[i];

    int u,v;
    for(int i=1; i<=m; i++){
        cin>>u>>v;
        edges[u].push_back(v);
    }

    for(int i=1; i<=n;i++){
        if(!res[i]) dfs(i);
    }

    int globalRes =0;
    for(int i=1; i<=n; i++){
        globalRes = max(globalRes, res[i]);
    }
    cout<<globalRes;
    return 0;
}