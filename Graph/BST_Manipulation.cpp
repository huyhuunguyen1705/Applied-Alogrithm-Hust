/*
Description
Given a BST initialized by NULL. Perform a sequence of operations on a BST including:
insert k: insert a key k into the BST (do not insert if the key k exists)
Input
•Each line contains command under the form: “insert k”
•The input is terminated by a line containing #
Output
•Write the sequence of keys of nodes visited by the pre-order traversal (separated by a SPACE character)
Example
Input
insert 20
insert 10
insert 26
insert 7
insert 15
insert 23
insert 30
insert 3
insert 8
#
Output
20 10 7 3 8 15 26 23 30
*/

#include<bits/stdc++.h>
using namespace std;

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* newNode(int id)
{
    Node* temp = new Node;
    temp->key = id;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node* node, int key)
{
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

void preOrder(Node* root)
{
    if (root != NULL) {
        cout<<root->key<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    Node* root = NULL;
    string cmd;
    int key;

    while (true) {
        cin>>cmd;
        if (cmd=="#") break; 
        else if(cmd=="insert"){
            cin>>key;
            root = insert(root, key);
        }
    }

    preOrder(root);

    return 0;
}
