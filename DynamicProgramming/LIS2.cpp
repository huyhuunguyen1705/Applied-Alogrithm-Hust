/*
Given a sequence a of positive a1, a2, . . ., an. A subsequence of a is defined to be the sequence obtained by removing some elements. Find the subsequence of a such that the elements is in an increasing order and the number of elements of the subsequence is maximal.

Input
Line 1: contains a positive integer n (1 <= n <= 10000)
Line 2: contains n elements of the given sequence (1 <= ai <= 10000)
Output
The length of the subsequence found.

Example
Input 
 

Output
3
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin>>n;
    vector<int> a(n+1);
    for(int i=1; i<=n; i++) cin>>a[i];
    
    vector<int> dp(n+1, 1);
    int lis = 1;
    for(int i=1; i<=n; i++){
        for(int j=1; j<i; j++){
            if(a[j]<a[i]){
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        lis = max(lis, dp[i]);
    }
    cout<<lis<<'\n';
    return 0;
}

