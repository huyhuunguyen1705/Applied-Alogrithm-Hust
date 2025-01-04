/*
Cho 2 tập số nguyên dương được biểu diễn bởi 2 dãy a = a1,..., an và b = b1,..., bm. Hãy tìm số phần tử thuộc giao của 2 tập hợp đã cho.
Dữ liệu vào
Dòng đầu chứa một số nguyên là số testcase: T (0 ≤ T ≤ 10). Tiếp theo, mỗi testcase được cho trên 4 dòng như sau:
• Dòng đầu chứa số nguyên dương: n
• Dòng tiếp theo chứa dãy a: a1 a2 ... an
• Dòng tiếp theo chứa số nguyên dương: m
• Dòng tiếp theo chứa dãy b: b1 b2 ... bm
Dữ liệu đảm bảo các số trong cùng một dãy thì đôi một khác nhau
Example:
Input:
1
4
2 1 4 3
3 
1 5 4
Output:
2
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n,m;
        cin>>n;
        set<int> tmp;
        set<int> res;
        for(int i=0;i<n;i++){
            int x; cin>>x;
            tmp.insert(x);
        }
        cin>>m;
        for(int i=0;i<m;i++){
            int x; cin>>x;
            if(tmp.find(x)!=tmp.end()) res.insert(x);
        }
        cout<<res.size()<<endl;
    }
}
/* Xóa phần tử một set
set<int> s;
s.erase(1); // xóa phần tử 1 trong set
*/ 