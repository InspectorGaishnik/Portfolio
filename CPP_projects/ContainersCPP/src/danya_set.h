#ifndef DANYA_SET_H_
#define DANYA_SET_H_

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "rbtree/rbtree.h"
#include "danya_vector.h"

namespace danya {
template <typename Key, typename Compare = std::less<Key>>
class set {
 private:
  struct key_compare_impl {
    Compare comp_;
    key_compare_impl() : comp_() {}
    explicit key_compare_impl(const Compare& comp) : comp_(comp) {}

    bool operator()(const Key& lhs, const Key& rhs) const {
      return comp_(lhs, rhs);
    }
  };

  RBTree<Key, key_compare_impl> tree_;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<value_type, key_compare_impl>::iterator;
  using const_iterator =
      typename RBTree<value_type, key_compare_impl>::const_iterator;
  using size_type = std::size_t;
  using key_compare = Compare;

  explicit set() : tree_(key_compare_impl()) {}

  explicit set(std::initializer_list<value_type> const& items);

  explicit set(const set& s);

  explicit set(set&& s) noexcept;

  ~set() = default;

  set& operator=(const set& s);

  set& operator=(set&& s) noexcept;

  iterator begin();

  iterator end();

  const_iterator begin() const;

  const_iterator end() const;

  const_iterator cbegin() const;

  const_iterator cend() const;

  iterator find(const key_type& key);

  const_iterator find(const key_type& key) const;

  bool empty() const;

  size_type size() const;

  size_type max_size() const;

  std::pair<iterator, bool> insert(const value_type& value);

  void erase(iterator pos);

  void clear();

  void swap(set& other);

  void merge(set& other);

  bool contains(const key_type& key) const;

  template <typename... Args>
  danya::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

template <typename Key, typename Compare>
set<Key, Compare>::set(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    tree_.insert(item);
  }
}

template <typename Key, typename Compare>
set<Key, Compare>::set(const set& s) : tree_(s.tree_) {}

template <typename Key, typename Compare>
set<Key, Compare>::set(set&& s) noexcept : tree_(std::move(s.tree_)) {}

template <typename Key, typename Compare>
set<Key, Compare>& set<Key, Compare>::operator=(const set& s) {
  if (this != &s) {
    tree_ = s.tree_;
  }
  return *this;
}

template <typename Key, typename Compare>
set<Key, Compare>& set<Key, Compare>::operator=(set&& s) noexcept {
  if (this != &s) {
    tree_ = std::move(s.tree_);
  }
  return *this;
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::begin() {
  return tree_.begin();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::end() {
  return tree_.end();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::const_iterator set<Key, Compare>::begin() const {
  return tree_.begin();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::const_iterator set<Key, Compare>::end() const {
  return tree_.end();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::const_iterator set<Key, Compare>::cbegin() const {
  return tree_.cbegin();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::const_iterator set<Key, Compare>::cend() const {
  return tree_.cend();
}

template <typename Key, typename Compare>
bool set<Key, Compare>::empty() const {
  return tree_.size() == 0;
}

template <typename Key, typename Compare>
typename set<Key, Compare>::size_type set<Key, Compare>::size() const {
  return tree_.size();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::size_type set<Key, Compare>::max_size() const {
  return tree_.max_size();
}

template <typename Key, typename Compare>
std::pair<typename set<Key, Compare>::iterator, bool> set<Key, Compare>::insert(
    const value_type& value) {
  return tree_.insert(value);
}

template <typename Key, typename Compare>
void set<Key, Compare>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key, typename Compare>
void set<Key, Compare>::clear() {
  tree_.clear();
}

template <typename Key, typename Compare>
void set<Key, Compare>::swap(set& other) {
  tree_.swap(other.tree_);
}

template <typename Key, typename Compare>
void set<Key, Compare>::merge(set& other) {
  for (auto it = other.begin(); it != other.end();) {
    auto current_it = it++;
    if (insert(*current_it).second) {
      other.erase(current_it);
    }
  }
}

template <typename Key, typename Compare>
bool set<Key, Compare>::contains(const key_type& key) const {
  return tree_.contains(key);
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::find(
    const key_type& key) {
  Node<value_type>* node = tree_.find(key);
  return iterator(node);
}

template <typename Key, typename Compare>
typename set<Key, Compare>::const_iterator set<Key, Compare>::find(
    const key_type& key) const {
  const Node<value_type>* node = tree_.find(key);
  return const_iterator(node);
}

template <typename Key, typename Compare>
template <typename... Args>
danya::vector<std::pair<typename set<Key, Compare>::iterator, bool>>
set<Key, Compare>::insert_many(Args&&... args) {
  danya::vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(args)), ...);
  return results;
}

}  // namespace danya

#endif