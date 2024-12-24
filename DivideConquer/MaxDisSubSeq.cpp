/*
Description
Given N elements (2≤ N ≤100,000) on a straight line at positions x1,…, xN(0≤ xi ≤1,000,000,000).
The distance of a subset of N elements is defined to be the minimum distance between two elements.
Find the subset of N given elements containing exactly C elements such that the distance is maximal.
Input
The first line contains a positive integer T (1 <= T <= 20) which is the number of test cases. 
Subsequent lines are T test cases with the following format:
Line 1: Two space-separated integers: N and C
Lines 2: contains  x1, x2, . . . , xN
Output
For each test case output one integer: the distance of the subset found.
Example
input
1
5 3
1 2 8 4 9
output
3
Explain: Jonh can put his 3 cows in the stalls at positions 1, 4 and 8, resulting in a minimum distance of 3.
*/
/*
Sắp xếp lại mảng theo thứ tự tăng dần
Thực hiện binary search để tìm kết quả tốt nhất 0<=d<=(a[n]-a[1])
Kiểm tra từ giá trị d=mid. Kiểm tra xem có thể chọn c phần tử sao cho khoảng cách giữa chúng >= d không 
Nếu d=mid là 1 giá trị khả thi, ta tiếp tục tìm kiếm nửa phải. Ngược lại ta tìm kiếm tiếp ở nửa trái
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;
int T, n, c, a[MAX];

bool check(int distance){
    int cnt = 1;
    int i=1, j=2;
    while(i<n){
        while(j<=n && a[j]-a[i]<distance) j++; // tìm phần tử j đầu tiên bên trái i mà a[j] - a[i] >= distance
        if(j<=n) cnt++; 
        if(cnt>=c) return true; // nếu có thể lấy đủ c phần tử
        i = j;
        j++;
    }
    return false;
}

int MaxDistance(){
    int l=0, r=a[n]-a[1]; // l, r là khoảng cách nhỏ nhất và lớn nhất có thể
    while(l<=r){
        int m = (l+r)/2;
        if(check(m)) l = m+1;
        else r = m-1;
    }
    return r;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>T;
    while(T--){
        cin>>n>>c;
        for(int i=1; i<=n; i++) cin>>a[i];
        sort(a+1, a+n+1);
        cout<< MaxDistance()<<'\n';
    }
}