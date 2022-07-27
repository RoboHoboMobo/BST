#include "BinarySearchTree.h"
#include "BinarySearchTree.tpp"

template class Custom::BinarySearchTree<int>;
template class Custom::BinarySearchTreeIterator<Custom::BinarySearchTree, int>;

template class Custom::BinarySearchTree<const int>;
template class Custom::BinarySearchTreeIterator<Custom::BinarySearchTree, const int>;
