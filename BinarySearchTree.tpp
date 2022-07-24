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
BinarySearchTree<T>::Node::Node(const T& key)
    : data{key}
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
    Node* root = bst.m_root;

    Node* node = copy(root, {}, m_size);

    while (node->parent)
        node = node->parent;

    m_root = node;
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& lhs)
{
    if (lhs.m_root == m_root)
        return *this;

    clear();

    Node* lhsRoot = lhs.m_root;
    Node* node = copy(lhsRoot, {}, m_size);

    while (node->parent)
        node = node->parent;

    m_root = node;

    return *this;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    clear();
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
void BinarySearchTree<T>::insert(const T& key)
{
    ++m_size;

    Node* newNode = new Node(key);

    if (!m_root) {
        m_root = newNode;

        return;
    }

    Node* current = m_root;
    Node* parent{};

    while (current) {
        parent = current;

        if (key < current->data)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    newNode->parent = parent;

    if (key < parent->data)
        parent->leftChild = newNode;
    else
        parent->rightChild = newNode;
}

template <typename T>
void BinarySearchTree<T>::erase(const T& key)
{
    Node* node = find(key);

    if (!node)
        return;

    --m_size;

    Node* parent = node->parent;
    Node* leftChild = node->leftChild;
    Node* rightChild = node->rightChild;

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

    Node* successor = getSuccessor(node);
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
void BinarySearchTree<T>::clear()
{
    clear(m_root);

    delete m_root;
    m_root = {};

    m_size = 0;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::find(const T& key) const
{
    Node* current = m_root;

    while (current) {
        if (key == current->data)
            return current;

        if (key < current->data)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

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

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::getSuccessor(Node* node)
{
    if (!node)
        return {};

    if (node->rightChild)
        return min(node->rightChild);

    Node* current = node;
    Node* parent = node->parent;

    while (parent && current == parent->rightChild) {
        current = parent;
        parent = current->parent;
    }

    return parent;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::getPredecessor(Node* node)
{
    if (!node)
        return {};

    if (node->leftChild)
        return max(node->leftChild);

    Node* current = node;
    Node* parent = node->parent;

    while (parent && current == parent->leftChild) {
        current = parent;
        parent = current->parent;
    }

    return parent;
}

template <typename T>
void BinarySearchTree<T>::clear(Node* node)
{
    Node* current = node;

    if (!node)
        return;

    clear(current->leftChild);
    clear(current->rightChild);
    current->erase();
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::copy(Node* node, Node* parent,
                                                              size_t& counter)
{
    if (!node)
        return {};

    ++counter;

    Node* current = new Node(node->data);
    current->parent = parent;

    copy(node->leftChild, current, counter);
    copy(node->rightChild, current, counter);

    return current;
}


}
