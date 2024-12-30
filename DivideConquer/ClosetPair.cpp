/* https://codeforces.com/group/Ir5CI6f3FD/contest/273369/problem/J
Cho N điểm trên mặt phẳng, hãy tìm một cặp điểm với khoảng cách euclid nhỏ nhất giữa chúng. Biết rằng không có hai điểm nào trùng nhau và có duy nhất một cặp có khoảng cách nhỏ nhất.
Input
Dòng đầu tiên chứa một số nguyên N (2≤N≤50000). N dòng tiếp theo mỗi dòng chứa hai số nguyên là tọa độ X và Y của một điểm. Giá trị tuyệt đối của X, Y không vượt quá 10^6.
Output
Ghi ra 3 số a,b, c, trong đó a,b (a<b) là các chỉ số của cặp điểm tìm được trong dữ liệu vào (chỉ số bắt đầu từ 0) và c là khoảng cách giữa chúng. Làm tròn c đến 6 chữ số sau dấu phẩy động.
Scoring
Subtask 1: N≤1000;
Subtask 2: N≤50000;
Example:
input:
5
0 0
0 1
100 45
2 3
9 9
output:
0 1 1.000000
input:
5
0 0
-4 1
-7 -2
4 5
1 1
output:
0 4 1.414214
*/
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

struct Point {
    int x, y, index;
};

double euclidean_distance(const Point &a, const Point &b) {
    return sqrt(1.0*(a.x - b.x)*(a.x - b.x) + 1.0*(a.y - b.y)*(a.y - b.y));
}

bool compare_x(const Point &a, const Point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool compare_y(const Point &a, const Point &b) {
    return a.y < b.y;
}

pair<pii, double> closest_pair(vector<Point> &points, int left, int right){
    if(right - left<=3){ // Truong hop co ban co toi da 3 diem (brute force)
    // Không thể chia thêm. Mỗi đoạn chỉ còn 1 hoặc 2 điểm, không đủ tạo thành một cặp điểm để tính khoảng cách
        double min_distance = INT_MAX;
        pii result;
        for(int i=left; i<right; i++){
            for(int j=i+1; j<right; j++){
                double distance = euclidean_distance(points[i], points[j]);
                if(distance < min_distance){
                    min_distance = distance;
                    result = {points[i].index, points[j].index};
                }
            }
        }
        return {result, min_distance};
    }

    int mid = (left + right) / 2;
    int mid_x = points[mid].x;

    auto left_result = closest_pair(points, left, mid);
    auto right_result = closest_pair(points, mid, right);

    pii min_pair;
    double min_distance;

    if(left_result.second < right_result.second){
        min_pair = left_result.first;
        min_distance = left_result.second;
    } else {
        min_pair = right_result.first;
        min_distance = right_result.second;
    }

    vector<Point> strip;
    for(int i=left; i<right; i++){
        if(abs(points[i].x - mid_x) < min_distance){
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compare_y);
    
    for(int i=0; i<strip.size(); i++){
        for(int j=i+1; j<strip.size() && strip[j].y - strip[i].y < min_distance; j++){
            double distance = euclidean_distance(strip[i], strip[j]);
            if(distance < min_distance){
                min_distance = distance;
                min_pair = {strip[i].index, strip[j].index};
            }
        }
    }
    return {min_pair, min_distance};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin>>n;
    vector<Point> points(n);
    for(int i=0; i<n; i++) {
        cin>>points[i].x>>points[i].y;
        points[i].index = i;
    }
    sort(points.begin(), points.end(), compare_x);
    auto result = closest_pair(points, 0, n);
    int a = result.first.first, b = result.first.second;
    if(a>b) swap(a, b);
    cout<<a<<" "<<b<<" "<<fixed<<setprecision(6)<<result.second;
    return 0;
}
