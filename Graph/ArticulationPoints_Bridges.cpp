/*
Given an undirected graph containing N vertices and M edges, find all the articulation points and the bridges in the graph.
Input
The first line consists of two space-separated integers denoting N and M, 
M lines follow, each containing two space-separated integers X and Y denoting there is an edge between X and Y.
Output
One line consists of two integers denoting the number of articulation points and the number of bridges.
Example
Input
10 12
1 10
10 2
10 3
2 4
4 5
5 2
3 6
6 7
7 3
7 8
8 9
9 7
Output
4  3
*/
/* 
1. Articulation Point (Điểm khớp)
Một đỉnh v trong đồ thị vô hướng được gọi là điểm khớp nếu khi loại bỏ đỉnh v (cùng với các cạnh liên quan đến nó), số thành phần liên thông của đồ thị tăng lên.
Nói cách khác, v là một đỉnh mà nếu bị loại bỏ, đồ thị sẽ không còn liên thông (hoặc số thành phần liên thông tăng).
2. Bridge (Cầu)
Định nghĩa:
Một cạnh e=(u,v) trong đồ thị vô hướng được gọi là cầu nếu khi loại bỏ cạnh đó, số thành phần liên thông của đồ thị tăng lên. 
Nói cách khác, e là một cạnh mà nếu bị loại bỏ, đồ thị sẽ không còn liên thông như ban đầu.
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;
int n,m;
int timeDFS, num[MAX], low[MAX];
int child[MAX];
int num_articulation_points, num_bridges, articulation_points[MAX];

vector<int> adj[MAX];

void dfs(int u, int pre){
    // u là đỉnh hiện tại mà thuật toán DFS đang duyệt
    // pre là đỉnh cha của u. Dùng để tránh quay ngược lại đỉnh chả trong đồ thị không hướng
    // Số lượng con trực tiếp của đỉnh u trong cây DFS
    num[u] = low[u] = ++timeDFS;
    for(int v: adj[u]){
        if(v!=pre){ 
            if(!num[v]){
                child[u]++;
                dfs(v,u);
                low[u] = min(low[u],low[v]);
                // check bridges
                if(low[v] > num[u]) num_bridges++; 
                // check articulation points
                if(pre!=0 && low[v]>=num[u]){// Đỉnh u không phải gốc của cay DFS và low[v] > num[u] với v là con trực tiếp của u
                    articulation_points[u] = 1;
                }
            }else{
                low[u] = min(low[u],num[v]);
            }
        }
    }
    if(pre==0 && child[u]>=2) articulation_points[u] =1 ; // Đỉnh u là gốc của cây DFS và có ít nhất 2 con trực tiếp
}

int main(){
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    cin>>n>>m;

    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i=1;i<=n;i++){
        if(!num[i]) dfs(i,0);
    }

    for(int i=1;i<=n;i++){
        num_articulation_points += articulation_points[i];
    }

    cout<<num_articulation_points<<" "<<num_bridges<<"\n";
    return 0;
}