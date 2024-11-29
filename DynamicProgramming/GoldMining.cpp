/*
Description
The Kingdom ALPHA has n warehouses of golds located on a straight line and are numbered 1, 2,..., n. The warehouse i has amount of ai(ai is non-negative integer) 
and is located at coordinate i (i=1,...,n). The King of ALPHA opens a competition for hunters who are responsible to find a subset of gold warehouses having
largest total amount of golds with respect to the condition that the distance between two selected warehouses must be greater than or equal to L1 and less than or equal to L2.
Input
Line 1 contains n, L1, and L2 (1≤n≤1000000,1≤L1≤L2≤n)
Line 2 contains n integers a1,a2,…,an
Output
Contains only one single integer denoting the total amount of golds of selected warehouses.
Example
Input
6 2 3
3 5 9 6 7 4
Output
19
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

typedef pair<int, int> ii;
int n, l1,l2, a[N], dp[N], res=0;
vector<ii> b; // vector = deque
priority_queue<ii> pq;

void inp(){
    cin>>n>>l1>>l2;
    for(int i=1; i<=n; i++) cin>>a[i];
}

void solve2(){ //use priorty queue
    for(int i=1; i<=l1; i++) dp[i] = a[i];
    for(int i=l1 + 1; i<=n; i++){
        pq.push(ii(dp[i-l1], i-l1));
        while(!pq.empty()){
            if(pq.top().second < i-l2) pq.pop();
            else break;
        }
        dp[i] = pq.top().first + a[i];
        res= max(res,dp[i]);
    }
    cout<<res<<'\n';
}

void solve1(){ // use deque/vector
    for(int i=1; i<=n; i++){
        dp[i] = a[i];
        while(!b.empty()){
            if(b.back().second < i-l2) b.pop_back();
            else break;
        }
        if(i-l1 > 0){
            if(b.empty()) b.push_back(ii(dp[i-l1], i-l1));
            else if(b.back().first < dp[i-l1]) b.push_back(ii(dp[i-l1], i-l1));
        }
        if(!b.empty()) dp[i] += b.back().first;
        res = max(res, dp[i]);
    }
    cout<<res<<'\n';
}

int main(){
    inp();
    //solve1();
    solve2();
    return 0;
}