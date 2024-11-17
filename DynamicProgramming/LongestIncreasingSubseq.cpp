/*
Description
Given a sequence a of positive a1, a2, . . ., an. A subsequence of a is defined to be the sequence obtained by removing some elements. 
Find the subsequence of a such that the elements is in an increasing order and the number of elements of the subsequence is maximal.
Input
Line 1: contains a positive integer n (1 <= n <= 100000)
Line 2: contains n elements of the given sequence (1 <= ai <= 100000)
Output
The length of the subsequence found.
Example
Input
6
5 8 2 8 10 10
Output
3
*/

#include <bits/stdc++.h>

using namespace std;

int main(){
    int n; cin>>n;
    vector<int> a(n);

    for(int i=0; i<n; i++) cin>>a[i];

    vector<int> dp; // dp[i] is the smallest number of the last element of the increasing subsequence of length i+1

    for(int i=0; i<n; i++){
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);// find the first element that is not less than a[i]
        if(it != dp.end()) *it = a[i];// if there is such element, update it
        else dp.push_back(a[i]);// if there is no such element, add a[i] to the end of dp
    }
    cout<<dp.size()<<'\n';
    return 0;
}