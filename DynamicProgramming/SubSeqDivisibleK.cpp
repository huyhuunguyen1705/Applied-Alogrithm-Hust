#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int longestSubsetDivisibleByK(vector<int>& arr, int n, int k) {
    vector<int> dp(k, -1); // dp[j]: độ dài lớn nhất của dãy con có tổng chia k dư j
    dp[0] = 0; // Tổng 0 có phần dư 0 và độ dài ban đầu là 0

    for (int i = 0; i < n; ++i) {
        vector<int> temp = dp; // Tạo bản sao để tránh ghi đè khi cập nhật
        for (int j = 0; j < k; ++j) {
            if (dp[j] != -1) { // Nếu tồn tại một dãy con có dư j
                int new_remainder = (j + arr[i]) % k; // Tính dư mới khi thêm arr[i]
                if (new_remainder < 0) new_remainder += k; // Xử lý dư âm
                temp[new_remainder] = max(temp[new_remainder], dp[j] + 1);
            }
        }
        dp = temp; // Cập nhật dp
    }

    return dp[0]; // Kết quả là dp[0] (dư 0)
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int result = longestSubsetDivisibleByK(arr, n, k);
    cout << result << endl;

    return 0;
}
