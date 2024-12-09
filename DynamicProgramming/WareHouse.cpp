/*
A truck is planned to arrive at some stations among N stations 1,2,...,N located on a line. Station i (i = 1,…,N) has coordinate i and has following information
ai : amount of goods
ti : pickup time duration for taking goods
The route of the truck is a sequence of stations x1<x2<...<xk (1≤xj≤ N, j=1,…,k). Due to technical constraints, the distance between two consecutive stations 
that the truck arrives xi and xi+1 is less than or equal to D and the total pickup time duration cannot exceed T.
Find a route for the truck such that total amount of goods picked up is maximal.
Input
Line 1: N, T, D (1 <= N <= 1000, 1 <= T <= 100, 1 <= D <= 10)
Line 2: a1,..., aN(1 <= ai<= 10)
Line 3: t1,..., tN(1 <= ti<= 10)
Output
Write the total amount of goods that the truck picks up in the route.
Example
Input
6 6 2
6 8 5 10 11 6
1 2 2 3 3 2
Output
24
*/
/* f[i][k] là số lượng hàng lớn nhất có thể lấy được khi nhà kho kết thúc ở i và thời gian lấy hàng không vượt quá k
Công thức: k<t[i] f[i][k]=0
           k>=t[i] f[i][k]=max(f[i]][k],f[j][k-t[i]]+a[i]) j=1-D->i-1
kết quả là max f[i][k] với i=1,n và k=1,T
*/

#include <bits/stdc++.h>
using namespace std;

int n, f[1005][102], T, D, a[1005], t[1005], res;

void solve(){
    for(int i=1; i<=n; i++){
        for(int k=t[i]; k<=T; k++){
            for(int j=max(0,i-D);j<i;j++){
                f[i][k]=max(f[i][k],f[j][k-t[i]]+a[i]);
            }
            res = max(res,f[i][k]);
        }
    }
    cout<<res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>T>>D;
    for(int i=1; i<=n; i++) cin>>a[i];
    for(int i=1; i<=n; i++) cin>>t[i];
    solve();
    return 0;
}