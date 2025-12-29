#ifndef DN_MAP_H_
#define DN_MAP_H_

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "rbtree/rbtree.h"
#include "dn_vector.h"

namespace dn {
template <typename Key, typename T, typename Compare = std::less<Key>>
class map {
 private:
  struct key_compare_impl {
    Compare comp_;
    key_compare_impl() : comp_() {}
    explicit key_compare_impl(const Compare& comp) : comp_(comp) {}

    bool operator()(const std::pair<const Key, T>& lhs,
                    const std::pair<const Key, T>& rhs) const {
      return comp_(lhs.first, rhs.first);
    }
  };

  RBTree<std::pair<const Key, T>, key_compare_impl> tree_;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<value_type, key_compare_impl>::iterator;
  using const_iterator = typename RBTree<value_type, key_compare_impl>::const_iterator;
  using size_type = std::size_t;

  explicit map() : tree_(key_compare_impl()) {}
  explicit map(std::initializer_list<value_type> const& items);
  explicit map(const map& m);
  explicit map(map&& m) noexcept;
  ~map() = default;
  map& operator=(const map& m);
  map& operator=(map&& m) noexcept;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  mapped_type& at(const key_type& key);
  const mapped_type& at(const key_type& key) const;
  mapped_type& operator[](const key_type& key);
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key, const mapped_type& obj);
  void erase(iterator pos);
  void clear();
  void swap(map& other);
  void merge(map& other);
  bool contains(const key_type& key) const;
  template <typename... Args>
  dn::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

template <typename Key, typename T, typename Compare>
map<Key, T, Compare>::map(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key, typename T, typename Compare>
map<Key, T, Compare>::map(const map& m) : tree_(m.tree_) {}

template <typename Key, typename T, typename Compare>
map<Key, T, Compare>::map(map&& m) noexcept : tree_(std::move(m.tree_)) {}

template <typename Key, typename T, typename Compare>
map<Key, T, Compare>& map<Key, T, Compare>::operator=(const map& m) {
  if (this != &m) {
    tree_ = m.tree_;
  }
  return *this;
}

template <typename Key, typename T, typename Compare>
map<Key, T, Compare>& map<Key, T, Compare>::operator=(map&& m) noexcept {
  if (this != &m) {
    tree_ = std::move(m.tree_);
  }
  return *this;
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::begin() {
  return tree_.begin();
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::end() {
  return tree_.end();
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::begin() const {
  return tree_.begin();
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::end() const {
  return tree_.end();
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::cbegin() const {
  return tree_.cbegin();
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::cend() const {
  return tree_.cend();
}

template <typename Key, typename T, typename Compare>
bool map<Key, T, Compare>::empty() const {
  return tree_.size() == 0;
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::size_type map<Key, T, Compare>::size() const {
  return tree_.size();
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::size_type map<Key, T, Compare>::max_size() const {
  return tree_.max_size();
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::mapped_type& map<Key, T, Compare>::at(const key_type& key) {
  value_type search_pair{key, mapped_type{}};
  Node<std::pair<const Key, T>>* node = tree_.find(search_pair);
  if (!node) {
    throw std::out_of_range("Key not found");
  }
  return node->val_.second;
}

template <typename Key, typename T, typename Compare>
const typename map<Key, T, Compare>::mapped_type& map<Key, T, Compare>::at(const key_type& key) const {
  value_type search_pair{key, mapped_type{}};
  Node<std::pair<const Key, T>>* node = tree_.find(search_pair);
  if (!node) {
    throw std::out_of_range("Key not found");
  }
  return node->val_.second;
}

template <typename Key, typename T, typename Compare>
typename map<Key, T, Compare>::mapped_type& map<Key, T, Compare>::operator[](const key_type& key) {
  value_type search_pair{key, mapped_type{}};
  Node<std::pair<const Key, T>>* node = tree_.find(search_pair);
  typename map<Key, T, Compare>::mapped_type* result = nullptr;

  if (node) {
    result = &(node->val_.second);
  } else {
    auto insert_result = tree_.insert(search_pair);
    result = &(insert_result.first->second);
  }

  return *result;
}

template <typename Key, typename T, typename Compare>
std::pair<typename map<Key, T, Compare>::iterator, bool>
map<Key, T, Compare>::insert(const value_type& value) {
  return tree_.insert(value);
}

template <typename Key, typename T, typename Compare>
std::pair<typename map<Key, T, Compare>::iterator, bool>
map<Key, T, Compare>::insert(const key_type& key, const mapped_type& obj) {
  return insert(value_type{key, obj});
}

template <typename Key, typename T, typename Compare>
std::pair<typename map<Key, T, Compare>::iterator, bool>
map<Key, T, Compare>::insert_or_assign(const key_type& key, const mapped_type& obj) {
  value_type search_pair{key, mapped_type{}};
  Node<std::pair<const Key, T>>* node = tree_.find(search_pair);
  std::pair<typename map<Key, T, Compare>::iterator, bool> result;

  if (node) {
    node->val_.second = obj;
    result = {iterator(node), false};
  } else {
    result = insert(value_type{key, obj});
  }

  return result;
}

template <typename Key, typename T, typename Compare>
void map<Key, T, Compare>::erase(iterator pos) {
  tree_.erase(*pos);
}

template <typename Key, typename T, typename Compare>
void map<Key, T, Compare>::clear() {
  tree_.clear();
}

template <typename Key, typename T, typename Compare>
void map<Key, T, Compare>::swap(map& other) {
  tree_.swap(other.tree_);
}

template <typename Key, typename T, typename Compare>
void map<Key, T, Compare>::merge(map& other) {
  for (auto it = other.begin(); it != other.end();) {
    auto current_it = it++;
    if (insert(*current_it).second) {
      other.erase(current_it);
    }
  }
}

template <typename Key, typename T, typename Compare>
bool map<Key, T, Compare>::contains(const key_type& key) const {
  value_type search_pair{key, mapped_type{}};
  return tree_.contains(search_pair);
}

template <typename Key, typename T, typename Compare>
template <typename... Args>
dn::vector<std::pair<typename map<Key, T, Compare>::iterator, bool>>
map<Key, T, Compare>::insert_many(Args&&... args) {
  dn::vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(args)), ...);
  return results;
}

}  // namespace dn
#endif