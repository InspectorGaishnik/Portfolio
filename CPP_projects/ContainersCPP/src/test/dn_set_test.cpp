#include "../dn_set.h"

#include <gtest/gtest.h>

#include <set>
#include <string>

TEST(SetTest, DefaultConstructor) {
  dn::set<int> s1;
  std::set<int> s2;
  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(SetTest, InitializerListConstructor) {
  dn::set<int> s1{1, 2, 3, 4, 5};
  std::set<int> s2{1, 2, 3, 4, 5};

  auto it1 = s1.begin();
  auto it2 = s2.begin();
  while (it1 != s1.end() && it2 != s2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(SetTest, CopyConstructor) {
  dn::set<int> s1{1, 2, 3};
  dn::set<int> s2(s1);

  EXPECT_EQ(s1.size(), s2.size());
  auto it1 = s1.begin();
  auto it2 = s2.begin();
  while (it1 != s1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(SetTest, MoveConstructor) {
  dn::set<int> s1{1, 2, 3};
  dn::set<int> s2(std::move(s1));

  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, MoveAssignment) {
  dn::set<int> s1{1, 2, 3};
  dn::set<int> s2;
  s2 = std::move(s1);

  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
}

TEST(SetTest, EmptyAndSize) {
  dn::set<int> s1;
  std::set<int> s2;

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());

  s1.insert(42);
  s2.insert(42);

  EXPECT_EQ(s1.empty(), s2.empty());
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(SetTest, MaxSize) {
  dn::set<int> s1;
  std::set<int> s2;

  EXPECT_GT(s1.max_size(), 0);
  EXPECT_GT(s2.max_size(), 0);
}

TEST(SetTest, IteratorBasic) {
  dn::set<int> s1{3, 1, 4, 1, 5};
  std::set<int> s2{3, 1, 4, 1, 5};

  auto it1 = s1.begin();
  auto it2 = s2.begin();

  while (it1 != s1.end() && it2 != s2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  EXPECT_EQ(it1, s1.end());
  EXPECT_EQ(it2, s2.end());
}

TEST(SetTest, IteratorEmpty) {
  dn::set<int> s1;
  EXPECT_EQ(s1.begin(), s1.end());
}

TEST(SetTest, InsertBasic) {
  dn::set<int> s1;
  std::set<int> s2;

  auto [it1, inserted1] = s1.insert(42);
  auto [it2, inserted2] = s2.insert(42);

  EXPECT_EQ(inserted1, inserted2);
  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(SetTest, InsertDuplicate) {
  dn::set<int> s1;
  s1.insert(42);
  auto [it, inserted] = s1.insert(42);

  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(s1.size(), 1);
}

TEST(SetTest, EraseBasic) {
  dn::set<int> s1{1, 2, 3, 4, 5};
  std::set<int> s2{1, 2, 3, 4, 5};

  auto it1 = s1.find(3);
  auto it2 = s2.find(3);

  s1.erase(it1);
  s2.erase(it2);

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_FALSE(s1.contains(3));
}

TEST(SetTest, EraseAll) {
  dn::set<int> s1{1, 2, 3};

  s1.erase(s1.find(1));
  s1.erase(s1.find(2));
  s1.erase(s1.find(3));

  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s1.begin(), s1.end());
}

TEST(SetTest, Clear) {
  dn::set<int> s1{1, 2, 3, 4, 5};

  EXPECT_FALSE(s1.empty());
  s1.clear();
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s1.begin(), s1.end());
}

TEST(SetTest, Swap) {
  dn::set<int> s1{1, 2, 3};
  dn::set<int> s2{4, 5, 6};

  s1.swap(s2);

  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Merge) {
  dn::set<int> s1{1, 2, 3};
  dn::set<int> s2{3, 4, 5};

  s1.merge(s2);

  EXPECT_EQ(s1.size(), 5);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s2.empty() || s2.size() == 1);
}

TEST(SetTest, Find) {
  dn::set<int> s1{1, 2, 3, 4, 5};

  auto it = s1.find(3);
  EXPECT_NE(it, s1.end());
  EXPECT_EQ(*it, 3);

  it = s1.find(999);
  EXPECT_EQ(it, s1.end());
}

TEST(SetTest, Contains) {
  dn::set<int> s1{1, 2, 3, 4, 5};

  EXPECT_TRUE(s1.contains(3));
  EXPECT_FALSE(s1.contains(999));
}

TEST(SetTest, InsertManyDuplicates) {
  dn::set<int> s1;
  std::set<int> stl_s1;

  auto results = s1.insert_many(1, 2, 3, 2, 4);

  dn::vector<std::pair<std::set<int>::iterator, bool>> stl_results;
  stl_results.push_back(stl_s1.insert(1));
  stl_results.push_back(stl_s1.insert(2));
  stl_results.push_back(stl_s1.insert(3));
  stl_results.push_back(stl_s1.insert(2));
  stl_results.push_back(stl_s1.insert(4));

  EXPECT_EQ(results.size(), stl_results.size());
  EXPECT_EQ(s1.size(), stl_s1.size());

  for (size_t i = 0; i < results.size(); ++i) {
    EXPECT_EQ(results[i].second, stl_results[i].second);
  }

  // Compare final set content
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_FALSE(s1.contains(5));

  EXPECT_TRUE(stl_s1.find(1) != stl_s1.end());
  EXPECT_TRUE(stl_s1.find(2) != stl_s1.end());
  EXPECT_TRUE(stl_s1.find(3) != stl_s1.end());
  EXPECT_TRUE(stl_s1.find(4) != stl_s1.end());
  EXPECT_TRUE(stl_s1.find(5) == stl_s1.end());

  auto it1 = s1.begin();
  auto it2 = stl_s1.begin();
  while (it1 != s1.end() && it2 != stl_s1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  EXPECT_EQ(it1, s1.end());
  EXPECT_EQ(it2, stl_s1.end());
}

TEST(SetTest, LargeInsert) {
  dn::set<int> s1;

  for (int i = 0; i < 1000; ++i) {
    s1.insert(i);
  }

  EXPECT_EQ(s1.size(), 1000);
  for (int i = 0; i < 1000; ++i) {
    EXPECT_TRUE(s1.contains(i));
  }
}

TEST(SetTest, StringType) {
  dn::set<std::string> s1{"hello", "world", "test"};
  std::set<std::string> s2{"hello", "world", "test"};

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s1.contains("hello"));
  EXPECT_FALSE(s1.contains("missing"));
}

TEST(SetTest, IteratorInvalidation) {
  dn::set<int> s1{1, 2, 3, 4, 5};
  auto it = s1.find(3);

  s1.erase(s1.find(2));  // Should not invalidate iterator to 3
  EXPECT_EQ(*it, 3);

  s1.erase(it);  // Now erase the element we have iterator to
  EXPECT_FALSE(s1.contains(3));
}

TEST(SetTest, EmptyErase) { dn::set<int> s1; }

TEST(SetTest, FindInEmpty) {
  dn::set<int> s1;
  EXPECT_EQ(s1.find(42), s1.end());
  EXPECT_FALSE(s1.contains(42));
}

TEST(SetTest, ClearEmpty) {
  dn::set<int> s1;
  s1.clear();
  EXPECT_TRUE(s1.empty());
}
