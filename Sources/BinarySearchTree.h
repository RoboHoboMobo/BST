#pragma once

#include <memory>

namespace Custom
{

template <typename T>
class BinarySearchTree;

template <typename T>
struct BinarySearchTreeNode
{
    using ValueType = T;

    BinarySearchTreeNode();
    BinarySearchTreeNode(const T& key);
    BinarySearchTreeNode(const BinarySearchTreeNode&) = delete;
    BinarySearchTreeNode& operator=(const BinarySearchTreeNode&) = delete;

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

private:
    Node* min(Node*);
    Node* max(Node*);
    Node* getSuccessor(Node*);
    Node* getPredecessor(Node*);

    void clear(Node*);
    Node* copy(Node* node, Node* parent, size_t& counter);
    bool isEqual(Node* lhs, Node* rhs) const;

    Node* m_root;
    size_t m_size;
};

} // namespace Custom
