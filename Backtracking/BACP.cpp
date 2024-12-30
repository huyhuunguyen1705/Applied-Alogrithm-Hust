/*
The BACP is to design a balanced academic curriculum by assigning periods to courses in a way that the academic load of each period is balanced. 
There are N courses 1,2,…,N that must be assigned to M periods 1,2,…,M. Each courses i has credit ci and has some courses as prerequisites.
The load of a period is defined to be the sum of credits of courses assigned to that period. The prerequisites information is represented by a matrix AN×N
in which Ai,j = 1 indicates that courses i must be assigned to a period before the period to which the course j is assigned.
Compute the assignment such that the maximum load for all periods is minimal.
Input
Line 1 contains N and M (2≤N≤16,2≤M≤5)
Line 2 contains c1,c2,…,cN
Line i+2(i=1,…,N) contains the ith line of the matrix A
Output
Unique line contains that maximum load for all periods of the solution found
Example:
Input
6 2
4 4 4 4 2 4
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 1 0 0 0
0 0 1 0 0 0
1 0 0 0 0 0
Output
12
*/
/*
#include <bits/stdc++.h>
using namespace std;
#define MAX 100
int n, m;
int A[MAX][MAX];
int c[MAX];
vector<int> before[MAX]; // after[i] gom cac mon phai hoc
vector<int> after[MAX];

int maxload = INT_MAX;
int period[MAX];
int load[MAX]; // so tin chi cua ki i
bool UCV(int i, int k)
{
    if (load[i] + c[k] >= maxload) // nhanh can
        return false;
    for (auto j : before[k])
    {
        if (period[j] > i)
            return false;
    }
    for (auto j : after[k])
    {
        if (period[j] < i)
            return false;
    }
    return true;
}

void TRY(int k)
{
    for (int i = 1; i <= m; i++)
    {
        if (UCV(i, k)) // mon k o ky i
        {
            period[k] = i;
            load[i] = load[i] + c[k];
            if (k == n)
            {
                int maxtemp = 0;
                for (int i = 1; i <= m; i++)
                    maxtemp = max(maxtemp, load[i]);
                maxload = min(maxload, maxtemp);
            }
            else
                TRY(k + 1);
            load[i] = load[i] - c[k];
        }
    }
}

int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> A[i][j];
            if (A[i][j] == 1)
            {
                before[j].push_back(i);
                after[i].push_back(j);
            }
        }
    memset(period, -1, sizeof(period));
    TRY(1);
    cout << maxload;
    return 0;
}
*/