/*
Description
Given an integers sequence a=(a1, a2,…, an). A subsequence of aa is defined to be ai, ai+1,…, aj. 
The weight of a subsequence is the sum of its elements. Find the subsequence having the highest weight.
Input
Line 1 contains n (1≤n≤10^6)
Line 2 contains a1,…,an (−500≤ai≤500)
Output
Write the weight of the highest subsequence found.
Example
input
10
3 -1 -3 5 2 5 0 -1 5 4
output
20
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e6 + 5;
int a[MAX], dp[MAX];

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Initialize the DP variables
    dp[0] = a[0];
    int res = a[0];

    // Loop through each element starting from the second one
    for (int i = 1; i < n; ++i) {
        // Decide whether to add a[i] to the current subsequence or start a new subsequence
        dp[i] = max(a[i], dp[i-1] + a[i]);

        // Update the maximum sum encountered
        res = max(res, dp[i]);
    }

    cout << res << '\n';
    return 0;
}