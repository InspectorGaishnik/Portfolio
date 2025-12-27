#ifndef VALIDATE_HPP
#define VALIDATE_HPP

#include <cassert>

#include "rbtree.h"

template <typename T>
int validate_rbtree_internal(Node<T>* node, int black_count,
                             int current_black) {
  auto res = current_black;
  if (node) {
    if (node->color_ == Color::Red) {
      assert(!node->left_ || node->left_->color_ == Color::Black);
      assert(!node->right_ || node->right_->color_ == Color::Black);
    }

    int left_black = validate_rbtree_internal(
        node->left_, black_count,
        current_black + (node->color_ == Color::Black ? 1 : 0));
    int right_black = validate_rbtree_internal(
        node->right_, black_count,
        current_black + (node->color_ == Color::Black ? 1 : 0));

    assert(left_black == right_black);
  }
  return res;
}

template <typename T>
void validate_rbtree(Node<T>* root) {
  if (root) {
    assert(root->color_ == Color::Black);

    int black_count = 0;
    Node<T>* node = root;
    while (node) {
      black_count += (node->color_ == Color::Black ? 1 : 0);
      node = node->left_;
    }

    validate_rbtree_internal(root, black_count, 0);
  }
}

#endif