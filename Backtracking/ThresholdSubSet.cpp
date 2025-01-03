/*
Một công ty sữa muốn tri ân khách hàng, công ty in vào mỗi hộp sữa tươi một số tự nhiên được lấy từ một danh sách các số tự nhiên bí mật khác nhau cho trước.
Người tiêu dùng nếu như thu thập một tập các hộp sữa tươi sao cho các số tự nhiên trong các hộp sữa này khác nhau và tổng của chúng lớn hơn hoặc bằng năm thành lập công ty sẽ được tặng thêm 1 hộp sữa tươi.
Hỏi có bao nhiêu cách khác nhau có thể đổi được quà. Hai cách được gọi là khác nhau, nếu tập hợp các số tự nhiên trên các hộp sữa là khác nhau.
Dữ liệu
· Dòng 1: Chứa 1 số nguyên n ( 1 <= n <= 20) số lượng phần tử trong danh sách số tự nhiên bí mật
· Dòng 2: Chứa n số tự nhiên, cách nhau bởi dấu cách, có giá trị nhỏ hơn 2000, là các số tự nhiên bí mật in trên các hộp sữa;
· Dòng 3: Chứa 1 số tự nhiên là năm thành lập công ty, số này có giá trị nhỏ hơn 2023;
Kết quả
· Một số tự nhiên duy nhất là số lượng các cách khác nhau thu thập các tập số trên các hộp sữa tươi có thể đổi được quà.
Ví dụ
Đầu vào
4
1000 1601 100 200
1901
Đầu ra
5
Giải thích ví dụ: Kết quả bằng 5, vì có 5 tập hợp thỏa mãn tổng các phần tử ít nhất 1901 là {1000, 1601}, {1000, 1601, 100}, {1000, 1601, 200}, {1000, 1601, 100, 200} và {1601, 100, 200}.
*/

#include <bits/stdc++.h>
using namespace std;
vector<int> a;
int n;
int threShold;
int cnt;

void TRY(int i, int currSum){
    if(i==n){
        if(currSum>=threShold) cnt++;
        return;
    }
    TRY(i+1, currSum);
    TRY(i+1, currSum + a[i]);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    a.resize(n);
    for(int i=0; i<n; i++) cin>>a[i];
    cin>>threShold;
    TRY(0,0);
    cout<<cnt<<endl;
    return 0;
}