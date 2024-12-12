/*
Description
Given an integer n, write a program to generate all permutations of 1, 2, ..., n in a lexicalgraphic order (elements of a permutation are separated by a SPACE character).
Example
Input 
3
Output
1 2 3 
1 3 2 
2 1 3 
2 3 1 
3 1 2 
3 2 1 
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 10;

int x[MAX];
bool visited[MAX];
int n;

void print(){
    for(int i=0; i<n; i++) cout<<x[i]<<" ";
    cout<<"\n";
}

void TRY(int k){
    for(int v=1;v<=n;v++){
        if(!visited[v]){
            x[k] = v;
            visited[v] = true;
            if(k==n-1) print();
            else TRY(k+1);
            visited[v] = false;
        }
    }
}

int main(){
    cin>>n;
    TRY(0);
    return 0;
}