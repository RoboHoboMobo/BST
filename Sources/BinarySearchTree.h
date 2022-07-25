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

    iterator begin();
    iterator end();

    iterator find(const T&);

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

private:
    PointerType m_ptr;
};

} // namespace Custom
