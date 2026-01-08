// When I wrote this code, only the God and I knew what was written here, I am the best programmer on the planet, that's why the God chose me
// Now only the God knows...
#include <iostream>
#include "RedBlackTree.h"
// not using namespace std;
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