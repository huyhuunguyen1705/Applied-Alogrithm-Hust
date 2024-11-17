/*
Description
Given a set of segments X = {(a1, b1), . . . , (an, bn)} in which ai < bi are coordinates of the segment i on a line, i = 1, …, n.  
Find a subset of X having largest cardinality in which no two segments of the subset intersect
Input
Line 1: contains a positive integer n (1 <= n <= 100000)
Line i+1 (i= 1,...,n): contains ai and bi (0 <= ai <= bi <= 1000000)
Output
Number of segments in the solution found.
Example
Input
6
0 10
3 7
6 14
9 11
12 15
17 19
Output
4
*/

#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int> 
const int MAX = 1e5 + 5;

int n;
pii a[MAX];

bool comparator(pii a, pii b){
    return a.second < b.second; // sort by the end of the segment in ascending order
}

int main(){
    cin>>n;
    for(int i=1; i<=n; i++){
        cin>>a[i].first>>a[i].second;
    }
    sort(a+1, a+n+1, comparator);
    int last = INT_MIN;
    int res = 0;
    for(int i=1; i<=n; i++){
        if(a[i].first > last){
            res++;
            last = a[i].second;
        }
    }
    cout<<res;
}

