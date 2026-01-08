//
// Created by DigitalMelquiades on 1/8/26.
//
#include <iostream>
#include "RedBlackTree.h"
#include "Node.h"

void RedBlackTree::inorder(Node* node) const {
    if (node == nullptr) return;
    inorder(node->left);
    std::cout<<node->value<<' ';
    inorder(node->right);
}
void RedBlackTree::preorder(Node* node) const {
    if (node == nullptr) return;
    std::cout<<node->value<<' ';
    preorder(node->left);
    preorder(node->right);
}
void RedBlackTree::postorder(Node* node) const {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    std::cout<<node->value<<' ';
}
bool RedBlackTree::search(const Node* node, const int& key) const {
    if (!node) return false;
    if (node->value == key) return true;
    if (key < node->value) return search(node->left, key);
    return search(node->right, key);
}
bool RedBlackTree::isRed(const Node* node) const { return node != nullptr && !node->isBlack; } // Implemented this helper function (n+1 helper function) because repeating code is bad practice as Mrs. Magda said
bool RedBlackTree::isBlack(const Node* node) const { return node == nullptr || node->isBlack; }
void RedBlackTree::fixInsert(Node* node) {
    while (node != root && isRed(node->parent)) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (isRed(uncle)) {
                colorflip(grandparent);
                node = grandparent;
            }
            else {
                if (node == parent->right) {
                    node = parent;
                    leftRotate(node);
                    parent = node->parent;
                }
                parent->isBlack = true;
                grandparent->isBlack = false;
                rightRotate(grandparent);
            }
        }
        else {
            Node* uncle = grandparent->left;
            if (isRed(uncle)) {
                colorflip(grandparent);
                node = grandparent;
            }
            else {
                if (node == parent->left) {
                    node = parent;
                    rightRotate(node);
                    parent = node->parent;
                }
                parent->isBlack = true;
                grandparent->isBlack = false;
                leftRotate(grandparent);
            }
        }
    }

    root->isBlack = true;
}
void RedBlackTree::fixDelete(Node* x, Node* parent) {
    while (x != root && isBlack(x)) {
        if (x == (parent ? parent->left : nullptr)) {

            Node* w = parent ? parent->right : nullptr;

            if (isRed(w)) {
                w->isBlack = true;
                parent->isBlack = false;
                leftRotate(parent);
                w = parent->right;
            }

            if (isBlack(w ? w->left : nullptr) && isBlack(w ? w->right : nullptr)) {
                if (w) w->isBlack = false;
                x = parent;
                parent = x ? x->parent : nullptr;
            }
            else {
                if (isBlack(w ? w->right : nullptr)) {
                    if (w && w->left) w->left->isBlack = true;
                    if (w) w->isBlack = false;
                    if (w) rightRotate(w);
                    w = parent ? parent->right : nullptr;
                }

                if (w) w->isBlack = parent ? parent->isBlack : true;
                if (parent) parent->isBlack = true;
                if (w && w->right) w->right->isBlack = true;
                if (parent) leftRotate(parent);
                x = root;
            }
        }
        else {
            Node* w = parent ? parent->left : nullptr;

            if (isRed(w)) {
                w->isBlack = true;
                parent->isBlack = false;
                rightRotate(parent);
                w = parent->left;
            }

            if (isBlack(w ? w->left : nullptr) && isBlack(w ? w->right : nullptr)) {
                if (w) w->isBlack = false;
                x = parent;
                parent = x ? x->parent : nullptr;
            }
            else {
                if (isBlack(w ? w->left : nullptr)) {
                    if (w && w->right) w->right->isBlack = true;
                    if (w) w->isBlack = false;
                    if (w) leftRotate(w);
                    w = parent ? parent->left : nullptr;
                }

                if (w) w->isBlack = parent ? parent->isBlack : true;
                if (parent) parent->isBlack = true;
                if (w && w->left) w->left->isBlack = true;
                if (parent) rightRotate(parent);
                x = root;
            }
        }
    }
    if (x) x->isBlack = true;
}
void RedBlackTree::deleteNode(Node* node) {
    Node* y = node;
    Node* x = nullptr;
    Node* xParent = nullptr;
    bool yOriginalBlack = y->isBlack;
    if (!node->left) {
        x = node->right;
        xParent = node->parent;
        transplant(node, node->right);
    }
    else if (!node->right) {
        x = node->left;
        xParent = node->parent;
        transplant(node, node->left);
    }
    else {
        y = minimum(node->right);
        yOriginalBlack = y->isBlack;
        x = y->right;
        if (y->parent == node) {
            xParent = y;
        } else {
            xParent = y->parent;
            transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
        y->isBlack = node->isBlack;
    }
    delete node;
    if (yOriginalBlack && root != nullptr) fixDelete(x, xParent);
}
Node* RedBlackTree::findNode(const int& key) {
    Node* current = root;
    while (current) {
        if (key == current->value) return current;
        if (key < current->value) current = current->left;
        else current = current->right;
    }
    return nullptr;
}
Node* RedBlackTree::copy(Node* node, Node* parent) {
    if (!node) return nullptr;
    Node* newNode = new Node(node->value);
    newNode->isBlack = node->isBlack;
    newNode->parent = parent;
    newNode->left = copy(node->left, newNode);
    newNode->right = copy(node->right, newNode);
    return newNode;
} // Using same recursive logic for copying as in ordering functions, recursion is op ngl
void RedBlackTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
} // There are countless helper functions, but only because I use recursive approach, and I cannot call root on main methods, user does not have access on root
Node* RedBlackTree::minimum(Node* node) {
    while (node && node->left) node = node->left;
    return node;
} // Defined this so when deleted a node we can find its successor
RedBlackTree::RedBlackTree() : root(nullptr) {}
RedBlackTree::RedBlackTree(const RedBlackTree& other) { root = copy(other.root, nullptr); }
RedBlackTree::~RedBlackTree(){ clear(root); root = nullptr; }
void RedBlackTree::leftRotate(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left) rightChild->left->parent = node;
    rightChild->parent = node->parent;
    if (!node->parent) root = rightChild;
    else if (node == node->parent->left) node->parent->left = rightChild;
    else node->parent->right = rightChild;
    rightChild->left = node;
    node->parent = rightChild;
}
void RedBlackTree::rightRotate(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right) leftChild->right->parent = node;
    leftChild->parent = node->parent;
    if (!node->parent) root = leftChild;
    else if (node == node->parent->right) node->parent->right = leftChild;
    else node->parent->left = leftChild;
    leftChild->right = node;
    node->parent = leftChild;
}
void RedBlackTree::transplant(Node* node, Node* v) {
    if (!node->parent) root = v;
    else if (node == node->parent->left) node->parent->left = v;
    else node->parent->right = v;
    if (v) v->parent = node->parent;
}
void RedBlackTree::insert(const int& value) {
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
void RedBlackTree::deleteNode(const int& value) {
    Node* node = findNode(value);
    if (node) deleteNode(node);
}
bool RedBlackTree::search(const int& key) const { return search(root,key); }
bool RedBlackTree::searchIt(const int& key) {
    Node* current = root;
    while (current) {
        if (key == current->value) return true;
        if (key < current->value) current = current->left;
        else current = current->right;
    }
    return false;
}
void RedBlackTree::colorflip(Node* grandparent) {
    if (!grandparent) return;
    grandparent->isBlack = false;
    if (grandparent->left)  grandparent->left->isBlack = true;
    if (grandparent->right) grandparent->right->isBlack = true;
}
void RedBlackTree::inorder() const { inorder(root); }
void RedBlackTree::preorder() const { preorder(root); }
void RedBlackTree::postorder() const { postorder(root); }
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other) {
    if (this != &other) {
        Node* newRoot = copy(other.root, nullptr);
        clear(root);
        root = newRoot;
    }
    return *this;
}
Node* RedBlackTree::insertRec(Node* node, Node* parent, const int& value, Node*& insertedNode) {
    if (!node) {
        insertedNode = new Node(value);
        insertedNode->parent = parent;
        return insertedNode;
    }
    if (value < node->value) node->left = insertRec(node->left, node, value, insertedNode);
    else if (value > node->value) node->right = insertRec(node->right, node, value, insertedNode);
    else return node;
    return node;
}
void RedBlackTree::insertRec(const int& value) {
    Node* inserted = nullptr;
    root = insertRec(root, nullptr, value, inserted);
    if (inserted) fixInsert(inserted);
}