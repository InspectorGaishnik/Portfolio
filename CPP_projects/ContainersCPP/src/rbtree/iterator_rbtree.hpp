#ifndef ITERATOR_RBTREE_HPP
#define ITERATOR_RBTREE_HPP

#include "rbtree.h"

template <typename T, typename Compare>
class RBTree<T, Compare>::iterator {
  template <typename U, typename V>
  friend class RBTree;

 public:
  Node<T>* get_node() const { return current_; }
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;

  explicit iterator(Node<T>* node = nullptr, Node<T>* end_node = nullptr)
      : current_(node), end_node_(end_node) {}

  reference operator*() const { return current_->val_; }
  pointer operator->() const { return &current_->val_; }

  iterator& operator++() {
    bool should_return = false;

    if (!current_) {
      should_return = true;
    }

    if (!should_return) {
      if (current_->current_pos_ < current_->count_ - 1) {
        current_->current_pos_++;
        should_return = true;
      }
    }

    if (!should_return) {
      if (current_->right_) {
        current_ = current_->right_;
        while (current_->left_) {
          current_ = current_->left_;
        }
        current_->current_pos_ = 0;
      } else {
        Node<T>* parent = current_->parent_;
        while (parent && current_ == parent->right_) {
          current_ = parent;
          parent = parent->parent_;
        }
        current_ = parent;
        if (current_) {
          current_->current_pos_ = 0;
        }
      }
    }

    return *this;
  }

  iterator operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  iterator& operator--() {
    iterator* result = this;

    if (!current_ && end_node_) {
      current_ = end_node_;
      if (current_) {
        current_->current_pos_ = current_->count_ - 1;
      }
    } else if (!current_) {
      result = this;
    } else if (current_->current_pos_ > 0) {
      current_->current_pos_--;
    } else if (current_->left_) {
      current_ = current_->left_;
      while (current_->right_) {
        current_ = current_->right_;
      }
      current_->current_pos_ = current_->count_ - 1;
    } else {
      Node<T>* parent = current_->parent_;
      while (parent && current_ == parent->left_) {
        current_ = parent;
        parent = parent->parent_;
      }
      current_ = parent;
      if (current_) {
        current_->current_pos_ = current_->count_ - 1;
      }
    }

    return *result;
  }

  iterator operator--(int) {
    iterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const iterator& other) const {
    return current_ == other.current_;
  }
  bool operator!=(const iterator& other) const {
    return current_ != other.current_;
  }

 private:
  Node<T>* current_;
  Node<T>* end_node_;
};

template <typename T, typename Compare>
class RBTree<T, Compare>::const_iterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = const T;
  using difference_type = std::ptrdiff_t;
  using pointer = const T*;
  using reference = const T&;

  explicit const_iterator(const Node<T>* node = nullptr,
                          const Node<T>* end_node = nullptr)
      : current_(node), end_node_(end_node) {}

  explicit const_iterator(const iterator& it)
      : current_(it.get_node()), end_node_(nullptr) {}

  reference operator*() const { return current_->val_; }
  pointer operator->() const { return &current_->val_; }

  const_iterator& operator++() {
    bool should_return = false;

    if (!current_) {
      should_return = true;
    }

    if (!should_return) {
      if (current_->current_pos_ < current_->count_ - 1) {
        current_->current_pos_++;
        should_return = true;
      }
    }

    if (!should_return) {
      if (current_->right_) {
        current_ = current_->right_;
        while (current_->left_) {
          current_ = current_->left_;
        }
        current_->current_pos_ = 0;
      } else {
        Node<T>* parent = current_->parent_;
        while (parent && current_ == parent->right_) {
          current_ = parent;
          parent = parent->parent_;
        }
        current_ = parent;
        if (current_) {
          current_->current_pos_ = 0;
        }
      }
    }

    return *this;
  }

  const_iterator operator++(int) {
    const_iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  const_iterator& operator--() {
    const_iterator* result = this;

    if (!current_ && end_node_) {
      current_ = end_node_;
      if (current_) {
        current_->current_pos_ = current_->count_ - 1;
      }
    } else if (!current_) {
      result = this;
    } else if (current_->current_pos_ > 0) {
      current_->current_pos_--;
    } else if (current_->left_) {
      current_ = current_->left_;
      while (current_->right_) {
        current_ = current_->right_;
      }
      current_->current_pos_ = current_->count_ - 1;
    } else {
      Node<T>* parent = current_->parent_;
      while (parent && current_ == parent->left_) {
        current_ = parent;
        parent = parent->parent_;
      }
      current_ = parent;
      if (current_) {
        current_->current_pos_ = current_->count_ - 1;
      }
    }

    return *result;
  }

  const_iterator operator--(int) {
    const_iterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const const_iterator& other) const {
    return current_ == other.current_;
  }
  bool operator!=(const const_iterator& other) const {
    return current_ != other.current_;
  }

 private:
  const Node<T>* current_;
  const Node<T>* end_node_;
};

template <typename T, typename Compare>
typename RBTree<T, Compare>::iterator RBTree<T, Compare>::begin() {
  Node<T>* node = root_;
  while (node && node->left_) {
    node = node->left_;
  }
  if (node) {
    node->current_pos_ = 0;
  }
  return iterator(node);
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::iterator RBTree<T, Compare>::end() {
  Node<T>* node = root_;
  while (node && node->right_) {
    node = node->right_;
  }
  return iterator(nullptr, node);
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::const_iterator RBTree<T, Compare>::begin() const {
  const Node<T>* node = root_;
  while (node && node->left_) {
    node = node->left_;
  }
  return const_iterator(node);
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::const_iterator RBTree<T, Compare>::end() const {
  const Node<T>* node = root_;
  while (node && node->right_) {
    node = node->right_;
  }
  return const_iterator(nullptr, node);
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::const_iterator RBTree<T, Compare>::cbegin() const {
  return begin();
}

template <typename T, typename Compare>
typename RBTree<T, Compare>::const_iterator RBTree<T, Compare>::cend() const {
  return end();
}

#endif