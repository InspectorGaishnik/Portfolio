#include "../dn_map.h"

#include <gtest/gtest.h>

#include <map>
#include <stdexcept>

TEST(dnMapTest, DefaultConstructor) {
  dn::map<int, int> m;
  std::map<int, int> std_m;
  EXPECT_EQ(m.empty(), std_m.empty());
  EXPECT_EQ(m.size(), std_m.size());
}

TEST(dnMapTest, InitializerListConstructor) {
  dn::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> std_m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), std_m.size());
  EXPECT_EQ(m.at(1), std_m.at(1));
  EXPECT_EQ(m.at(2), std_m.at(2));
  EXPECT_EQ(m.at(3), std_m.at(3));
}

TEST(dnMapTest, CopyConstructor) {
  dn::map<int, int> m1{{1, 10}, {2, 20}};
  dn::map<int, int> m2(m1);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.at(1), m2.at(1));
  EXPECT_EQ(m1.at(2), m2.at(2));
}

TEST(dnMapTest, MoveConstructor) {
  dn::map<int, int> m1{{1, 10}, {2, 20}};
  dn::map<int, int> m2(std::move(m1));
  EXPECT_EQ(m2.size(), 2);
  EXPECT_TRUE(m1.empty());
}

TEST(dnMapTest, MoveAssignment) {
  dn::map<int, int> m1{{1, 10}, {2, 20}};
  dn::map<int, int> m2;
  m2 = std::move(m1);
  EXPECT_EQ(m2.size(), 2);
  EXPECT_TRUE(m1.empty());
}

TEST(dnMapTest, AtValid) {
  dn::map<int, std::string> m{{1, "one"}, {2, "two"}};
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
}

TEST(dnMapTest, AtInvalid) {
  dn::map<int, std::string> m;
  EXPECT_THROW(m.at(999), std::out_of_range);
}

TEST(dnMapTest, SubscriptOperator) {
  dn::map<int, std::string> m;
  m[1] = "one";
  m[2] = "two";
  EXPECT_EQ(m[1], "one");
  EXPECT_EQ(m[2], "two");
  EXPECT_EQ(m[3], "");
}

TEST(dnMapTest, BeginEnd) {
  dn::map<int, int> m{{1, 10}, {2, 20}};
  std::map<int, int> std_m{{1, 10}, {2, 20}};

  auto it = m.begin();
  auto std_it = std_m.begin();

  EXPECT_EQ((*it).first, (*std_it).first);
  EXPECT_EQ((*it).second, (*std_it).second);
}

TEST(dnMapTest, Empty) {
  dn::map<int, int> m1;
  EXPECT_TRUE(m1.empty());

  dn::map<int, int> m2{{1, 10}};
  EXPECT_FALSE(m2.empty());
}

TEST(dnMapTest, Size) {
  dn::map<int, int> m;
  EXPECT_EQ(m.size(), 0);

  m.insert({1, 10});
  EXPECT_EQ(m.size(), 1);

  m.insert({2, 20});
  EXPECT_EQ(m.size(), 2);
}

TEST(dnMapTest, MaxSize) {
  dn::map<int, int> m;
  EXPECT_GT(m.max_size(), 0);
}

TEST(dnMapTest, Clear) {
  dn::map<int, int> m{{1, 10}, {2, 20}};
  EXPECT_FALSE(m.empty());
  m.clear();
  EXPECT_TRUE(m.empty());
}

TEST(dnMapTest, Insert) {
  dn::map<int, std::string> m;
  auto result = m.insert({1, "one"});
  EXPECT_TRUE(result.second);
  EXPECT_EQ((*result.first).first, 1);

  result = m.insert({1, "ONE"});
  EXPECT_FALSE(result.second);
}

TEST(dnMapTest, InsertKeyValue) {
  dn::map<int, std::string> m;
  auto result = m.insert(1, "one");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(m.at(1), "one");
}

TEST(dnMapTest, InsertOrAssign) {
  dn::map<int, std::string> m;
  auto result = m.insert_or_assign(1, "one");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(m.at(1), "one");

  result = m.insert_or_assign(1, "ONE");
  EXPECT_FALSE(result.second);
  EXPECT_EQ(m.at(1), "ONE");
}

TEST(dnMapTest, Erase) {
  dn::map<int, int> m{{1, 10}, {2, 20}, {3, 30}};
  auto it = m.begin();
  m.erase(it);
  EXPECT_EQ(m.size(), 2);
  EXPECT_FALSE(m.contains(1));
}

TEST(dnMapTest, Swap) {
  dn::map<int, int> m1{{1, 10}, {2, 20}};
  dn::map<int, int> m2{{3, 30}, {4, 40}};

  m1.swap(m2);

  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m2.size(), 2);
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m2.contains(1));
}

TEST(dnMapTest, Merge) {
  dn::map<int, int> m1{{1, 10}, {2, 20}};
  dn::map<int, int> m2{{3, 30}, {4, 40}};

  m1.merge(m2);

  EXPECT_EQ(m1.size(), 4);
  EXPECT_TRUE(m2.empty());
}

TEST(dnMapTest, Contains) {
  dn::map<int, int> m{{1, 10}, {2, 20}};
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_FALSE(m.contains(3));
}

TEST(dnMapTest, InsertMany) {
  dn::map<int, std::string> m;
  auto results =
      m.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                    std::make_pair(1, "ONE"));

  EXPECT_EQ(results.size(), 3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_FALSE(results[2].second);
  EXPECT_EQ(m.size(), 2);
}

TEST(dnMapTest, MemoryLeakCheck) {
  for (int i = 0; i < 1000; ++i) {
    dn::map<int, int> m;
    for (int j = 0; j < 100; ++j) {
      m.insert({j, j * 10});
    }
    for (int j = 0; j < 50; ++j) {
      auto it = m.begin();
      m.erase(it);
    }
  }
}

TEST(dnMapTest, LargeData) {
  dn::map<int, int> m;
  for (int i = 0; i < 10000; ++i) {
    m.insert({i, i * 2});
  }
  EXPECT_EQ(m.size(), 10000);
  for (int i = 0; i < 10000; ++i) {
    EXPECT_EQ(m.at(i), i * 2);
  }
}
