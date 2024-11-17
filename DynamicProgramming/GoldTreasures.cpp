/*
Trong thế giới huyền bí của vương quốc An Lạc, huyền thoại kể về một lời nguyền cổ xưa mà chỉ những kẻ dũng cảm nhất mới có thể phá vỡ.
Vương quốc này có những kho báu bí ẩn, mỗi kho chứa một lượng vàng khổng lồ ciđược đặt tại các vị trí kỳ diệu có toạ độ (xi, yi). 
Những người đi tìm kho báu chỉ có thể bắt đầu hành trình từ cổng thành cổ tại (0,0) và theo một quy tắc đặc biệt: họ chỉ được phép di chuyển về phía mặt trời mọc - theo hướng không giảm của cả hai toạ độ x và y - để tìm đến các kho báu.
Điều này nghĩa là từ kho báu tại (xi, yi), người ta chỉ có thể tiếp tục hành trình đến kho báu (xj, yj) nếu xi ≤ xj và yi ≤ yj.
Kẻ tìm kho báu phải sắp xếp một lộ trình khôn ngoan để thu thập được nhiều vàng nhất, nhưng cần phải nhớ rằng, lời nguyền sẽ chỉ cho phép họ đi theo hướng mặt trời mọc như đã mô tả.
Dữ liệu vào:
Dòng thứ nhất chứa số nguyên dương n là số lượng kho báu (1 ≤ n ≤ 10^3).
Trong n dòng tiếp theo, mỗi dòng chứa hai số nguyên dương xi, yi, ci (1 ≤ xi, yi, ci ≤ 10^9) là toạ độ và lượng vàng của kho báu thứ i, i = 1, 2, …, n.
Kết quả:
Ghi ra một số nguyên duy nhất là tổng lượng vàng lớn nhất có thể tìm được.
Dữ liệu vào
10
2 4 7
4 2 10
4 6 2
5 5 7
1 3 9
1 5 1
1 1 3
3 1 5
3 3 6
2 2 2
Kết quả:
26
Giải thích:
Đường đi tối ưu đi qua các kho báu có toạ độ lần lượt   là (1, 1), (1, 3), (2,4) và (5,5) có tổng lượng vàng là 3 + 9 + 7 + 7 = 26
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e3 + 5;

int n;
pair<int, int> x[MAX]; // x[i] ~ 2d là toạ độ vàng của kho báu thứ i

int c[MAX][MAX]; // c[i][j] là lượng vàng ở (xi, yj)

long long ans[MAX]; // ans[i] là lượng vàng lớn nhất có thể tìm được khi đi đến kho báu thứ i

int main(){
    cin>>n;
    int tmp;
    for(int i=1; i<=n; i++){
        cin>>x[i].first>>x[i].second>>tmp;
        c[x[i].first][x[i].second] = tmp;
    }
    sort(x+1, x+n+1); // sắp xếp các kho báu theo x tăng dần, nếu x bằng nhau thì y tăng dần
    ans[0] = 0;
    x[0] = make_pair(0, 0);
    for(int i=1; i<=n; i++){
        if(x[i]==x[i-1]) ans[i] = ans[i-1];
        else{
            for(int j=0; j<=i-1; j++){ // x[j].first <=x[i].first
                if(x[j].second <= x[i].second){
                    ans[i] = max(ans[i], ans[j] + c[x[i].first][x[i].second]);
                }
            }
        }
    }
    long long res= 0;
    for(int i=1 ; i<=n; i++){
        res = max(res, ans[i]);
    }
    cout<<res;
    return 0;
}

/* GPT
#include <bits/stdc++.h>
using namespace std;

// Struct để lưu thông tin của mỗi kho báu
struct Treasure {
    int x, y, c; // Toạ độ (x, y) và lượng vàng c
};

// Hàm chính để giải bài toán
long long maxGold(vector<Treasure>& treasures) {
    // Sắp xếp các kho báu theo x tăng dần, nếu x bằng nhau thì y tăng dần
    sort(treasures.begin(), treasures.end(), [](const Treasure& a, const Treasure& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    // Cấu trúc dữ liệu để lưu trạng thái dp tương ứng với từng giá trị y
    map<int, long long> dp;
    dp[0] = 0; // Trạng thái ban đầu: tại y = 0, tổng vàng là 0

    long long max_gold = 0; // Kết quả tối đa

    for (const auto& t : treasures) {
        // Truy vấn giá trị tối ưu với y <= t.y
        auto it = dp.upper_bound(t.y); // Tìm trạng thái có y lớn hơn t.y
        if (it != dp.begin()) {
            --it;
        }
        long long max_dp = (it != dp.end() && it->first <= t.y) ? it->second : 0;

        // Tính dp tại (t.x, t.y)
        long long current_gold = max_dp + t.c;
        max_gold = max(max_gold, current_gold);

        // Cập nhật dp[t.y] nếu cần thiết
        if (dp.find(t.y) != dp.end()) {
            dp[t.y] = max(dp[t.y], current_gold);
        } else {
            dp[t.y] = current_gold;
        }

        // Xóa các trạng thái không tối ưu
        auto next_it = dp.upper_bound(t.y);
        while (next_it != dp.end() && next_it->second <= current_gold) {
            next_it = dp.erase(next_it);
        }
    }

    return max_gold;
}

int main() {
    // Đọc dữ liệu đầu vào
    int n;
    cin >> n;
    vector<Treasure> treasures(n);
    for (int i = 0; i < n; ++i) {
        cin >> treasures[i].x >> treasures[i].y >> treasures[i].c;
    }

    // Gọi hàm giải bài toán và in kết quả
    cout << maxGold(treasures) << endl;

    return 0;
}


*/