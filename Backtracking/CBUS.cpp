/*
There are n passengers 1, 2, …, n. The passenger i want to travel from point i to point i + n (i = 1,2,…,n). 
There is a bus located at point 0 and has k places for transporting the passengers (it means at any time, there are at most k passengers on the bus). 
You are given the distance matrix c in which c(i,j) is the traveling distance from point i to point j (i, j = 0,1,…, 2n).
Compute the shortest route for the bus, serving n passengers and coming back to point 0. 
Input
Line 1 contains n and k (1≤n≤11,1≤k≤10)
Line i+1 (i=1,2,…,2n+1) contains the (i−1)th line of the matrix c (rows and columns are indexed from 0,1,2,..,2n).
Output
Unique line contains the length of the shortest route.
Example
Input
3  2
0  8  5  1  10  5  9
9  0  5  6  6  2  8
2  2  0  3  8  7  2
5  3  4  0  3  2  7
9  6  8  7  0  9  10
3  8  10  6  5  0  2
3  4  4  5  2  2  0
Output
25
*/  
#include <bits/stdc++.h>
using namespace std;

const int MAX = 15;

int N; // Number of passengers
int capacity; // Capacity of the bus
int c[2*MAX][2*MAX]; // Distance matrix
int c_min; // Minimum distance
int x[2*MAX]; // the road of the bus visit 2n points
int visited[2*MAX];
int load; // current load of the bus
int f; // current cost
int f_best; // best cost
int x_best[2*MAX]; // best solution

void input(){
    cin>>N>>capacity;
    c_min = INT_MAX;
    for(int i=0; i<=2*N; i++){
        for(int j=0; j<=2*N; j++){
            cin>>c[i][j];
            if(i!=j) c_min = min(c_min, c[i][j]);
        }
    }
}

bool check(int v, int k){ // check v for x[k]
    if(visited[v]) return false;
    if(v>N){
        if(!visited[v-N]) return false;
    }else{
        if(load+1>capacity) return false;
    }
    return true;
}

void updateSol(){
    if(f + c[x[2*N]][0] < f_best){
        f_best = f + c[x[2*N]][0];
        for(int i=0; i<=2*N; i++) x_best[i] = x[i];
    }
}

void TRY(int k){
    for(int v=1; v<=2*N; v++){ // default x[0]=0 and visited[i]=false for i=1,n
        if(check(v,k)){
            x[k] = v;
            f += c[x[k-1]][x[k]];
            if(v<=N) load += 1;
            else load -= 1;
            visited[v] = true;
            if(k==2*N) updateSol();
            else{
                if(f + (2*N+1-k)*c_min < f_best){
                    TRY(k+1);
                }
            }
            if(v<=N) load -= 1;
            else load +=1;
            visited[v] = false;
            f -= c[x[k-1]][x[k]];
        }
    }
}

void solve(){
    load = 0;
    f = 0;
    f_best = INT_MAX;
    TRY(1);
    cout<<f_best;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    input();
    solve();
    return 0;
}
