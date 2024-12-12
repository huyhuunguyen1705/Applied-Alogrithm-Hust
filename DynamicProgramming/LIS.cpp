/* LIS 
Cho dãy a có n phần tử. Một dãy con của a là dãy thu được bằng cách xóa đi một số phần tử của a và giữ nguyên thứ tự  
các phần tử còn lại ( có thể không xóa phần tử nào). Hãy tìm dãy con tăng dài nhất của a. 
Dữ liệu vào: 
Dòng 1: Chứa số nguyên n( 1≤n≤1000 ) 
Dòng 2: Chứa n số nguyên  a1 a2 … an ( |ai|≤1e9 ) 
Kết quả: 
Dòng đầu tiên chứa độ dài dãy con tăng dài nhất 
Dòng thứ 2 chứa chỉ số các phần tử được chọn vào dãy con đó 
Nếu có nhiều dãy con tăng dài nhất, in ra dãy bất kỳ trong số đó 
Ví dụ: 
Dữ liệu mẫu: 
6 
2 1 5 4 3 6 
Kết quả mẫu: 
3 
2 5 6 
Hướng dẫn: 
Bài toán này được giải bằng phương pháp quy hoạch động. 
Giả sử lis(i) là độ dài dãy con tăng dài nhất kết thúc tại ai. Khi đó ta có công thức truy hồi sau: lis(i)=max1≤j≤i−1:aj<ai(lis(j)+1) 
*/