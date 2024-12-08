/*
Given a sequence of positive integers a1, a2, . . ., an. Perform a sequence of actions of following types:
update i v : assign ai = v
get-max i j : return the maximum value of the subsequence ai, ai+1, . . ., aj

**Input**

Line 1: contains a positive integer n (1 <= n <= 100000)

Line 2: contains a1, a2, . . ., an. (1 <= ai <= 10000)

Line 3: contains a positive integer m (1 <= m <= 100000) which is the number of actions

Line i + 3 (i = 1, 2, . . ., m): contains an action described above

Example
Input
10
1 10 9 7 1 4 2 4 8 10 
5
get-max 5 8
get-max 5 9
get-max 3 8
update 9 20
get-max 4 10

Ouput
4
8
9
20
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 4e5 + 5; // n khong vuot qua 1e5. So luong nut toi da cua cay segment la 4n

int maxVal[MAX]; // mang chua gia tri lon nhat cua cac doan con co id la i
int n;// so phan tu cua day


int getMaxNode(int id, int left, int right, int first, int last){
    //return the max value of afirst,...,alast from the node (id, left, right)
    if(last<left || first>right) return INT_MIN; //[left, right] and [first, last] are disjoint
    if(first<=left && last>=right) return maxVal[id]; //[left, right] is inside [first, last]
    int mid = (left+right)/2;
    int leftId = 2*id, rightId = 2*id+1; //left child and right child
    int maxLeft = getMaxNode(leftId, left, mid, first, last);
    int maxRight = getMaxNode(rightId, mid+1, right, first, last);
    return max(maxLeft, maxRight);
}

int getMax(int first, int last){
    return getMaxNode(1, 1, n, first, last);
}

void updateNode(int id, int left, int right, int idx, int val){
    if(left>right) return;
    if(idx <left || idx>right) return;
    if(left==right){
        maxVal[id] = val;
        return;
    }
    int leftId = 2*id, rightId = 2*id+1;
    int mid = (left+right)/2;
    updateNode(leftId, left, mid, idx, val);
    updateNode(rightId, mid+1, right, idx, val);
    maxVal[id] = max(maxVal[leftId], maxVal[rightId]);
}

void Update(int idx, int val){
    updateNode(1, 1, n, idx, val);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1; i<=n; i++){
        int x; cin>>x;
        Update(i,x);
    }

    int m; cin>>m;
    while(m--){
        string s;
        int a,b;
        cin>>s>>a>>b;
        if(s=="get-max") cout<<getMax(a,b)<<'\n';
        else Update(a,b);
    }
    return 0;
}