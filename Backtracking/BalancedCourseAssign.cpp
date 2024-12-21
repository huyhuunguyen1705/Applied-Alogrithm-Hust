/*
At the beginning of the semester, the head of a computer science department D have to assign courses to teachers in a balanced way. The department D has
m teachers T={1,2,...,m} and n courses C={1,2,...,n}. Each teacher t∈T has a preference list which is a list of courses he/she can teach depending on his/her
specialization. We known a list of pairs of conflicting two courses that cannot be assigned to the same teacher as these courses have been already scheduled in
the same slot of the timetable. The load of a teacher is the number of courses assigned to her/him. How to assign n courses to m teacher such that each course
assigned to a teacher is in his/her preference list, no two conflicting courses are assigned to the same teacher, and the maximal load is minimal.
Input
The input consists of following lines
Line 1: contains two integer m and n (1≤m≤10, 1≤n≤30)
Line i+1: contains an positive integer k and k positive integers indicating the courses that teacher i can teach (∀i=1,…,m)
Line m+2: contains an integer k
Line i+m+2: contains two integer i and j indicating two conflicting courses (∀i=1,…,k)
Output
The output contains a unique number which is the maximal load of the teachers in the solution found and the value -1 if not solution found.
Example
Input
4 12
5 1 3 5 10 12
5 9 3 4 8 12
6 1 2 3 4 9 7
7 1 2 3 5 6 10 11
25
1 2
1 3
1 5
2 4
2 5
2 6
3 5
3 7
3 10
4 6
4 9
5 6
5 7
5 8
6 8
6 9
7 8
7 10
7 11
8 9
8 11
8 12
9 12
10 11
11 12

Output
3
*/
#include <bits/stdc++.h>
using namespace std;

const int MAX = 35;

vector<int> canTeach[MAX]; //canTeach[i] is the vector of teacher can teach course i
int m,n;
bool conflict[MAX][MAX];
int x[MAX]; // x[i] is the teacher assigned to course i
int load[MAX]; // load[i] is the number of courses assigned to teacher i
int res = INT_MAX;

void input(){
    cin>>m>>n;
    memset(conflict, false, sizeof(conflict));
    for(int i=1;i<=m;i++){
        int k; cin>>k;
        for(int j=0;j<k;j++){
            int tmp; cin>>tmp;
            canTeach[tmp].push_back(i);
        }
    }
    int l; cin>>l;
    for(int t=0; t<l; t++){
        int i,j; cin>>i>>j;
        conflict[i][j]=conflict[j][i]=true;
    }
}

//can teacher t can teach k-th course
bool check(int t, int k){
    for(int i=1; i<=k-1; i++){
        if(conflict[i][k] && x[i]==t) return false;
    }
    return true;
}

void Solution(){
    int maxLoad = 0;
    for(int i=1; i<=m; i++){
        maxLoad = max(maxLoad, load[i]);
    }
    res = min (res, maxLoad);
}

void TRY(int k){
    for(int i=0; i<canTeach[k].size(); i++){
        int t = canTeach[k][i]; // teacher t can teach course k
        if(check(t,k)){
            x[k] = t; // assign course k to teacher t
            load[t] ++;
            if(k==n) Solution();
            else{
                if(load[t]<res) TRY(k+1);
            }
            load[t] --;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    input();
    TRY(1);
    cout<< (res==INT_MAX?-1:res);
    return 0;
}
