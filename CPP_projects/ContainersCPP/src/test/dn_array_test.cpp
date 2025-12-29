#include "../dn_array.h"

#include <gtest/gtest.h>

#include <array>
#include <string>

TEST(ArrayTest, DefaultConstructor) {
  dn::array<int, 3> dn_arr{};
  std::array<int, 3> std_arr{};

  EXPECT_EQ(dn_arr.size(), std_arr.size());
  EXPECT_EQ(dn_arr.empty(), std_arr.empty());
}

TEST(ArrayTest, InitializerListConstructor) {
  dn::array<int, 5> dn_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(dn_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, InitializerListConstructorThrow) {
  EXPECT_THROW((dn::array<int, 2>{1, 2, 3}), std::out_of_range);
  EXPECT_THROW((dn::array<std::string, 1>{"a", "b"}), std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
  dn::array<int, 3> original = {1, 2, 3};
  dn::array<int, 3> copy(original);

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(original[i], copy[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  dn::array<int, 3> original = {1, 2, 3};
  dn::array<int, 3> moved(std::move(original));

  dn::array<int, 3> expected = {1, 2, 3};
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(moved[i], expected[i]);
  }
}

TEST(ArrayTest, MoveAssignment) {
  dn::array<int, 3> original = {1, 2, 3};
  dn::array<int, 3> moved = {4, 5, 6};
  moved = std::move(original);

  dn::array<int, 3> expected = {1, 2, 3};
  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(moved[i], expected[i]);
  }
}

TEST(ArrayTest, AtValid) {
  dn::array<int, 3> dn_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(dn_arr.at(0), std_arr.at(0));
  EXPECT_EQ(dn_arr.at(1), std_arr.at(1));
  EXPECT_EQ(dn_arr.at(2), std_arr.at(2));
}

TEST(ArrayTest, AtInvalid) {
  dn::array<int, 3> arr = {1, 2, 3};
  EXPECT_THROW(arr.at(3), std::out_of_range);
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(ArrayTest, SubscriptOperator) {
  dn::array<int, 3> dn_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(dn_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, Front) {
  dn::array<int, 3> dn_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(dn_arr.front(), std_arr.front());
}

TEST(ArrayTest, Back) {
  dn::array<int, 3> dn_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(dn_arr.back(), std_arr.back());
}

TEST(ArrayTest, Data) {
  dn::array<int, 3> dn_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(*dn_arr.data(), *std_arr.data());
  EXPECT_EQ(dn_arr.data()[1], std_arr.data()[1]);

  dn_arr.data()[0] = 42;
  EXPECT_EQ(dn_arr[0], 42);
}

TEST(ArrayTest, BeginEnd) {
  dn::array<int, 3> dn_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  auto dn_it = dn_arr.begin();
  auto std_it = std_arr.begin();

  while (dn_it != dn_arr.end() && std_it != std_arr.end()) {
    EXPECT_EQ(*dn_it++, *std_it++);
  }
}

TEST(ArrayTest, Empty) {
  dn::array<int, 0> empty_arr{};
  dn::array<int, 3> non_empty_arr = {1, 2, 3};

  EXPECT_TRUE(empty_arr.empty());
  EXPECT_FALSE(non_empty_arr.empty());
}

TEST(ArrayTest, Size) {
  dn::array<int, 0> arr0{};
  dn::array<int, 5> arr5{};
  dn::array<int, 10> arr10{};

  EXPECT_EQ(arr0.size(), 0);
  EXPECT_EQ(arr5.size(), 5);
  EXPECT_EQ(arr10.size(), 10);
}

TEST(ArrayTest, MaxSize) {
  dn::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayTest, Swap) {
  dn::array<int, 3> arr1 = {1, 2, 3};
  dn::array<int, 3> arr2 = {4, 5, 6};

  arr1.swap(arr2);

  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, Fill) {
  dn::array<int, 5> dn_arr{};
  std::array<int, 5> std_arr{};

  dn_arr.fill(42);
  std_arr.fill(42);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(dn_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, ZeroSizeArray) {
  dn::array<int, 0> dn_arr{};
  std::array<int, 0> std_arr{};

  EXPECT_EQ(dn_arr.size(), std_arr.size());
  EXPECT_EQ(dn_arr.empty(), std_arr.empty());
  EXPECT_EQ(dn_arr.max_size(), std_arr.max_size());

  EXPECT_EQ(dn_arr.begin(), dn_arr.end());
}

TEST(ArrayTest, ConstMethods) {
  const dn::array<int, 3> dn_arr = {1, 2, 3};
  const std::array<int, 3> std_arr = {1, 2, 3};

  EXPECT_EQ(dn_arr.front(), std_arr.front());
  EXPECT_EQ(dn_arr.back(), std_arr.back());
  EXPECT_EQ(dn_arr.size(), std_arr.size());
  EXPECT_EQ(dn_arr.empty(), std_arr.empty());
  EXPECT_EQ(dn_arr.max_size(), std_arr.max_size());
}

TEST(ArrayTest, IteratorArithmetic) {
  dn::array<int, 5> arr = {1, 2, 3, 4, 5};

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
  dn::array<int, 10000> dn_arr{};
  std::array<int, 10000> std_arr{};

  for (size_t i = 0; i < 10000; ++i) {
    dn_arr[i] = static_cast<int>(i);
    std_arr[i] = static_cast<int>(i);
  }

  for (size_t i = 0; i < 10000; ++i) {
    EXPECT_EQ(dn_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, StringArrayMemory) {
  dn::array<std::string, 3> dn_arr = {"hello", "world", "test"};
  std::array<std::string, 3> std_arr = {"hello", "world", "test"};

  for (size_t i = 0; i < 3; ++i) {
    EXPECT_EQ(dn_arr[i], std_arr[i]);
  }

  dn_arr[0] = "modified";
  EXPECT_EQ(dn_arr[0], "modified");
}

TEST(ArrayTest, BoolArray) {
  dn::array<bool, 4> dn_arr = {true, false, true, false};
  std::array<bool, 4> std_arr = {true, false, true, false};

  for (size_t i = 0; i < 4; ++i) {
    EXPECT_EQ(dn_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, ExceptionSafety) {
  dn::array<int, 3> arr = {1, 2, 3};

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
  dn::array<int, 0> empty1;
  dn::array<int, 0> empty2(std::move(empty1));
  dn::array<int, 0> empty3;
  empty3 = std::move(empty2);

  EXPECT_TRUE(empty3.empty());
}

TEST(ArrayTest, SelfSwap) {
  dn::array<int, 3> arr = {1, 2, 3};
  arr.swap(arr);

  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, MemoryAlignment) {
  struct AlignedStruct {
    alignas(64) int data;
  };

  dn::array<AlignedStruct, 4> arr;
  std::array<AlignedStruct, 4> std_arr;

  for (size_t i = 0; i < 4; ++i) {
    arr[i].data = static_cast<int>(i);
    std_arr[i].data = static_cast<int>(i);
    EXPECT_EQ(arr[i].data, std_arr[i].data);
  }
}

TEST(ArrayTest, IteratorComparison) {
  dn::array<int, 3> arr = {1, 2, 3};

  auto it1 = arr.begin();
  auto it2 = arr.begin();
  auto it3 = arr.end();

  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 == it3);
  EXPECT_TRUE(it1 != it3);
}

TEST(ArrayTest, ReverseIteration) {
  dn::array<int, 3> dn_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};

  int dn_sum = 0;
  for (auto it = dn_arr.end() - 1; it >= dn_arr.begin(); --it) {
    dn_sum += *it;
  }

  int std_sum = 0;
  for (auto it = std_arr.end() - 1; it >= std_arr.begin(); --it) {
    std_sum += *it;
  }

  EXPECT_EQ(dn_sum, std_sum);
}