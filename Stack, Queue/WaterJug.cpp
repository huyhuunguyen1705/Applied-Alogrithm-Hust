/*
There are two jugs, a-litres jug and b-litres jug (a, b are positive integers). 
There is a pump with unlimited water. Given a positive integer c, how to get exactly c litres.
Input
Line 1: contains positive integers a,   b,  c  (1 <= a, b, c <= 900)
Output
write the number of steps or write -1 (if no solution found)
Example
Input
6  8  4
Output
4
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

const int MAX =  2e3 + 5;
int d[MAX][MAX];
queue<pii> q;

void new_state(int x, int y, int z){ // d[x][y] là số bước ít nhất từ ban đầu để có trạng thái hiện tại
    if(x>=0 && y>=0 && !d[x][y]){
        d[x][y] = z + 1;
        q.push({x,y});
    }
}

void solve(){
    int a,b,c; cin>>a>>b>>c;
    q.push({0,0});
    while(!q.empty()){
        pii x=q.front(); q.pop();
        int r = d[x.first][x.second];
        if(x.first == c || x.second == c){
            cout<<r;
            return;
        }
        new_state(a,x.second,r);
        new_state(x.first,b,r);
        new_state(0,x.second,r);
        new_state(x.first,0,r);
        int z = min(a-x.first,x.second);
        new_state(x.first+z,x.second-z,r);
        z = min(b-x.second,x.first);
        new_state(x.first-z,x.second+z,r);
    }
    cout<<-1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
