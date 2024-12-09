/*
Description
Given a string containing only characters (, ), [, ] {, }. Write a program that checks whether the string is correct in expression.
Example
 ([]{()}()[]): correct
 ([]{()]()[]): incorrect
Input
One line contains the string (the length of the string is less than or equal to $10^6$)One line contains the string (the length of the string is less than or equal to 10
6
)
Output
Write 1 if the sequence is correct, and write 0, otherwise
Example
Input
(()[][]{}){}{}[][]({[]()})
Output
1
*/

#include<bits/stdc++.h>
using namespace std;

bool check(const string& s){
    stack<int> stk;
    for(int i=0; i<s.size(); i++){
        if(s[i]=='(' || s[i]=='[' || s[i]=='{') stk.push(s[i]);
        else{
            if(!stk.empty() && ((stk.top()=='(' && s[i]==')') ||
                                (stk.top()=='[' && s[i]==']') ||
                                (stk.top()=='{' && s[i]=='}'))) stk.pop();
            else return false;
            }
    }
    return stk.empty();
}

int main() {
    string s; cin>>s;
    cout<<check(s);
    return 0;
    
}
