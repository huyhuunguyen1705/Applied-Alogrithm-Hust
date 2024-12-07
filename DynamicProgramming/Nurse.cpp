/*
Description
The director of a hospital want to schedule a working plan for a nurse in a given period of N consecutive days 1,..., N. Due to the policy of the hospital,
each nurse cannot work all the days 1,..., N. Instead, there must be days off in which the nurse need to take a rest. A working plan is a sequence of disjoint working periods.
A working period of a nurse is defined to be a sequence of consecutive days on which the nurse must work and the length of the working period is the number of consecutive days of that working period.
he hospital imposes two constraints:
Each nurse can take a rest only one day between two consecutive working periods. it means that if the nurse takes a rest today, then she has to work tomorrow (1)
The length of each working period must be greater or equal to K1 and less than or equal to K2 (2) 
The director of the hospital want to know how many possible working plans satisfying above constraint?	
Input
 The input consists of one line which contains 3 positive integers N, K1, K2 (2 <= N <= 1000, K1 < K2 <= 400)
Output
The output consists of only one single integer M modulo 10^9 + 7 where M is the total working plans satisfying the above constraints.
Example
Input
6 2 3
Output
4
*/
// dp[i][0] số cách lập lịch đến ngày thứ i và ngày i không làm việc
// dp[i][1] số cách lập lịch đến ngày thứ i và ngày i làm việc
#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e3 + 5, MOD = 1e9 + 7;
int n, k1, k2;
int dp[MAX][2], res;

void input(){
    cin >> n >> k1 >> k2;
}

void solve(){
    dp[0][0] = dp[0][1] = 1;
    for(int i=1; i<=n; i++){
        for(int j=k1; j<=k2; j++){
            if(i-j <0) break;
            dp[i][1] += dp[i-j][0];
            dp[i][1] %= MOD;
        }
        dp[i][0] = dp[i-1][1];
    }
    res = (dp[n][0] + dp[n][1]) % MOD;
    cout<<res<<'\n';
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    input();
    solve();

    return 0;
}

/*
#include<bits/stdc++.h>
using namespace std;

const int LIM = 1e3+7;
int N, K1, K2;
int f[LIM]{0};
int main() {
    cin >> N >> K1 >> K2;
    //f[i]: kết thúc tại i và ngày i làm việc
    for(int i=1; i<=N; i++){
        if(i < K1 ) f[i] = 0;
        else if(i == K1) f[i] = 1;
        else if(i<=K2) f[i] = 2;
        else if(i>K2) {
            for(int u=1; u<=i; u++)
            if(i-u+1>=K1 && i-u+1<=K2) {
                if(u>=3) f[i]+=f[u-2];
                else if(u == 2) f[i]+=1;
                //cout << u;
            }
        }
        //cout << f[i] <<"\n";
    }
    cout<< f[N]+f[N-1];
}
*/
