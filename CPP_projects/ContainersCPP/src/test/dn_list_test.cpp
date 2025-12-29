#include "../dn_list.h"

#include <gtest/gtest.h>

#include <list>
#include <string>

TEST(dnListTest, DefaultConstructor) {
  std::list<int> std_empty;
  dn::list<int> dn_empty;

  EXPECT_EQ(std_empty.size(), dn_empty.size());
  EXPECT_EQ(std_empty.empty(), dn_empty.empty());
}

TEST(dnListTest, SizeConstructor) {
  std::list<int> std_list(5);
  dn::list<int> dn_list(5);

  EXPECT_EQ(std_list.size(), dn_list.size());
  EXPECT_FALSE(dn_list.empty());
}

TEST(dnListTest, InitializerListConstructor) {
  std::list<int> std_list = {1, 2, 3, 4, 5};
  dn::list<int> dn_list = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list.size(), dn_list.size());

  auto std_it = std_list.begin();
  auto dn_it = dn_list.begin();
  while (std_it != std_list.end() && dn_it != dn_list.end()) {
    EXPECT_EQ(*std_it, *dn_it);
    ++std_it;
    ++dn_it;
  }
}

TEST(dnListTest, CopyConstructor) {
  dn::list<int> original = {1, 2, 3, 4, 5};
  dn::list<int> copy(original);

  EXPECT_EQ(original.size(), copy.size());

  auto orig_it = original.begin();
  auto copy_it = copy.begin();
  while (orig_it != original.end() && copy_it != copy.end()) {
    EXPECT_EQ(*orig_it, *copy_it);
    ++orig_it;
    ++copy_it;
  }
}

TEST(dnListTest, MoveConstructor) {
  dn::list<int> original = {1, 2, 3, 4, 5};
  size_t original_size = original.size();

  dn::list<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), original_size);
  EXPECT_EQ(original.size(), 0);
  EXPECT_TRUE(original.empty());
}

TEST(dnListTest, MoveAssignment) {
  dn::list<int> original = {1, 2, 3, 4, 5};
  dn::list<int> target;

  target = std::move(original);

  EXPECT_EQ(target.size(), 5);
  EXPECT_EQ(original.size(), 0);
  EXPECT_TRUE(original.empty());
}

TEST(dnListTest, FrontBackAccess) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list.front(), dn_list.front());
  EXPECT_EQ(std_list.back(), dn_list.back());
}

TEST(dnListTest, Iterators) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_it = std_list.begin();
  auto dn_it = dn_list.begin();

  while (std_it != std_list.end() && dn_it != dn_list.end()) {
    EXPECT_EQ(*std_it, *dn_it);
    ++std_it;
    ++dn_it;
  }

  EXPECT_EQ(dn_it, dn_list.end());
}

TEST(dnListTest, Empty) {
  std::list<int> std_empty;
  dn::list<int> dn_empty;
  dn::list<int> dn_non_empty = {1, 2, 3};

  EXPECT_TRUE(std_empty.empty());
  EXPECT_TRUE(dn_empty.empty());
  EXPECT_FALSE(dn_non_empty.empty());
}

TEST(dnListTest, Size) {
  std::list<int> std_empty;
  dn::list<int> dn_empty;
  dn::list<int> dn_list = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_empty.size(), dn_empty.size());
  EXPECT_EQ(5, dn_list.size());
}

TEST(dnListTest, MaxSize) {
  dn::list<int> dn_list;
  std::list<int> std_list;

  EXPECT_GE(dn_list.max_size(), std_list.max_size());
}

TEST(dnListTest, Clear) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  dn_list.clear();
  EXPECT_TRUE(dn_list.empty());
  EXPECT_EQ(dn_list.size(), 0);
}

TEST(dnListTest, Insert) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_pos = std_list.begin();
  ++std_pos;
  auto dn_pos = dn_list.begin();
  ++dn_pos;

  auto std_result = std_list.insert(std_pos, 99);
  auto dn_result = dn_list.insert(dn_pos, 99);

  EXPECT_EQ(*std_result, *dn_result);
  EXPECT_EQ(std_list.size(), dn_list.size());

  auto std_it = std_list.begin();
  auto dn_it = dn_list.begin();
  while (std_it != std_list.end() && dn_it != dn_list.end()) {
    EXPECT_EQ(*std_it, *dn_it);
    ++std_it;
    ++dn_it;
  }
}

TEST(dnListTest, InsertAtEnd) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_result = std_list.insert(std_list.end(), 99);
  auto dn_result = dn_list.insert(dn_list.end(), 99);

  EXPECT_EQ(*std_result, *dn_result);
  EXPECT_EQ(std_list.back(), dn_list.back());
}

TEST(dnListTest, Erase) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_pos = std_list.begin();
  ++std_pos;
  auto dn_pos = dn_list.begin();
  ++dn_pos;

  std_list.erase(std_pos);
  dn_list.erase(dn_pos);

  EXPECT_EQ(std_list.size(), dn_list.size());

  auto std_it = std_list.begin();
  auto dn_it = dn_list.begin();
  while (std_it != std_list.end() && dn_it != dn_list.end()) {
    EXPECT_EQ(*std_it, *dn_it);
    ++std_it;
    ++dn_it;
  }
}

TEST(dnListTest, EraseBegin) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  std_list.erase(std_list.begin());
  dn_list.erase(dn_list.begin());

  EXPECT_EQ(std_list.front(), dn_list.front());
  EXPECT_EQ(std_list.size(), dn_list.size());
}

TEST(dnListTest, EraseEnd) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_pos = --std_list.end();
  auto dn_pos = --dn_list.end();

  std_list.erase(std_pos);
  dn_list.erase(dn_pos);

  EXPECT_EQ(std_list.back(), dn_list.back());
  EXPECT_EQ(std_list.size(), dn_list.size());
}

TEST(dnListTest, PushBack) {
  dn::list<int> dn_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  std_list.push_back(99);
  dn_list.push_back(99);

  EXPECT_EQ(std_list.back(), dn_list.back());
  EXPECT_EQ(std_list.size(), dn_list.size());
}

TEST(dnListTest, PopBack) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  std_list.pop_back();
  dn_list.pop_back();

  EXPECT_EQ(std_list.back(), dn_list.back());
  EXPECT_EQ(std_list.size(), dn_list.size());
}

TEST(dnListTest, PushFront) {
  dn::list<int> dn_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  std_list.push_front(99);
  dn_list.push_front(99);

  EXPECT_EQ(std_list.front(), dn_list.front());
  EXPECT_EQ(std_list.size(), dn_list.size());
}

TEST(dnListTest, PopFront) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  std_list.pop_front();
  dn_list.pop_front();

  EXPECT_EQ(std_list.front(), dn_list.front());
  EXPECT_EQ(std_list.size(), dn_list.size());
}

TEST(dnListTest, Swap) {
  dn::list<int> list1 = {1, 2, 3};
  dn::list<int> list2 = {4, 5, 6, 7};

  size_t size1 = list1.size();
  size_t size2 = list2.size();

  list1.swap(list2);

  EXPECT_EQ(list1.size(), size2);
  EXPECT_EQ(list2.size(), size1);
  EXPECT_EQ(list1.front(), 4);
  EXPECT_EQ(list2.front(), 1);
}

TEST(dnListTest, Merge) {
  dn::list<int> list1 = {1, 3, 5};
  dn::list<int> list2 = {2, 4, 6};
  std::list<int> std_list1 = {1, 3, 5};
  std::list<int> std_list2 = {2, 4, 6};

  list1.merge(list2);
  std_list1.merge(std_list2);

  EXPECT_EQ(list1.size(), std_list1.size());
  EXPECT_TRUE(list2.empty());

  auto std_it = std_list1.begin();
  auto dn_it = list1.begin();
  while (std_it != std_list1.end() && dn_it != list1.end()) {
    EXPECT_EQ(*std_it, *dn_it);
    ++std_it;
    ++dn_it;
  }
}

TEST(dnListTest, MergeEmpty) {
  dn::list<int> list1 = {1, 2, 3};
  dn::list<int> list2;

  size_t original_size = list1.size();
  list1.merge(list2);

  EXPECT_EQ(list1.size(), original_size);
  EXPECT_TRUE(list2.empty());
}

TEST(dnListTest, Splice) {
  dn::list<int> list1 = {1, 2, 3};
  dn::list<int> list2 = {4, 5, 6};
  std::list<int> std_list1 = {1, 2, 3};
  std::list<int> std_list2 = {4, 5, 6};

  auto dn_pos = ++list1.begin();
  auto std_pos = ++std_list1.begin();

  list1.splice(dn_pos, list2);
  std_list1.splice(std_pos, std_list2);

  EXPECT_EQ(list1.size(), std_list1.size());
  EXPECT_TRUE(list2.empty());

  auto std_it = std_list1.begin();
  auto dn_it = list1.begin();
  while (std_it != std_list1.end() && dn_it != list1.end()) {
    EXPECT_EQ(*std_it, *dn_it);
    ++std_it;
    ++dn_it;
  }
}

TEST(dnListTest, Reverse) {
  dn::list<int> dn_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  std_list.reverse();
  dn_list.reverse();

  EXPECT_EQ(std_list.size(), dn_list.size());

  auto std_it = std_list.begin();
  auto dn_it = dn_list.begin();
  while (std_it != std_list.end() && dn_it != dn_list.end()) {
    EXPECT_EQ(*std_it, *dn_it);
    ++std_it;
    ++dn_it;
  }
}

TEST(dnListTest, ReverseEmpty) {
  dn::list<int> empty_list;
  empty_list.reverse();
  EXPECT_TRUE(empty_list.empty());
}

TEST(dnListTest, Unique) {
  dn::list<int> list_with_duplicates = {1, 1, 2, 3, 3, 3, 4, 5, 5};
  std::list<int> std_list_with_duplicates = {1, 1, 2, 3, 3, 3, 4, 5, 5};

  list_with_duplicates.unique();
  std_list_with_duplicates.unique();

  EXPECT_EQ(list_with_duplicates.size(), std_list_with_duplicates.size());

  auto std_it = std_list_with_duplicates.begin();
  auto dn_it = list_with_duplicates.begin();
  while (std_it != std_list_with_duplicates.end() &&
         dn_it != list_with_duplicates.end()) {
    EXPECT_EQ(*std_it, *dn_it);
    ++std_it;
    ++dn_it;
  }
}

TEST(dnListTest, Sort) {
  dn::list<int> unsorted = {5, 3, 1, 4, 2};
  std::list<int> std_unsorted = {5, 3, 1, 4, 2};

  unsorted.sort();
  std_unsorted.sort();

  EXPECT_EQ(unsorted.size(), std_unsorted.size());

  auto std_it = std_unsorted.begin();
  auto dn_it = unsorted.begin();
  while (std_it != std_unsorted.end() && dn_it != unsorted.end()) {
    EXPECT_EQ(*std_it, *dn_it);
    ++std_it;
    ++dn_it;
  }
}

TEST(dnListTest, SortEmpty) {
  dn::list<int> empty_list;
  empty_list.sort();
  EXPECT_TRUE(empty_list.empty());
}

TEST(dnListTest, SortSingleElement) {
  dn::list<int> single_list = {42};
  single_list.sort();

  EXPECT_EQ(single_list.size(), 1);
  EXPECT_EQ(single_list.front(), 42);
}

TEST(dnListTest, InsertMany) {
  dn::list<int> list = {1, 2, 3};
  auto pos = ++list.begin();

  list.insert_many(pos, 4, 5, 6);

  EXPECT_EQ(list.size(), 6);

  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(dnListTest, InsertManyBack) {
  dn::list<int> list = {1, 2, 3};

  list.insert_many_back(4, 5, 6);

  EXPECT_EQ(list.size(), 6);
  EXPECT_EQ(list.back(), 6);

  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(dnListTest, InsertManyFront) {
  dn::list<int> list = {4, 5, 6};

  list.insert_many_front(1, 2, 3);

  EXPECT_EQ(list.size(), 6);
  EXPECT_EQ(list.front(), 1);

  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(dnListTest, StringOperations) {
  dn::list<std::string> dn_list = {"hello", "world"};
  std::list<std::string> std_list = {"hello", "world"};

  dn_list.push_back("test");
  std_list.push_back("test");

  dn_list.push_front("first");
  std_list.push_front("first");

  EXPECT_EQ(dn_list.size(), std_list.size());
  EXPECT_EQ(dn_list.front(), std_list.front());
  EXPECT_EQ(dn_list.back(), std_list.back());
}

TEST(dnListTest, LargeList) {
  const int size = 10000;
  dn::list<int> large_list;
  std::list<int> std_large_list;

  for (int i = 0; i < size; ++i) {
    large_list.push_back(i);
    std_large_list.push_back(i);
  }

  EXPECT_EQ(large_list.size(), std_large_list.size());
  EXPECT_EQ(large_list.front(), std_large_list.front());
  EXPECT_EQ(large_list.back(), std_large_list.back());
}

TEST(dnListTest, MoveToEmpty) {
  dn::list<int> empty;
  dn::list<int> full = {1, 2, 3};

  empty = std::move(full);

  EXPECT_EQ(empty.size(), 3);
  EXPECT_TRUE(full.empty());
}

TEST(dnListTest, IteratorIncrementDecrement) {
  dn::list<int> list = {1, 2, 3, 4, 5};
  auto it = list.begin();
  auto original = *it;

  ++it;
  --it;

  EXPECT_EQ(*it, original);
}

TEST(dnListTest, EdgeCaseEmptyOperations) {
  dn::list<int> empty;

  EXPECT_NO_THROW(empty.pop_back());
  EXPECT_NO_THROW(empty.pop_front());
  EXPECT_NO_THROW(empty.erase(empty.begin()));

  empty.clear();
  EXPECT_TRUE(empty.empty());
}

TEST(dnListTest, InsertAtInvalidPosition) {
  std::list<int> list = {1, 2, 3};
  std::list<int> empty;

  auto invalid_it = empty.begin();
  list.insert(invalid_it, 99);

  EXPECT_EQ(list.size(), 4);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
