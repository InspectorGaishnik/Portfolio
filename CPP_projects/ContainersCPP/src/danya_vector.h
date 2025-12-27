#ifndef DANYA_VECTOR_H_
#define DANYA_VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace danya {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;

 public:
  vector() : data_(nullptr), size_(0), capacity_(0) {}

  explicit vector(size_type n)
      : data_(n ? new T[n]() : nullptr), size_(n), capacity_(n) {}

  vector(std::initializer_list<value_type> const &items)
      : data_(new T[items.size()]),
        size_(items.size()),
        capacity_(items.size()) {
    std::copy(items.begin(), items.end(), data_);
  }

  vector(const vector &v)
      : data_(new T[v.capacity_]), size_(v.size_), capacity_(v.capacity_) {
    std::copy(v.data_, v.data_ + v.size_, data_);
  }

  vector(vector &&v) noexcept
      : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

  ~vector() { delete[] data_; }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] data_;
      data_ = v.data_;
      size_ = v.size_;
      capacity_ = v.capacity_;
      v.data_ = nullptr;
      v.size_ = 0;
      v.capacity_ = 0;
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_ || size_ == 0) throw std::out_of_range("vector::at");
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }
  const_reference front() const {
    if (empty()) throw std::out_of_range("vector::front on empty vector");
    return data_[0];
  }
  const_reference back() const {
    if (empty()) throw std::out_of_range("vector::back on empty vector");
    return data_[size_ - 1];
  }
  T *data() { return data_; }

  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }
  const_iterator cbegin() const { return data_; }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void reserve(size_type newCapacity) {
    if (newCapacity > capacity_) {
      T *new_data = new T[newCapacity];
      std::copy(data_, data_ + size_, new_data);
      delete[] data_;
      data_ = new_data;
      capacity_ = newCapacity;
    }
  }

  size_type capacity() const { return capacity_; }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      T *new_data = new T[size_];
      std::copy(data_, data_ + size_, new_data);
      delete[] data_;
      data_ = new_data;
      capacity_ = size_;
    }
  }

  void clear() { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - begin();
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    pos = begin() + index;
    std::move_backward(pos, end(), end() + 1);
    *pos = value;
    size_++;
    return pos;
  }

  void erase(iterator pos) {
    if (pos >= end()) return;
    std::move(pos + 1, end(), pos);
    size_--;
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
  }

  void pop_back() {
    if (size_ > 0) {
      size_--;
    }
  }

  void swap(vector &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    auto index = pos - cbegin();
    size_type count = sizeof...(Args);

    if (size_ + count > capacity_) {
      reserve(std::max(capacity_ * 2, size_ + count));
    }

    iterator insert_pos = begin() + index;

    std::move_backward(insert_pos, end(), end() + count);

    size_type i = 0;
    (void)std::initializer_list<int>{
        (*(insert_pos + i++) = std::forward<Args>(args), 0)...};

    size_ += count;
    return insert_pos;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }
};
}  // namespace danya
#endif