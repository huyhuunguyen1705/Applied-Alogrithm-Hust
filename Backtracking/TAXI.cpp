/*
There are n passengers 1,2,…,n. The passenger i want to travel from point i to point i+n(i=1,2,…,n). There is a taxi located at point 0 for
transporting the passengers.Given the distance matrix c(2n+1)∗(2n+1) in which c(i,j) is the traveling distance from point i to point j(i,j=0,1,…,2n). 
Compute the shortest route for the taxi, serving n passengers and coming back to point 0 such that at any moment, there are no more than one passenger in the taxi,
and no point is visited more than once (except for point 0, which can be visited up to twice).
Input:
Line 1 contains n(1≤n≤11).
Line i+1(i=1,2,…,2n+1) contains the ith line of the matrix c.
Output:
Unique line contains the length of the shortest route.
Example:
Input:
2
0 8 5 1 10
5 0 9 3 5
6 6 0 8 2
2 6 3 0 7
2 5 3 4 0
Output:
17
*/
#include <bits/stdc++.h>
using namespace std;

bool visited[12];
int n, c[25][25], x[15], d[15][15];
int dist = 0, ans = INT_MAX;
int min_edge = INT_MAX, min_to_depot = INT_MAX;

void TRY(int k){
    if(k==n+1){
        dist += d[x[n]][0];
        if(dist<ans) ans = dist;
        dist -= d[x[n]][0];
        return;
    }
    for(int i=1; i<=n; i++){
        if(visited[i]) continue;
        visited[i] = true;
        x[k] = i;
        dist += d[x[k-1]][x[k]];
        if(dist + (n-k)*min_edge + min_to_depot < ans){
            TRY(k+1);
        }
        dist -= d[x[k-1]][x[k]];
        visited[i] = false;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i = 0; i < 2*n+1; i++){
        for(int j = 0; j < 2*n+1; j++){
            cin >> c[i][j];
        }
    }
    for(int i=1; i<=n;i++){
        for(int j=1; j<=n;j++){
            d[i][j] = c[i+n][j] + c[j][j+n];
            min_edge = min(min_edge, d[i][j]);
        }
        d[i][0] = c[i+n][0];
        d[0][i] = c[0][i] + c[i][i+n];
        min_to_depot = min(min_to_depot, d[i][0]);
    }
    TRY(1);
    cout<<ans;
    return 0;
}
/*
#include <bits/stdc++.h>
using namespace std;
int n, a[50][50], x[50], visited[50], best = INT_MAX, curr = 0, cmin = INT_MAX;
void input()
{
    cin >> n;
    for (int i = 0; i <= 2 * n; i++)
        for (int j = 0; j <= 2 * n; j++)
        {
            cin >> a[i][j];
            if (a[i][j])
                cmin = min(cmin, a[i][j]);
        }
    x[0] = 0;
    visited[0] = 1;
}
bool UCV(int i, int k)
{
    if (visited[i] == 1)
        return false;
    if ((curr + a[x[k - 1] + n][i] + a[i][i + n] + cmin * (2 * n + 1 - 2 * k)) >= best)
        return false;
    return true;
}
void TRY(int k)
{
    for (int i = 1; i <= n; i++)
    {
        if (UCV(i, k))
        {
            if (k == 1)
                curr = curr + a[x[0]][i] + a[i][i + n];
            else
            {
                curr = curr + a[x[k - 1] + n][i] + a[i][i + n];
            }
            x[k] = i;
            visited[i] = 1;
            if (k == n)
                best = min(best, curr + a[i + n][0]);
            else
                TRY(k + 1);
            visited[i] = 0;
            if (k == 1)
                curr = curr - a[x[0]][i] - a[i][i + n];
            else
                curr = curr - a[x[k - 1] + n][i] - a[i][i + n];
        }
    }
}
int main()
{
    input();
    TRY(1);
    cout << best;
    return 0;
}
*/