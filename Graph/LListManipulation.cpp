/*
Description
Viết chương trình thực hiện công việc sau:
Xây dựng danh sách liên kết với các khóa được cung cấp ban đầu là dãy a
1
, a
2
, …, a
n
, sau đó thực hiện các thao tác trên danh sách bao gồm: thêm 1 phần tử vào đầu, vào cuối danh sách, hoặc vào trước, vào sau 1 phần tử nào đó trong danh sách, hoặc loại bỏ 1 phần tử nào đó trong danh sách

Input
Dòng 1: ghi số nguyên dương n (1 <= n <= 1000)
Dòng 2: ghi các số nguyên dương a
1
, a
2
, …, a
n
.
Các dòng tiếp theo lần lượt là các lệnh để thao tác (kết thúc bởi ký hiệu #) với các loại sau:
addlast  k: thêm phần tử có key bằng k vào cuối danh sách (nếu k chưa tồn tại)
addfirst  k: thêm phần tử có key bằng k vào đầu danh sách (nếu k chưa tồn tại)
addafter  u  v: thêm phần tử có key bằng u vào sau phần tử có key bằng v trên danh sách (nếu v đã tồn tại trên danh sách và u chưa tồn tại)
addbefore  u  v: thêm phần tử có key bằng  u vào trước phần tử có key bằng v trên danh sách (nếu v đã tồn tại trên danh sách và u của tồn tại)
remove  k: loại bỏ phần tử có key bằng k khỏi danh sách
reverse: đảo ngược thứ tự các phần tử của danh sách (không được cấp phát mới các phần tử, chỉ được thay đổi mối nối liên kết)
Output
Ghi ra dãy khóa của danh sách thu được sau 1 chuỗi các lệnh thao tác đã cho

Example
Input
5
5 4 3 2 1
addlast 3
addlast 10
addfirst 1
addafter 10 4
remove 1
#

Output
5 4 3 2 10 
*/

#include<bits/stdc++.h>
using namespace std;

typedef struct Node{
    int key;
    struct Node* next;
}Node;

Node* createNode(int key)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

bool keyExists(Node* head, int key)
{
    Node* current = head;
    while (current != NULL) {
        if (current->key == key)
            return true;
        current = current->next;
    }
    return false;
}

void addFirst(Node** head, int key)
{
    if (keyExists(*head, key))
        return;
    Node* newNode = createNode(key);
    newNode->next = *head;
    *head = newNode;
}

void addLast(Node** head, int key)
{
    if (keyExists(*head, key))
        return;
    Node* newNode = createNode(key);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void addAfter(Node* head, int newKey, int existingKey)
{
    if (keyExists(head, newKey))
        return;
    Node* temp = head;
    while (temp != NULL && temp->key != existingKey) {
        temp = temp->next;
    }
    if (temp != NULL) {
        Node* newNode = createNode(newKey);
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void addBefore(Node** head, int newKey, int existingKey)
{
    if (keyExists(*head, newKey))
        return;
    if (*head == NULL)
        return;
    if ((*head)->key == existingKey) {
        addFirst(head, newKey);
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL && temp->next->key != existingKey) {
        temp = temp->next;
    }
    if (temp->next != NULL) {
        Node* newNode = createNode(newKey);
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void removeNode(Node** head, int key)
{
    if (!keyExists(*head, key))
        return;
    Node *temp = *head, *prev = NULL;
    if (temp != NULL && temp->key == key) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

void reverseList(Node** head)
{
    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void printList(Node* head)
{
    Node* temp = head;
    while (temp != NULL) {
        cout<<temp->key<<" ";
        temp = temp->next;
    }
    cout<<'\n';
}

int main()
{
    Node* head = NULL;
    int n, key;
    string cmd;
    int u, v;

    // Read initial list elements
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin>>key;
        addLast(&head, key);
    }

    // Process commands
    while (true) {
        cin>>cmd;
        if (cmd=="#") break;

        if (cmd=="addlast") {
            cin>>key;
            addLast(&head, key);
        } else if (cmd == "addfirst") {
            cin>>key;
            addFirst(&head, key);
        } else if (cmd=="addafter") {
            cin>>u>>v;
            addAfter(head, u, v);
        } else if (cmd=="addbefore") {
            cin>>u>>v;
            addBefore(&head, u, v);
        } else if (cmd=="remove") {
            cin>>key;
            removeNode(&head, key);
        } else if (cmd=="reverse") {
            reverseList(&head);
        }
    }

    printList(head);

    return 0;
}