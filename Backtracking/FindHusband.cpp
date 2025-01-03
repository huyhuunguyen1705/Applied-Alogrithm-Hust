/*
Để tìm kiếm chồng là một anh chàng khoa học máy tính, công chúa của một đất nước ra một đề toán như sau: Cho n số nguyên, hãy chọn một tập con của tập
n số nguyên này sao cho tổng của các số nguyên được chọn không vượt qua M cho trước và hiệu giữa M và tổng của những số nguyên được chọn là nhỏ nhất.
Đầu vào
· Dòng 1: Số nguyên n (1 <= n <= 20)
· Dòng 2: n số nguyên cách nhau bởi dấu cách, giá trị của các số nguyên này nằm từ 1 tới 1000
· Dòng 3: Số nguyên M (1 <= M <= 100000)
Đầu ra
· Một số tự nhiên là hiệu của M và tổng của các số nguyên được chọn nhỏ nhất.
Ví dụ
Input   (stdin)
5
208   750 114 184 538
897
Output   (stdout)
33
*/

#include <bits/stdc++.h>
using namespace std;
vector<int> a;
int n;
int M;
int maxSum;

void TRY(int i, int currSum){
    if(i>=n){
        if(currSum<=M) maxSum = max(maxSum, currSum);
        return;
    }
    TRY(i+1, currSum);
    TRY(i+1, currSum + a[i]);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    a.resize(n);
    for(int i=0; i<n; i++) cin>>a[i];
    cin>>M;
    TRY(0,0);
    int res = M - maxSum;
    cout<<res<<'\n';
    return 0;
}
