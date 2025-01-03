/*
Given a sequence of distinct integers a1, a2,..., an . Compute the number P of triples of distinct indices 
(i, j, k) such that among 3 items ai, aj, ak there is an item which is equal to the sum of 2 remaining items. 
Input
Line 1: contains an integer n (1 <= n <= 2000)
Line 2: contains n integers a1, a2,..., an (1 <= ai <= 100000)
Output
Write the value P mod 10^9+7
Example
Input 
6
1 3 4 5 8 9
Output 
5
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1e9 + 7;
const int N = 2005;
int n, a[N];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    for(int i=1; i<=n; i++) cin >> a[i];
    sort(a+1, a+n+1, [](int x, int y){
        return x < y;
    });

    int cnt = 0;
    for(int i=3; i<=n; i++){
        int left=1, right=i-1;
        while(left<right){
            if (a[left] + a[right] < a[i]) left++;
            else if (a[left] + a[right] > a[i]) right--;
            else {
                cnt++;
                cnt = cnt%MOD;
                left++;
                right--;
            }

        }
    }
    cout<<(cnt%MOD)<<endl;
    return 0;
}