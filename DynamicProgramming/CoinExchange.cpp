/*
Given a set of coins with denominations D1, D2, ..., Dn and a denomination x. Find the minimum number of coins to exchange for denomination x.
Input
Line 1: contains 2 positive integers n and x (1 <= n <= 1000, 1 <= x <= 1000)
Line 2: contains n positive integers D1, D2, . . ., Dn

Output
Write the minimum number of coins used

Example
Input
4 10
2 1 1 3 
Output
4
*/
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, x;
    cin>>n>>x;
    vector<int> D(n+1);
    for(int i=1; i<=n; i++) cin>>D[i];
    vector<int> dp(x+1, INF);
    dp[0] = 0;
    for(int i=1; i<=n; i++){
        for(int j=D[i]; j<=x; j++){
            dp[j] = min(dp[j], dp[j-D[i]]+1);
        }
    }
    cout<<((dp[x]!=INF)?dp[x]:-1);
    return 0;
}