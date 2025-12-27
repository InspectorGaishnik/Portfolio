#include "../danya_array.h"

#include <gtest/gtest.h>

#include <array>
#include <string>

TEST(ArrayTest, DefaultConstructor) {
  danya::array<int, 3> danya_arr{};
  std::array<int, 3> std_arr{};

  EXPECT_EQ(danya_arr.size(), std_arr.size());
  EXPECT_EQ(danya_arr.empty(), std_arr.empty());
}

TEST(ArrayTest, InitializerListConstructor) {
  danya::array<int, 5> danya_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(danya_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, InitializerListConstructorThrow) {
  EXPECT_THROW((danya::array<int, 2>{1, 2, 3}), std::out_of_range);
  EXPECT_THROW((danya::array<std::string, 1>{"a", "b"}), std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
  danya::array<int, 3> original = {1, 2, 3};
  danya::array<int, 3> copy(original);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(original[i], copy[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  danya::array<int, 3> original = {1, 2, 3};
  danya::array<int, 3> moved(std::move(original));

  danya::array<int, 3> expected = {1, 2, 3};
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(moved[i], expected[i]);
  }
}

TEST(ArrayTest, MoveAssignment) {
  danya::array<int, 3> original = {1, 2, 3};
  danya::array<int, 3> moved = {4, 5, 6};
  moved = std::move(original);

  danya::array<int, 3> expected = {1, 2, 3};
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(moved[i], expected[i]);
  }
}

TEST(ArrayTest, AtValid) {
  danya::array<int, 3> danya_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(danya_arr.at(0), std_arr.at(0));
  EXPECT_EQ(danya_arr.at(1), std_arr.at(1));
  EXPECT_EQ(danya_arr.at(2), std_arr.at(2));
}

TEST(ArrayTest, AtInvalid) {
  danya::array<int, 3> arr = {1, 2, 3};
  EXPECT_THROW(arr.at(3), std::out_of_range);
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(ArrayTest, SubscriptOperator) {
  danya::array<int, 3> danya_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(danya_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, Front) {
  danya::array<int, 3> danya_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(danya_arr.front(), std_arr.front());
}

TEST(ArrayTest, Back) {
  danya::array<int, 3> danya_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(danya_arr.back(), std_arr.back());
}

TEST(ArrayTest, Data) {
  danya::array<int, 3> danya_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(*danya_arr.data(), *std_arr.data());
  EXPECT_EQ(danya_arr.data()[1], std_arr.data()[1]);

  danya_arr.data()[0] = 42;
  EXPECT_EQ(danya_arr[0], 42);
}

TEST(ArrayTest, BeginEnd) {
  danya::array<int, 3> danya_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  auto danya_it = danya_arr.begin();
  auto std_it = std_arr.begin();

  while (danya_it != danya_arr.end() && std_it != std_arr.end()) {
    EXPECT_EQ(*danya_it++, *std_it++);
  }
}

TEST(ArrayTest, Empty) {
  danya::array<int, 0> empty_arr{};
  danya::array<int, 3> non_empty_arr = {1, 2, 3};

  EXPECT_TRUE(empty_arr.empty());
  EXPECT_FALSE(non_empty_arr.empty());
}

TEST(ArrayTest, Size) {
  danya::array<int, 0> arr0{};
  danya::array<int, 5> arr5{};
  danya::array<int, 10> arr10{};

  EXPECT_EQ(arr0.size(), 0);
  EXPECT_EQ(arr5.size(), 5);
  EXPECT_EQ(arr10.size(), 10);
}

TEST(ArrayTest, MaxSize) {
  danya::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayTest, Swap) {
  danya::array<int, 3> arr1 = {1, 2, 3};
  danya::array<int, 3> arr2 = {4, 5, 6};

  arr1.swap(arr2);

  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, Fill) {
  danya::array<int, 5> danya_arr{};
  std::array<int, 5> std_arr{};

  danya_arr.fill(42);
  std_arr.fill(42);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(danya_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, ZeroSizeArray) {
  danya::array<int, 0> danya_arr{};
  std::array<int, 0> std_arr{};

  EXPECT_EQ(danya_arr.size(), std_arr.size());
  EXPECT_EQ(danya_arr.empty(), std_arr.empty());
  EXPECT_EQ(danya_arr.max_size(), std_arr.max_size());

  EXPECT_EQ(danya_arr.begin(), danya_arr.end());
}

TEST(ArrayTest, ConstMethods) {
  const danya::array<int, 3> danya_arr = {1, 2, 3};
  const std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(danya_arr.front(), std_arr.front());
  EXPECT_EQ(danya_arr.back(), std_arr.back());
  EXPECT_EQ(danya_arr.size(), std_arr.size());
  EXPECT_EQ(danya_arr.empty(), std_arr.empty());
  EXPECT_EQ(danya_arr.max_size(), std_arr.max_size());
}

TEST(ArrayTest, IteratorArithmetic) {
  danya::array<int, 5> arr = {1, 2, 3, 4, 5};

  auto it = arr.begin();
  int val1 = *it;
  EXPECT_EQ(val1, 1);

  int val2 = *(it + 1);
  EXPECT_EQ(val2, 2);

  int val3 = *(it + 2);
  EXPECT_EQ(val3, 3);

  it += 3;
  int val4 = *it;
  EXPECT_EQ(val4, 4);

  auto it2 = arr.end() - 1;
  int val5 = *it2;
  EXPECT_EQ(val5, 5);
}

TEST(ArrayTest, LargeArrayMemory) {
  danya::array<int, 10000> danya_arr{};
  std::array<int, 10000> std_arr{};

  for (size_t i = 0; i < 10000; ++i) {
    danya_arr[i] = static_cast<int>(i);
    std_arr[i] = static_cast<int>(i);
  }

  for (size_t i = 0; i < 10000; ++i) {
    EXPECT_EQ(danya_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, StringArrayMemory) {
  danya::array<std::string, 3> danya_arr = {"hello", "world", "test"};
  std::array<std::string, 3> std_arr = {"hello", "world", "test"};

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(danya_arr[i], std_arr[i]);
  }

  danya_arr[0] = "modified";
  EXPECT_EQ(danya_arr[0], "modified");
}

TEST(ArrayTest, BoolArray) {
  danya::array<bool, 4> danya_arr = {true, false, true, false};
  std::array<bool, 4> std_arr = {true, false, true, false};

  for (size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(danya_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, ExceptionSafety) {
  danya::array<int, 3> arr = {1, 2, 3};

  try {
    arr.at(10);
    FAIL() << "Expected std::out_of_range";
  } catch (const std::out_of_range& e) {
    EXPECT_STREQ(e.what(), "array::at");
  } catch (...) {
    FAIL() << "Expected std::out_of_range, got different exception";
  }

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(arr[i], i + 1);
  }
}

TEST(ArrayTest, MoveFromEmptyArray) {
  danya::array<int, 0> empty1;
  danya::array<int, 0> empty2(std::move(empty1));
  danya::array<int, 0> empty3;
  empty3 = std::move(empty2);

  EXPECT_TRUE(empty3.empty());
}

TEST(ArrayTest, SelfSwap) {
  danya::array<int, 3> arr = {1, 2, 3};
  arr.swap(arr);

  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, MemoryAlignment) {
  struct AlignedStruct {
    alignas(64) int data;
  };

  danya::array<AlignedStruct, 4> arr;
  std::array<AlignedStruct, 4> std_arr;

  for (size_t i = 0; i < 4; ++i) {
    arr[i].data = static_cast<int>(i);
    std_arr[i].data = static_cast<int>(i);
    EXPECT_EQ(arr[i].data, std_arr[i].data);
  }
}

TEST(ArrayTest, IteratorComparison) {
  danya::array<int, 3> arr = {1, 2, 3};

  auto it1 = arr.begin();
  auto it2 = arr.begin();
  auto it3 = arr.end();

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
  EXPECT_TRUE(it1 != it3);
}

TEST(ArrayTest, ReverseIteration) {
  danya::array<int, 3> danya_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  int danya_sum = 0;
  for (auto it = danya_arr.end() - 1; it >= danya_arr.begin(); --it) {
    danya_sum += *it;
  }

  int std_sum = 0;
  for (auto it = std_arr.end() - 1; it >= std_arr.begin(); --it) {
    std_sum += *it;
  }

  EXPECT_EQ(danya_sum, std_sum);
}