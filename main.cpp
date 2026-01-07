#include <iostream>
#include "Node.h"

class RedBlackTree {
    Node* root;
    void inorder(Node* node) const {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout<<node->value<<' ';
        inorder(node->right);
    } // I had to implement them as private methods, because I cannot pass root as an argument in driver
    void preorder(Node* node) const {
        if (node == nullptr) return;
        std::cout<<node->value<<' ';
        preorder(node->left);
        preorder(node->right);
    }
    void postorder(Node* node) const {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        std::cout<<node->value<<' ';
    }
public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree(){}
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left) y->left->parent = x;
        y->parent = x->parent;

        if (!x->parent)root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right) y->right->parent = x;
        y->parent = x->parent;

        if (!x->parent) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;

        y->right = x;
        x->parent = y;
    }
    bool search(Node* n, int key) const {
        if (!n || n->value == key) return true;
        if (key < n->value) return search(n->left, key);
        if (key > n->value) return search(n->right, key);
        return false;
    }
    void insert(Node* node) {

    }
};


int main() {
    return 0;
}
