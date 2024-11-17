/*
Description
Given a family tree represented by child-parent (c,p) relations in which c is a child of p. Perform queries about the family tree:
descendants <name>: return number of descendants of the given <name>
generation <name>: return the number of generations of the descendants of the given <name>

Note that: the total number of people in the family is less than or equal to 10
4
Input
Contains two blocks. The first block contains information about child-parent, including lines (terminated by a line containing ***), each line contains: <child> <parent> where <child> is a string represented the name of the child and <parent> is a string represented the name of the parent. The second block contains lines (terminated by a line containing ***), each line contains two string <cmd> and <param> where <cmd> is the command (which can be descendants or generation) and <param> is the given name of the person participating in the  query.
Output
Each line is the result of a corresponding query.
Example
Input
Peter Newman
Michael Thomas
John David
Paul Mark
Stephan Mark
Pierre Thomas
Mark Newman
Bill David
David Newman
Thomas Mark
***
descendants Newman
descendants Mark
descendants David
generation Mark
***
Output
10
5
2
2
*/

#include <bits/stdc++.h>
using namespace std;

// Hàm đệ quy để đếm số lượng hậu duệ
int countDescendants(const string& name, unordered_map<string, vector<string>>& children) {
    if (children.find(name) == children.end()) return 0; // Nếu không có hậu duệ nào
    int count = 0;
    for (const string& child : children[name]) {
        count += 1 + countDescendants(child, children);
    }
    return count;
}

// Hàm đệ quy để tìm số thế hệ của hậu duệ
int findGenerations(const string& name, unordered_map<string, vector<string>>& children) {
    if (children.find(name) == children.end()) return 0; // Nếu không có hậu duệ nào
    int maxGeneration = 0;
    for (const string& child : children[name]) {
        maxGeneration = max(maxGeneration, 1 + findGenerations(child, children));
    }
    return maxGeneration;
}

int main() {
    unordered_map<string, vector<string>> children; // Bản đồ lưu quan hệ cha-con
    string child, parent;

    // Đọc khối thông tin cha-con
    while (true) {
        cin >> child;
        if (child == "***") break;
        cin >> parent;
        children[parent].push_back(child);
    }

    string cmd, name;

    // Đọc khối các truy vấn
    while (true) {
        cin >> cmd;
        if (cmd == "***") break;
        cin >> name;

        if (cmd == "descendants") {
            cout << countDescendants(name, children) << endl;
        } else if (cmd == "generation") {
            cout << findGenerations(name, children) << endl;
        }
    }

    return 0;
}
