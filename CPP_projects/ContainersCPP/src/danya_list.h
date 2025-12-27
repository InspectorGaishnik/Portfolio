#ifndef DANYA_LIST_H_
#define DANYA_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

namespace danya {

template <typename T>
class list {
 private:
  struct Node {
    T value;
    Node* next;
    Node* prev;

    Node() : next(nullptr), prev(nullptr) {}
    explicit Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
    explicit Node(T&& val)
        : value(std::move(val)), next(nullptr), prev(nullptr) {}
  };

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class ListIterator;
  class ListConstIterator;

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  class ListIterator {
   public:
    ListIterator() : node_(nullptr) {}
    explicit ListIterator(Node* node) : node_(node) {}

    reference operator*() const { return node_->value; }
    ListIterator& operator++() {
      if (node_) node_ = node_->next;
      return *this;
    }
    ListIterator& operator--() {
      if (node_) node_ = node_->prev;
      return *this;
    }
    bool operator==(const ListIterator& other) const {
      return node_ == other.node_;
    }
    bool operator!=(const ListIterator& other) const {
      return node_ != other.node_;
    }

   private:
    Node* node_;
    friend class list<T>;
  };

  class ListConstIterator {
   public:
    ListConstIterator() : node_(nullptr) {}
    explicit ListConstIterator(const Node* node) : node_(node) {}
    ListConstIterator(const ListIterator& it) : node_(it.node_) {}

    const_reference operator*() const { return node_->value; }
    ListConstIterator& operator++() {
      if (node_) node_ = node_->next;
      return *this;
    }
    ListConstIterator& operator--() {
      if (node_) node_ = node_->prev;
      return *this;
    }
    bool operator==(const ListConstIterator& other) const {
      return node_ == other.node_;
    }
    bool operator!=(const ListConstIterator& other) const {
      return node_ != other.node_;
    }

   private:
    const Node* node_;
    friend class list<T>;
  };

  list() : size_(0) {
    dummy_ = new Node();
    dummy_->next = dummy_;
    dummy_->prev = dummy_;
  }

  explicit list(size_type n) : list() {
    for (size_type i = 0; i < n; ++i) {
      push_back(T());
    }
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (const auto& item : items) {
      push_back(item);
    }
  }

  list(const list& l) : list() {
    Node* current = l.dummy_->next;
    while (current != l.dummy_) {
      push_back(current->value);
      current = current->next;
    }
  }

  list(list&& l) noexcept : dummy_(l.dummy_), size_(l.size_) {
    l.dummy_ = new Node();
    l.dummy_->next = l.dummy_;
    l.dummy_->prev = l.dummy_;
    l.size_ = 0;
  }

  ~list() {
    clear();
    delete dummy_;
  }

  list& operator=(list&& l) noexcept {
    if (this != &l) {
      clear();
      delete dummy_;
      dummy_ = l.dummy_;
      size_ = l.size_;
      l.dummy_ = new Node();
      l.dummy_->next = l.dummy_;
      l.dummy_->prev = l.dummy_;
      l.size_ = 0;
    }
    return *this;
  }

  const_reference front() const { return dummy_->next->value; }
  const_reference back() const { return dummy_->prev->value; }

  iterator begin() { return iterator(dummy_->next); }
  iterator end() { return iterator(dummy_); }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  iterator insert(iterator pos, const_reference value) {
    Node* new_node = new Node(value);
    Node* pos_node = pos.node_;
    Node* prev_node = pos_node->prev;

    new_node->next = pos_node;
    new_node->prev = prev_node;
    prev_node->next = new_node;
    pos_node->prev = new_node;

    ++size_;
    return iterator(new_node);
  }

  void erase(iterator pos) {
    if (pos.node_ == dummy_ || empty()) {
      return;
    }

    Node* node_to_delete = pos.node_;
    Node* prev_node = node_to_delete->prev;
    Node* next_node = node_to_delete->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    delete node_to_delete;
    --size_;
  }

  void push_back(const_reference value) { insert(end(), value); }
  void pop_back() {
    if (!empty()) {
      erase(iterator(dummy_->prev));
    }
  }
  void push_front(const_reference value) { insert(begin(), value); }
  void pop_front() {
    if (!empty()) {
      erase(begin());
    }
  }

  void swap(list& other) {
    std::swap(dummy_, other.dummy_);
    std::swap(size_, other.size_);
  }

  void merge(list& other) {
    if (this == &other || other.empty()) return;

    iterator this_it = begin();
    while (this_it.node_ != dummy_ && !other.empty()) {
      if (other.front() < *this_it) {
        Node* node_to_move = other.dummy_->next;

        other.dummy_->next = node_to_move->next;
        node_to_move->next->prev = other.dummy_;
        --other.size_;

        Node* this_node = this_it.node_;
        Node* prev_node = this_node->prev;

        prev_node->next = node_to_move;
        node_to_move->prev = prev_node;
        node_to_move->next = this_node;
        this_node->prev = node_to_move;
        ++size_;
      } else {
        ++this_it;
      }
    }

    if (!other.empty()) {
      splice(end(), other);
    }
  }

  void splice(const_iterator pos, list& other) {
    if (other.empty()) return;

    Node* pos_node = const_cast<Node*>(pos.node_);
    Node* first = other.dummy_->next;
    Node* last = other.dummy_->prev;
    Node* prev_node = pos_node->prev;

    prev_node->next = first;
    first->prev = prev_node;
    last->next = pos_node;
    pos_node->prev = last;

    size_ += other.size_;

    other.dummy_->next = other.dummy_;
    other.dummy_->prev = other.dummy_;
    other.size_ = 0;
  }

  void reverse() {
    if (size_ <= 1) return;
    Node* current = dummy_;
    do {
      std::swap(current->next, current->prev);
      current = current->prev;
    } while (current != dummy_);
  }

  void unique() {
    if (size_ <= 1) return;
    iterator it = begin();
    iterator next = it;
    ++next;
    while (next != end()) {
      if (*it == *next) {
        iterator to_erase = next;
        ++next;
        erase(to_erase);
      } else {
        it = next;
        ++next;
      }
    }
  }

  void sort() {
    if (size_ <= 1) return;
    bool swapped;
    do {
      swapped = false;
      for (iterator it = begin(); it != end(); ++it) {
        iterator next = it;
        ++next;
        if (next != end() && *next < *it) {
          std::swap(*it, *next);
          swapped = true;
        }
      }
    } while (swapped);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    iterator non_const_pos(const_cast<Node*>(pos.node_));

    (insert(non_const_pos, value_type(std::forward<Args>(args))), ...);

    return iterator(const_cast<Node*>(pos.node_));
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    value_type temp_args[] = {std::forward<Args>(args)...};

    for (size_t i = sizeof...(Args); i > 0; --i) {
      push_front(temp_args[i - 1]);
    }
  }

 private:
  Node* dummy_;
  size_type size_;
};

}  // namespace danya

#endif