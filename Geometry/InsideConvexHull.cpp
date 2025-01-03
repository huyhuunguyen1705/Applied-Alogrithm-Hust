/*
Cho n điểm 𝑃1,𝑃2,…,𝑃𝑛 trên mặt phẳng, tọa độ nguyên. Cho 𝐾 điểm 𝑇1,𝑇2,…,𝑇𝑘. Hãy kiểm tra xem tập điểm 𝑃1,𝑃2,…,𝑃n​  có tạo thành đa giác lồi hay không? 
Nếu có thì kiểm tra mỗi điểm trong số 𝑇1,𝑇2,…,𝑇𝑘 có nằm trong (hoặc trên cạnh) của đa giác lồi đó hay không? (các điểm đều có tọa độ nguyên nằm trong khoảng từ −1000 đến 1000).
Dữ liệu:
Dòng 1: Ghi số nguyên dương n (3 <= n <= 10000).
Dòng 2..n+1: Mỗi dòng ghi 2 số nguyên 𝑥,𝑦 (−1000 ≤ 𝑥,𝑦 ≤ 1000) là tọa độ của điểm 𝑃𝑖.
Dòng n+2: Ghi số nguyên dương 𝑘 (1 <= k <= 10000).
Dòng n+3..n+2+k: Mỗi dòng ghi 2 số nguyên 𝑥,𝑦 (−1000 ≤ 𝑥,𝑦 ≤ 1000) là tọa độ của điểm 𝑇𝑖.
Kết quả:
Dòng tứ k: Ghi giá rị 1 nếu tập điểm P1,...,Pn tạo thành đa giác lồi và điểm Tk nằm trong hoặc trên cạnh đa giác đó; và ghi ra 0, nếu ngược lại.
Ví dụ:
Input:
4
5 6
3 7
2 5
5 3
4
8 7
4 5
3 7
0 0
Output:
0
1
1
0
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;

struct Point {
    int x, y;
    Point() : x(0), y(0){}
    Point(int x, int y): x(x), y(y){}
};

Point P[MAX];
int n;
vector<Point> C;
Point O; // O is the point with the smallest y-coordinate and the smallest x-coordinate

int dist2(Point &a, Point &b){
    int x = b.x - a.x;
    int y = b.y - a.y;
    return x*x + y*y;
}

int cross_product(Point &O, Point &A, Point &B){
    // Tich co huong 2 vector (O,A) x (O,B)
    int xa = A.x - O.x, ya = A.y - O.y,
        xb = B.x - O.x, yb = B.y - O.y;
    return xa * yb - xb * ya;
    //cp > 0 thi B nam ben trai OA
}

bool cmp(Point &A, Point &B){
    int cp = cross_product(O, A, B);
    return cp == 0 ? dist2(O, A) < dist2(O, B) : cp > 0;
}

int ccw(Point &A, Point &B, Point &C){
    // Tra ve 0 neu A, B, C thang hang
    // Tra ve 1 neu C nam ben trai AB 
    // Tra ve -1 neu C nam ben phai AB 
    int cp = cross_product(A, B, C);
    return cp == 0 ? 0 : (cp < 0 ? -1 : 1);
}

bool same_side(Point &A, Point &B, Point &C, Point &D){
   // return true if c and d are in the same side of line AB
   int sc = ccw(A,B,C);
   int sd = ccw(A,B,D); 
   return sc * sd >= 0;
}

void findConvexHull(Point *P, int n){
    C.clear();
    int k = 0;
    for(int i=1; i<n; i++){
        if(P[i].y < P[k].y || (P[i].y == P[k].y && P[i].x < P[k].x)) k=i;
    }
    swap(P[0], P[k]); // Let P[0] be the lowest point
    O = P[0];
    sort(P+1, P+n, cmp);
    C.push_back(P[0]);
    C.push_back(P[1]);
    for(int i=2; i<n; i++){
        while(C.size() > 1 && ccw(C[C.size()-2], C[C.size()-1], P[i]) <= 0) C.pop_back();
        C.push_back(P[i]);
    }
}

int checkInsideConvexHull(vector<Point> &C, Point &T){
    int last = C.size() - 1;
    if(same_side(C[0], C[1], C[last], T) && same_side(C[0], C[last], C[1], T)){
        int l = 1, r = C.size() - 1;
        while(r - l > 1){
            int mid = (l + r) / 2;
            if(same_side(C[0], C[mid], C[last], T)) l = mid;
            else r = mid;
        }
        if(!same_side(C[l], C[r], C[0], T)) return 0;
        else return 1;
    }
    return 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0; i<n; i++){
        cin >> P[i].x >> P[i].y;
    }
    findConvexHull(P, n);
    int res = 1;
    if(C.size()!=n) res = 0;
    int K; cin >> K;
    for(int k=1; k<=K; k++){
        int x,y; cin>>x>>y;
        Point T(x,y);
        int resT;
        if(res==1){
            resT = checkInsideConvexHull(C, T);
        }
        cout<<resT<<endl;
    }
    return 0;
}