/*
Description
Given a sequence of n integers a=a1, . . ., an. A subsequence of a consists of contiguous elements of a
(for example, ai, ai+1, . . . ,aj). 
The weight of a subsequence is defined to be the sum of its elements. A subsequence is called even-subsequnce if its weight is even. 
Find the even-subsequence of a having largest weight.
Input
Line 1: contains a positive integer n (1 <= n <= 10^6)
Line 2: contains a1, . . ., an(-10^6 <= ai <= 10^6)
Output
The weight of the largest even-subsequence found, or write NOT_FOUND if no solution found.
Example
Input
4
1  2  -3  4
Output
4
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e6 + 5;
long long n;
long long res = 0;
long long a[MAX], odd[MAX], even[MAX];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    a[0] = 0;
    even[0] = 0;
    odd[0] = 0;
    cin>>n;
    for(long long i = 1; i <= n; i++){
        cin >> a[i];
        if(!(a[i]%2)){ // a[i] is even
            even[i] = max(even[i-1]+a[i], a[i]);
            if(odd[i-1]) odd[i] = odd[i-1]+a[i]; //if i-1>0
        }else{ // a[i] is odd
            odd[i] = max(even[i-1]+a[i], a[i]);
            if(odd[i-1]) even[i] = odd[i-1]+a[i]; //if i-1>0
        }
        res = max(res, even[i]);
    }
    cout<<res;
    return 0;
}