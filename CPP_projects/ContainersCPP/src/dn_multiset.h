#ifndef DN_MULTISET_H_
#define DN_MULTISET_H_

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "rbtree/rbtree.h"
#include "dn_vector.h"

namespace dn {

template <typename Key, typename Compare = std::less<Key>>
class multiset {
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

  explicit multiset() : tree_(key_compare_impl()) {}

  explicit multiset(std::initializer_list<value_type> const& items);
  explicit multiset(const multiset& ms);
  explicit multiset(multiset&& ms) noexcept;
  ~multiset() = default;

  multiset& operator=(const multiset& ms);
  multiset& operator=(multiset&& ms) noexcept;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  iterator insert(const value_type& value);
  void erase(iterator pos);
  void clear();
  void swap(multiset& other);
  void merge(multiset& other);

  iterator find(const key_type& key);
  const_iterator find(const key_type& key) const;
  bool contains(const key_type& key) const;
  size_type count(const key_type& key) const;

  iterator lower_bound(const key_type& key);
  const_iterator lower_bound(const key_type& key) const;
  iterator upper_bound(const key_type& key);
  const_iterator upper_bound(const key_type& key) const;
  std::pair<iterator, iterator> equal_range(const key_type& key);

  template <typename... Args>
  dn::vector<iterator> insert_many(Args&&... args);
};

template <typename Key, typename Compare>
multiset<Key, Compare>::multiset(std::initializer_list<value_type> const& items)
    : tree_(key_compare_impl()) {
  for (const auto& item : items) {
    tree_.insert_or_increment(item);
  }
}

template <typename Key, typename Compare>
multiset<Key, Compare>::multiset(const multiset& ms) : tree_(ms.tree_) {}

template <typename Key, typename Compare>
multiset<Key, Compare>::multiset(multiset&& ms) noexcept
    : tree_(std::move(ms.tree_)) {}

template <typename Key, typename Compare>
multiset<Key, Compare>& multiset<Key, Compare>::operator=(const multiset& ms) {
  if (this != &ms) {
    tree_ = ms.tree_;
  }
  return *this;
}

template <typename Key, typename Compare>
multiset<Key, Compare>& multiset<Key, Compare>::operator=(
    multiset&& ms) noexcept {
  if (this != &ms) {
    tree_ = std::move(ms.tree_);
  }
  return *this;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::begin() {
  return tree_.begin();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::end() {
  return tree_.end();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::begin()
    const {
  return tree_.begin();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::end()
    const {
  return tree_.end();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::cbegin()
    const {
  return tree_.cbegin();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::cend()
    const {
  return tree_.cend();
}

template <typename Key, typename Compare>
bool multiset<Key, Compare>::empty() const {
  return tree_.size() == 0;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::size_type multiset<Key, Compare>::size()
    const {
  return tree_.size();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::size_type multiset<Key, Compare>::max_size()
    const {
  return tree_.max_size();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::insert(
    const value_type& value) {
  auto result = tree_.insert_or_increment(value);
  return result.first;
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::erase(iterator pos) {
  tree_.erase_or_decrement(pos);
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::clear() {
  tree_.clear();
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::swap(multiset& other) {
  tree_.swap(other.tree_);
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::merge(multiset& other) {
  auto it = other.begin();
  while (it != other.end()) {
    auto current_val = *it;
    insert(current_val);
    other.erase(it);
    it = other.begin();
  }
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::find(
    const key_type& key) {
  Node<value_type>* node = tree_.find(key);
  return iterator(node);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::find(
    const key_type& key) const {
  const Node<value_type>* node = tree_.find(key);
  return const_iterator(node);
}

template <typename Key, typename Compare>
bool multiset<Key, Compare>::contains(const key_type& key) const {
  return tree_.contains(key);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::size_type multiset<Key, Compare>::count(
    const key_type& key) const {
  return tree_.count(key);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::lower_bound(
    const key_type& key) {
  Node<value_type>* result = nullptr;
  Node<value_type>* current = tree_.get_root();

  while (current) {
    if (!tree_.get_comp()(current->val_, key)) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  return iterator(result);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator
multiset<Key, Compare>::lower_bound(const key_type& key) const {
  const Node<value_type>* result = nullptr;
  const Node<value_type>* current = tree_.get_root();

  while (current) {
    if (!tree_.get_comp()(current->val_, key)) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  return const_iterator(result);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::upper_bound(
    const key_type& key) {
  Node<value_type>* result = nullptr;
  Node<value_type>* current = tree_.get_root();

  while (current) {
    if (tree_.get_comp()(key, current->val_)) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  return iterator(result);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator
multiset<Key, Compare>::upper_bound(const key_type& key) const {
  const Node<value_type>* result = nullptr;
  const Node<value_type>* current = tree_.get_root();

  while (current) {
    if (tree_.get_comp()(key, current->val_)) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  return const_iterator(result);
}

template <typename Key, typename Compare>
std::pair<typename multiset<Key, Compare>::iterator,
          typename multiset<Key, Compare>::iterator>
multiset<Key, Compare>::equal_range(const key_type& key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key, typename Compare>
template <typename... Args>
dn::vector<typename multiset<Key, Compare>::iterator>
multiset<Key, Compare>::insert_many(Args&&... args) {
  dn::vector<iterator> results;
  (results.push_back(insert(args)), ...);
  return results;
}

}  // namespace dn

#endif
