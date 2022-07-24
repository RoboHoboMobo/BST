#pragma once

#include <memory>

namespace Custom
{

template <typename T>
class BinarySearchTree
{
public:
    struct Node;

    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree&);
    BinarySearchTree& operator=(const BinarySearchTree&);
    virtual ~BinarySearchTree();

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

    Node* m_root;
    size_t m_size;
};

template <typename T>
struct BinarySearchTree<T>::Node
{
    Node();
    Node(const T& key);

    void erase();

    T data;
    Node* parent;
    Node* leftChild;
    Node* rightChild;
};

} // namespace Custom