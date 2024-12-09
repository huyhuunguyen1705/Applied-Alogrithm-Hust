/*
A Rectangle of size n x mis divided into unit-square 1 x 1 with two colors black and white. The rectangle is represented by a matrix A(nx m) in which A(i, j) = 1 means that the unit-square at row i, column jis black and A(i, j) = 0 means that the unit-square at row icolumn jis white.
Find the sub-rectangle of the given rectangle containing only black unit-squares such that the area is maximal.
Input
•Line 1: contains 2 positive integers nand m(1 <= n, m<= 1000)
•Line i+1 (i= 1,…, n): contains the ith of the matrix A
Output
Write the area of the sub-rectangle found.

Example 
Input
4 4
0 1 1 1
1 1 1 0
1 1 0 0
1 1 1 0
Output
6
---------------------------
Một hình chữ nhật kích thước n x m được chia thành các ô vuông con 1 x 1 với 2 màu đen hoặc trắng. Hình chữ nhật được biểu diễn bởi ma trận A(n x m) trong đó A(i, j) = 1 có nghĩa ô hàng i, cột j là ô đen và A(i, j) = 0 có nghĩa ô vuông hàng i cột j là ô trắng.
Hãy xác định hình chữ nhật con của bảng đã cho bao gồm toàn ô đen và có diện tích lớn nhất.
Dữ liệu
· Dòng 1: chứa số nguyên dương n và m (1 <= n,m <= 1000)
· Dòng i+1 (i = 1,…, n): chứa hàng thứ i của ma trận A
Kết quả
· Ghi ra diện tích của hình chữ nhật lớn nhất tìm được
Ví dụ
Dữ liệu
4 4
0 1 1 1
1 1 1 0
1 1 0 0
1 1 1 0
Kết quả
6
*/

#include <bits/stdc++.h>

using namespace std;

// Function to calculate the largest rectangle in histogram
int largestRec(vector<int>& heights){
    stack<int> st; // Ngan xep luu chi so cac cot ma co chieu cao tang dan
    heights.push_back(0); // Them cot 0 vao cuoi de tinh toan cho den cot cuoi cung. Đồng thời để lấy diện tích hcn với chiều cao là chiều cao nhỏ nhất trong histogram, chiều dài là số histogram
    int maxArea = 0;
    int n = heights.size();
    for(int i=0; i<n; i++){
        while(!st.empty() && heights[st.top()] > heights[i]){//Khi gặp một cột nhỏ hơn cột ở đỉnh ngăn xếp, loại bỏ các cột trong ngăn xếp để tính diện tích các hình chữ nhật có chiều cao bằng cột ở đỉnh ngăn xếp đó.
            int h = heights[st.top()]; // Loai bo cot nay khoi ngan xep vi cot tiep theo nho hon, khong the mo rong hcn sd chieu cao do
            st.pop(); 
            int width = st.empty() ? i : i - 1 - st.top() ; // Tinh chieu rong cua hcn
            maxArea = max(maxArea, h*width);
        }
        st.push(i);
    }
    return maxArea;
}
/*
Giả sử heights = [2, 1, 5, 6, 2, 3]:

Bước 1: st = [0] (Đẩy cột đầu tiên)
Bước 2: Cột thứ 2 nhỏ hơn cột đầu tiên → Loại cột đầu tiên, tính diện tích 2×1=2. Chinh la TH st.empty()
Bước 3: st = [1] (Đẩy cột thứ 2 vào ngăn xếp)
Bước 4: Đẩy cột thứ 3 và 4 vào ngăn xếp st = [1, 2, 3]
Bước 5: Cột thứ 5 nhỏ hơn cột thứ 4 → Loại cột thứ 4 và 3, tính diện tích 6×1=6, sau đó 5×2=10.
Bước 6: Đẩy các cột còn lại vào và xử lý tương tự.

Trạng thái trước bước 5:

Mảng heights = [2, 1, 5, 6, 2, 3]
Ngăn xếp st = [1, 2, 3] (chỉ số các cột đã được thêm vào)
Cột hiện tại là heights[4] = 2
Xử lý khi gặp cột heights[4] = 2
So sánh với đỉnh ngăn xếp:
heights[st.top()] = heights[3] = 6
heights[4] = 2 < 6 → Cần xử lý cột ở đỉnh ngăn xếp.
Bước 1: Loại bỏ cột heights[3] = 6
Lấy chỉ số cột cao nhất: h = heights[3] = 6
Loại bỏ chỉ số 3 khỏi ngăn xếp → st = [1, 2]
Tính chiều rộng:
Vì ngăn xếp không rỗng, chiều rộng = 4 - st.top() - 1 = 4 - 2 - 1 = 1
Diện tích: 
Area=6×1=6
Cập nhật maxArea = 6
Bước 2: Loại bỏ cột heights[2] = 5
Lấy chỉ số cột cao nhất: h = heights[2] = 5
Loại bỏ chỉ số 2 khỏi ngăn xếp → st = [1]
Tính chiều rộng:
Vì ngăn xếp không rỗng, chiều rộng = 4 - st.top() - 1 = 4 - 1 - 1 = 2
Diện tích: 
Area=5×2=10
Cập nhật maxArea = 10
Dừng việc loại bỏ:
Giờ ngăn xếp là st = [1], đỉnh ngăn xếp là heights[1] = 1, nhỏ hơn heights[4] = 2, nên không loại bỏ nữa.
Thêm chỉ số cột hiện tại vào ngăn xếp:
st.push(4) → st = [1, 4]

*/

// Function to calculate the maximal rectangle in the matrix
int maximalRec(vector<vector<int>>& matrix){
    if(matrix.empty()) return 0;
    int n = matrix.size(), m = matrix[0].size();
    vector<int> heights(m, 0);
    int maxArea = 0;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            heights[j] = matrix[i][j] == 1 ? heights[j] +1 : 0;
        }
        maxArea = max(maxArea, largestRec(heights));
    }
    return maxArea;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n,vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> matrix[i][j];
        }
    }
    cout<<maximalRec(matrix);
    return 0;
}