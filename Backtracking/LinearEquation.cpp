/*
Given a positive integer n and n positive integers a1, a2,..., an. Compute the number of positive integer solutions to the equation: a1X1 + a2X2 + ... + anXn = M
Input
Dòng 1: n và M
Dòng 2: a1, a2,..., an
Output
Số nghiệm nguyên dương
Ví dụ
Input
3 5
1 1 1
Output
6
*/
#include <bits/stdc++.h>
using namespace std;

int n,m;
vector<int> a,x;
int currSum;
int cnt;

void TRY(int k, int arrMin){
    for(int v=1; v<=(m-currSum-arrMin*(n-1-k))/a[k]; v++){
        x[k] = v;
        currSum += a[k] * x[k];
        if(k==n-1){
            if(currSum==m) cnt++;
        }else TRY(k+1, arrMin);
        currSum -= a[k] * x[k];
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    a.resize(n);
    x.resize(n);
    for(int i=0; i<n; i++) cin>>a[i];
    int arrMin = *min_element(a.begin(), a.end());
    TRY(0, arrMin);
    cout<<cnt;
    return 0;
}