/*
Đề bài giống KnapSack 0-1 nhưng có thể chọn vô hạn số lượng của mỗi vật phẩm
Input:
    Dòng đầu tiên chứa n và W
    n dòng tiep theo, mỗi dòng chứa 2 số nguyên dương wi và vi
Output:
    Dòng đầu tiên in ra tổng giá trị lớn nhất của các vật lấy được.
    Dòng thứ hai in ra n số nguyên c1, c2,..., cn, trong đó ci là số lượng của vật thứ i được chọn
Test ví dụ:
Input:
2 100
1 1
50 30
Output:
100
100 0
*/
/*
Ý tưởng: dp[i] là tổng gtri lớn nhất thu đc với giới hạn trong tải i
    Xét giới hạn tải trọng i và viên đá quý wj, vj. Nếu như i >=wj thì có thể chọn vật nay vào ba lô
    Kết quả cần tìm là dp[W]
*/

#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

void input(int &n, int &W, vector<pii> &items){
    cin >> n >> W;
    items.resize(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> items[i].first >> items[i].second;
}

void trace_back(int n, int W, vector<int> &dp, vector<pii> &items){
    vector<int> picked_items(n+1, 0);
    while(W>0){
        for(int i=1; i<=n; i++){
            if(W>=items[i].first && dp[W] == dp[W-items[i].first] + items[i].second){
                picked_items[i]++;
                W -= items[i].first;
                break;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout<<picked_items[i]<<' ';
    }
}

void solve(int n, int W, vector<pii> items){
    vector<int> dp(W + 1, 0);
    for(int i=0; i<=W; i++){
        for(int j=1; j<=n; j++){
            if(i >= items[j].first)
                dp[i] = max(dp[i], dp[i-items[j].first] + items[j].second);
        }
    }
    cout<<dp[W]<<'\n';
    trace_back(n,W,dp,items);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, W;

    vector<pii> items;

    input(n, W, items);
    solve(n, W, items);
}