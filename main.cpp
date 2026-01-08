#include <iostream>
#include "Node.h"
// not using namespace std;
class RedBlackTree {
    Node* root;
    void inorder(Node* node) const {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout<<node->value<<' ';
        inorder(node->right);
    }
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
    bool search(const Node* node, const int& key) const {
        if (!node) return false;
        if (node->value == key) return true;
        if (key < node->value) return search(node->left, key);
        return search(node->right, key);
    }
    bool isRed(const Node* node) { return node && !node->isBlack; } // Implemented this helper function (n+1 helper function) because repeating code is bad practice as Mrs. Magda said
    void fixInsert(Node* node) {
        while (node != root && isRed(node->parent)) {
            Node* parent = node->parent;
            Node* grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (isRed(uncle)) {
                    parent->isBlack = true;
                    uncle->isBlack = true;
                    grandparent->isBlack = false;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        node = parent;
                        leftRotate(node);
                    }
                    parent->isBlack = true;
                    grandparent->isBlack = false;
                    rightRotate(grandparent);
                }
            } else {
                Node* uncle = grandparent->left;
                if (isRed(uncle)) {
                    parent->isBlack = true;
                    uncle->isBlack = true;
                    grandparent->isBlack = false;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        node = parent;
                        rightRotate(node);
                    }
                    parent->isBlack = true;
                    grandparent->isBlack = false;
                    leftRotate(grandparent);
                }
            }
        }
        root->isBlack = true;
    }
    Node* copy(Node* node, Node* parent) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->value);
        newNode->isBlack = node->isBlack;
        newNode->parent = parent;
        newNode->left = copy(node->left, newNode);
        newNode->right = copy(node->right, newNode);
        return newNode;
    } // Using same recursive logic for copying as in ordering functions, recursion is op ngl
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    } // There are countless helper functions, but only because I use recursive approach, and I cannot call root on main methods, user does not have access on root
public:
    RedBlackTree() : root(nullptr) {}
    RedBlackTree(const RedBlackTree& other) { root = copy(other.root, nullptr); }
    ~RedBlackTree(){ clear(root); }
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
    void insert(const int& value) {
        Node* newNode = new Node(value);
        Node* parent = nullptr;
        Node* current = root;
        while (current) {
            parent = current;
            if (value < current->value) current = current->left;
            else if (value > current->value) current = current->right;
            else { delete newNode; return; }
        }
        newNode->parent = parent;
        if (!parent) root = newNode;
        else if (value < parent->value) parent->left = newNode;
        else parent->right = newNode;
        fixInsert(newNode);
    }
    bool search(const int& key) const { return search(root,key); }
    void inorder() const { inorder(root); } // I will implement my own display order approach, because fuck you
    void preorder() const { preorder(root); }
    void postorder() const { postorder(root); }
};

int main() {
    return 0;
}
