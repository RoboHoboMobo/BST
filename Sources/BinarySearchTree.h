#pragma once

#include <stddef.h>

#include <initializer_list>

#include <type_traits>

namespace Custom
{

template <typename T>
class BinarySearchTreeNode;

template <typename T>
class BinarySearchTree;

template <typename BinarySearchTreeNode>
class BinarySearchTreeIterator;

template <typename T>
class BinarySearchTreeNode
{
public:
    using ValueType = T;

    BinarySearchTreeNode* min();
    BinarySearchTreeNode* max();
    BinarySearchTreeNode* getPredecessor();
    BinarySearchTreeNode* getSuccessor();

    const BinarySearchTreeNode* min() const;
    const BinarySearchTreeNode* max() const;
    const BinarySearchTreeNode* getPredecessor() const;
    const BinarySearchTreeNode* getSuccessor() const;

    T& getData();
    const T& getData() const;

    bool isLeaf() const;

    BinarySearchTreeNode* getLeftChild();
    BinarySearchTreeNode* getRightChild();

    const BinarySearchTreeNode* getLeftChild() const;
    const BinarySearchTreeNode* getRightChild() const;

    friend class BinarySearchTree<T>;

private:
    BinarySearchTreeNode();
    BinarySearchTreeNode(const ValueType& key);
    BinarySearchTreeNode(const BinarySearchTreeNode&) = delete;
    BinarySearchTreeNode(BinarySearchTreeNode&&) = delete;
    BinarySearchTreeNode& operator=(const BinarySearchTreeNode&) = delete;
    BinarySearchTreeNode& operator=(BinarySearchTreeNode&&) = delete;

    void erase();

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
    using iterator = BinarySearchTreeIterator<Node>;
    using const_iterator = BinarySearchTreeIterator<const Node>;
public:
    BinarySearchTree() noexcept;
    BinarySearchTree(const BinarySearchTree&);
    BinarySearchTree(std::initializer_list<ValueType>);
    BinarySearchTree(BinarySearchTree&&) noexcept;

    BinarySearchTree& operator=(const BinarySearchTree&);
    BinarySearchTree& operator=(std::initializer_list<ValueType>);
    BinarySearchTree& operator=(BinarySearchTree&&) noexcept;

    virtual ~BinarySearchTree() noexcept;

    bool operator==(const BinarySearchTree&) const;
    bool operator!=(const BinarySearchTree&) const;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void insert(const ValueType& key);
    void insert(std::initializer_list<ValueType>);

    void erase(const ValueType& key);
    void clear() noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    iterator find(const ValueType& key);
    const_iterator find(const ValueType& key) const;

    iterator getRoot() noexcept;
    const_iterator getRoot() const noexcept;

    void swap(BinarySearchTree&) noexcept;

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

template <typename BinarySearchTreeNode>
class BinarySearchTreeIterator
{
public:
    using ValueType = typename BinarySearchTreeNode::ValueType;
    using PointerType = BinarySearchTreeNode*;
    using ReferenceType = typename std::conditional<
    std::is_const<BinarySearchTreeNode>::value, const ValueType&, ValueType&>::type;

public:
    BinarySearchTreeIterator(PointerType ptr);

    BinarySearchTreeIterator& operator++();
    BinarySearchTreeIterator operator++(int);

    BinarySearchTreeIterator& operator--();
    BinarySearchTreeIterator operator--(int);

    bool operator==(const BinarySearchTreeIterator& rhs) const;
    bool operator!=(const BinarySearchTreeIterator& rhs) const;

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
