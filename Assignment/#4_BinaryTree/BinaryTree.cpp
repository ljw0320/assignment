#include <iostream>

struct Node 
{
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* Insert(Node* root, int key)
{
    if (!root) return new Node(key);
    if (key < root->key)
        root->left = Insert();
}

int main()
{
    
}

