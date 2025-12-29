#ifndef REMOVE_NODE_HPP
#define REMOVE_NODE_HPP

#include "rbtree.h"

template <typename T, typename Compare>
void RBTree<T, Compare>::delete_node_and_fix(Node<T>* node, Node<T>* y,
                                             Node<T>* x,
                                             Color y_original_color) {
  bool should_return = false;

  if (y_original_color == Color::Black) {
    if (x) {
      fix_delete(x);
    } else {
      Node<T> temp(T{});
      temp.color_ = Color::Black;
      temp.parent_ = y;
      fix_delete(&temp);
    }
  }

  if (!should_return) {
    delete node;
    if (size_ > 0) size_--;
  }
}

template <typename T, typename Compare>
Node<T>* RBTree<T, Compare>::prepare_deletion(Node<T>* node, Node<T>*& y,
                                              Node<T>*& x,
                                              Color& y_original_color) {
  Node<T>* result = nullptr;

  y = node;
  y_original_color = y->color_;

  if (!node->left_) {
    x = node->right_;
    transplant(node, node->right_);
  } else if (!node->right_) {
    x = node->left_;
    transplant(node, node->left_);
  } else {
    y = minimum(node->right_);
    y_original_color = y->color_;
    x = y->right_;

    if (y->parent_ == node) {
      if (x) x->parent_ = y;
    } else {
      transplant(y, y->right_);
      y->right_ = node->right_;
      if (y->right_) y->right_->parent_ = y;
    }

    transplant(node, y);
    y->left_ = node->left_;
    if (y->left_) y->left_->parent_ = y;
    y->color_ = node->color_;
  }

  result = y;
  return result;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::handle_black_node_deletion(Node<T>* x, Node<T>* y) {
  if (x) {
    fix_delete(x);
  } else {
    Node<T> temp(T{});
    temp.color_ = Color::Black;
    temp.parent_ = y;
    fix_delete(&temp);
  }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::erase(const T& val) {
  Node<T>* node = find(val);
  bool should_return = (node == nullptr);

  if (!should_return) {
    Node<T>* y = nullptr;
    Node<T>* x = nullptr;
    Color y_original_color = Color::Black;

    y = prepare_deletion(node, y, x, y_original_color);

    if (y_original_color == Color::Black) {
      handle_black_node_deletion(x, y);
    }

    delete node;
    if (size_ > 0) size_--;
  }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::erase(iterator pos) {
  if (pos != end()) {
    Node<T>* node = pos.get_node();
    erase(node->val_);
  }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::erase_or_decrement(iterator pos) {
  bool should_return = (pos == iterator(nullptr));
  Node<T>* node = nullptr;

  if (!should_return) {
    node = pos.get_node();
    should_return = (node == nullptr);
  }

  bool should_decrement = false;
  Node<T>* y = nullptr;
  Node<T>* x = nullptr;
  Color y_original_color = Color::Black;

  if (!should_return) {
    if (node->count_ > 1) {
      node->count_--;
      size_--;
      if (node->current_pos_ > 0) {
        node->current_pos_--;
      }
      should_return = true;
    } else {
      should_decrement = true;
    }
  }

  if (!should_return && should_decrement) {
    y = prepare_deletion(node, y, x, y_original_color);
  }

  if (!should_return && should_decrement && y_original_color == Color::Black) {
    handle_black_node_deletion(x, y);
  }

  if (!should_return && should_decrement) {
    delete node;
    if (size_ > 0) size_--;
  }
}

template <typename T, typename Compare>
Node<T>* RBTree<T, Compare>::minimum(Node<T>* node) {
  while (node->left_) {
    node = node->left_;
  }
  return node;
}

#endif