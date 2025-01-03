/*
Given a set of points P1, P2, ..., Pn on the plane: point Pi has coordinate (xi,yi).
Compute the convex hull of the given points: The convex hull is a subset of the given points that forms a convex polygon that contains all the given points.
Input
Line 1: contains a positive integer n (3 <= n <= 100000)
Line i+1 (i = 1, 2, ..., n): contains 2 integers xi, yi (-1000 <= xi, yi <= 1000)
Output 
Line 1: writes the number of points of the convex hull found 
Subsequent lines, each line contains 2 integers which are the x-coordinate and y-coordinate of a point of the convex hull found 
Example 
Input 
6
4 5
5 3
5 6
2 5
8 7
3 7
Output
4
5 3
8 7
3 7
2 5 
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAX = 1e5 + 5;

struct Point{
    int x, y;
    Point() : x(0), y(0){};
    Point(int x, int y): x(x), y(y){};
};

int n;
Point P[MAX];
vector<Point> S; //Stack

int dist2(Point &O, Point &A){
    int x = A.x - O.x;
    int y = A.y - O.y;
    return x*x + y*y;
}

int cross_product(Point &O, Point &A, Point &B){
    int xA = A.x - O.x;
    int yA = A.y - O.y;
    int xB = B.x - O.x;
    int yB = B.y - O.y;
    return xA*yB - xB*yA;
}

bool cmp(Point &A, Point &B){
    int cp = cross_product(P[0], A, B); //cp==0 thi B thuoc OA, cp<0 thi B nam ben trai OA, cp>0 thi B nam ben phai OA
    return (cp==0) ? dist2(P[0], A)<dist2(P[0], B) : cp>0;
}

int ccw(Point &O, Point &A, Point &B){
    int cp = cross_product(O, A, B);
    return (cp==0) ? 0 : (cp>0 ? 1 :-1);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=0; i<n;i++){
        cin>>P[i].x>>P[i].y;
    }

    // find bottom-left point
    int k = 0;
    for(int i=0; i<n; i++){
        if(P[i].y < P[k].y || (P[i].y == P[k].y && P[i].x < P[k].x)){
            k = i;
        }
    }
    swap(P[0], P[k]);
    sort(P+1, P+n, cmp);
    S.push_back(P[0]);
    S.push_back(P[1]);

    for(int i=2; i<n; i++){
        while(S.size()>1 && ccw(S[S.size()-2], S[S.size()-1], P[i])<=0){
            S.pop_back();
        }
        S.push_back(P[i]);
    }

    int size = S.size();
    cout<<size<<endl;
    for(int i=0; i<size; i++){
        cout<<S[i].x<<" "<<S[i].y<<endl;
    }
    return 0;
}