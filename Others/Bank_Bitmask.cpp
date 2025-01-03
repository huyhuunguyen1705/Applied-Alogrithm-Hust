/*
Ngân hàng cần chuyển n túi tiền từ trụ sở chính đến các chi nhánh của mình bằng hai xe chuyên dụng chở tiền có khả năng vận chuyển bằng nhau.
Mỗi túi tiền có một giá trị nhất định. Để giảm thiểu rủi ro hoạt động, người điều phối vận chuyển tiền cần phải chia những túi tiền này cho hai xe sao cho
sự chênh lệch về tổng giá trị tiền được vận chuyển bởi hai xe này càng nhỏ càng tốt.)
Input/Đầu vào
Row 1: A integer representing the number of cash bags, n (1 <= n <= 20) (Một số nguyên biểu thị số lượng túi tiền, không xác định)
Row 2: n integers separated by by spaces, each representing the value of a cash bag. These integers range from 1 to 1000 (n số nguyên được phân cách bằng dấu cách, mỗi số biểu thị giá trị của một túi tiền. Những số nguyên này nằm trong khoảng từ 1 đến 1000.)
Output/Đầu ra
An integer representing the smallest possible difference in the total values of money transported by the two vehicles. (Một số nguyên biểu thị cho sự chênh lệch nhỏ nhất có thể trong tổng giá trị tiền được vận chuyển bởi hai xe.)
Example/Ví dụ
Input   (stdin)
5
208   750 114 184 538
Output (stdout)
66
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    // Biến lưu kết quả nhỏ nhất
    int min_difference = INT_MAX;

    // Duyệt tất cả các cách phân chia
    int total_states = 1 << n; // 2^n
    for (int state = 0; state < total_states; ++state) {
        int sum1 = 0, sum2 = 0;

        // Phân chia túi tiền theo bitmask
        for (int i = 0; i < n; ++i) {
            if (state & (1 << i)) {
                sum1 += values[i]; // Nhóm 1
            } else {
                sum2 += values[i]; // Nhóm 2
            }
        }

        // Tính chênh lệch và cập nhật kết quả
        int difference = abs(sum1 - sum2);
        min_difference = min(min_difference, difference);
    }

    // In kết quả
    cout << min_difference << endl;

    return 0;
}
