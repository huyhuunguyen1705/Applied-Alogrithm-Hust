/* Lập lịch cho y tá 
Một y tá cần lập lịch làm việc trong N ngày, mỗi ngày chỉ có thể là làm việc hay nghỉ ngơi. Một lịch làm việc là tốt nếu không có hai ngày nghỉ nào liên tiếp và mọi chuỗi 
ngày tối đại làm việc liên tiếp đều có số ngày thuộc đoạn [K1,K2]. Hãy liệt kê tất cả các cách lập lịch tốt, với mỗi lịch in ra trên một dòng một xâu nhị phân độ dài n 
với bit 0/1 tương ứng là nghỉ/làm việc. Các xâu phải được in ra theo thứ tự từ điển 
Dữ liệu vào: 
Ghi 3 số nguyên N,K1,K2 ( N≤200,K1<K2≤70 ) 
Kết quả: 
Ghi danh sách các lịch tìm được theo thứ tự từ điển 
Ví dụ: 
Dữ liệu mẫu: 
6 2 3 
Kết quả mẫu: 
011011 
110110 
110111 
111011 
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 202;
int N, K1, K2;
int x[MAX];
int L=0; // track the length of current consecutive working days

void printResult() {
    for (int i=1; i<=N; i++) cout << x[i];
    cout << '\n';
}

// check v ? valid for x[k]
bool check(int v, int k){
    if(k==1) return true;
    else{
        if(v==0){
            if(x[k-1]==0) return false;
            else if(L<K1) return false;
        }else{ // v = 1 = x[k]
            if(x[k-1]==0){
                if(N+1-k<K1) return false;
            }else{ // x[k-1] == 1
                if(L+1>K2) return false;
            }
        }
        return true;
    }
    return true;
}

void TRY(int k){
    for(int v=0; v<=1; v++){
        if(check(v, k)){
            x[k] = v;
            int preL = L;
            if(v==1){
                if(x[k-1]==1) L++;
                else L=1;
            }else L=0;
            if(k==N) printResult();
            else TRY(k+1);
            L=preL;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K1 >> K2;
    TRY(1);
    return 0;
}