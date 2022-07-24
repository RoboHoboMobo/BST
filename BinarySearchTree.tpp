#include "BinarySearchTree.h"

namespace Custom {

template <typename T>
BinarySearchTree<T>::Node::Node()
    : data{}
    , parent{}
    , leftChild{}
    , rightChild{}
{
}

template <typename T>
BinarySearchTree<T>::Node::Node(const T& value)
    : data{value}
    , parent{}
    , leftChild{}
    , rightChild{}
{
}

template <typename T>
void BinarySearchTree<T>::Node::erase()
{
    delete leftChild;
    leftChild = nullptr;

    delete rightChild;
    rightChild = nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
    : m_root{}
    , m_size{}
{
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& bst)
    : m_root{}
    , m_size{}
{
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& bst)
{
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
}

template <typename T>
inline bool BinarySearchTree<T>::empty() const
{
    return m_size;
}

template <typename T>
inline size_t BinarySearchTree<T>::size() const
{
    return m_size;
}

template <typename T>
void BinarySearchTree<T>::insert(const T& value)
{
    Node* newNode = new Node(value);

    if (!m_root) {
        m_root = newNode;

        return;
    }

    Node* current = m_root;
    Node* parent{};

    while (current) {
        parent = current;

        if (value < current->data)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    newNode->parent = parent;

    if (value < parent->data)
        parent->leftChild = newNode;
    else
        parent->rightChild = newNode;

}

template <typename T>
void BinarySearchTree<T>::erase(const T& value)
{
    Node* node = find(value);

    if (!node)
        return;

    Node* parent = node->parent;
    Node* leftChild = node->leftChild;
    Node* rightChild = node->rightChild;

/*
    if (!leftChild && !rightChild) {
        if (node == m_root)
            m_root = {};
        else {
            if (node == parent->leftChild)
                parent->leftChild = {};
            else
                parent->rightChild = {};
        }

        delete node;

        return;
    }
*/

    if (!leftChild) {
        if (node == m_root) {
            m_root = rightChild;
            m_root->parent = {};
        }
        else {
            if (node == parent->leftChild)
                parent->leftChild = rightChild;
            else
                parent->rightChild = rightChild;

            if (rightChild)
                rightChild->parent = parent;
        }

        delete node;

        return;
    }

    if (leftChild && !rightChild) {
        if (node == m_root) {
            m_root = leftChild;
            m_root->parent = {};
        }
        else {
            if (node == parent->leftChild)
                parent->leftChild = leftChild;
            else
                parent->rightChild = leftChild;

            leftChild->parent = parent;
        }

        delete node;

        return;
    }

    Node* successor = min(rightChild);
    Node* oldRightChild = successor->rightChild;

    successor->rightChild = rightChild;
    rightChild->parent = successor;

    rightChild->leftChild = oldRightChild;
    oldRightChild->parent = rightChild;

    successor->leftChild = leftChild;
    leftChild->parent = successor;

    if (node == m_root) {
        m_root = successor;
        m_root->parent = {};
    }
    else {
        if (node == parent->leftChild)
            parent->leftChild = successor;
        else
            parent->rightChild = successor;

        successor->parent = parent;
    }

    delete node;

    return;
}

template <typename T>
void BinarySearchTree<T>::swap(BinarySearchTree& bst)
{
}

template <typename T>
void BinarySearchTree<T>::clear()
{
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::find(const T&) const
{
    return {};
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::min(Node* node)
{
    if (!node)
        return {};

    Node* result = node;

    while (result->leftChild)
        result = result->leftChild;

    return result;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::max(Node* node)
{
    if (!node)
        return {};

    Node* result = node;

    while (result->rightChild)
        result = result->rightChild;

    return result;
}


}
