//
// Created by Digital Melquiades on 1/7/26.
//

#ifndef REDBLACKTREE_NODE_H
#define REDBLACKTREE_NODE_H
class Node {
    friend class RedBlackTree;
private:
    int value;
    bool isBlack;
    bool isLeftChild;
    Node* parent;
    Node* left;
    Node* right;
public:
    // Constructor
    Node() : value(0), isBlack(false), isLeftChild(false), left(nullptr), right(nullptr), parent(nullptr) {}
    void makeBlack() { isBlack = true; }
};
#endif //REDBLACKTREE_NODE_H