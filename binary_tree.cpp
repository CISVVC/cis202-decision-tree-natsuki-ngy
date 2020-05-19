//SOLUTION
#include <algorithm>
#include "binary_tree.h"

using namespace std;

Binary_tree::Binary_tree()
{
    root = nullptr;
}

Binary_tree::Binary_tree(string root_data)
{
    root = new Node;
    root->data = root_data;
    root->left = nullptr;
    root->right = nullptr;
}

Binary_tree::Binary_tree(string root_data, Binary_tree left, Binary_tree right)
{
    root = new Node;
    root->data = root_data;
    root->left = left.root;
    root->right = right.root;
}

int Binary_tree::height(const Node* n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + max(height(n->left), height(n->right));
    }
}

int Binary_tree::height() const
{
    return height(root);
}

bool Binary_tree::empty() const
{
    return root == nullptr;
}

string Binary_tree::data() const
{
    return root->data;
}

Binary_tree Binary_tree::left() const
{
    Binary_tree result;
    result.root = root->left;
    return result;
}

Binary_tree Binary_tree::right() const
{
    Binary_tree result;
    result.root = root->right;
    return result;
}

void Binary_tree::set(string question, Binary_tree current_tree, Binary_tree new_tree)
{
    string temp = current_tree.root->data; 
    current_tree.root->data = question;
    current_tree.root->left = new_tree.root;

    Node *right = new Node;
    right->data = temp;
    right->right = nullptr;
    right->left = nullptr;

    current_tree.root->right = right;
}


