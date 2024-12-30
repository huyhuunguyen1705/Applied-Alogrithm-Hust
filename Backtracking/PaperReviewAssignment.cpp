/*
The chair of a conference must assign scientific papers to reviewers in a balance way. There are N papers 1,2…,N and M reviewers 1,2,…,M.
Each paper i has a list L(i) of reviewers who are willing to review that paper. A review plan is an assignment reviewers to papers. 
The load of a reviewer is the number of papers he/she have to review. Given a constant b, compute the assignment such that
Each paper is reviewed by exactly b reviewers. The maximum load of all reviewers is minimal 
Input
Line 1 contains N, M and b
Line i+1 (i = 1,…,N) contains a positive integer k
followed by k positive integers representing the list L(i)
Output
Unique line contains the maximum load for all reviewers of the solution found or contains -1 if no solution found
*/
/*
#include <bits/stdc++.h>
using namespace std;
#define MAX 100
int n, m, b;
int maxload = INT_MAX;
int can_review[MAX][MAX]; // can_review [i][j] nguoi i co the revew bai j
int review[MAX][MAX];     // nguoi i review bai j
int load[MAX];
int reviewed[MAX];                                                                              // bai i da duoc bao nhieu nguoi review
bool UCV(int i, int k) { return (can_review[i][k] && !review[i][k] && load[i] + 1 < maxload); } // UCV(i,k) returns true if person i can review paper k and has not already done so and the load of person i is less than maxload.

void TRY(int k)
{
    for (int i = 1; i <= m; i++)
    {
        if (UCV(i, k))
        {
            review[i][k] = 1;
            load[i]++;
            reviewed[k]++;
            if (reviewed[k] == b)
            {
                if (k < n)
                    TRY(k + 1);
                else
                {
                    int maxtemp = 0;
                    for (int j = 1; j <= m; j++)
                        maxtemp = max(maxtemp, load[j]);
                    maxload = min(maxload, maxtemp);
                }
            }
            else
                TRY(k);
            review[i][k] = 0;
            load[i]--;
            reviewed[k]--;
        }
    }
}

int main()
{
    cin >> n >> m >> b;
    int temp1, temp2;
    for (int i = 1; i <= n; i++)
    {
        cin >> temp1;
        for (int j = 1; j <= temp1; j++)
        {
            cin >> temp2;
            can_review[temp2][i] = 1;
        }
    }
    TRY(1);
    cout << maxload;
}
*/