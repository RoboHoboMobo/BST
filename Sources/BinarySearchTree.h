#pragma once

#include <memory>

namespace Custom
{

template <typename T>
class BinarySearchTree;

template <typename BinarySearchTree>
class BinarySearchTreeIterator;

template <typename T>
struct BinarySearchTreeNode
{
    using ValueType = T;

    BinarySearchTreeNode();
    BinarySearchTreeNode(const T& key);
    BinarySearchTreeNode(const BinarySearchTreeNode&) = delete;
    BinarySearchTreeNode& operator=(const BinarySearchTreeNode&) = default;

    void erase();

    BinarySearchTreeNode* min();
    BinarySearchTreeNode* max();
    BinarySearchTreeNode* getPredecessor();
    BinarySearchTreeNode* getSuccessor();

    T data;
    BinarySearchTreeNode* parent;
    BinarySearchTreeNode* leftChild;
    BinarySearchTreeNode* rightChild;
};

template <typename T>
class BinarySearchTree
{
public:
    using ValueType = T;
    using Node = BinarySearchTreeNode<T>;
    using iterator = BinarySearchTreeIterator<BinarySearchTree<T>>;
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree&);
    BinarySearchTree& operator=(const BinarySearchTree&);
    virtual ~BinarySearchTree();

    bool operator==(const BinarySearchTree&) const;
    bool operator!=(const BinarySearchTree&) const;

    inline bool empty() const;
    inline size_t size() const;

    void insert(const T& key);
    void erase(const T& key);
    void clear();

    Node* find(const T&) const;

    iterator begin();
    iterator end();

private:
    Node* min(Node*);
    Node* max(Node*);
    Node* getPredecessor(Node*);
    Node* getSuccessor(Node*);

    void clear(Node*);
    Node* copy(Node* node, Node* parent, size_t& counter);
    bool isEqual(Node* lhs, Node* rhs) const;

    Node* m_root;
    size_t m_size;
};

template <typename BinarySearchTree>
class BinarySearchTreeIterator
{
public:
    using ValueType = typename BinarySearchTree::ValueType;
    using PointerType = BinarySearchTreeNode<ValueType>*;
    using ReferenceType = ValueType&;
public:
    BinarySearchTreeIterator(PointerType ptr)
        : m_ptr{ptr}
    {
    }

    BinarySearchTreeIterator& operator++()
    {
        if (!m_ptr)
            return *this;

        m_ptr = m_ptr->getSuccessor();

        return *this;
    }

    BinarySearchTreeIterator operator++(int)
    {
        if (!m_ptr)
            return *this;

        BinarySearchTreeIterator result = *this;
        ++(*this);

        return result;
    }

    BinarySearchTreeIterator& operator--()
    {
        if (!m_ptr)
            return *this;

        m_ptr = m_ptr->getPredecessor();

        return *this;
    }

    BinarySearchTreeIterator operator--(int)
    {
        if (!m_ptr)
            return *this;

        BinarySearchTreeIterator result = *this;
        --(*this);

        return result;
    }

    bool operator==(const BinarySearchTreeIterator& rhs)
    {
        return m_ptr == rhs.m_ptr;
    }

    bool operator!=(const BinarySearchTreeIterator& rhs)
    {
        return !(*this == rhs);
    }

    PointerType operator->()
    {
        return m_ptr;
    }

    ReferenceType operator*()
    {
        return m_ptr->data;
    }

private:
    PointerType m_ptr;
};

} // namespace Custom
