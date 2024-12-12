/*
Given an integer n, write a program that generates all binary sequences without consecutive 11 in a lexicographic order.
Input
Line 1: contains an integer n (1 <= n <= 20)
Output
Write binary sequences in a lexicographic order, each sequence in a line
Example
Input
3
Output
000
001
010
100
101
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 25;
int x[MAX];
int n;

void print(){
    for(int i=0; i<n; i++) cout<<x[i];
    cout<<'\n';
}

void TRY(int k){
    for(int v=0; v<=1; v++){
        if(k>0 && x[k-1]==1 && v==1) continue;
        x[k] = v;
        if(k==n-1) print();
        else TRY(k+1);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    TRY(0);
    return 0;
}