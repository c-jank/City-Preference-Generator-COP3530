#include <iostream>
#include <vector>

using namespace std;

class SplayTree {
    struct Node {
        int score;
        Node *left, *right;

        Node(int key) {
            left = nullptr;
            right = nullptr;
            score = key;
        }
    };

    Node *NewNode(int score) {
        Node *node = new Node(score);
        return node;
    }

    Node *LeftRotate(Node *old) {
        Node* replacement = old->right;
        old->right = replacement->left;
        replacement->left = old;
        return replacement;
    }

    Node *RightRotate(Node *old) {
        Node* replacement = old->left;
        old->left = replacement->right;
        replacement->right = old;
        return replacement;
    }

    Node* Splay(Node* root, int score) {
        if (root == nullptr) {
            return root;
        }
        if (root->score < score) {
            if (root->right == nullptr)
                return root;
            if (root->right->score > score) {
                root->right->left = Splay(root->right->left, score);
                if (root->right->left != nullptr)
                    root->right = RightRotate(root->right);
            }
            else if (root->right->score < score) {
                root->right->right = Splay(root->right->right, score);
                root = LeftRotate(root);
            }
            return (root->right == nullptr) ? root : LeftRotate(root);
        }
        else {
            if (root->left == nullptr) {
                return root;
            }
            if (root->left->score > score) {
                root->left->left = Splay(root->left->left, score);
                root = RightRotate(root);
            }
            else if (root->left->score < score) {
                root->left->right = Splay(root->left->right, score);
                if (root->left->right != nullptr)
                    root->left = LeftRotate(root->left);
            }
            return (root->left == nullptr) ? root : RightRotate(root);
        }
    }
public:
    Node* Insert(Node* root, int score) {
        if (root == nullptr) {
            return NewNode(score);
        }
        root = Splay(root, score);
        Node* new_node = NewNode(score);
        Node* node = NewNode(score);
        if (root->score < score) {
            node->left = root;
            node->right = root->right;
            root->right = nullptr;
        }
        else {
            node->right = root;
            node->left = root->left;
            root->left = nullptr;
        }
        return node;
    }

    vector<Node*> PreOrderHelper(Node* root, vector<Node*> nodes, int results) {
        if (root != nullptr && nodes.size() < results) {
            nodes.push_back(root);
            PreOrderHelper(root->left, nodes, results);
            PreOrderHelper(root->right, nodes, results);
        }
        return nodes;
    }

    vector<Node*> PreOrder(int results) {
        vector<Node*> nodes;
        nodes = PreOrderHelper(this->root, nodes, results);
    }
    Node* root;
    SplayTree() {
        root = nullptr;
    }
};