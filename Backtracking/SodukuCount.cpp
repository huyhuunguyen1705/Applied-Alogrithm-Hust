/*
Write a program to compute the number of sudoku solutions (fill the zero elements of a given partial sudoku table)
Fill numbers from 1, 2, 3, .., 9 to 9 x 9 table so that:
Numbers of each row are distinct
Numbers of each column are distinct
Numbers on each sub-square 3 x 3 are distinct
Input
Each line i (i = 1, 2, ..., 9) contains elements of the ith row of the Sudoku table: elements are numbers from 0 to 9 (value 0 means the empty cell of the table)
Output
Write the number of solutions foundd
Example
Input
0 0 3 4 0 0 0 8 9
0 0 6 7 8 9 0 2 3
0 8 0 0 2 3 4 5 6
0 0 4 0 6 5 0 9 7
0 6 0 0 9 0 0 1 4
0 0 7 2 0 4 3 6 5
0 3 0 6 0 2 0 7 8
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
Output
64
*/

#include <bits/stdc++.h>
using namespace std;
int x[9][9];
int cnt=0;

int check(int ucv, int r, int c){
    for(int i=0; i<9; i++){
        if(x[r][i]==ucv) return 0;
        if(x[i][c]==ucv) return 0;
    }

    int I= (r/3)*3;
    int J= (c/3)*3; // I, J is the top-left corner of the sub-square 3x3
    for(int i=I; i<I+3; i++){
        for(int j=J; j<J+3; j++){
            if(x[i][j]==ucv) return 0;
        }
    }
    return 1;
}

void TRY(int r, int c){
    if(r==9){
        cnt++;
        return;
    }
    if(x[r][c]!=0){
        if(c==8) TRY(r+1, 0);
        else TRY(r, c+1);
    }else{
        for(int v=1; v<=9; v++){
            if(check(v, r, c)){
                x[r][c] = v;
                if(c==8) TRY(r+1, 0);
                else TRY(r, c+1);
                x[r][c] = 0;
            }
        }
    }
}

int main(){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            cin>>x[i][j];
        }
    }
    TRY(0,0);
    cout<<cnt;
}
