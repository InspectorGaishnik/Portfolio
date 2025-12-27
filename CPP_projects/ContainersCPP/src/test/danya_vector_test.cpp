#include "../danya_vector.h"

#include <gtest/gtest.h>

#include <vector>

class stdTestVector {
 public:
  std::vector<int> emptyVec;
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  std::vector<int> vec2 = std::vector<int>(5);
};

class danyaTestVector {
 public:
  danya::vector<int> emptyVec;
  danya::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  danya::vector<int> vec2 = danya::vector<int>(5);
};

stdTestVector stdVector;
danyaTestVector danyaVector;

TEST(danyavectorTest, Test1) {
  int danyaErrorCodeEmpty = danyaVector.emptyVec.empty();
  int stdErrorCodeEmpty = stdVector.emptyVec.empty();

  int danyaErrorCodeEmpty2 = danyaVector.vec.empty();
  int stdErrorCodeEmpty2 = stdVector.emptyVec.empty();

  EXPECT_EQ(danyaErrorCodeEmpty, stdErrorCodeEmpty);
  EXPECT_NE(danyaErrorCodeEmpty2, stdErrorCodeEmpty2);
}

TEST(danyavectorTest, Test2) {
  int danyaErrorCodeSize = danyaVector.vec.size();
  int stdErrorCodeSize = stdVector.vec.size();

  EXPECT_EQ(danyaErrorCodeSize, stdErrorCodeSize);
}

TEST(danyavectorTest, Test3) {
  int danyaErrorCodeSize = danyaVector.vec.capacity();
  int stdErrorCodeSize = stdVector.vec.capacity();

  EXPECT_EQ(danyaErrorCodeSize, stdErrorCodeSize);
}

TEST(danyavectorTest, Test4) {
  int danyaErrorCodeSize = danyaVector.vec2.size();
  int stdErrorCodeSize = stdVector.vec2.size();

  EXPECT_EQ(danyaErrorCodeSize, stdErrorCodeSize);
}

TEST(danyavectorTest, Test5) {
  int danyaErrorCodeSize = danyaVector.vec2.capacity();
  int stdErrorCodeSize = stdVector.vec2.capacity();

  EXPECT_EQ(danyaErrorCodeSize, stdErrorCodeSize);
}

TEST(danyavectorTest, Test6) {
  for (size_t i = 0; i < danyaVector.vec2.size(); i++) {
    EXPECT_EQ(danyaVector.vec2[i], 0);
  }

  for (size_t i = 0; i < danyaVector.vec2.size(); i++) {
    EXPECT_EQ(danyaVector.vec2[i], stdVector.vec2[i]);
  }
}

TEST(danyavectorTest, Test7) { EXPECT_EQ(danyaVector.vec.size(), 7); }

TEST(danyavectorTest, Test8) {
  for (size_t i = 0; i < danyaVector.vec.size(); i++) {
    EXPECT_EQ(danyaVector.vec[i], i + 1);
  }
}

TEST(danyavectorTest, Test9) {
  danya::vector<int> danyacopy(danyaVector.vec);

  EXPECT_EQ(danyacopy.size(), danyaVector.vec.size());

  for (size_t i = 0; i < danyacopy.size(); i++) {
    EXPECT_EQ(danyacopy[i], danyaVector.vec[i]);
  }
}

TEST(danyavectorTest, Test10) {
  danya::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  danya::vector<int> moved(std::move(vec));

  EXPECT_EQ(moved.size(), 7);

  EXPECT_EQ(moved[0], 1);
  EXPECT_EQ(moved[1], 2);
  EXPECT_EQ(moved[2], 3);
  EXPECT_EQ(moved[3], 4);
  EXPECT_EQ(moved[4], 5);
  EXPECT_EQ(moved[5], 6);
  EXPECT_EQ(moved[6], 7);

  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_EQ(vec.data(), nullptr);
}

TEST(danyavectorTest, Test11) {
  danya::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  danya::vector<int> target;
  target = std::move(vec);

  EXPECT_EQ(target.size(), 7);

  EXPECT_EQ(target[0], 1);
  EXPECT_EQ(target[1], 2);
  EXPECT_EQ(target[2], 3);
  EXPECT_EQ(target[3], 4);
  EXPECT_EQ(target[4], 5);
  EXPECT_EQ(target[5], 6);
  EXPECT_EQ(target[6], 7);

  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_EQ(vec.data(), nullptr);
}

TEST(danyavectorTest, Test12) {
  EXPECT_EQ(danyaVector.vec.at(0), 1);
  EXPECT_EQ(danyaVector.vec.at(1), 2);
  EXPECT_EQ(danyaVector.vec.at(2), 3);
  EXPECT_EQ(danyaVector.vec.at(3), 4);
  EXPECT_EQ(danyaVector.vec.at(4), 5);
  EXPECT_EQ(danyaVector.vec.at(5), 6);
  EXPECT_EQ(danyaVector.vec.at(6), 7);
}

TEST(danyavectorTest, AtOutOfRange) {
  EXPECT_THROW(danyaVector.emptyVec.at(0), std::out_of_range);
  EXPECT_THROW(danyaVector.vec.at(7), std::out_of_range);
}

TEST(danyavectorTest, Front) {
  EXPECT_EQ(danyaVector.vec.front(), 1);
  EXPECT_THROW(danyaVector.emptyVec.front(), std::out_of_range);
}

TEST(danyavectorTest, Back) {
  EXPECT_EQ(danyaVector.vec.back(), 7);
  EXPECT_THROW(danyaVector.emptyVec.back(), std::out_of_range);
}

TEST(danyavectorTest, Data) {
  EXPECT_EQ(danyaVector.vec.data(), danyaVector.vec.begin());
  EXPECT_EQ(danyaVector.emptyVec.data(), nullptr);
}

TEST(danyavectorTest, Iterators) {
  int expected = 1;
  for (int* it = danyaVector.vec.begin(); it != danyaVector.vec.end(); it++) {
    EXPECT_EQ(*it, expected++);
  }
}

TEST(danyavectorTest, ConstIterators) {
  const danya::vector constVec = {1, 2, 3, 4, 5};
  int expected = 1;
  for (const int* it = constVec.cbegin();
       it != constVec.cbegin() + constVec.size(); it++) {
    EXPECT_EQ(*it, expected++);
  }
}

TEST(danyavectorTest, Empty) {
  int danyaErrorCodeEmpty = danyaVector.emptyVec.empty();
  int stdErrorCodeEmpty = stdVector.emptyVec.empty();
  EXPECT_EQ(danyaErrorCodeEmpty, stdErrorCodeEmpty);
  EXPECT_TRUE(danyaVector.emptyVec.empty());
  EXPECT_FALSE(danyaVector.vec.empty());
}

TEST(danyavectorTest, Size) {
  int danyaErrorCodeEmpty = danyaVector.emptyVec.size();
  int stdErrorCodeEmpty = stdVector.emptyVec.size();

  EXPECT_EQ(danyaErrorCodeEmpty, stdErrorCodeEmpty);
  EXPECT_EQ(danyaVector.emptyVec.size(), 0);
  EXPECT_EQ(danyaVector.vec.size(), 7);
}

TEST(danyavectorTest, MaxSize) {
  EXPECT_GT(danyaVector.vec.max_size(), 11110);
  EXPECT_GT(danyaVector.vec.max_size(), 461168601);
}

TEST(danyavectorTest, Reverse) {
  danya::vector<int> vec;
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
  EXPECT_EQ(vec.size(), 0);

  vec.push_back(1);
  vec.reserve(5);
  EXPECT_GE(vec.capacity(), 10);
}

TEST(danyavectorTest, Capacity) {
  danya::vector<int> vec{1, 2};
  EXPECT_EQ(vec.capacity(), 2);

  vec.reserve(20);
  EXPECT_EQ(vec.capacity(), 20);
}

TEST(danyavectorTest, ShrinkToFit) {
  danya::vector<int> vec;
  vec.reserve(10);
  vec.push_back(1);
  vec.push_back(2);

  EXPECT_GE(vec.capacity(), 10);
  EXPECT_EQ(vec.size(), 2);

  vec.shrink_to_fit();
  EXPECT_GE(vec.capacity(), 2);
  EXPECT_EQ(vec.size(), 2);
}

TEST(danyavectorTest, Clear) {
  danya::vector<int> vec{1, 2, 3};
  vec.clear();
  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.size(), 0);
  EXPECT_GE(vec.capacity(), 3);
}

TEST(danyavectorTest, Insert) {
  danya::vector<int> vec{1, 3, 4};
  auto it = vec.insert(vec.begin() + 1, 2);

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(*it, 2);
}

TEST(danyavectorTest, InsertAtEnd) {
  danya::vector<int> vec{1, 2, 3};
  auto it = vec.insert(vec.end(), 4);

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(*it, 4);
}

TEST(danyavectorTest, Erase) {
  danya::vector<int> vec{1, 2, 3, 4};
  vec.erase(vec.begin() + 1);

  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 3);
  EXPECT_EQ(vec[2], 4);
}

TEST(danyavectorTest, Push_back) {
  danya::vector<int> vec{1, 2, 3};
  vec.push_back(4);
  vec.push_back(5);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(danyavectorTest, Pop_back) {
  danya::vector<int> vec{1, 2, 3};
  vec.pop_back();

  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);

  vec.pop_back();
  vec.pop_back();
  EXPECT_TRUE(vec.empty());
}

TEST(danyavectorTest, Swap) {
  danya::vector<int> vec{1, 2, 3, 4};
  danya::vector<int> vec2{5, 6};

  vec.swap(vec2);

  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 5);
  EXPECT_EQ(vec[1], 6);

  EXPECT_EQ(vec2.size(), 4);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
  EXPECT_EQ(vec2[3], 4);
}

TEST(danyavectorTest, InsertMany) {
  danya::vector<int> vec{1, 5};
  vec.insert_many(vec.begin() + 1, 2, 3, 4);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(danyavectorTest, InsertManyBack) {
  danya::vector<int> vec{1, 2};
  vec.insert_many_back(3, 4, 5);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(danyavectorTest, LargeReserve) {
  danya::vector<int> vec;
  size_t large_size = 1000000;
  vec.reserve(large_size);
  EXPECT_EQ(vec.capacity(), large_size);
  EXPECT_EQ(vec.size(), 0);
}

TEST(danyavectorTest, MoveEmptyVector) {
  danya::vector<int> emptyVec;
  danya::vector<int> moved(std::move(emptyVec));

  EXPECT_TRUE(moved.empty());
  EXPECT_TRUE(emptyVec.empty());
}
