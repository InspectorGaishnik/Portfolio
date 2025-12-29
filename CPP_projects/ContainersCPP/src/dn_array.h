#ifndef DN_ARRAY_H_
#define DN_ARRAY_H_

#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace dn {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  T data_[N];

 public:
  array() = default;

  array(std::initializer_list<value_type> const &items) {
    if (items.size() > N) {
      throw std::out_of_range("Too many initializers");
    }
    std::copy(items.begin(), items.end(), data_);
  }

  array(const array &a) { std::copy(a.data_, a.data_ + N, data_); }

  array(array &&a) noexcept { std::copy(a.data_, a.data_ + N, data_); }

  ~array() = default;

  array &operator=(array &&a) noexcept {
    if (this != &a) {
      std::copy(a.data_, a.data_ + N, data_);
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("array::at");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference front() const { return data_[0]; }

  const_reference back() const { return data_[N - 1]; }

  iterator data() { return data_; }

  iterator begin() { return data_; }

  iterator end() { return data_ + N; }

  bool empty() const { return N == 0; }

  size_type size() const { return N; }

  size_type max_size() const { return N; }

  void swap(array &other) {
    for (size_type i = 0; i < N; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }

  void fill(const_reference value) { std::fill(begin(), end(), value); }
};
}  // namespace dn

#endif