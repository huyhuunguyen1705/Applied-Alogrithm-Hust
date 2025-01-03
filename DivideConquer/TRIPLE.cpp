/* 
Cho dãy các số nguyên dương a = (a1,...,aN) và số nguyên dương K. Tính Q là số triple (i,j,k) mà 1<=i<j<k<=N và a[i] + a[j] + a[k] = K.
Input
The input consists of following lines:
Line 1 contains N and K (1≤N≤5000,1≤K≤10^5).
Line 2 contains a1,…,aN (1≤ai≤105)
Output
Write the value Q
Example:
Input:
6 12
2 3 4 1 6 7
Output:
3
*/
// binary search O(N^2)
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 5005;
const int MOD = 1e9 + 7;
int n, Q, a[N];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> Q;
    for(int i=1; i<=n; i++) cin>>a[i];
    sort(a+1, a+n+1, [](const int a, const int b){
        return a<b;
    });

    int cnt=0;
    for(int i=1; i<=n; i++){
        int j = i+1;
        int k = n;
        while(j<k){
            if (a[i]+a[j]+a[k]<Q){
                j++;
            } else if (a[i] + a[j] +a[k]>Q){
                k--;
            } else {
                cnt++;
                cnt = cnt%MOD;
                j++;
                k--;
            }
        }
    }
    cout<<cnt<<'\n';
    return 0;
}


/* Divide and Conquer O(n^2logn)
#include <bits/stdc++.h>
using namespace std;

// Function to count the number of valid triples using Divide and Conquer
long long countTriples(vector<int>& a, int left, int right, int K) {
    if (right - left < 2) {
        return 0;
    }

    int mid = left + (right - left) / 2;
    long long count = 0;

    // Count triples in the left half
    count += countTriples(a, left, mid, K);

    // Count triples in the right half
    count += countTriples(a, mid + 1, right, K);

    // Count triples crossing the middle
    for (int i = left; i <= mid; ++i) {
        for (int j = i + 1; j <= mid; ++j) {
            int remaining = K - a[i] - a[j];
            count += upper_bound(a.begin() + mid + 1, a.begin() + right + 1, remaining) -
                     lower_bound(a.begin() + mid + 1, a.begin() + right + 1, remaining);
        }
    }

    // Merge step to maintain sorted order
    inplace_merge(a.begin() + left, a.begin() + mid + 1, a.begin() + right + 1);

    return count;
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    // Sort the array initially for binary search in Divide and Conquer
    sort(a.begin(), a.end());

    long long result = countTriples(a, 0, N - 1, K);
    cout << result << endl;

    return 0;
}
*/