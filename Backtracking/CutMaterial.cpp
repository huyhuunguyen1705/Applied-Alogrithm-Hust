/*
Given a material having the shape rectangle with height H and width W. We need to cut this material into n smaller rectangle submaterials of size
(h1,w1), (h2, w2), ..., (hn, wn). Write a program to check if we can perform this cut.
Input
Line 1: contains two positive integers H, W (1 <= H, W <= 10)
Line 2: contains a positive integer n (1 <= n <= 10)
Line i+2 (i= 1,...,n): contains two positive integer hi and wi (1 <= hi, wi <= 10)
Output
Write 1 if we can perform the cut and write 0, otherwise.
Example
Input
7 5
4
1 5
6 2
2 2
4 3
Output
1
*/

#include<bits/stdc++.h>
using namespace std;

int H, W, h[15], w[15], n, cnt=0;

bool material[15][15]{0};

bool check(int row, int col, int i, int j){
    // check xem o (i,j) dat duoc hcn row, col khong ?
    for(int u=i; u<=i+col-1; u++){
        for(int v=j; v<=j+row-1; v++){
            if(u>H || v>W || material[u][v]) return false;
        }
    }
    return true;
}

void TRY(int k){
    for(int i=1; i<=H; i++){
        for(int j=1; j<=W; j++){
            if(!material[i][j]){
                if(check(w[k], h[k], i, j)){
                    for(int u=i; u<=i+h[k]-1; u++){
                        for(int v=j; v<=j+w[k]-1; v++){
                            material[u][v] = true;
                        }
                    }
                    if(k==n){
                        cnt++;
                        return;
                    }else TRY(k+1);

                    for(int u=i; u<=i+h[k]-1; u++){
                        for(int v=j; v<=j+w[k]-1; v++){
                            material[u][v] = false;
                        }
                    }
                }

                if(check(h[k], w[k], i, j)){
                    for(int u=i; u<=i+w[k]-1; u++){
                        for(int v=j; v<=j+h[k]-1; v++){
                            material[u][v] = true;
                        }
                    }
                    if(k==n){
                        cnt++;
                        return;
                    }else TRY(k+1);

                    for(int u=i; u<=i+w[k]-1; u++){
                        for(int v=j; v<=j+h[k]-1; v++){
                            material[u][v] = false;
                        }
                    }
                }
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>H>>W>>n;
    for(int i=1; i<=n; i++){
        cin>>h[i]>>w[i];
    }
    TRY(1);
    if(cnt) cout<<1;
    else cout<<0;
}