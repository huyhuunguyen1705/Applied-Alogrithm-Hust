/*
Cho một chuỗi chỉ chứa các phần sau: '{', '}', '(', ')', '[', ']'. Ở một số nơi có 'X' thay cho bất kỳ dấu ngoặc nào.
Xác định xem bằng cách thay thế tất cả 'X' bằng dấu ngoặc thích hợp, có thể tạo ra một chuỗi dấu ngoặc hợp lệ hay không.

Input: {(X[X])}
Output: Balanced

Explaination: The balanced expression after replacing X with suitable bracket is: {([[]])}.

Input : [{X}(X)]
Output : Not balanced

Explanation: No substitution of X with any bracket results in a balanced expression.
*/

#include <bits/stdc++.h>

using namespace std;

// Function to check if 2 brackets are matching or not
bool isMatch(char a, char b){
    if((a == '(' && b == ')') ||
       (a == '{' && b == '}') ||
       (a == '[' && b == ']') ||
       (a == 'X')) return true;
    return false;
}

// Recursive function to check the given expression is balanced or not
bool isBalanced(string &s, stack<char> st, int idx){
    // Basecase: if the index is equal to the size of the string and the stack is empty, return true
    if(idx == s.length()) return st.empty();

    char topSt;
    bool res;

    // Case 1: If the current character is an opening bracket, push it into the stack
    if(s[idx] == '(' || s[idx] == '{' || s[idx] == '['){
        st.push(s[idx]);
        return isBalanced(s, st, idx+1);
    }

    // Case 2: If the current character is a closing bracket
    else if(s[idx] == ')' || s[idx] == '}' || s[idx] == ']'){
        if(st.empty()) return false;
        topSt = st.top();
        st.pop();
        if(!isMatch(topSt, s[idx])) return false;
        return isBalanced(s, st, idx+1);
        /* logic wrong
        if(isMatch(topSt, s[idx])){
            st.pop();
            return isBalanced(s, st, idx+1);
        }
        return false;
        */
    }

    // Case 3: If the current character is 'X' then check for both cases when 'X' can be opening or closing bracket.
    else if(s[idx] == 'X'){
        stack<char> tmp = st;
        tmp.push(s[idx]);
        res = isBalanced(s, tmp, idx+1);
        if(res) return true;
        if(st.empty()) return false;
        st.pop();
        return isBalanced(s, st, idx+1);
    }
    return true;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s; cin>>s;
    stack<char> st;


    //Check if the String is of even length
    if(s.length()%2==0){
        if (isBalanced(s, st, 0)) 
            cout << "Balanced";    
        else
            cout << "Not Balanced"; 
    }
   
      // If the length of the string is not even 
      // then it is not a balanced string
    else{
          cout << "Not Balanced"; 
    }
    return 0;
}