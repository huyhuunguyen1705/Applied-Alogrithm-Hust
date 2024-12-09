/*
Cho một lược đồ gồm n cột chữ nhật liên tiếp nhau có chiều rộng bằng 1 và chiều cao lần lượt là các số nguyên không âm h1,h2,…,hn.  
Hãy xác định hình chữ nhật có diện tích lớn nhất có thể tạo thành từ các cột liên tiếp. 
Dữ liệu vào: 
Dòng thứ nhất chứa số nguyên dương n ( 1≤n≤1e6 ). 
Dòng thứ hai chứa n số nguyên không âm h1,h2,…,hn cách nhau bởi dấu cách ( 0≤hi≤1e9 ). 
Kết quả: 
In ra số nguyên duy nhất là diện tích hình chữ nhật lớn nhất có thể tạo thành từ các cột liên tiếp của lược đồ. 
Ví dụ: 
Dữ liệu vào: 
7 
6 2 5 4 5 1 6 
Kết quả: 
12   
*/

#include <bits/stdc++.h>

using namespace std;

void solve(){
    int n;cin>>n;
    vector<int> heights(n);
    for(int i=0;i<n;i++) cin>>heights[i];
    heights.push_back(0);
    stack<int> st;
    int maxArea = 0;
    for(int i=0;i<=n;i++){
        while(!st.empty() && heights[st.top()] > heights[i]){
            int h = heights[st.top()];
            st.pop();
            int width = st.empty()? i : i-1-st.top();
            maxArea = max(maxArea, h*width);
        }
        st.push(i);
    }
    cout<<maxArea<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}