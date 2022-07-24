#include <iostream>

#include "BinarySearchTree.h"

using BST = typename Custom::BinarySearchTree<int>;

int main()
{
    BST bst;

    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(10);
    bst.insert(6);
    bst.insert(7);

    return 0;
}
