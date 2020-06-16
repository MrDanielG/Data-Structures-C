#include <iostream>
#include <vector>
using namespace std;

// Data structure to store a Binary Tree node
struct Node
{
    int data;
    Node *left, *right;
};

// Function to create a new binary tree node having given key
Node* newNode(int key)
{
    Node* node = new Node;
    node->data = key;
    node->left = node->right = nullptr;

    return node;
}

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void printTree(Node *root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;
    
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->left, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->data << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->right, trunk, false);
}

// Function to insert given key into the tree
void insert(Node*& root, string level, int key)
{
    // tree is empty
    if (level.length() == 0)
    {
        root = newNode(key);
        return;
    }

    int i = 0;
    Node* ptr = root;
    while (i < level.length() - 1)
    {
        if (level[i++] == 'L')
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }

    if (level[i] == 'L')
        ptr->left = newNode(key);
    else
        ptr->right = newNode(key);
}

// main function
int main()
{
    Node* root = nullptr;

    // Construct above tree
    vector<pair<string, int> > keys =
    {
        {"", 1}, {"L", 2}, {"R", 3}, {"LL", 4}, {"LR", 5}, {"RL", 6},
        {"RR", 7}, {"LLL", 8}, {"LLR", 9}, {"LRL", 10}, {"LRR", 11},
        {"RLL", 12}, {"RLR", 13}, {"RRL", 14}, {"RRR", 15}
    };

    for (auto pair: keys)
        insert(root, pair.first, pair.second);
    
    // print constructed binary tree
    printTree(root, nullptr, false);

    return 0;
}