/*
Cho 2 đồ thị vô hướng G1 = (V1, E1) và G2 = (V2, E2) trong đó V1 = {1,…,n1} là tập đỉnh của G1 và G2 = {1,2,…,n2} là tập đỉnh của G2.
Hai đồ thị được gọi là đẳng cấu nếu tồn tại một song ánh f từ V1 đến V2 sao cho (u,v) là cạnh của G1 khi vào chỉ khi (f(u), f(v)) là một cạnh của G2.
Dữ liệu
· Dòng 1: ghi số nguyên dương n1 và m1  (1 <= n1 <= 20, 1 <= m1 <= 40) tương ứng là số đỉnh và số cạnh của G1
· Dòng thứ i+1 (i=1,…,n1): ghi 2 số nguyên dương u và v là đầu mút của cạnh thứ i của G1
· Dòng thứ m1 + 2: ghi 2 số nguyên dương n2 và m2 (1 <= n2 <= 20, 1 <= m2 <= 40) tương ứng là số đỉnh và số cạnh của G2
· Dòng thứ m1 + 2 + i (i = 1,…,m2): ghi 2 số nguyên dương u và v là đầu mút của cạnh thứ i của G2
Kết quả
· Ghi ra giá trị 1 nếu G1 và G2 đẳng cấu và ghi ra giá trị 0, nếu ngược lại
Ví dụ
Dữ liệu
4 5
1 2
1 3
2 3
2 4
3 4
4 5
1 2
1 3
1 4
2 3
3 4
Kết quả
1
*/
/* O(n!)
Sử dụng hàm next_permutation để duyệt qua tất cả các hoán vị của tập đỉnh V1. 
Với mỗi hoán vị, kiểm tra xem các cạnh của G1 có ánh xạ đúng đến các cạnh của G2 hay không.
*/
#include <bits/stdc++.h>
using namespace std;
// vector permutation có ý nghĩa là ánh xạ f[i] là ảnh của i qua phép biến đổi f
bool areIsomorphic(vector<vector<int>>& adj1, vector<vector<int>>& adj2, int n1, int n2){
    if(n1!=n2) return false;
    vector<int> permutation(n1 + 1);
    for(int i=1; i<=n1; i++) permutation[i]=i;
    do{
        bool isIsomorphic=true;
        for(int i=1; i<=n1; i++){
            for(int j=1; j<=n1; j++){
                if(adj1[i][j]!=adj2[permutation[i]][permutation[j]]){
                    isIsomorphic=false;
                    break;
                }
            }
            if(!isIsomorphic) break; // Nếu cách ánh xạ này không đưa về 2 đồ thị đẳng cấu thì dừng
        }
        if(isIsomorphic) return true; // Nếu tồn tại một cách ánh xạ đưa về 2 đồ thị đẳng cấu kết luận là đẳng cấu
    }while(next_permutation(permutation.begin() + 1, permutation.end()));
    return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int u,v;

    int n1, m1;
    cin >> n1 >> m1;
    vector<vector<int>> adj1(n1 + 1, vector<int>(n1 + 1, 0));
    for(int i=0;i<m1;i++){
        cin>>u>>v;
        adj1[u][v]=adj1[v][u]=1;
    }
    
    int n2, m2;
    cin >> n2 >> m2;
    vector<vector<int>> adj2(n2 + 1, vector<int>(n2 + 1, 0));
    for(int i=0; i<m2;i++){
        cin>>u>>v;
        adj2[u][v]=adj2[v][u]=1;
    }
    cout<<(areIsomorphic(adj1, adj2, n1, n2) ? 1 : 0)<<'\n';
    return 0;
}

/* Optimize a litter bit with backtracking but harder to implement
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Hàm kiểm tra tính đẳng cấu với backtracking
bool isIsomorphicBacktrack(int idx, vector<int>& mapping, vector<bool>& used, vector<vector<int>>& adj1, vector<vector<int>>& adj2, int n) {
    if (idx == n) return true;

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            // Kiểm tra ánh xạ tạm thời
            bool valid = true;
            for (int j = 0; j < idx; j++) {
                if (adj1[idx][j] != adj2[i][mapping[j]]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                mapping[idx] = i;
                used[i] = true;

                if (isIsomorphicBacktrack(idx + 1, mapping, used, adj1, adj2, n)) {
                    return true;
                }

                // Hoàn tác ánh xạ
                used[i] = false;
            }
        }
    }

    return false;
}

bool areIsomorphic(vector<vector<int>>& adj1, vector<vector<int>>& adj2, int n1, int n2) {
    if (n1 != n2) return false;

    // Kiểm tra bậc của các đỉnh
    vector<int> degree1(n1, 0), degree2(n2, 0);
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            degree1[i] += adj1[i][j];
            degree2[i] += adj2[i][j];
        }
    }

    sort(degree1.begin(), degree1.end());
    sort(degree2.begin(), degree2.end());

    if (degree1 != degree2) return false;

    // Backtracking kiểm tra ánh xạ
    vector<int> mapping(n1, -1);
    vector<bool> used(n1, false);
    return isIsomorphicBacktrack(0, mapping, used, adj1, adj2, n1);
}

int main() {
    int n1, m1;
    cin >> n1 >> m1;

    vector<vector<int>> adj1(n1, vector<int>(n1, 0));
    for (int i = 0; i < m1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj1[u][v] = adj1[v][u] = 1;
    }

    int n2, m2;
    cin >> n2 >> m2;

    vector<vector<int>> adj2(n2, vector<int>(n2, 0));
    for (int i = 0; i < m2; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj2[u][v] = adj2[v][u] = 1;
    }

    cout << (areIsomorphic(adj1, adj2, n1, n2) ? 1 : 0) << endl;

    return 0;
}

*/