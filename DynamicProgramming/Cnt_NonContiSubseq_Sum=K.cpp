/*
Cho một dãy số A gồm n số nguyên dương: a1,a2,.., an. Hãy đếm số lượng dãy con không liên tục của dãy A sao cho tổng các phần tử trong dãy con đó bằng K.
Input:
    Dòng đầu tiên chứa 2 số nguyên n và K (1 ≤ n ≤ 1000, 1 ≤ K ≤ 1000)
    Dòng thứ 2 chứa n số nguyên dương a1,a2,.., an (1 ≤ ai ≤ 1000)
Output:
    In ra số nguyên duy nhất là số lượng dãy con có tổng bằng K. Kết quả có thể rát lớn, hãy in ra phần dư của kết quả khi chia cho 10^9+7

Ví dụ:
Input:
4 6
1 2 3 3
Output: 3
*/
/*
Ý tưởng: dp[i][j] là số lượng dãy con không liên tục của dãy A[1..i] có tổng là j. Khi xét ptu ai, ta có thể:
- Không chọn ai vào dãy con, khi đó tổng số dãy con tạo ra sẽ là từ mảng con A[1...i-1] với tổng là j,
số lượng là dp[i-1][j]. TH này xảy ra cả khi j<ai và j>=ai
- Chọn ai vào dãy con, khi đó số dãy con tạo ra sẽ là dp[i-1][j-ai]. TH chỉ xảy ra nếu j>=ai 
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e3 + 5;
const int MOD = 1e9 + 7;

int n, K;
int a[MAX];
int dp[MAX][MAX];

void input(){
    cin>>n>>K;
    for(int i=1; i<=n; i++) cin>>a[i];
}

void solve(){
    for(int i=0; i<=n; i++) dp[i][0] = 1; // vi với j=0, chỉ có 1 cách là không chọn phần tử nào
    // Cung co the suy ra tu TH j=a[i], khi do dp[i-1][j-a[i]] = 1 bieu thi co 1 cach chon: Chon moi ptu ai

    for(int i=1; i<=n; i++){
        for(int j=1; j<=K; j++){
            dp[i][j] = dp[i-1][j];
            if(j >= a[i]) dp[i][j] = (dp[i][j] + dp[i-1][j-a[i]]) % MOD;
        }
    }

    cout<<dp[n][K];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    input();
    solve();
    return 0;
}