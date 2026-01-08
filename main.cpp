// When I wrote this code, only the God and I knew what was written here, I am the best programmer on the planet, that's why the God chose me
// Now only the God knows...
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
    bool isBlack(const Node* node) { return node && node->isBlack; }
    void fixInsert(Node* node) {
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
    void fixDelete(Node* x, Node* parent) {
        while (x != root && isBlack(x)) {
            if (x == parent->left) {
                Node* w = parent->right;

                if (!isBlack(w)) {
                    w->isBlack = true;
                    parent->isBlack = false;
                    leftRotate(parent);
                    w = parent->right;
                }

                if (isBlack(w->left) && isBlack(w->right)) {
                    w->isBlack = false;
                    x = parent;
                    parent = x->parent;
                } else {
                    if (isBlack(w->right)) {
                        w->left->isBlack = true;
                        w->isBlack = false;
                        rightRotate(w);
                        w = parent->right;
                    }

                    w->isBlack = parent->isBlack;
                    parent->isBlack = true;
                    w->right->isBlack = true;
                    leftRotate(parent);
                    x = root;
                }
            }
            else {
                Node* w = parent->left;

                if (!isBlack(w)) {
                    w->isBlack = true;
                    parent->isBlack = false;
                    rightRotate(parent);
                    w = parent->left;
                }

                if (isBlack(w->left) && isBlack(w->right)) {
                    w->isBlack = false;
                    x = parent;
                    parent = x->parent;
                } else {
                    if (isBlack(w->left)) {
                        w->right->isBlack = true;
                        w->isBlack = false;
                        leftRotate(w);
                        w = parent->left;
                    }

                    w->isBlack = parent->isBlack;
                    parent->isBlack = true;
                    w->left->isBlack = true;
                    rightRotate(parent);
                    x = root;
                }
            }
        }
        if (x) x->isBlack = true;
    }
    void deleteNode(Node* node) {
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
        if (yOriginalBlack) fixDelete(x, xParent);
    }
    Node* findNode(const int& key) {
        Node* current = root;
        while (current) {
            if (key == current->value) return current;
            if (key < current->value) current = current->left;
            else current = current->right;
        }
        return nullptr;
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
    Node* minimum(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    } // Defined this so when deleted a node we can find its successor
public:
    RedBlackTree() : root(nullptr) {}
    RedBlackTree(const RedBlackTree& other) { root = copy(other.root, nullptr); }
    ~RedBlackTree(){ clear(root); }
    void leftRotate(Node* node) {
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
    void rightRotate(Node* node) {
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
    void transplant(Node* node, Node* v) {
        if (!node->parent) root = v;
        else if (node == node->parent->left) node->parent->left = v;
        else node->parent->right = v;
        if (v) v->parent = node->parent;
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
    void deleteNode(const int& value) {
        Node* node = findNode(value);
        if (node) deleteNode(node);
    }
    bool search(const int& key) const { return search(root,key); }
    bool searchIt(const int& key) {
        Node* current = root;
        while (current) {
            if (key == current->value) return true;
            if (key < current->value) current = current->left;
            else current = current->right;
        }
        return false;
    }
    void colorflip(Node* grandparent) {
        grandparent->isBlack = false;
        if (grandparent->left) grandparent->left->isBlack = true;
        if (grandparent->right) grandparent->right->isBlack = true;
    }
    void inorder() const { inorder(root); }
    void preorder() const { preorder(root); }
    void postorder() const { postorder(root); }
    RedBlackTree& operator=(const RedBlackTree& other);
};

RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root, nullptr);
    }
    return *this;
}

int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);

    std::cout << "Inorder: ";
    tree.inorder();

    std::cout << "\nPreorder: ";
    tree.preorder();

    std::cout << "\nPostorder: ";
    tree.postorder();

    tree.deleteNode(5);
    tree.deleteNode(25);
    std::cout<<"\nAfter deletion: ";
    tree.inorder();

    std::cout << "\nSearch 15: " << (tree.search(15) ? "Found":"Not Found");
    std::cout << "\nSearch 15: " << (tree.searchIt(15) ? "Found":"Not Found");
    std::cout << "\nSearch 99: " << (tree.search(99) ? "Found":"Not Found");
    std::cout << "\nSearch 99: " << (tree.searchIt(99) ? "Found":"Not Found");

    RedBlackTree copy = tree;
    std::cout << "\nCopied tree inorder: ";
    copy.inorder();
    return 0;
}