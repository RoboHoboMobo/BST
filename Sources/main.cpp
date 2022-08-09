#include <iostream>
#include <vector>

#include "BinarySearchTree.h"

template <typename T>
bool isLeaf(const typename Custom::BinarySearchTreeNode<T>* node)
{
    return node && !node->leftChild && !node->rightChild;
}

template <typename T>
std::vector<T> getLeafs(const Custom::BinarySearchTree<T>& bst)
{
    std::vector<T> result;

    for (auto it = bst.cbegin(); it != bst.cend(); ++it) {
        if (isLeaf(it.get()))
            result.emplace_back(*it);
    }

    return result;
}

template <typename T>
void getLeafsRecursively(const typename Custom::BinarySearchTree<T>::Node* node,
                         std::vector<T>& nodeList)
{
    if (!node)
        return;

    if (isLeaf(node))
        nodeList.push_back(node->data);

    getLeafsRecursively(node->leftChild, nodeList);
    getLeafsRecursively(node->rightChild, nodeList);
}

template <typename T>
void getLeafsRecursively(const typename Custom::BinarySearchTree<const T>::Node* node,
                         std::vector<T>& nodeList)
{
    if (!node)
        return;

    if (isLeaf<const T>(node))
        nodeList.push_back(node->data);

    getLeafsRecursively(node->leftChild, nodeList);
    getLeafsRecursively(node->rightChild, nodeList);
}

using BST = Custom::BinarySearchTree<int>;

int main()
{
    const BST bst{10, 5, 21, 2, 7, 15, 25, 1, 3, 11, 17, 32};

    /*                 10
     *               /    \
     *              5      21
     *            / \     /  \
     *           2   7   15   25
     *          / \     /  \   \
     *         1   3   11  17  32
     */

    const std::vector<int> leafs = getLeafs(bst);

    // for (auto leaf : leafs)
    //     std::cout << leaf << std::endl;

    std::vector<int> leafsRec;
    getLeafsRecursively(bst.getRoot(), leafsRec);

    for (auto leaf : leafsRec)
        std::cout << leaf << std::endl;

    return 0;
}
