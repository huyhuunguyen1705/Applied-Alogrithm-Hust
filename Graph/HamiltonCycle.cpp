/*
Given an undirected graph G = (V,E). Write a program to check if G is a Hamiltonian graph.
Input
Line 1: a positive integer T (number of graphs)
Subsequent lines are information about T graphs, each has the following format:
Line 1: n and m (number of nodes and edges)
Line i+1 (i = 1, 2, ..., m): u and v : two end points of the ith edge
Output
In the ith line, write 1 if the corresponding is a Hamiltonian graph, and write 0, otherwise
Example
Input
2
5 5
1 2
1 3
2 4
2 5
3 5
7 13
1 3
1 5
1 7
2 4
2 5
2 6
3 4
3 5 
3 7
4 6
4 7
5 7
6 7

Output
0
1
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5 + 5;
int n,m,visited[MAX], ans=0;
vector<int> edges[MAX];

void dfs(int i, int k){
    if(k==n){
        for(int j:edges[i]){
            if(j==1){
                ans=1;
                break;
            }
        }
        return;
    }
    for(int j:edges[i]){
        if(!visited[j]){
            visited[j]=1;
            dfs(j,k+1);
            visited[j]=0;
        }
    }
}

void solve(){
    cin>>n>>m;
    for (int i=1;i<=n;i++) edges[i].clear();
    for(int i=1;i<=m;i++){
        int x,y; cin>>x>>y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    visited[1]=true;
    dfs(1,1);
    cout<<ans<<'\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        solve();
    }
}
/* GPT
#include <bits/stdc++.h>
using namespace std;
//backtracking
const int maxn = 100;
int n, m;
vector<vector<int>> edges;
bool adj[maxn][maxn];
vector<bool> visited;

bool isSafe(int v, vector<int>& path, int pos) {
    if (!adj[path[pos - 1]][v]) return false;
    if (find(path.begin(), path.begin() + pos, v) != path.begin() + pos) return false;
    return true;
}

bool hamiltonianCycleUtil(vector<int>& path, int pos) {
    if (pos == n) {
        return adj[path[pos - 1]][path[0]];  
    }

    for (int v = 1; v <= n; ++v) {
        if (isSafe(v, path, pos)) {
            path[pos] = v;

            if (hamiltonianCycleUtil(path, pos + 1))
                return true;

            path[pos] = -1; 
        }
    }
    return false;
}

bool isHamiltonianCycle() {
    vector<int> path(n + 1, -1);
    path[0] = 1; 

    if (hamiltonianCycleUtil(path, 1))
        return true;

    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        edges.clear();
        memset(adj, 0, sizeof(adj));
        edges.resize(n + 1); 
        for (int i = 0; i < m; ++i) {
            int v1, v2;
            cin >> v1 >> v2;
            edges[v1].push_back(v2);
            edges[v2].push_back(v1);
            adj[v1][v2] = true;
            adj[v2][v1] = true;
        }
        cout << (isHamiltonianCycle() ? 1 : 0) << endl;
    }
}

*/