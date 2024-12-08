/*
FiboString định nghĩa bởi F0 = a, F1 = b và Fn = Fn-1Fn-2 với mọi n >= 2. 
7 ví dụ đầu tiên của xâu FiboString là: a,b ,ab, bab, abbab, bababbab, abbabbababbab
Cho số nguyên dương n, hãy xác định ký tự ở vị trí thứ k trong xâu Fn.
0<=n<=45, 1<=k<=|Fn|
Input: n,k
Output: ký tự ở vị trí thứ k trong xâu Fn
*/

/*
Ý tưởng:
Độ dài các chuỗi Fn: |F0|=1, |F1|=1 và |Fn|=|Fn-1|+|Fn-2| với n>=2 
Nếu cần tìm ký tự thứ k trong Fn
    Nếu n=0 trả về 'a'
    Nếu n=1 trả về 'b'
    Nếu k<=|Fn-2| thì tìm ký tự thứ k trong Fn-2
    Nếu k>|Fn-2|, giảm k đi |Fn-2| và tìm trong Fn-1
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int n;
ll k;

ll fib_len[46]; // mang luu do dai cua chuoi Fn

char find_kth_char(int n, ll k){
    if(n==0) return 'a';
    if(n==1) return 'b';
    // Chia de tri
    if(k<=fib_len[n-2]) return find_kth_char(n-2, k);// Tim trong f[n-2]
    return find_kth_char(n-1, k-fib_len[n-2]);// Tim trong f[n-1]
}

int main(){
    ios::sync_with_stdio(0);
    fib_len[0]=fib_len[1]=1;
    for(int i=2; i<=45; i++) fib_len[i] = fib_len[i-1] + fib_len[i-2];
    cin >> n >> k;
    cout<<find_kth_char(n, k)<<'\n';
}