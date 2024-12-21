/*
A fleet of K identical trucks having capacity Q need to be scheduled to delivery pepsi packages from a central depot 0 to clients 1,2,…,n. Each client i requests d[i] packages.
The distance from location i to location j is c[i,j], 0≤i,j≤n. Due to some technical constraints, there is a list F of pairs of client (i,j) that cannot be scheduled to be served by the same truck.
A delivery solution is a set of routes: each truck is associated with a route, starting from depot, visiting some clients and returning to the depot for deliverying requested pepsi packages such that:
Each client is visited exactly by one route
Total number of packages requested by clients of each truck cannot exceed its capacity
If (i,j) in F, then clients i and j must be visited by different trucks 

Goal: Find a solution having minimal total travel distance
Note that: 
There might be the case that a truck does not visit any client (empty route)
The orders of clients in a route is important, e.g., routes 0 -> 1 -> 2 -> 3 -> 0 and 0 -> 3-> 2 -> 1 -> 0 are different.
Input
Line 1: n,K,Q (2≤n≤12,1≤K≤5,1≤Q≤50)
Line 2: d[1],...,d[n](1≤d[i]≤10)
Line i+3 (i=0,…,n): the ith row of the distance matrix c (1≤c[i,j]≤30)
Line n+4: contains an integer M  which is the number of pairs of the list F (0 <= M <= n*(n-1)/2)
Line m + n + 4 (m = 1,...,M): contains 2 positive integers i and j: (i,j) is the mth pair of the list F

Output
Minimal total travel distance or write -1 if the given problem does not have any solution.
Example
Input
3 2 7
3 2 3
0 2 3 1  
4 0 1 3  
2 3 0 4 
3 2 4 0
1  
1 2

Output
13
*/
// Testcase: 3/5
#include <bits/stdc++.h>
using namespace std;

int n, K, Q, nbR=0, segments=0, c_min=INT_MAX, f=0, f_otp=INT_MAX;
int c[15][15], d[15], y[15], x[15], load[15], visited[15];
bool conflict[15][15];
vector<int> vt[15];

bool check_X(int v, int k) {
    if (v > 0 && visited[v]) return false;
    if (load[k] + d[v] > Q) return false;
    for(int i = 0; i < vt[k].size(); i++) {
        if (conflict[vt[k][i]][v]) return false;
    }
    return true;
}

void TRY_X(int s, int k) {
    if (s == 0) {
        if (k < K) TRY_X(y[k+1], k+1);
        return;
    }
    for (int v = 0; v <= n; v++) {
        if (check_X(v, k)) {
            x[s] = v;
            visited[v] = true;
            f += c[s][v];
            load[k] += d[v];
            vt[k].push_back(v);
            segments++;
            if (v > 0) {
                if (f + (n + nbR - segments) * c_min < f_otp) TRY_X(v, k);
            } else {
                if (k == K && segments == n + nbR) {
                    f_otp = min(f_otp, f);
                } else {
                    if (f + (n - nbR - segments) * c_min < f_otp) TRY_X(y[k+1], k+1);
                }
            }
            visited[v] = false;
            f -= c[s][v];
            load[k] -= d[v];
            vt[k].pop_back();
            segments--;
        }
    }
}

bool check_Y(int v, int k){
    if(v==0) return true; // this truck is not used
    if(load[k]+d[v]>Q) return false;
    if(visited[v]) return false;
    return true;
}

void TRY_Y(int k) {
    int s = y[k-1] > 0 ? y[k-1] + 1 : 0;
    for (int v = s; v <= n; v++) {
        if (check_Y(v, k)) {
            y[k] = v;
            if (v > 0) segments++;
            visited[v] = true;
            f += c[0][v];
            load[k] += d[v];
            vt[k].push_back(v);
            if (k < K) TRY_Y(k+1);
            else {
                nbR = segments;
                TRY_X(y[1], 1);
            }
            load[k] -= d[v];
            visited[v] = false;
            f -= c[0][v];
            vt[k].pop_back();
            if (v > 0) segments--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> K >> Q;
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> c[i][j];
            if (i != j) c_min = min(c_min, c[i][j]);
        }
    }

    int M; cin >> M;
    memset(conflict, false, sizeof(conflict));
    for (int i = 1; i <= M; i++) {
        int u, v; cin >> u >> v;
        conflict[u][v] = conflict[v][u] = true;
    }

    TRY_Y(1);
    cout << (f_otp == INT_MAX ? -1 : f_otp);
    return 0;
}
