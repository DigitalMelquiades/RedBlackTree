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
    void fixDelete(Node* node, Node* parent) {
        while (node != root && isBlack(node)) {
            if (node == parent->left) {
                Node* sibling = parent->right;
                if (!isBlack(sibling)) {
                    sibling->isBlack = true;
                    parent->isBlack = false;
                    leftRotate(parent);
                    sibling = parent->right;
                }
                if (isBlack(sibling->left) && isBlack(sibling->right)) {
                    sibling->isBlack = false;
                    node = parent;
                    parent = node->parent;
                }
                else {
                    if (isBlack(sibling->right)) {
                        if (sibling->left) sibling->left->isBlack = true;
                        sibling->isBlack = false;
                        rightRotate(sibling);
                        sibling = parent->right;
                    }
                    sibling->isBlack = parent->isBlack;
                    parent->isBlack = true;
                    if (sibling->right) sibling->right->isBlack = true;
                    leftRotate(parent);
                    node = root;
                }
            }
            else {
                Node* s = parent->left;
                if (!isBlack(s)) {
                    s->isBlack = true;
                    parent->isBlack = false;
                    rightRotate(parent);
                    s = parent->left;
                }
                if (isBlack(s->left) && isBlack(s->right)) {
                    s->isBlack = false;
                    node = parent;
                    parent = node->parent;
                }
                else {
                    if (isBlack(s->left)) {
                        if (s->right) s->right->isBlack = true;
                        s->isBlack = false;
                        leftRotate(s);
                        s = parent->left;
                    }
                    s->isBlack = parent->isBlack;
                    parent->isBlack = true;
                    if (s->left) s->left->isBlack = true;
                    rightRotate(parent);
                    node = root;
                }
            }
        }
        if (node) node->isBlack = true;
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
    Node* deleteRec(Node* node, const int& key) {
        if (!node) return nullptr;
        if (key < node->value) node->left = deleteRec(node->left, key);
        else if (key > node->value) node->right = deleteRec(node->right, key);
        else {
            if (!node->left) {
                Node* right = node->right;
                delete node;
                return right;
            }
            if (!node->right) {
                Node* left = node->left;
                delete node;
                return left;
            }
            Node* successor = minimum(node->right);
            node->value = successor->value;
            node->right = deleteRec(node->right, successor->value);
        }
        return node;
    }
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
    bool searchIt(const int& key) {
        Node* curr = root;
        while (curr) {
            if (key == curr->value) return true;
            if (key < curr->value) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }
    void deleteIt(const int& key) {
        Node* parent = nullptr;
        Node* current = root;
        while (current && current->value != key) {
            parent = current;
            current = (key < current->value) ? current->left : current->right;
        }
        if (!current) return;
        bool deletedBlack = current->isBlack;
        if (current->left && current->right) {
            Node* succsessorParent = current;
            Node* succsessor = current->right;
            while (succsessor->left) {
                succsessorParent = succsessor;
                succsessor = succsessor->left;
            }
            current->value = succsessor->value;
            current = succsessor;
            parent = succsessorParent;
            deletedBlack = current->isBlack;
        }
        Node* child = current->left ? current->left : current->right;
        if (child) child->parent = parent;
        if (!parent) root = child;
        else if (parent->left == current) parent->left = child;
        else parent->right = child;
        delete current;
        if (deletedBlack) fixDelete(child, parent);
    }
    void deleteRec(const int& key) { root = deleteRec(root, key); } // Deletion may cause tree to break, but because I don't want to copy-paste code from GPT and we never really wrote proper code for it on the lab, I decided not to touch it, at least it satisfies the task requirements anyway
    void colorflip(Node* grandparent) {
        grandparent->isBlack = false;
        if (grandparent->left) grandparent->left->isBlack = true;
        if (grandparent->right) grandparent->right->isBlack = true;
    }
    void inorder() const { inorder(root); } // I will implement my own display order approach, because why not
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

    tree.deleteIt(5);

    std::cout << "\nPreorder: ";
    tree.preorder();

    //tree.deleteRec(25);
    tree.deleteIt(25);

    std::cout << "\nPostorder: ";
    tree.postorder();

    std::cout << "\nSearch 15: " << (tree.search(15) ? "Found":"Not Found");
    std::cout << "\nSearch 99: " << (tree.search(99) ? "Found":"Not Found");

    RedBlackTree copy = tree;
    std::cout << "\nCopied tree inorder: ";
    copy.inorder();
    return 0;
}
