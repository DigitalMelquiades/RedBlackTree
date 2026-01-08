//
// Created by DigitalMelquiades on 1/8/26.
//

#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H
#include "Node.h"

class RedBlackTree {
    Node* root;
    void inorder(Node* node) const;
    void preorder(Node* node) const;
    void postorder(Node* node) const;
    bool search(const Node* node, const int& key) const;
    bool isRed(const Node* node);
    bool isBlack(const Node* node);
    void fixInsert(Node* node);
    void fixDelete(Node* x, Node* parent);
    void deleteNode(Node* node);
    Node* findNode(const int& key);
    Node* copy(Node* node, Node* parent);
    void clear(Node* node);
    Node* minimum(Node* node);
public:
    RedBlackTree();
    RedBlackTree(const RedBlackTree& other);
    ~RedBlackTree();
    void leftRotate(Node* node);
    void rightRotate(Node* node);
    void transplant(Node* node, Node* v);
    void insert(const int& value);
    void deleteNode(const int& value);
    bool search(const int& key) const;
    bool searchIt(const int& key);
    void colorflip(Node* grandparent);
    void inorder() const;
    void preorder() const;
    void postorder() const;
    RedBlackTree& operator=(const RedBlackTree& other);
};

#endif //REDBLACKTREE_REDBLACKTREE_H