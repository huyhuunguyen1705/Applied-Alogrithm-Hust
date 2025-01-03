/*
Cho dãy a = a1, a2, ..., an. Một dãy con của dãy a được định nghĩa là 1 dãy gồm các phần tử liên tiếp đứng cạnh nhau của a (ai, ai+1,..., aj). 
Hãy tìm dãy con có ít nhất 2 phần tử đồng thời 2 phần tử đứng cạnh nhau có tính chẵn lẻ khác nhau (1 phần tử chẵn và 1 phần tử lẻ) có số phần tử lớn nhất.
Input
Dòng 1: số nguyên dương n (2 <= n <= 100000)
Dòng 2: dãy a1, a2,..., an (1 <= ai <= 1000000)
Output
Ghi ra số phần tử của dãy con tìm được (ghi ra giá trị 0 nếu không tồn tại phương án nào).
Example
Input 
10
1 2 3 4 5 9 8 5 8 10 
Output 
5
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5 + 5;
int n, a[MAX];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1; i<=n; i++) cin>>a[i];
    int res = INT_MIN, cnt = 1;
    for(int i=2; i<=n; i++){
        if(((a[i]-a[i-1])%2)!=0) cnt++;
        else{
            res = max(res, cnt);
            cnt = 1;
        }
    }
    cout<< res;
    return 0;
}