/*
Xét bài toán tìm dãy con chung dài nhất (**LCS – longest common subsequence**): “Cho 2 dãy X = <*x*1, …, *xm*> và Y = <*y*1,…,*yn*>,
hãy tìm độ dài của dãy con chung có độ dài dài nhất của X và Y”. Sau đây là một biến thể của bài toán dãy con chung dài nhất:
Trong mỗi dãy X và Y đều có thể chứa các ký tự đại diện “?” và ký tự đại diện này ở mỗi vị trí khác nhau trong dãy (X hoặc Y) đều được
phép “***khớp”/matching*** với bất kỳ 1 ký tự khác của dãy còn lại.
Chú ý: ký tự đại diện ? ở dãy này không được phép ***“khớp”/matching*** với ký tự đại diện ? ở dãy khác. Hãy giải biến thể này của bài toán dãy con chung dài nhất.

**Input:**

· Dòng 1: xâu kí tự X (có độ dài ≥ 1 và ≤ 50)

· Dòng 2: xâu kí tự Y (có độ dài ≥ 1 và ≤ 50)

**Output:**

Độ dài của dãy con chung có độ dài dài nhất của X và Y.
*/