#pragma once

#include <stddef.h>

#include <initializer_list>

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
    BinarySearchTreeNode(const ValueType& key);
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
    BinarySearchTree(std::initializer_list<ValueType>);
    virtual ~BinarySearchTree();

    bool operator==(const BinarySearchTree&) const;
    bool operator!=(const BinarySearchTree&) const;

    bool empty() const;
    size_t size() const;

    void insert(const ValueType& key);
    void insert(std::initializer_list<ValueType>);

    void erase(const ValueType& key);
    void clear();

    iterator begin();
    iterator end();

    iterator begin() const;
    iterator end() const;

    iterator find(const ValueType& key) const;

    iterator getRoot() const;

private:
    Node* min(Node*) const;
    Node* max(Node*) const;
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
    BinarySearchTreeIterator(PointerType ptr);

    BinarySearchTreeIterator& operator++();
    BinarySearchTreeIterator operator++(int);

    BinarySearchTreeIterator& operator--();
    BinarySearchTreeIterator operator--(int);

    bool operator==(const BinarySearchTreeIterator& rhs);
    bool operator!=(const BinarySearchTreeIterator& rhs);

    operator bool() const;
    bool operator!() const;

    PointerType operator->();
    ReferenceType operator*();

    PointerType getPtr();
    operator PointerType();

private:
    PointerType m_ptr;
};

} // namespace Custom
