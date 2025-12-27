#ifndef VISUALIZE_HPP
#define VISUALIZE_HPP

#include <iostream>
#include <string>

#include "rbtree.h"

template <typename T>
static void visualize_helper(const Node<T>* node, const std::string& prefix,
                             bool is_left) {
  if (node) {
    if (node->right_) {
      visualize_helper(node->right_, prefix + (is_left ? "│   " : "    "),
                       false);
    }

    std::cout << prefix << (is_left ? "└── " : "┌── ") << node->val_ << "("
              << (node->color_ == Color::Red ? "R" : "B") << ")\n";

    if (node->left_) {
      visualize_helper(node->left_, prefix + (is_left ? "    " : "│   "), true);
    }
  }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::visualize() const {
  if (root_) {
    visualize_helper(root_, "", true);
    std::cout << std::endl;
  } else {
    std::cout << "<empty tree>\n";
  }
}

#endif