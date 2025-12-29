#include "../dn_vector.h"

#include <gtest/gtest.h>

#include <vector>

class stdTestVector {
 public:
  std::vector<int> emptyVec;
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  std::vector<int> vec2 = std::vector<int>(5);
};

class dnTestVector {
 public:
  dn::vector<int> emptyVec;
  dn::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  dn::vector<int> vec2 = dn::vector<int>(5);
};

stdTestVector stdVector;
dnTestVector dnVector;

TEST(dnvectorTest, Test1) {
  int dnErrorCodeEmpty = dnVector.emptyVec.empty();
  int stdErrorCodeEmpty = stdVector.emptyVec.empty();

  int dnErrorCodeEmpty2 = dnVector.vec.empty();
  int stdErrorCodeEmpty2 = stdVector.emptyVec.empty();

  EXPECT_EQ(dnErrorCodeEmpty, stdErrorCodeEmpty);
  EXPECT_NE(dnErrorCodeEmpty2, stdErrorCodeEmpty2);
}

TEST(dnvectorTest, Test2) {
  int dnErrorCodeSize = dnVector.vec.size();
  int stdErrorCodeSize = stdVector.vec.size();

  EXPECT_EQ(dnErrorCodeSize, stdErrorCodeSize);
}

TEST(dnvectorTest, Test3) {
  int dnErrorCodeSize = dnVector.vec.capacity();
  int stdErrorCodeSize = stdVector.vec.capacity();

  EXPECT_EQ(dnErrorCodeSize, stdErrorCodeSize);
}

TEST(dnvectorTest, Test4) {
  int dnErrorCodeSize = dnVector.vec2.size();
  int stdErrorCodeSize = stdVector.vec2.size();

  EXPECT_EQ(dnErrorCodeSize, stdErrorCodeSize);
}

TEST(dnvectorTest, Test5) {
  int dnErrorCodeSize = dnVector.vec2.capacity();
  int stdErrorCodeSize = stdVector.vec2.capacity();

  EXPECT_EQ(dnErrorCodeSize, stdErrorCodeSize);
}

TEST(dnvectorTest, Test6) {
  for (size_t i = 0; i < dnVector.vec2.size(); i++) {
    EXPECT_EQ(dnVector.vec2[i], 0);
  }

  for (size_t i = 0; i < dnVector.vec2.size(); i++) {
    EXPECT_EQ(dnVector.vec2[i], stdVector.vec2[i]);
  }
}

TEST(dnvectorTest, Test7) { EXPECT_EQ(dnVector.vec.size(), 7); }

TEST(dnvectorTest, Test8) {
  for (size_t i = 0; i < dnVector.vec.size(); i++) {
    EXPECT_EQ(dnVector.vec[i], i + 1);
  }
}

TEST(dnvectorTest, Test9) {
  dn::vector<int> dncopy(dnVector.vec);

  EXPECT_EQ(dncopy.size(), dnVector.vec.size());

  for (size_t i = 0; i < dncopy.size(); i++) {
    EXPECT_EQ(dncopy[i], dnVector.vec[i]);
  }
}

TEST(dnvectorTest, Test10) {
  dn::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  dn::vector<int> moved(std::move(vec));

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

TEST(dnvectorTest, Test11) {
  dn::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  dn::vector<int> target;
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

TEST(dnvectorTest, Test12) {
  EXPECT_EQ(dnVector.vec.at(0), 1);
  EXPECT_EQ(dnVector.vec.at(1), 2);
  EXPECT_EQ(dnVector.vec.at(2), 3);
  EXPECT_EQ(dnVector.vec.at(3), 4);
  EXPECT_EQ(dnVector.vec.at(4), 5);
  EXPECT_EQ(dnVector.vec.at(5), 6);
  EXPECT_EQ(dnVector.vec.at(6), 7);
}

TEST(dnvectorTest, AtOutOfRange) {
  EXPECT_THROW(dnVector.emptyVec.at(0), std::out_of_range);
  EXPECT_THROW(dnVector.vec.at(7), std::out_of_range);
}

TEST(dnvectorTest, Front) {
  EXPECT_EQ(dnVector.vec.front(), 1);
  EXPECT_THROW(dnVector.emptyVec.front(), std::out_of_range);
}

TEST(dnvectorTest, Back) {
  EXPECT_EQ(dnVector.vec.back(), 7);
  EXPECT_THROW(dnVector.emptyVec.back(), std::out_of_range);
}

TEST(dnvectorTest, Data) {
  EXPECT_EQ(dnVector.vec.data(), dnVector.vec.begin());
  EXPECT_EQ(dnVector.emptyVec.data(), nullptr);
}

TEST(dnvectorTest, Iterators) {
  int expected = 1;
  for (int* it = dnVector.vec.begin(); it != dnVector.vec.end(); it++) {
    EXPECT_EQ(*it, expected++);
  }
}

TEST(dnvectorTest, ConstIterators) {
  const dn::vector constVec = {1, 2, 3, 4, 5};
  int expected = 1;
  for (const int* it = constVec.cbegin();
       it != constVec.cbegin() + constVec.size(); it++) {
    EXPECT_EQ(*it, expected++);
  }
}

TEST(dnvectorTest, Empty) {
  int dnErrorCodeEmpty = dnVector.emptyVec.empty();
  int stdErrorCodeEmpty = stdVector.emptyVec.empty();
  EXPECT_EQ(dnErrorCodeEmpty, stdErrorCodeEmpty);
  EXPECT_TRUE(dnVector.emptyVec.empty());
  EXPECT_FALSE(dnVector.vec.empty());
}

TEST(dnvectorTest, Size) {
  int dnErrorCodeEmpty = dnVector.emptyVec.size();
  int stdErrorCodeEmpty = stdVector.emptyVec.size();

  EXPECT_EQ(dnErrorCodeEmpty, stdErrorCodeEmpty);
  EXPECT_EQ(dnVector.emptyVec.size(), 0);
  EXPECT_EQ(dnVector.vec.size(), 7);
}

TEST(dnvectorTest, MaxSize) {
  EXPECT_GT(dnVector.vec.max_size(), 11110);
  EXPECT_GT(dnVector.vec.max_size(), 461168601);
}

TEST(dnvectorTest, Reverse) {
  dn::vector<int> vec;
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
  EXPECT_EQ(vec.size(), 0);

  vec.push_back(1);
  vec.reserve(5);
  EXPECT_GE(vec.capacity(), 10);
}

TEST(dnvectorTest, Capacity) {
  dn::vector<int> vec{1, 2};
  EXPECT_EQ(vec.capacity(), 2);

  vec.reserve(20);
  EXPECT_EQ(vec.capacity(), 20);
}

TEST(dnvectorTest, ShrinkToFit) {
  dn::vector<int> vec;
  vec.reserve(10);
  vec.push_back(1);
  vec.push_back(2);

  EXPECT_GE(vec.capacity(), 10);
  EXPECT_EQ(vec.size(), 2);

  vec.shrink_to_fit();
  EXPECT_GE(vec.capacity(), 2);
  EXPECT_EQ(vec.size(), 2);
}

TEST(dnvectorTest, Clear) {
  dn::vector<int> vec{1, 2, 3};
  vec.clear();
  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.size(), 0);
  EXPECT_GE(vec.capacity(), 3);
}

TEST(dnvectorTest, Insert) {
  dn::vector<int> vec{1, 3, 4};
  auto it = vec.insert(vec.begin() + 1, 2);

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(*it, 2);
}

TEST(dnvectorTest, InsertAtEnd) {
  dn::vector<int> vec{1, 2, 3};
  auto it = vec.insert(vec.end(), 4);

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(*it, 4);
}

TEST(dnvectorTest, Erase) {
  dn::vector<int> vec{1, 2, 3, 4};
  vec.erase(vec.begin() + 1);

  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 3);
  EXPECT_EQ(vec[2], 4);
}

TEST(dnvectorTest, Push_back) {
  dn::vector<int> vec{1, 2, 3};
  vec.push_back(4);
  vec.push_back(5);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(dnvectorTest, Pop_back) {
  dn::vector<int> vec{1, 2, 3};
  vec.pop_back();

  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);

  vec.pop_back();
  vec.pop_back();
  EXPECT_TRUE(vec.empty());
}

TEST(dnvectorTest, Swap) {
  dn::vector<int> vec{1, 2, 3, 4};
  dn::vector<int> vec2{5, 6};

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

TEST(dnvectorTest, InsertMany) {
  dn::vector<int> vec{1, 5};
  vec.insert_many(vec.begin() + 1, 2, 3, 4);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(dnvectorTest, InsertManyBack) {
  dn::vector<int> vec{1, 2};
  vec.insert_many_back(3, 4, 5);

  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(dnvectorTest, LargeReserve) {
  dn::vector<int> vec;
  size_t large_size = 1000000;
  vec.reserve(large_size);
  EXPECT_EQ(vec.capacity(), large_size);
  EXPECT_EQ(vec.size(), 0);
}

TEST(dnvectorTest, MoveEmptyVector) {
  dn::vector<int> emptyVec;
  dn::vector<int> moved(std::move(emptyVec));

  EXPECT_TRUE(moved.empty());
  EXPECT_TRUE(emptyVec.empty());
}
