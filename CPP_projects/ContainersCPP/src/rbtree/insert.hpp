#ifndef INSERT_HPP
#define INSERT_HPP

#include "rbtree.h"

template <typename T, typename Compare>
typename RBTree<T, Compare>::iterator RBTree<T, Compare>::create_root(
    const T& val) {
  Node<T>* new_node = nullptr;
  iterator result(nullptr);

  new_node = new Node<T>(val);
  root_ = new_node;
  root_->color_ = Color::Black;
  size_ = 1;
  result = iterator(root_);

  return result;
}
template <typename T, typename Compare>
std::pair<Node<T>*, Node<T>*> RBTree<T, Compare>::find_insert_position(
    const T& val) {
  Node<T>* curr = root_;
  Node<T>* parent = nullptr;
  Node<T>* result_first = nullptr;
  Node<T>* result_second = nullptr;

  while (curr) {
    parent = curr;
    if (comp_(val, curr->val_)) {
      curr = curr->left_;
    } else if (comp_(curr->val_, val)) {
      curr = curr->right_;
    } else {
      result_first = curr;
      result_second = nullptr;
      goto end_loop;
    }
  }

  result_first = parent;
  result_second = nullptr;

end_loop:
  return {result_first, result_second};
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::iterator RBTree<T, Compare>::insert_new_node(
    Node<T>* parent, const T& val) {
  Node<T>* new_node = nullptr;
  iterator result(nullptr);

  new_node = new Node<T>(val);
  new_node->parent_ = parent;

  if (!parent || comp_(val, parent->val_)) {
    if (!parent) {
      root_ = new_node;
    } else {
      parent->left_ = new_node;
    }
  } else {
    parent->right_ = new_node;
  }

  size_++;
  fix_insert(new_node);
  result = iterator(new_node);

  return result;
}

template <typename T, typename Compare>
std::pair<Node<T>*, bool> RBTree<T, Compare>::find_or_prepare_insert(
    const T& val) {
  Node<T>* curr = root_;
  Node<T>* result_first = nullptr;
  bool result_second = false;
  bool found = false;

  while (curr && !found) {
    if (comp_(val, curr->val_)) {
      if (curr->left_) {
        curr = curr->left_;
      } else {
        result_first = curr;
        result_second = true;
        found = true;
      }
    } else if (comp_(curr->val_, val)) {
      if (curr->right_) {
        curr = curr->right_;
      } else {
        result_first = curr;
        result_second = false;
        found = true;
      }
    } else {
      result_first = curr;
      result_second = false;
      found = true;
    }
  }

  if (!curr && !found) {
    result_first = nullptr;
    result_second = false;
  }

  return {result_first, result_second};
}

template <typename T, typename Compare>
std::pair<typename RBTree<T, Compare>::iterator, bool>
RBTree<T, Compare>::insert(const T& val) {
  iterator result_iterator(nullptr);
  bool result_bool = false;
  bool done = false;

  if (!root_) {
    result_iterator = create_root(val);
    result_bool = true;
    done = true;
  }

  if (!done) {
    auto position_result = find_insert_position(val);
    Node<T>* existing_or_parent = position_result.first;
    Node<T>* new_node_ptr = position_result.second;

    if (new_node_ptr == nullptr && existing_or_parent != nullptr &&
        !(comp_(val, existing_or_parent->val_) ||
          comp_(existing_or_parent->val_, val))) {
      result_iterator = iterator(existing_or_parent);
      result_bool = false;
      done = true;
    }
  }

  if (!done) {
    auto position_result = find_insert_position(val);
    result_iterator = insert_new_node(position_result.first, val);
    result_bool = true;
  }

  return {result_iterator, result_bool};
}

template <typename T, typename Compare>
std::pair<typename RBTree<T, Compare>::iterator, bool>
RBTree<T, Compare>::insert_or_increment(const T& val) {
  iterator result_iterator(nullptr);
  bool result_bool = false;
  bool done = false;
  if (!root_) {
    result_iterator = create_root(val);
    result_bool = true;
    done = true;
  }
  if (!done) {
    auto prepare_result = find_or_prepare_insert(val);
    Node<T>* node = prepare_result.first;
    bool should_insert_left = prepare_result.second;
    if (node == nullptr) {
      result_iterator = create_root(val);
      result_bool = true;
      done = true;
    } else if (!(comp_(val, node->val_) || comp_(node->val_, val))) {
      node->count_++;
      size_++;
      result_iterator = iterator(node);
      result_bool = false;
      done = true;
    } else {
      Node<T>* parent = node;
      Node<T>* new_node = new Node<T>(val);
      new_node->parent_ = parent;
      if (should_insert_left) {
        parent->left_ = new_node;
      } else {
        parent->right_ = new_node;
      }
      size_++;
      fix_insert(new_node);
      result_iterator = iterator(new_node);
      result_bool = true;
      done = true;
    }
  }
  return {result_iterator, result_bool};
}

#endif