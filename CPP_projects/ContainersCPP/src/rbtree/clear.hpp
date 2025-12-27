#ifndef CLEAR_HPP
#define CLEAR_HPP

#include "rbtree.h"

template <typename T, typename Compare>
void RBTree<T, Compare>::clear() {
  clear(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::swap(RBTree& other) {
  std::swap(root_, other.root_);
  std::swap(comp_, other.comp_);
  std::swap(size_, other.size_);
}

#endif