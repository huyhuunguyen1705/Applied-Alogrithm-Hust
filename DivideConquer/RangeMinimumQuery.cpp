/*
Given a sequence of n integers a0,...,an-1. We denote rmq(i,j) the minimum element of the sequence ai,...,aj. Given m pairs (i1, j1),...,(im, jm),
compute the sum Q = rmq(i1,j1) + . . . + rmq(im, jm)
Input
Line 1: n (1 <=  n <= 10^6)
Line 2: a0,...,an-1( 1 <= ai <= 10^6)
line 3: m (1  <= m <= 10^6)
Line k+3 (k=1, . . ., m): ik, jk (0  <=  ik< jk< n)
Output
Write the value Q
Example
Input
16
2 4 6 1 6 8 7 3 3 5 8 9 1 2 6 4
4
1 5
0 9
1 15
6 10
Output
6
*/

/* M[i][j] là chỉ số của phần tử nhỏ nhất của dãy con bắt đầu từ aj và có 2^i phần tử và i=0,1,2,...,log2(n+1) và j=0,..,n-1
   M[i][j] = j nếu i=0
   M[i][j] = M[i-1][j] nếu a[M[i-1][j]] <= a[M[i-1][j+2^(i-1)]]
   M[i][j] = M[i-1][j+2^(i-1)] nếu a[M[i-1][j]] > a[M[i-1][j+2^(i-1)]]
   rmq(i,j) = m[k][i] nếu a[m[k][i]] <= a[m[k][j-2^k+1]]
            = m[k][j-2^k+1] nếu a[m[k][i]] > a[m[k][j-2^k+1]]
   với k = log2(j-i+1)// k là hơn một nửa độ dài đoạn i, j

   Ở code dưới chuyển chỉ số về gía trị của phần tử nhỏ nhất của dãy con bắt đầu từ aj và có 2^i phần tử
*/

#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n;  cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];

    int max_log = log2(n-1-0+1);
    vector<vector<int>> f(max_log+1, vector<int>(n));

    for(int i=0; i<n; i++) f[0][i] = a[i];

    for(int j=1; (1<<j)<=n; j++){
        for(int i=0; i+(1<<j)<=n; i++){
            f[j][i] = min(f[j-1][i], f[j-1][i+(1<<(j-1))]);
        }
    }

    int m;  cin>>m;
    long long sum = 0;
    for(int i=0;i<m;i++){
        int l,r;    cin>>l>>r;
        int k = log2(r-l+1);
        sum += min(f[k][l], f[k][r-(1<<k)+1]);
    }
    cout<<sum;
    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 5;

int M[30][MAX],// return the index of largest elemnt between A[i] and A[j]
A[MAX], n;

void preprocessing(){ // set values for M
    for(int j=0; (1<<j)<=n; j++){
        for(int i=0; i<n; i++){
            M[j][i] = -1;
        }
    }
    for(int i=0; i<n; i++) M[0][i] = i;
    for(int j=1; (1<<j)<=n; j++){
        for(int i=0; i+(1<<j)-1<n; i++){
            if(A[M[j-1][i]] < A[M[j-1][i + (1<<(j-1))]]){
                M[j][i] = M[j-1][i];
            }else{
                M[j][i] = M[j-1][i + (1<<(j-1))];
            }
        }
    }
}

int rmq(int i, int j){
    int k = log2(j-i+1);
    int p2k = (1 << k); //pow(2,k)
    if(A[M[k][i]] <= A[M[k][j-p2k+1]]) return M[k][i];
    else return M[k][j-p2k+1];
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++) cin >> A[i];
    preprocessing();
    int m, res = 0;
    cin >> m;
    for(int v=0; v<m; v++){
        int i, j;
        cin >> i >> j;
        res += A[rmq(i,j)];
    }
    cout << res;
    return 0;
}
*/