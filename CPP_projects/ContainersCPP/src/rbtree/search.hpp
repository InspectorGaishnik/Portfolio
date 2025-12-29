#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "rbtree.h"

template <typename T, typename Compare>
Node<T>* RBTree<T, Compare>::find(const T& val) const {
  Node<T>* result = nullptr;
  Node<T>* curr = root_;

  while (curr && !result) {
    if (comp_(val, curr->val_)) {
      curr = curr->left_;
    } else if (comp_(curr->val_, val)) {
      curr = curr->right_;
    } else {
      result = curr;
    }
  }

  return result;
}

template <typename T, typename Compare>
bool RBTree<T, Compare>::contains(const T& val) const {
  bool result = false;
  Node<T>* curr = root_;

  while (curr && !result) {
    if (comp_(val, curr->val_)) {
      curr = curr->left_;
    } else if (comp_(curr->val_, val)) {
      curr = curr->right_;
    } else {
      result = true;
    }
  }

  return result;
}

#endif