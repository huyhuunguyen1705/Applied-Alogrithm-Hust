/*
Cho dãy số nguyên a. Dãy con của a là dãy thu được bằng cách xóa đi một số phần tử của a (có thể không xóa phần tử nào, cũng có thể xóa hết tất cả).
Một dãy con được gọi là đẹp nếu phần tử đứng sau lớn hơn phần tử đứng trước đúng một đơn vị. Yêu cầu: Hãy tìm dãy con đẹp dài nhất của dãy a.
Dữ liệu vào
Dòng đầu chứa một số nguyên là số testcase: T (0 ≤ T ≤ 10). Tiếp theo, mỗi testcase được cho trên 2 dòng nhưsau:
• Dòng đầu chứa số phần tử của dãy a: n
• Dòng tiếp theo chứa dãy a
Kết quả
Ghi ra T dòng, mỗi dòng một số nguyên duy nhất là độ dài của dãy con đẹp dài nhất tìm được tương ứng với
testcase trong input.
Example:
Input:
1
6
3 1 2 4 3 5
Output:
3
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n; cin>>n;
        vector<int> a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        int res=INT_MIN;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(a[i]==a[j]+1) dp[i]=max(dp[i],dp[j]+1);
            }
        res=max(res,dp[i]);
        }
        cout<<res<<endl;
    }
    return 0;
}