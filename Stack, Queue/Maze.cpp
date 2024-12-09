/*
Một mê cung hình chữ nhật được biểu diễn bởi 0-1 ma trận NxM trong đó A[i,j] = 1 thể hiện ô (i,j) là tường gạch và A[i,j] = 0 thể hiện ô (i,j) là ô trống,
có thể di chuyển vào. Từ 1 ô trống, ta có thể di chuyển sang 1 trong 4 ô lân cận (lên trên, xuống dưới, sang trái, sang phải) nếu ô đó là ô trống. 
Xuất phát từ 1 ô trống trong mê cung, hãy tìm đường ngắn nhất thoát ra khỏi mê cung.

Input
Dòng 1: ghi 4 số nguyên dương n, m, r, c trong đó n và m tương ứng là số hàng và cột của ma trận A (1 <= n,m <= 999) và r, c tương ứng là chỉ số hàng, cột của ô xuất phát.
Dòng i+1 (i=1,...,n): ghi dòng thứ i của ma trận A

Output
Ghi giá số bước cần di chuyển ngắn nhất để thoát ra khỏi mê cung, hoặc ghi giá trị -1 nếu không tìm thấy đường đi nào thoát ra khỏi mê cung.

Ví dụ

Input
8 12 5 6
1 1 0 0 0 0 1 0 0 0 0 1
1 0 0 0 1 1 0 1 0 0 1 1
0 0 1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 1 0 0 1 0 1
1 0 0 1 0 0 0 0 0 1 0 0
1 0 1 0 1 0 0 0 1 0 1 0
0 0 0 0 1 0 1 0 0 0 0 0
1 0 1 1 0 1 1 1 0 1 0 1

Output
7
*/

#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
const int MAX = 1e3 + 5;

int n, m, r, c;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int matrix[MAX][MAX];
bool visited[MAX][MAX];
int d[MAX][MAX]; // distance matrix
int x = -1, y= -1; // the present position we are visiting

void BFS(int r, int c){
    queue<pii> q;
    q.push(make_pair(r, c));
    visited[r][c] = true;
    while(!q.empty()){
        pii u = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int tx = u.first + dx[i];
            int ty = u.second + dy[i];
            if(!matrix[tx][ty] && !visited[tx][ty]){
                d[tx][ty] = d[u.first][u.second] + 1;
                if(tx<=1 || tx>=n || ty<=1 || ty>=m){// điểm đầu tiên đến biên
                    x = tx;
                    y = ty;
                    return;
                }
                visited[tx][ty] = true;
                q.push(make_pair(tx, ty));
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>r>>c;
    for(int i=1; i<=n; i++){
        for(int j=1;j<=m; j++){
            cin>>matrix[i][j];
        }
    }
    BFS(r, c);
    if(x<0 || y<0) cout<<-1;
    else cout<<d[x][y]+1; // Đang ở biên, di thêm một bước để ra khỏi ma trận
    return 0;
}