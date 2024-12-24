/*
Cho một danh sách các hình chữ nhật 1, 2,…, n. Hãy tìm diện tích hình chữ nhật nhỏ nhất bao tất cả các hình chữ nhật trong danh sách trên
Dữ liệu
Dòng 1: chứa số nguyên dương n (1 <= n <= 1000)
Dòng i+1 (i=1,…,n): chứa 4 số nguyên dương x1,y1, x2,y2 trong đó (x1,y1) và (x2,y2) là tọa độ 2 đỉnh đối của hình chữ nhật thứ i (1 <= x1, y1, x2, y2 <= 100)
Kết quả
Ghi ra diện tích của hình chữ nhật nhỏ nhất tìm được
Ví dụ
Dữ liệu
3
2 4 2 7
3 2 4 7
1 2 5 2
Kết quả
20
*/

#include <bits/stdc++.h>
using namespace std;

int n;
int xmin(INT_MAX), xmax(INT_MIN), ymin(INT_MAX), ymax(INT_MIN);

int  main(){
    cin >> n;
    while(n--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        xmin = min(xmin, min(a,c));
        xmax = max(xmax, max(a,c)); 
        ymin = min(ymin, min(b,d));
        ymax = max(ymax, max(b,d));
    }
    cout << (xmax-xmin)*(ymax-ymin);
}