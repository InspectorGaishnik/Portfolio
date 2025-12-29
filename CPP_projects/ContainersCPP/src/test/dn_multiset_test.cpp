#include "../dn_multiset.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <set>
#include <vector>

TEST(MultisetTest, DefaultConstructor) {
  dn::multiset<int> ms;
  std::multiset<int> std_ms;
  EXPECT_EQ(ms.empty(), std_ms.empty());
  EXPECT_EQ(ms.size(), std_ms.size());
}

TEST(MultisetTest, InitializerListConstructor) {
  dn::multiset<int> ms{1, 2, 2, 3, 3, 3};
  std::multiset<int> std_ms{1, 2, 2, 3, 3, 3};
  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_TRUE(std::equal(ms.begin(), ms.end(), std_ms.begin()));
}

TEST(MultisetTest, CopyConstructor) {
  dn::multiset<int> ms1{1, 2, 2, 3};
  dn::multiset<int> ms2(ms1);
  std::multiset<int> std_ms1{1, 2, 2, 3};
  std::multiset<int> std_ms2(std_ms1);
  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_TRUE(std::equal(ms1.begin(), ms1.end(), ms2.begin()));
  EXPECT_TRUE(std::equal(ms2.begin(), ms2.end(), std_ms2.begin()));
}

TEST(MultisetTest, MoveConstructor) {
  dn::multiset<int> ms1{1, 2, 3};
  dn::multiset<int> ms2(std::move(ms1));
  std::multiset<int> std_ms1{1, 2, 3};
  std::multiset<int> std_ms2(std::move(std_ms1));
  EXPECT_EQ(ms2.size(), std_ms2.size());
  EXPECT_TRUE(std::equal(ms2.begin(), ms2.end(), std_ms2.begin()));
  EXPECT_TRUE(ms1.empty());
}

TEST(MultisetTest, MoveAssignment) {
  dn::multiset<int> ms1{1, 2, 3};
  dn::multiset<int> ms2;
  ms2 = std::move(ms1);
  std::multiset<int> std_ms1{1, 2, 3};
  std::multiset<int> std_ms2;
  std_ms2 = std::move(std_ms1);
  EXPECT_EQ(ms2.size(), std_ms2.size());
  EXPECT_TRUE(std::equal(ms2.begin(), ms2.end(), std_ms2.begin()));
  EXPECT_TRUE(ms1.empty());
}

TEST(MultisetTest, BeginEnd) {
  dn::multiset<int> ms{3, 1, 2};
  std::multiset<int> std_ms{3, 1, 2};
  auto it = ms.begin();
  auto std_it = std_ms.begin();
  EXPECT_EQ(*it, *std_it);
  ++it;
  ++std_it;
  EXPECT_EQ(*it, *std_it);
}

TEST(MultisetTest, Empty) {
  dn::multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  ms.insert(1);
  EXPECT_FALSE(ms.empty());
}

TEST(MultisetTest, Size) {
  dn::multiset<int> ms;
  EXPECT_EQ(ms.size(), 0);
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  EXPECT_EQ(ms.size(), 3);
}

TEST(MultisetTest, MaxSize) {
  dn::multiset<int> ms;
  EXPECT_GT(ms.max_size(), 0);
}

TEST(MultisetTest, Clear) {
  dn::multiset<int> ms{1, 2, 3};
  EXPECT_FALSE(ms.empty());
  ms.clear();
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

TEST(MultisetTest, Insert) {
  dn::multiset<int> ms;
  auto it = ms.insert(5);
  EXPECT_EQ(*it, 5);
  it = ms.insert(3);
  EXPECT_EQ(*it, 3);
  it = ms.insert(7);
  EXPECT_EQ(*it, 7);
  it = ms.insert(3);
  EXPECT_EQ(*it, 3);
  EXPECT_EQ(ms.size(), 4);
}

TEST(MultisetTest, Erase) {
  dn::multiset<int> ms{1, 2, 3, 2};
  std::multiset<int> std_ms{1, 2, 3, 2};
  auto it = ms.find(2);
  ms.erase(it);
  std_ms.erase(std_ms.find(2));
  EXPECT_EQ(ms.size(), std_ms.size());
  EXPECT_TRUE(std::equal(ms.begin(), ms.end(), std_ms.begin()));
}

TEST(MultisetTest, Swap) {
  dn::multiset<int> ms1{1, 2, 3};
  dn::multiset<int> ms2{4, 5};
  ms1.swap(ms2);
  EXPECT_EQ(ms1.size(), 2);
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms2.contains(1));
}

TEST(MultisetTest, Merge) {
  dn::multiset<int> ms1{1, 2, 3};
  dn::multiset<int> ms2{3, 4, 5};
  ms1.merge(ms2);
  EXPECT_EQ(ms1.size(), 6);
  EXPECT_EQ(ms2.size(), 0);
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms1.contains(5));
}

TEST(MultisetTest, Count) {
  dn::multiset<int> ms{1, 2, 2, 3, 3, 3};
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 3);
  EXPECT_EQ(ms.count(4), 0);
}

TEST(MultisetTest, Find) {
  dn::multiset<int> ms{1, 2, 3};
  auto it = ms.find(2);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 2);
  it = ms.find(4);
  EXPECT_EQ(it, ms.end());
}

TEST(MultisetTest, Contains) {
  dn::multiset<int> ms{1, 2, 3};
  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(4));
}

TEST(MultisetTest, EqualRange) {
  dn::multiset<int> ms{1, 2, 2, 3};
  auto range = ms.equal_range(2);
  auto it = range.first;
  int count = 0;
  while (it != range.second) {
    ++count;
    ++it;
  }
  EXPECT_EQ(count, 2);
}

TEST(MultisetTest, LowerBound) {
  dn::multiset<int> ms{1, 2, 3, 3, 4};
  auto it = ms.lower_bound(3);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 3);
}

TEST(MultisetTest, UpperBound) {
  dn::multiset<int> ms{1, 2, 3, 3, 4};
  auto it = ms.upper_bound(3);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 4);
}

TEST(MultisetTest, InsertMany) {
  dn::multiset<int> ms;
  auto results = ms.insert_many(1, 2, 3, 2, 1);
  EXPECT_EQ(ms.size(), 5);
  EXPECT_EQ(results.size(), 5);
  EXPECT_EQ(ms.count(1), 2);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 1);
}

TEST(MultisetTest, LargeInsertAndErase) {
  dn::multiset<int> ms;
  for (int i = 0; i < 1000; ++i) {
    ms.insert(i % 100);
  }
  EXPECT_EQ(ms.size(), 1000);

  for (int i = 0; i < 100; ++i) {
    auto range = ms.equal_range(i);
    while (range.first != range.second) {
      ms.erase(range.first++);
    }
  }
  EXPECT_EQ(ms.size(), 0);
}

TEST(MultisetTest, MemoryLeakCheck) {
  dn::multiset<int> *ms = new dn::multiset<int>{1, 2, 3, 4, 5};
  delete ms;
}

TEST(MultisetTest, IteratorIncrementDecrement) {
  dn::multiset<int> ms{1, 2, 3, 4, 5};
  auto it = ms.begin();
  ++it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
  it = ms.end();
  --it;
  EXPECT_EQ(*it, 5);
}

TEST(MultisetTest, ConstIterator) {
  const dn::multiset<int> ms{1, 2, 3};
  auto it = ms.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(MultisetTest, CompareWithStdMultiset) {
  dn::multiset<int> ms;
  std::multiset<int> std_ms;
  for (int i = 0; i < 100; ++i) {
    int val = rand() % 50;
    ms.insert(val);
    std_ms.insert(val);
  }
  EXPECT_TRUE(std::equal(ms.begin(), ms.end(), std_ms.begin()));
}

TEST(MultisetTest, EraseNonexistentElement) {
  dn::multiset<int> ms{1, 2, 3};
  auto it = ms.find(4);
  ms.erase(it);
  EXPECT_EQ(ms.size(), 3);
}

TEST(MultisetTest, InsertDuplicate) {
  dn::multiset<int> ms;
  ms.insert(1);
  ms.insert(1);
  ms.insert(1);
  EXPECT_EQ(ms.size(), 3);
  EXPECT_EQ(ms.count(1), 3);
}