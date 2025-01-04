/*
Đêm Giao Thừa năm nay có n nhóm người tụ tập đứng dọc đường bờ hồ để xem pháo hoa. Các nhóm được đánh số từ 1 đến n theo thứ tự từ đầu đường đến cuối đường,
nhóm thứ i có ai người. Sắp đến giờ xem pháo hoa, các nhóm này sẽ hợp nhất với nhau để tạo thành một nhóm duy nhất. Quá trình hợp nhất nhóm diễn ra như sau:
• Nếu chỉ còn một nhóm thì dừng quá trình.
• Ngược lại, hai nhóm kề nhau sẽ hợp lại với nhau: Nhóm 1 hợp lại với nhóm 2, nhóm 3 hợp lại với nhóm 4,... Nếu có lẻ nhóm, nhóm sau cùng sẽ không phải làm gì.
• Đánh số lại các nhóm mới từ đầu đường đến cuối đường, bắt đầu từ 1.
• Lặp lại bước một.
Thời gian cần để hai nhóm hợp nhất với nhau bằng tổng số người trong hai nhóm. Mỗi lần hợp nhất, các nhóm sẽ thực hiện song song, 
sau đó chờ các nhóm khác thực hiện xong để tiếp tục lần hợp mới. Do đó thời gian cần cho mỗi lần hợp nhất (tức mỗi vòng lặp) sẽ là lượng thời gian lớn nhất
trong số các cặp nhóm cần hợp. Cụ thể, thời gian mà k nhóm b1, b2, . . . , bk cần để thực hiện một lần hợp nhất là max(b1+b2, b3+b4,...,bk−1+bk) nếu k chẵn,
và max(b1 + b2, b3 + b4, . . . , bk−2 + bk−1) nếu k lẻ.
Yêu cầu: Hãy tính tổng thời gian hợp nhất của tất cả các nhóm người.
Dữ liệu vào
Dòng đầu chứa một số nguyên là số testcase: T (0 ≤ T ≤ 10). Tiếp theo, mỗi testcase được cho trên 2 dòng như
sau:
• Dòng đầu chứa số nguyên dương: n
• Dòng tiếp theo chứa dãy a: a1 a2 ... an
Kết quả
Ghi ra T dòng, mỗi dòng là tổng thời gian tìm được tương ứng với testcase trong input.
Example:
Input:
1
6
3 1 2 5 4 3
Output:
36
Giải thích
Lần 1 mất max(3 + 1, 2 + 5, 4 + 3) = 7 đơn vị thời gian. Các nhóm sau đó: 4 7 7
Lần 2 mất 4+7=11 đơn vị thời gian. Các nhóm sau đó: 11 7
Lần 3 mất 11+7=18 đơn vị thời gian. Tổng là 36
*/

#include  <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n, cnt = 0;
        cin>>n;
        int a[n+1];
        for(int i=0;i<n;i++) cin>>a[i];
        while(n>1){
            if(n%2==1){ //  Nếu dãy lẻ thì thêm 0 vào cuối dãy
                a[n] = 0;
                n++;
            }
            n = n/2;
            for(int i=0;i<n; i++){
                a[i] = a[2*i] + a[2*i+1];
            }
            cnt += *max_element(a,a+n);
        }
        cout << cnt <<endl;
    }
}