/*
Đề bài
Cho một chiếc balo có sức chứa tối đa là 𝑊 (đơn vị trọng lượng). Có 𝑛 món đồ, mỗi món đồ có: Trọng lượng wi(1≤𝑤𝑖≤𝑊), Giá trị vi(1≤𝑣𝑖≤10^3)
Bạn cần chọn một số món đồ (có thể không chọn món nào) để đưa vào balo sao cho:
Tổng trọng lượng của các món đồ không vượt quá W.
Tổng giá trị của các món đồ được chọn là lớn nhất có thể.
Dữ liệu vào
.
Dòng đầu tiên chứa hai số nguyên dương n và W. 
n dòng tiếp theo, mỗi dòng chứa hai số nguyên dương wi và vi phân tách nhau bởi dấu cách.
Dữ liệu ra
Dòng đầu tiên in ra tổng giá trị lớn nhất của các vật lấy được.
Dòng thứ hai in ra chỉ số của các vật được lựa chọn theo thứ tự tăng dần.
Ví dụ
Input:
3 50
10 60
20 100
30 120
Output:
220
2 3
*/

/* Ý tưởng dp[i][j] là tổng giá trị lớn nhất của đồ vật lấy được khi chọn trong các đồ vật từ 1 tới i
và giới hạn tổng trọng lượng của chúng là j. Kết quả của bài toán là dp[n][W]
  Xét đồ vật thứ i, và giới hạn trọng lượng hiện tại là j, ta có 2 phương án chọn:
    -Nếu đồ vật thứ i ko đc chọn vào pa tối ưu, thì kq tối ưu đc sẽ đc chọn trong (i-1) đồ vật
    trước đó với giới hạn trọng lượng vẫn là j
    -Nếu đồ vật thứ i đc chọn vào pa tối ưu, thì tải trọng còn lại có thể sd là j-wi cho (i-1) đồ vật
    trước đó, và ta thêm đc thêm gtri vi của vật thứ i. Chỉ xét khi j>=wi
*/
#include <bits/stdc++.h>

using namespace std;

void enter(int &n, int &W, vector < pair < int, int > > &items)
{
    cin >> n >> W;

    items.resize(n + 1);

    // Sử dụng kiểu pair để nhập dữ liệu các món đồ.
    // items[i].first và items[i].second lần lượt là trọng lượng và giá trị của đồ vật thứ i.
    for (int i = 1; i <= n; ++i)
        cin >> items[i].first >> items[i].second;
}

// Truy vết các món đồ được chọn.
void trace_back(int n, int W, vector < vector < int > > &dp, vector < pair < int, int > > &items)
{
    vector < int > picked_items;
    while (n > 0)
    {
        if (dp[n][W] == dp[n - 1][W])
            --n;
        else 
        {
            picked_items.push_back(n);
            W -= items[n].second;
            --n;
        }
    }

    for (int i = picked_items.size() - 1; i >= 0; --i)
        cout << picked_items[i] << ' ';
}

// Quy hoạch động.
void solution(int n, int W, vector < pair < int, int > > &items)
{
    vector < vector < int > > dp(n + 1, vector < int >(W + 1, 0));

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= W; ++j)
        {
            dp[i][j] = dp[i - 1][j]; // không thể chọn đồ vật thứ i do items[i].first > j

            if (j >= items[i].first)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - items[i].first] + items[i].second); // nếu có thể chọn vật thứ i, lấy max của việc chọn và không chọn
        }

    // In kết quả.
    cout << dp[n][W] << endl;
    trace_back(n, W, dp, items);
}

int main()
{
    int n, W;
    vector < pair < int, int > > items;

    enter(n, W, items);
    solution(n, W, items);
    return 0;
}
