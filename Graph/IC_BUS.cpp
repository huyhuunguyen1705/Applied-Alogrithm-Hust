/*
Có n thành phố 1, 2, ..., n. Giữa 2 thành phố i và j có thể có 1 con đường (2 chiều) kết nối giữa chúng. 
Mỗi thành phố i có tuyến buýt i với C[i] là giá vé mỗi khi lên xe và D[i] là số thành phố tối đa mà buýt i có thể đi đến trên 1 hành trình đi qua các con đường kết nối.
Hãy tìm cách đi từ thành phố 1 đến thành phố n với số tiền phải trả là ít nhất
Input
Dòng 1: chứa 2 số nguyên dương n và m trong đó n là số thành phố và m là số con đường kết nối các thành phố (1 <= n <= 5000, 1 <= m <= 10000)
Dòng i+1 (i = 1,2,...,n): chứa 2 số nguyên dương C[i] và D[i] (1 <= C[i] <= 10000, 1 <= D[i] <= 100)
Dòng n+1+i (i = 1, 2, ..., m): chứa 2 số nguyên dương i và j trong đó giữa thành phố i và j có con đường kết nối
Output
Số tiền tối thiểu phải bỏ ra để đi buýt từ thành phố 1 đến thành phố n
Example
Input
6 6
10 2
30 1
50 1
20 3
30 1
20 1
1 2
1 3
1 5
2 4
2 5
4 6
Output
30
Giải thích: 
-Lên buýt 1 từ thành phố 1 đến thành phố 4 mất 10 đồng
-Lên buýt 4 từ thành phố 4 đến thành phố 6 mất 20 đồng
Tổng cộng mất 10 + 20 = 30 đồng
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int maxN = 5005, maxM = 10005;
int n,m;
vector<vector<int>> edges(maxN,vector<int>(0));
int cost[maxN][maxN], c[maxN], d[maxN];
bool visited[maxN];
/* hàm dfs
Tính toán chi phí từ thành phố root đến các thành phố khác trong phạm vi maxd của tuyến buýt root
u: thành phố hiện tại đang xét 
p: thành phố trước đó (tránh đi ngược lại)
depth: số bước đã đi
*/
 
void dfs(int root, int maxd, int u, int p, int depth){
    if(depth >= maxd) return; // đến tp thứ depth thì dừng vì đã đi 0,1,2,...,depth-1 tổng cộng depth thành phốphố
    for(int v: edges[u]){
        if(v==p || visited[v]) continue;
        visited[v] = 1;
        cost[root][v] = c[root];
        dfs(root, maxd, v, u, depth+1);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i=1; i<=n; i++) cin >> c[i] >> d[i];
    for(int i=0; i<m; i++){
        int a,b; cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    for(int i=1; i<=n; i++){
        memset(visited,0,sizeof(visited));
        for(int j=1; j<=n; j++) cost[i][j] = INT_MAX-5e7; 
        dfs(i, d[i], i, -1, 0);
    }
    // Dijkstra algorithm
    memset(visited,0,sizeof(visited));
    for(int i=1; i<=n; i++) c[i]=5e7;
    priority_queue<pii, vector<pii>, greater<pii>> pq; //pii.fi: Chi phí từ đỉnh gốc(1) đến đỉnh hiện tại còn pii.se: Đỉnh hiện tại mà thuật toán đang xét
    // pq sẽ tự động sắp xếp các đỉnh theo chi phí tăng dần
    pq.push({0,1});
    c[1]=0;
    while(!pq.empty()){
        pii top = pq.top();
        pq.pop();
        int vertex = top.se;
        visited[vertex] = 1;
        // Duyệt qua các đỉnh kề của vertex
        for (int i = 1; i <= n; ++i) {
            if (visited[i]) continue;
            int tmp = c[vertex] + cost[vertex][i];// Ban đầu đặt c[vertex] = 5e7 và cost[vertex][i] =INT_MAX - 5e7 để phép cộng này không bị tràn số
            if (tmp < c[i]) {
                pq.push({tmp, i});
                c[i] = tmp;
            }
        }
    }
    cout<<c[n]<<'\n';
    return 0;
}
