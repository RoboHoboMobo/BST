#pragma once

#include <stddef.h>

#include <initializer_list>

namespace Custom
{

template <typename T>
class BinarySearchTree;

template <template <typename> class BinarySearchTree, typename ValueType>
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

    const BinarySearchTreeNode* min() const;
    const BinarySearchTreeNode* max() const;
    const BinarySearchTreeNode* getPredecessor() const;
    const BinarySearchTreeNode* getSuccessor() const;

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
    using iterator = BinarySearchTreeIterator<BinarySearchTree, T>;
    using const_iterator = BinarySearchTreeIterator<BinarySearchTree, const T>;
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

    const_iterator cbegin() const;
    const_iterator cend() const;

    iterator find(const ValueType& key);
    const_iterator find(const ValueType& key) const;

    iterator getRoot();
    const_iterator getRoot() const;

    void swap(BinarySearchTree&);

private:
    Node* min(Node*) const;
    Node* max(Node*) const;
    Node* getPredecessor(Node*);
    Node* getSuccessor(Node*);

    void clear(Node*);
    Node* copy(Node* node, Node* parent, size_t& counter);
    bool isEqual(Node* lhs, Node* rhs) const;

    Node* doFind(const ValueType& key) const;

    Node* m_root;
    size_t m_size;
};

template <template <typename> class BinarySearchTree, typename ValueType>
class BinarySearchTreeIterator
{
public:
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

    operator PointerType();
    PointerType get();

private:
    PointerType m_ptr;
};

} // namespace Custom
