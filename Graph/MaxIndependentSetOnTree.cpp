/* Max Independent Set on a Tree
Cho cây T = (V,E) trong đó V = {1,…,n} là tập các đỉnh và E là tập gồm n-1 cạnh. Mỗi đỉnh v của đồ thị có trọng số w(v). 
Hãy chọn ra tập S các đỉnh sao cho hai đỉnh kề nhau không cùng được chọn và tổng trọng số các đỉnh được chọn là lớn nhất.
Dữ liệu
· Dòng 1: ghi số nguyên dương n (1 <= n <= 100000)
· Dòng 2: ghi n số nguyên dương w(1), w(2), …, w(n) là trọng số các đỉnh tương ứng
· Dòng i+2 (i = 1,…,n-1): ghi 2 số nguyên dương u và v là 2 đầu mút của cạnh thứ i của T
Kết quả:
· Ghi ra tổng trọng số của các đỉnh được chọn
Ví dụ
Dữ liệu
9
9 5 10 4 3 2 6 1 8
1 5
2 3
2 4
2 6
3 5
6 7
6 8
6 9
Kết quả
38
*/

// dynamic programming on treetree 
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;

vector<int> tree[MAXN + 1];
int weight[MAXN + 1];
long long dp[MAXN + 1][2];
bool visited[MAXN + 1];

void dfs(int node) {
    visited[node] = true;
    dp[node][0] = 0; // Không chọn đỉnh này
    dp[node][1] = weight[node]; // Chọn đỉnh này
    for (int neighbor : tree[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
            // Nếu không chọn đỉnh này, có thể chọn hoặc không chọn các con của nó
            dp[node][0] += max(dp[neighbor][0], dp[neighbor][1]);
            // Nếu chọn đỉnh này, không được chọn các con của nó
            dp[node][1] += dp[neighbor][0];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;

    for (int i = 1; i <= n; ++i) cin>>weight[i];
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    // Khởi động DFS từ đỉnh 1 (hoặc bất kỳ đỉnh nào vì là cây)
    dfs(1);
    // Kết quả là giá trị lớn nhất giữa chọn hoặc không chọn đỉnh gốc
    cout << max(dp[1][0], dp[1][1]) << endl;
    return 0;
}

/* Brute Force 2/5
#include <bits/stdc++.h>
using namespace std;

int n, w[21], tmp1, tmp2;
bool e[21][21];
bool subset[21];
int mis = 0;

bool check(int k) {
    for (int i = 0; i < k; ++i) {
        if (i == k) continue;
        if (e[k][i] && subset[i]) return false;
    }
    return true;
}

void Try(int k) {
    if (k == n) {
        int tmp_mis = 0;
        for (int i = 0; i < n; ++i) {
            if (subset[i]) tmp_mis += w[i];
        }
        mis = max(tmp_mis, mis);
        return;
    }
    subset[k] = 0;
    Try(k + 1);
    subset[k] = 1;
    if (check(k)) Try(k + 1);
}

int main() {
    memset(e, 0, sizeof(e));
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> w[i];
    for (int i = 0; i < n - 1; ++i) {
        cin >> tmp1 >> tmp2;
        e[tmp1 - 1][tmp2 - 1] = true;
        e[tmp2 - 1][tmp1 - 1] = true;
    }
    Try(0);
    cout << mis;
    return 0;
}
*/