#ifndef DANYA_STACK_H_
#define DANYA_STACK_H_

#include "danya_list.h"

namespace danya {

template <typename T>
class stack {
public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

private:
  list<T> container_;

public:
  stack() : container_() {}
  stack(std::initializer_list<value_type> const& items) : container_(items) {}
  stack(const stack& s) : container_(s.container_) {}
  stack(stack&& s) noexcept : container_(std::move(s.container_)) {}
  ~stack() = default;
  stack& operator=(stack&& s) noexcept {
    container_ = std::move(s.container_);
    return *this;
  }

  const_reference top() const { return container_.back(); }

  bool empty() const { return container_.empty(); }
  size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_back(); }
  void swap(stack& other) { container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    container_.insert_many_back(std::forward<Args>(args)...);
  }
};

}  // namespace danya

#endif
