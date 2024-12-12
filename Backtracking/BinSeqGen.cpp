/*
Given an integer n, write a program that generates all the binary sequences of length n in a lexicographic order.
Input
Line 1: contains an integer n (1 <= n <= 20)
Output
Write binary sequences in a lexicographic ordder, each sequence in a line

Example
Input
3
Output
000
001
010
011
100
101
110
111
*/

#include <bits/stdc++.h>

using namespace std;
const int MAX = 25;
int n;
int x[MAX];

void print(){
    for(int i=0;i<n;i++) cout<<x[i];
    cout<<'\n';
}

void TRY(int k){
    for(int v=0;v<=1;v++){
        x[k]=v;
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

/*
//C++
#include <bits/stdc++.h>
using namespace std;

void dfs(int n, string current){
    if(current.size() == n){
        cout << current << '\n';
        return;
    }
    dfs(n, current + "0");
    dfs(n, current + '1');
}

int main() {
    int n; cin>>n;
    dfs(n, "");
    return 0;
}
*/