#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "rbtree.h"

template <typename T, typename Compare>
RBTree<T, Compare>& RBTree<T, Compare>::operator=(const RBTree& other) {
  if (this != &other) {
    clear(root_);
    comp_ = other.comp_;
    size_ = other.size_;
    root_ = other.root_ ? copy_subtree(other.root_, nullptr) : nullptr;
  }
  return *this;
}

template <typename T, typename Compare>
RBTree<T, Compare>& RBTree<T, Compare>::operator=(RBTree&& other) noexcept {
  if (this != &other) {
    clear(root_);
    root_ = other.root_;
    comp_ = std::move(other.comp_);
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

#endif