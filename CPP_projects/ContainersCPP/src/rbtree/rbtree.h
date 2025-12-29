#ifndef RBTREE_H
#define RBTREE_H

#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>

enum class Color { Red, Black };

template <typename T>
struct Node {
  T val_;
  Color color_;
  Node<T>* left_;
  Node<T>* right_;
  Node<T>* parent_;
  size_t count_;
  mutable size_t current_pos_;

  explicit Node(const T& val)
      : val_(val),
        color_(Color::Red),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        count_(1),
        current_pos_(0) {}
};

template <typename T, typename Compare = std::less<T>>
class RBTree {
 public:
  explicit RBTree() : root_(nullptr), comp_(Compare()), size_(0) {}
  explicit RBTree(const Compare& comp)
      : root_(nullptr), comp_(comp), size_(0) {}
  ~RBTree() { clear(root_); }
  explicit RBTree(const RBTree& other);
  explicit RBTree(RBTree&& other) noexcept;
  RBTree& operator=(const RBTree& other);
  RBTree& operator=(RBTree&& other) noexcept;
  class iterator;
  class const_iterator;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  void erase(const T& val_);
  void erase(iterator pos);
  void erase_or_decrement(iterator pos);
  [[nodiscard]] Node<T>* get_root() const { return root_; }
  [[nodiscard]] Node<T>* find(const T& val_) const;
  [[nodiscard]] bool contains(const T& val_) const;
  [[nodiscard]] bool empty() const { return root_ == nullptr; }
  std::pair<iterator, bool> insert(const T& val);
  std::pair<iterator, bool> insert_or_increment(const T& val);
  size_t count(const T& val) const;

  using key_type = T;
  using mapped_type = void;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  [[nodiscard]] size_type size() const { return size_; }
  [[nodiscard]] size_type max_size() const {
    return std::numeric_limits<size_type>::max();
  }
  void clear();
  void swap(RBTree& other);

  const Compare& get_comp() const { return comp_; }

  void visualize() const;

 private:
  Node<T>* root_;
  Compare comp_;
  size_t size_;

  void left_rotate(Node<T>* up_to_leftdown);
  void right_rotate(Node<T>* up_to_rightdown);
  void fix_insert(Node<T>* k);
  void clear(Node<T>* node);
  void transplant(Node<T>* u, Node<T>* v);

  void handle_red_uncle_case(Node<T>*& k, Node<T>* uncle);
  void handle_black_uncle_case(Node<T>*& k);
  void handle_left_parent_case(Node<T>*& k);
  void handle_right_parent_case(Node<T>*& k);

  void handle_red_sibling_case(Node<T>*& x, Node<T>* w, Node<T>* x_parent);
  void handle_black_sibling_case(Node<T>*& x, Node<T>* w, Node<T>* x_parent);
  void handle_double_black_case(Node<T>*& x, Node<T>* w, Node<T>* x_parent);
  void fix_delete(Node<T>* x);
  Node<T>* minimum(Node<T>* node);
  Node<T>* copy_subtree(Node<T>* node, Node<T>* parent);

  RBTree<T, Compare>::iterator create_root(const T& val);
  std::pair<Node<T>*, Node<T>*> find_insert_position(const T& val);
  RBTree<T, Compare>::iterator insert_new_node(Node<T>* parent, const T& val);
  std::pair<Node<T>*, bool> find_or_prepare_insert(const T& val);

  void delete_node_and_fix(Node<T>* node, Node<T>* y, Node<T>* x,
                           Color y_original_color);
  Node<T>* prepare_deletion(Node<T>* node, Node<T>*& y, Node<T>*& x,
                            Color& y_original_color);
  void handle_black_node_deletion(Node<T>* x, Node<T>* y);

  bool should_continue_fix_delete(Node<T>* x);
  void handle_null_x_case(Node<T>*& x, Node<T>*& x_parent,
                          bool& should_continue);
  void process_left_child_case(Node<T>*& x, Node<T>*& x_parent);
  void process_right_child_case(Node<T>*& x, Node<T>*& x_parent);
};

template <typename T, typename Compare>
RBTree<T, Compare>::RBTree(const RBTree& other)
    : comp_(other.comp_), size_(other.size_) {
  if (other.root_) {
    root_ = copy_subtree(other.root_, nullptr);
  } else {
    root_ = nullptr;
  }
}

template <typename T, typename Compare>
Node<T>* RBTree<T, Compare>::copy_subtree(Node<T>* node, Node<T>* parent) {
  if (!node) return nullptr;
  Node<T>* new_node = new Node<T>(node->val_);
  new_node->color_ = node->color_;
  new_node->parent_ = parent;
  new_node->left_ = copy_subtree(node->left_, new_node);
  new_node->right_ = copy_subtree(node->right_, new_node);
  new_node->count_ = node->count_;
  new_node->current_pos_ = node->current_pos_;
  return new_node;
}

template <typename T, typename Compare>
RBTree<T, Compare>::RBTree(RBTree&& other) noexcept
    : root_(other.root_), comp_(std::move(other.comp_)), size_(other.size_) {
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename T, typename Compare>
size_t RBTree<T, Compare>::count(const T& val) const {
  Node<T>* node = find(val);
  return node ? node->count_ : 0;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::clear(Node<T>* node) {
  if (node) {
    clear(node->left_);
    clear(node->right_);
    delete node;
  }
}
#include "balancing.hpp"
#include "clear.hpp"
#include "insert.hpp"
#include "iterator_rbtree.hpp"
#include "operators.hpp"
#include "remove_node.hpp"
#include "search.hpp"
#include "validate.hpp"
#include "visualize.hpp"

#endif
