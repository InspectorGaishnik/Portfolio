#include "../danya_list.h"

#include <gtest/gtest.h>

#include <list>
#include <string>

TEST(danyaListTest, DefaultConstructor) {
  std::list<int> std_empty;
  danya::list<int> danya_empty;

  EXPECT_EQ(std_empty.size(), danya_empty.size());
  EXPECT_EQ(std_empty.empty(), danya_empty.empty());
}

TEST(danyaListTest, SizeConstructor) {
  std::list<int> std_list(5);
  danya::list<int> danya_list(5);

  EXPECT_EQ(std_list.size(), danya_list.size());
  EXPECT_FALSE(danya_list.empty());
}

TEST(danyaListTest, InitializerListConstructor) {
  std::list<int> std_list = {1, 2, 3, 4, 5};
  danya::list<int> danya_list = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list.size(), danya_list.size());

  auto std_it = std_list.begin();
  auto danya_it = danya_list.begin();
  while (std_it != std_list.end() && danya_it != danya_list.end()) {
    EXPECT_EQ(*std_it, *danya_it);
    ++std_it;
    ++danya_it;
  }
}

TEST(danyaListTest, CopyConstructor) {
  danya::list<int> original = {1, 2, 3, 4, 5};
  danya::list<int> copy(original);

  EXPECT_EQ(original.size(), copy.size());

  auto orig_it = original.begin();
  auto copy_it = copy.begin();
  while (orig_it != original.end() && copy_it != copy.end()) {
    EXPECT_EQ(*orig_it, *copy_it);
    ++orig_it;
    ++copy_it;
  }
}

TEST(danyaListTest, MoveConstructor) {
  danya::list<int> original = {1, 2, 3, 4, 5};
  size_t original_size = original.size();

  danya::list<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), original_size);
  EXPECT_EQ(original.size(), 0);
  EXPECT_TRUE(original.empty());
}

TEST(danyaListTest, MoveAssignment) {
  danya::list<int> original = {1, 2, 3, 4, 5};
  danya::list<int> target;

  target = std::move(original);

  EXPECT_EQ(target.size(), 5);
  EXPECT_EQ(original.size(), 0);
  EXPECT_TRUE(original.empty());
}

TEST(danyaListTest, FrontBackAccess) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list.front(), danya_list.front());
  EXPECT_EQ(std_list.back(), danya_list.back());
}

TEST(danyaListTest, Iterators) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_it = std_list.begin();
  auto danya_it = danya_list.begin();

  while (std_it != std_list.end() && danya_it != danya_list.end()) {
    EXPECT_EQ(*std_it, *danya_it);
    ++std_it;
    ++danya_it;
  }

  EXPECT_EQ(danya_it, danya_list.end());
}

TEST(danyaListTest, Empty) {
  std::list<int> std_empty;
  danya::list<int> danya_empty;
  danya::list<int> danya_non_empty = {1, 2, 3};

  EXPECT_TRUE(std_empty.empty());
  EXPECT_TRUE(danya_empty.empty());
  EXPECT_FALSE(danya_non_empty.empty());
}

TEST(danyaListTest, Size) {
  std::list<int> std_empty;
  danya::list<int> danya_empty;
  danya::list<int> danya_list = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_empty.size(), danya_empty.size());
  EXPECT_EQ(5, danya_list.size());
}

TEST(danyaListTest, MaxSize) {
  danya::list<int> danya_list;
  std::list<int> std_list;

  EXPECT_GE(danya_list.max_size(), std_list.max_size());
}

TEST(danyaListTest, Clear) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  danya_list.clear();
  EXPECT_TRUE(danya_list.empty());
  EXPECT_EQ(danya_list.size(), 0);
}

TEST(danyaListTest, Insert) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_pos = std_list.begin();
  ++std_pos;
  auto danya_pos = danya_list.begin();
  ++danya_pos;

  auto std_result = std_list.insert(std_pos, 99);
  auto danya_result = danya_list.insert(danya_pos, 99);

  EXPECT_EQ(*std_result, *danya_result);
  EXPECT_EQ(std_list.size(), danya_list.size());

  auto std_it = std_list.begin();
  auto danya_it = danya_list.begin();
  while (std_it != std_list.end() && danya_it != danya_list.end()) {
    EXPECT_EQ(*std_it, *danya_it);
    ++std_it;
    ++danya_it;
  }
}

TEST(danyaListTest, InsertAtEnd) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_result = std_list.insert(std_list.end(), 99);
  auto danya_result = danya_list.insert(danya_list.end(), 99);

  EXPECT_EQ(*std_result, *danya_result);
  EXPECT_EQ(std_list.back(), danya_list.back());
}

TEST(danyaListTest, Erase) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_pos = std_list.begin();
  ++std_pos;
  auto danya_pos = danya_list.begin();
  ++danya_pos;

  std_list.erase(std_pos);
  danya_list.erase(danya_pos);

  EXPECT_EQ(std_list.size(), danya_list.size());

  auto std_it = std_list.begin();
  auto danya_it = danya_list.begin();
  while (std_it != std_list.end() && danya_it != danya_list.end()) {
    EXPECT_EQ(*std_it, *danya_it);
    ++std_it;
    ++danya_it;
  }
}

TEST(danyaListTest, EraseBegin) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  std_list.erase(std_list.begin());
  danya_list.erase(danya_list.begin());

  EXPECT_EQ(std_list.front(), danya_list.front());
  EXPECT_EQ(std_list.size(), danya_list.size());
}

TEST(danyaListTest, EraseEnd) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  auto std_pos = --std_list.end();
  auto danya_pos = --danya_list.end();

  std_list.erase(std_pos);
  danya_list.erase(danya_pos);

  EXPECT_EQ(std_list.back(), danya_list.back());
  EXPECT_EQ(std_list.size(), danya_list.size());
}

TEST(danyaListTest, PushBack) {
  danya::list<int> danya_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  std_list.push_back(99);
  danya_list.push_back(99);

  EXPECT_EQ(std_list.back(), danya_list.back());
  EXPECT_EQ(std_list.size(), danya_list.size());
}

TEST(danyaListTest, PopBack) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  std_list.pop_back();
  danya_list.pop_back();

  EXPECT_EQ(std_list.back(), danya_list.back());
  EXPECT_EQ(std_list.size(), danya_list.size());
}

TEST(danyaListTest, PushFront) {
  danya::list<int> danya_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  std_list.push_front(99);
  danya_list.push_front(99);

  EXPECT_EQ(std_list.front(), danya_list.front());
  EXPECT_EQ(std_list.size(), danya_list.size());
}

TEST(danyaListTest, PopFront) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  std_list.pop_front();
  danya_list.pop_front();

  EXPECT_EQ(std_list.front(), danya_list.front());
  EXPECT_EQ(std_list.size(), danya_list.size());
}

TEST(danyaListTest, Swap) {
  danya::list<int> list1 = {1, 2, 3};
  danya::list<int> list2 = {4, 5, 6, 7};

  size_t size1 = list1.size();
  size_t size2 = list2.size();

  list1.swap(list2);

  EXPECT_EQ(list1.size(), size2);
  EXPECT_EQ(list2.size(), size1);
  EXPECT_EQ(list1.front(), 4);
  EXPECT_EQ(list2.front(), 1);
}

TEST(danyaListTest, Merge) {
  danya::list<int> list1 = {1, 3, 5};
  danya::list<int> list2 = {2, 4, 6};
  std::list<int> std_list1 = {1, 3, 5};
  std::list<int> std_list2 = {2, 4, 6};

  list1.merge(list2);
  std_list1.merge(std_list2);

  EXPECT_EQ(list1.size(), std_list1.size());
  EXPECT_TRUE(list2.empty());

  auto std_it = std_list1.begin();
  auto danya_it = list1.begin();
  while (std_it != std_list1.end() && danya_it != list1.end()) {
    EXPECT_EQ(*std_it, *danya_it);
    ++std_it;
    ++danya_it;
  }
}

TEST(danyaListTest, MergeEmpty) {
  danya::list<int> list1 = {1, 2, 3};
  danya::list<int> list2;

  size_t original_size = list1.size();
  list1.merge(list2);

  EXPECT_EQ(list1.size(), original_size);
  EXPECT_TRUE(list2.empty());
}

TEST(danyaListTest, Splice) {
  danya::list<int> list1 = {1, 2, 3};
  danya::list<int> list2 = {4, 5, 6};
  std::list<int> std_list1 = {1, 2, 3};
  std::list<int> std_list2 = {4, 5, 6};

  auto danya_pos = ++list1.begin();
  auto std_pos = ++std_list1.begin();

  list1.splice(danya_pos, list2);
  std_list1.splice(std_pos, std_list2);

  EXPECT_EQ(list1.size(), std_list1.size());
  EXPECT_TRUE(list2.empty());

  auto std_it = std_list1.begin();
  auto danya_it = list1.begin();
  while (std_it != std_list1.end() && danya_it != list1.end()) {
    EXPECT_EQ(*std_it, *danya_it);
    ++std_it;
    ++danya_it;
  }
}

TEST(danyaListTest, Reverse) {
  danya::list<int> danya_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  std_list.reverse();
  danya_list.reverse();

  EXPECT_EQ(std_list.size(), danya_list.size());

  auto std_it = std_list.begin();
  auto danya_it = danya_list.begin();
  while (std_it != std_list.end() && danya_it != danya_list.end()) {
    EXPECT_EQ(*std_it, *danya_it);
    ++std_it;
    ++danya_it;
  }
}

TEST(danyaListTest, ReverseEmpty) {
  danya::list<int> empty_list;
  empty_list.reverse();
  EXPECT_TRUE(empty_list.empty());
}

TEST(danyaListTest, Unique) {
  danya::list<int> list_with_duplicates = {1, 1, 2, 3, 3, 3, 4, 5, 5};
  std::list<int> std_list_with_duplicates = {1, 1, 2, 3, 3, 3, 4, 5, 5};

  list_with_duplicates.unique();
  std_list_with_duplicates.unique();

  EXPECT_EQ(list_with_duplicates.size(), std_list_with_duplicates.size());

  auto std_it = std_list_with_duplicates.begin();
  auto danya_it = list_with_duplicates.begin();
  while (std_it != std_list_with_duplicates.end() &&
         danya_it != list_with_duplicates.end()) {
    EXPECT_EQ(*std_it, *danya_it);
    ++std_it;
    ++danya_it;
  }
}

TEST(danyaListTest, Sort) {
  danya::list<int> unsorted = {5, 3, 1, 4, 2};
  std::list<int> std_unsorted = {5, 3, 1, 4, 2};

  unsorted.sort();
  std_unsorted.sort();

  EXPECT_EQ(unsorted.size(), std_unsorted.size());

  auto std_it = std_unsorted.begin();
  auto danya_it = unsorted.begin();
  while (std_it != std_unsorted.end() && danya_it != unsorted.end()) {
    EXPECT_EQ(*std_it, *danya_it);
    ++std_it;
    ++danya_it;
  }
}

TEST(danyaListTest, SortEmpty) {
  danya::list<int> empty_list;
  empty_list.sort();
  EXPECT_TRUE(empty_list.empty());
}

TEST(danyaListTest, SortSingleElement) {
  danya::list<int> single_list = {42};
  single_list.sort();

  EXPECT_EQ(single_list.size(), 1);
  EXPECT_EQ(single_list.front(), 42);
}

TEST(danyaListTest, InsertMany) {
  danya::list<int> list = {1, 2, 3};
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

TEST(danyaListTest, InsertManyBack) {
  danya::list<int> list = {1, 2, 3};

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

TEST(danyaListTest, InsertManyFront) {
  danya::list<int> list = {4, 5, 6};

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

TEST(danyaListTest, StringOperations) {
  danya::list<std::string> danya_list = {"hello", "world"};
  std::list<std::string> std_list = {"hello", "world"};

  danya_list.push_back("test");
  std_list.push_back("test");

  danya_list.push_front("first");
  std_list.push_front("first");

  EXPECT_EQ(danya_list.size(), std_list.size());
  EXPECT_EQ(danya_list.front(), std_list.front());
  EXPECT_EQ(danya_list.back(), std_list.back());
}

TEST(danyaListTest, LargeList) {
  const int size = 10000;
  danya::list<int> large_list;
  std::list<int> std_large_list;

  for (int i = 0; i < size; ++i) {
    large_list.push_back(i);
    std_large_list.push_back(i);
  }

  EXPECT_EQ(large_list.size(), std_large_list.size());
  EXPECT_EQ(large_list.front(), std_large_list.front());
  EXPECT_EQ(large_list.back(), std_large_list.back());
}

TEST(danyaListTest, MoveToEmpty) {
  danya::list<int> empty;
  danya::list<int> full = {1, 2, 3};

  empty = std::move(full);

  EXPECT_EQ(empty.size(), 3);
  EXPECT_TRUE(full.empty());
}

TEST(danyaListTest, IteratorIncrementDecrement) {
  danya::list<int> list = {1, 2, 3, 4, 5};
  auto it = list.begin();
  auto original = *it;

  ++it;
  --it;

  EXPECT_EQ(*it, original);
}

TEST(danyaListTest, EdgeCaseEmptyOperations) {
  danya::list<int> empty;

  EXPECT_NO_THROW(empty.pop_back());
  EXPECT_NO_THROW(empty.pop_front());
  EXPECT_NO_THROW(empty.erase(empty.begin()));

  empty.clear();
  EXPECT_TRUE(empty.empty());
}

TEST(danyaListTest, InsertAtInvalidPosition) {
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
