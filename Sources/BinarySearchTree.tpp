#include "BinarySearchTree.h"

#include <iostream>

namespace Custom {

template <typename ValueType>
BinarySearchTreeNode<ValueType>::BinarySearchTreeNode()
    : data{}
    , parent{}
    , leftChild{}
    , rightChild{}
{
}

template <typename ValueType>
BinarySearchTreeNode<ValueType>::BinarySearchTreeNode(const ValueType& key)
    : data{key}
    , parent{}
    , leftChild{}
    , rightChild{}
{
}

template <typename ValueType>
void BinarySearchTreeNode<ValueType>::erase()
{
    delete leftChild;
    leftChild = nullptr;

    delete rightChild;
    rightChild = nullptr;
}

template <typename ValueType>
BinarySearchTreeNode<ValueType>* BinarySearchTreeNode<ValueType>::min()
{
    const auto* constThis = this;

    return const_cast<BinarySearchTreeNode<ValueType>*>(constThis->min());
}
template <typename ValueType>
BinarySearchTreeNode<ValueType>* BinarySearchTreeNode<ValueType>::max()
{
    const auto* constThis = this;

    return const_cast<BinarySearchTreeNode<ValueType>*>(constThis->max());
}

template <typename ValueType>
BinarySearchTreeNode<ValueType>* BinarySearchTreeNode<ValueType>::getPredecessor()
{
    const auto* constThis = this;

    return const_cast<BinarySearchTreeNode<ValueType>*>(constThis->getPredecessor());
}

template <typename ValueType>
BinarySearchTreeNode<ValueType>* BinarySearchTreeNode<ValueType>::getSuccessor()
{
    const auto* constThis = this;

    return const_cast<BinarySearchTreeNode<ValueType>*>(constThis->getSuccessor());
}

template <typename ValueType>
const BinarySearchTreeNode<ValueType>* BinarySearchTreeNode<ValueType>::min() const
{
    const BinarySearchTreeNode* result = this;

    while (result->leftChild)
        result = result->leftChild;

    return result;
}

template <typename ValueType>
const BinarySearchTreeNode<ValueType>* BinarySearchTreeNode<ValueType>::max() const
{
    auto result = this;

    while (result->rightChild)
        result = result->rightChild;

    return result;
}

template <typename ValueType>
const BinarySearchTreeNode<ValueType>*
BinarySearchTreeNode<ValueType>::getPredecessor() const
{
    if (leftChild)
        return leftChild->max();

    auto current = this;
    auto p = parent;

    while (p && current == p->leftChild) {
        current = p;
        p = current->parent;
    }

    return p;
}

template <typename ValueType>
const BinarySearchTreeNode<ValueType>*
BinarySearchTreeNode<ValueType>::getSuccessor() const
{
    if (rightChild)
        return rightChild->min();

    auto current = this;
    auto p = parent;

    while (p && current == p->rightChild) {
        current = p;
        p = current->parent;
    }

    return p;
}

template <typename ValueType>
ValueType& BinarySearchTreeNode<ValueType>::getData()
{
    return  data;
}

template <typename ValueType>
const ValueType& BinarySearchTreeNode<ValueType>::getData() const
{
    return  data;
}

template <typename ValueType>
bool BinarySearchTreeNode<ValueType>::isLeaf() const
{
    return !leftChild && !rightChild;
}

template <typename ValueType>
BinarySearchTreeNode<ValueType>* BinarySearchTreeNode<ValueType>::getLeftChild()
{
    return leftChild;
}

template <typename ValueType>
BinarySearchTreeNode<ValueType>* BinarySearchTreeNode<ValueType>::getRightChild()
{
    return rightChild;
}

template <typename ValueType>
const BinarySearchTreeNode<ValueType>*
BinarySearchTreeNode<ValueType>::getLeftChild() const
{
    return leftChild;
}

template <typename ValueType>
const BinarySearchTreeNode<ValueType>*
BinarySearchTreeNode<ValueType>::getRightChild() const
{
    return rightChild;
}

/**
 * @class BinarySearchTree
 */

template <typename ValueType>
BinarySearchTree<ValueType>::BinarySearchTree()
    : m_root{}
    , m_size{}
{
}

template <typename ValueType>
BinarySearchTree<ValueType>::BinarySearchTree(const BinarySearchTree& bst)
    : m_root{}
    , m_size{}
{
    Node* root = bst.m_root;

    Node* node = copy(root, {}, m_size);

    while (node->parent)
        node = node->parent;

    m_root = node;
}

template <typename ValueType>
BinarySearchTree<ValueType>::BinarySearchTree(std::initializer_list<ValueType> list)
    : m_root{}
    , m_size{}
{
    for (auto key : list)
        insert(key);
}

template <typename ValueType>
BinarySearchTree<ValueType>::BinarySearchTree(BinarySearchTree&& bst)
    : m_root{}
    , m_size{}
{
    swap(bst);
}

template <typename ValueType>
BinarySearchTree<ValueType>&
BinarySearchTree<ValueType>::operator=(const BinarySearchTree& rhs)
{
    if (rhs.m_root == m_root)
        return *this;

    clear();

    if (!rhs.m_root)
        return *this;

    Node* rhsRoot = rhs.m_root;
    Node* node = copy(rhsRoot, {}, m_size);

    while (node->parent)
        node = node->parent;

    m_root = node;

    return *this;
}

template <typename ValueType>
BinarySearchTree<ValueType>&
BinarySearchTree<ValueType>::operator=(std::initializer_list<ValueType> list)
{
    if (m_root)
        clear();

    for (auto key : list)
        insert(key);

    return *this;
}

template <typename ValueType>
BinarySearchTree<ValueType>&
BinarySearchTree<ValueType>::operator=(BinarySearchTree&& rhs)
{
    if (rhs.m_root == m_root)
        return *this;

    if (m_root)
        clear();

    swap(rhs);

    return *this;
}

template <typename ValueType>
BinarySearchTree<ValueType>::~BinarySearchTree()
{
    clear();
}

template <typename ValueType>
bool BinarySearchTree<ValueType>::operator==(const BinarySearchTree& rhs) const
{
    if (rhs.m_root == m_root)
        return true;

    if (m_size != rhs.m_size)
        return false;

    Node* lhsRoot = m_root;
    Node* rhsRoot = rhs.m_root;

    return isEqual(lhsRoot, rhsRoot);
}

template <typename ValueType>
bool BinarySearchTree<ValueType>::operator!=(const BinarySearchTree& rhs) const
{
    return !(*this == rhs);
}


template <typename ValueType>
bool BinarySearchTree<ValueType>::empty() const
{
    return m_size == 0;
}

template <typename ValueType>
size_t BinarySearchTree<ValueType>::size() const
{
    return m_size;
}

template <typename ValueType>
void BinarySearchTree<ValueType>::insert(const ValueType& key)
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

template <typename ValueType>
void BinarySearchTree<ValueType>::insert(std::initializer_list<ValueType> list)
{
    for (auto key : list)
        insert(key);
}

template <typename ValueType>
void BinarySearchTree<ValueType>::erase(const ValueType& key)
{
    Node* node = find(key).get();

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

template <typename ValueType>
void BinarySearchTree<ValueType>::clear()
{
    clear(m_root);

    delete m_root;
    m_root = {};

    m_size = 0;
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::iterator
BinarySearchTree<ValueType>::find(const ValueType& key)
{
    return doFind(key);
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::const_iterator
BinarySearchTree<ValueType>::find(const ValueType& key) const
{
    return doFind(key);
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::iterator
BinarySearchTree<ValueType>::getRoot()
{
    return m_root;
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::const_iterator
BinarySearchTree<ValueType>::getRoot() const
{
    return m_root;
}

template <typename ValueType>
void BinarySearchTree<ValueType>::swap(BinarySearchTree& bst)
{
    if (bst.m_root == m_root)
        return;

    std::swap(bst.m_root, m_root);
    std::swap(bst.m_size, m_size);
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::iterator BinarySearchTree<ValueType>::begin()
{
    return min(m_root);
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::iterator BinarySearchTree<ValueType>::end()
{
    return nullptr;
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::const_iterator
BinarySearchTree<ValueType>::cbegin() const
{
    return min(m_root);
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::const_iterator
BinarySearchTree<ValueType>::cend() const
{
    return nullptr;
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::Node*
BinarySearchTree<ValueType>::min(Node* node) const
{
    if (!node)
        return {};

    return node->min();
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::Node*
BinarySearchTree<ValueType>::max(Node* node) const
{
    if (!node)
        return {};

    return node->max();
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::Node*
BinarySearchTree<ValueType>::getPredecessor(Node* node)
{
    if (!node)
        return {};

    return node->getPredecessor();
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::Node*
BinarySearchTree<ValueType>::getSuccessor(Node* node)
{
    if (!node)
        return {};

    return node->getSuccessor();
}

template <typename ValueType>
void BinarySearchTree<ValueType>::clear(Node* node)
{
    Node* current = node;

    if (!node)
        return;

    clear(current->leftChild);
    clear(current->rightChild);
    current->erase();
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::Node*
BinarySearchTree<ValueType>::copy(Node* node, Node* parent, size_t& counter)
{
    if (!node)
        return {};

    ++counter;

    Node* current = new Node(node->data);
    current->parent = parent;

    if (node->parent) {
        if (node == node->parent->leftChild)
            parent->leftChild = current;
        else
            parent->rightChild = current;
    }

    copy(node->leftChild, current, counter);
    copy(node->rightChild, current, counter);

    return current;
}

template <typename ValueType>
bool BinarySearchTree<ValueType>::isEqual(Node* lhs, Node* rhs) const
{
    if (!lhs && !rhs)
        return true;

    if (lhs && rhs)
        return lhs->data == rhs->data &&
               isEqual(lhs->leftChild, rhs->leftChild) &&
               isEqual(lhs->rightChild, rhs->rightChild);

    return {};
}

template <typename ValueType>
typename BinarySearchTree<ValueType>::Node*
BinarySearchTree<ValueType>::doFind(const ValueType& key) const
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

    return nullptr;
}

template <typename BinarySearchTreeNode>
BinarySearchTreeIterator<BinarySearchTreeNode>::BinarySearchTreeIterator(PointerType ptr)
    : m_ptr{ptr}
{
}

template <typename BinarySearchTreeNode>
BinarySearchTreeIterator<BinarySearchTreeNode>&
BinarySearchTreeIterator<BinarySearchTreeNode>::operator++()
{
    if (!m_ptr)
        return *this;

    m_ptr = m_ptr->getSuccessor();

    return *this;
}

template <typename BinarySearchTreeNode>
BinarySearchTreeIterator<BinarySearchTreeNode>
BinarySearchTreeIterator<BinarySearchTreeNode>::operator++(int)
{
    if (!m_ptr)
        return *this;

    BinarySearchTreeIterator result = *this;
    ++(*this);

    return result;
}

template <typename BinarySearchTreeNode>
BinarySearchTreeIterator<BinarySearchTreeNode>&
BinarySearchTreeIterator<BinarySearchTreeNode>::operator--()
{
    if (!m_ptr)
        return *this;

    m_ptr = m_ptr->getPredecessor();

    return *this;
}

template <typename BinarySearchTreeNode>
BinarySearchTreeIterator<BinarySearchTreeNode>
BinarySearchTreeIterator<BinarySearchTreeNode>::operator--(int)
{
    if (!m_ptr)
        return *this;

    BinarySearchTreeIterator result = *this;
    --(*this);

    return result;
}

template <typename BinarySearchTreeNode>
bool BinarySearchTreeIterator<BinarySearchTreeNode>::
operator==(const BinarySearchTreeIterator& rhs) const
{
    return m_ptr == rhs.m_ptr;
}

template <typename BinarySearchTreeNode>
bool BinarySearchTreeIterator<BinarySearchTreeNode>::
operator!=(const BinarySearchTreeIterator& rhs) const
{
    return !(*this == rhs);
}

template <typename BinarySearchTreeNode>
BinarySearchTreeIterator<BinarySearchTreeNode>::operator bool() const
{
    return m_ptr;
}

template <typename BinarySearchTreeNode>
bool BinarySearchTreeIterator<BinarySearchTreeNode>::operator!() const
{
    return !m_ptr;
}

template <typename BinarySearchTreeNode>
typename BinarySearchTreeIterator<BinarySearchTreeNode>::PointerType
BinarySearchTreeIterator<BinarySearchTreeNode>::operator->()
{
    return m_ptr;
}

template <typename BinarySearchTreeNode>
typename BinarySearchTreeIterator<BinarySearchTreeNode>::ReferenceType
BinarySearchTreeIterator<BinarySearchTreeNode>::operator*()
{
    return m_ptr->getData();
}

template <typename BinarySearchTreeNode>
BinarySearchTreeIterator<BinarySearchTreeNode>::operator PointerType()
{
    return m_ptr;
}

template <typename BinarySearchTreeNode>
typename BinarySearchTreeIterator<BinarySearchTreeNode>::PointerType
BinarySearchTreeIterator<BinarySearchTreeNode>::get()
{
    return m_ptr;
}

} // namespace Custom


