/*
Cho một dãy số nguyên A gồm n số a1, a2, …, an. Một dãy con của dãy A là dãy thu được bằng cách xoá không hoặc một số phần tử của dãy A. Hãy tìm 
dãy con dài nhất có các phần tử tăng ngặt và có tính “chẵn lẻ” xen kẽ nhau, nghĩa là tổng hai phần tử liên tiếp nhau bất kỳ luôn không chia hết cho 2.
Dữ liệu vào:
Dòng thứ nhất chứa một số nguyên T là số bộ testcase (1 <= T <= 10).
Mỗi nhóm dòng trong T nhóm dòng tiếp theo có cấu trúc như sau:
- Dòng thứ nhất chứa số nguyên n là số phần tử của dãy A (1 <= n <= 10^5)
- Dòng thứ hai chứa n số nguyên ai cách nhau bởi dấu cách (|ai| <= 10^9)
Kết quả:
In ra T dòng, mỗi dòng chứa một số nguyên duy nhất là độ dài của dãy con dài nhất thoả mãn yêu cầu bài toán ứng với từng testcase.
Ví dụ:
Dữ liệu vào
2
10
-22 -7 -5 17 41 -9 -44 14 107 -249
15
19 -17 5 39 -19 -15 -32 7 6 -155 69 104 -27 39 155
Kết quả
4
5
Giải thích:
Với testcase 1, dãy con dài nhất có độ dài là 4, chẳng hạn dãy -22 -9 14 107. Với testcase thứ 2, dãy con dài nhất có độ dài bằng 5 có thể là -15 6 69 104 155.
*/
// 4/5 test 
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5 + 5;
int n, a[MAX];

void solve(){
    cin>>n;
    for(int i=1; i<=n; i++) cin>>a[i];
    vector<int> dp(n+1,1);
    int res = INT_MIN;
    int lis = 1;
    for(int i=1; i<=n;i++){
        for(int j=1;j<i;j++){
            if(a[j]<a[i] && (a[i]+a[j])%2){
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        res = max(res, dp[i]);
    }
    cout<<res<<'\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        solve();
    }
    return 0;
}