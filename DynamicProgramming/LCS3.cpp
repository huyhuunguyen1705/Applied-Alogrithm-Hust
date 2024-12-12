/*
Denote X = X1, X2, …, Xn, a subsequence of X is created by removing some element from X.  Given two sequences X = X1, X2, …, Xn and Y = Y1, Y2, …, Ym.
Find a common subsequence of X and Y such that the length is the longest.
Input
Line 1: two positive integers n and m (1 <= n,m <= 10000)
Line 2: n integers X1, X2, …, Xn
Line 3:  m integers Y1, Y2, …, Ym
Output
Length of the longest subsequence of X and Y
Example 
Input
7 10
3 7 2 5 1 4 9
4 3 2 3 6 1 5 4 9 7
Output
5
*/

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int>> vii;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin>>n>>m;
    vi x(n+1), y(m+1);
    for(int i=1; i<=n; i++) cin>>x[i];
    for(int i=1; i<=m; i++) cin>>y[i];
    vii dp(n+1, vi(m+1, 0));
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(x[i]==y[j]) dp[i][j] = 1 + dp[i-1][j-1];
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    cout<<dp[n][m];
    return 0;
}