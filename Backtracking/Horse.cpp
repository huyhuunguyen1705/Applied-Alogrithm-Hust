/*
Quân mã đi tuần:
Trên bàn cờ vua kích thước n×n có một quân mã đang ở ô (1, 1). Hãy đưa ra một dãy các di chuyển của mã  
sao cho mỗi ô trên bàn cờ đều được đi qua đúng 1 lần (ô (1, 1) được xem là đã đi qua) và in ra dãy di chuyển đó.
*/

#include <bits/stdc++.h>
using namespace std;

int n;
int X[100], Y[100]; // Lua toa do cac buoc di chuyen cua quan ma
bool mark[100][100]; // mark[i][j] = 1 neu o (i, j) da di qua

const int dx[] = {1,1,2,2,-1,-1,-2,-2};
const int dy[] = {2,-2,1,-1,2,-2,1,-1};

void print_sol(){
    for(int i=1; i<=n*n; i++){
        cout<<X[i]<<" "<<Y[i]<<'\n';
    }
    cout<<endl;
    exit(0); // TIm duoc loi giai dau tien se dung lai
}

bool check(int x, int y){
    if(x<1 || x>n || y<1 || y>n) return false;
    if(mark[x][y]) return false;
    return true;
}

void TRY(int k){
    for(int i=0; i<8; i++){
        int u = X[k-1] + dx[i];
        int v = Y[k-1] + dy[i];
        if(check(u,v)){
            mark[u][v] = true;
            X[k] = u;
            Y[k] = v;
            if(k==n*n) print_sol();
            else TRY(k+1);
            mark[u][v]=false;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    mark[1][1] = true;
    X[1] = Y[1] = 1;
    TRY(2);
    return 0;
}

