/* Path in Maze - hackerrank
You are given an  maze. The grid consists of the characters # and .. A # represents a wall, and a . represents a walkable tile. In addition,
there is a single character S representing your starting position, and a single character T representing the target position.
You can only move upwards, downwards, leftwards and rightwards and you can only move to walkable tiles. Also, you can't move outside the grid.
Write a program that calculates the minimum number of moves to travel from S to T. If it is impossible to reach T from S, then output DOOMED.
Input Format
The first line contains two integers,  and , separated by a single space. The next  lines each contain a string of length  consisting of #, ., S or T.
Output Format
Output a single line containing the minimum number of moves to travel from S to T, or DOOMED if it is impossible.
Constraints
It is guaranteed that there are exactly one S and exactly one T in the grid.
Sample Input 1
7 11
...........
.#########.
...#...#...
S#.#.#.#.#T
.#...#...#.
.#########.
...........
Sample Output 1
16
Sample Input 2
4 4
..S#
..#T
.#..
#...
Sample Output 2
DOOMED
 */

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

const int MAX = 1e3 + 5;
vector<vector<char>> matrix(MAX, vector<char>(MAX));
bool visited[MAX][MAX];
vector<vector<int>> d(MAX, vector<int>(MAX, 0));
int n, m;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int x = -1, y = -1;
pii start;

void bfs(pii start, vector<vector<char>> &matrix){
    queue<pii> q;
    q.push(start);
    visited[start.first][start.second] = true;

    while(!q.empty()){
        pii u = q.front();
        q.pop();
        
        for(int i = 0; i < 4; i++){
            int tx = u.first + dx[i];
            int ty = u.second + dy[i];
            
            if(tx >= 1 && tx <= n && ty >= 1 && ty <= m && 
                matrix[tx][ty] != '#' && !visited[tx][ty]){
                d[tx][ty] = d[u.first][u.second] + 1;
                
                if(matrix[tx][ty] == 'T'){
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
    
    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> matrix[i][j];
            if(matrix[i][j] == 'S'){
                start = make_pair(i, j);
            }
        }
    }

    bfs(start, matrix);
    
    if(x < 0 || y < 0) 
        cout << "DOOMED";
    else 
        cout << d[x][y];

    return 0;
}