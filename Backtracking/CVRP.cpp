/*
A fleet of K identical trucks having capacity Q need to be scheduled to delivery pepsi packages from a central depot 0 to clients 1,2,…,n. Each client i requests d[i] packages.
The distance from location i to location j is c[i,j], 0≤i,j≤n. A delivery solution is a set of routes: each truck is associated with a route, starting from depot,
visiting some clients and returning to the depot for deliverying requested pepsi packages such that:
Each client is visited exactly by one route
Total number of packages requested by clients of each truck cannot exceed its capacity
Goal
Find a solution having minimal total travel distance
Note that: 
There might be the case that a truck does not visit any client (empty route)
The orders of clients in a route is important, e.g., routes 0 -> 1 -> 2 -> 3 -> 0 and 0 -> 3-> 2 -> 1 -> 0 are different.
Input
Line 1: n,K,Q (2≤n≤12,1≤K≤5,1≤Q≤50)
Line 2: d[1],...,d[n](1≤d[i]≤10)
Line i+3 (i=0,…,n): the ith row of the distance matrix c (1≤c[i,j]≤30)
Output
Minimal total travel distance
Example
Input
4 2 15
7 7 11 2
0 12 12 11 14
14 0 11 14 14
14 10 0 11 12
10 14 12 0 13
10 13 14 11 0
Output
70
*/

#include <bits/stdc++.h>
using namespace std;

int n, // number of clients
K, // number of trucks
Q, //  maximum capacity of each truck
nbR = 0, // the number of trucks we need use, some truck are not used
segments = 0,cMin = INT_MAX, 
f = 0, f_otp = INT_MAX;
int c[15][15], // cost matrix
d[15], // client i has d[i] packages
y[15], // the first client that truck i visit 
x[15], // x[i] is the next client after client i. We can encode like this because each client exist only one route
load[15], // the present load of truck i
visited[15];

bool check_X(int v, int k){ // check truck k is valid for client v or not ?
    if(v>0 && visited[v]) return false;
    if(load[k] + d[v] > Q) return false;
    return true;
}

void TRY_X(int s, int k){
    if(s==0){
        if(k<K) TRY_X(y[k+1],k+1);
        return ;
    }
    for(int v=0; v<=n; v++){
        if(check_X(v,k)){
            x[s]=v;
            visited[v]=true;
            f+=c[s][v];
            load[k]+=d[v];
            segments++;
            if(v>0){
                if(f+(n+nbR-segments)*cMin<f_otp) TRY_X(v,k);
            }else{
                if(k==K){
                    if(segments==n+nbR) f_otp=min(f,f_otp);
                }else{
                    if(f+(n+nbR-segments)*cMin<f_otp) TRY_X(y[k+1],k+1);   
                }
            }
            visited[v]=false;
            f-=c[s][v];
            load[k]-=d[v];
            segments-=1;
        }
    }
}

bool check_Y(int v, int k){
    if(v==0) return true;
    if(load[k]+d[v]>Q) return false;
    if(visited[v]) return false;
    return true;
}

void TRY_Y(int k){
    int s=0;
    if(y[k-1]>0) s=y[k-1]+1;
    for(int v=s; v<=n; v++){
        if(check_Y(v,k)){
            y[k]=v;
            if(v>0) segments++;
            visited[v]=true;
            f+=c[0][v];
            load[k]+=d[v];
            if(k<K) TRY_Y(k+1);
            else{
                nbR=segments;
                TRY_X(y[1],1);
            }
            load[k]-=d[v];
            visited[v]=false;
            f-=c[0][v];
            if(v>0) segments--;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>K>>Q;
    for(int i=1; i<=n; i++) cin>>d[i];
    for(int i=0; i<=n; i++){
        for(int j=0; j<=n; j++){
            cin>>c[i][j];
            if(i!=j && c[i][j]<cMin) cMin = c[i][j];
        }
    }
    TRY_Y(1);
    cout<<f_otp;
}
