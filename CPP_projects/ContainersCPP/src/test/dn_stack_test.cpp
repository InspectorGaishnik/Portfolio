#include "../dn_stack.h"

#include <gtest/gtest.h>

#include <stack>
#include <string>

TEST(StackTest, DefaultConstructor) {
  dn::stack<int> dn_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(dn_stack.empty(), std_stack.empty());
  EXPECT_EQ(dn_stack.size(), std_stack.size());
}

TEST(StackTest, InitializerListConstructor) {
  dn::stack<int> dn_stack{1, 2, 3, 4, 5};
  std::stack<int> std_stack;
  for (int i = 1; i <= 5; ++i) std_stack.push(i);

  EXPECT_EQ(dn_stack.size(), std_stack.size());
  while (!dn_stack.empty()) {
    EXPECT_EQ(dn_stack.top(), std_stack.top());
    dn_stack.pop();
    std_stack.pop();
  }
}

TEST(StackTest, CopyConstructor) {
  dn::stack<int> original{1, 2, 3};
  dn::stack<int> copy(original);

  EXPECT_EQ(original.size(), copy.size());
  while (!original.empty()) {
    EXPECT_EQ(original.top(), copy.top());
    original.pop();
    copy.pop();
  }
}

TEST(StackTest, MoveConstructor) {
  dn::stack<int> original{1, 2, 3};
  dn::stack<int> moved(std::move(original));

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.top(), 3);
}

TEST(StackTest, MoveAssignment) {
  dn::stack<int> original{1, 2, 3};
  dn::stack<int> target;
  target = std::move(original);

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(target.size(), 3);
  EXPECT_EQ(target.top(), 3);
}

TEST(StackTest, Empty) {
  dn::stack<int> empty_stack;
  dn::stack<int> non_empty_stack{1};

  EXPECT_TRUE(empty_stack.empty());
  EXPECT_FALSE(non_empty_stack.empty());
}

TEST(StackTest, Size) {
  dn::stack<int> stack;
  EXPECT_EQ(stack.size(), 0);

  for (int i = 1; i <= 10; ++i) {
    stack.push(i);
    EXPECT_EQ(stack.size(), i);
  }
}

TEST(StackTest, Top) {
  dn::stack<int> stack;
  stack.push(42);
  EXPECT_EQ(stack.top(), 42);

  stack.push(100);
  EXPECT_EQ(stack.top(), 100);

  stack.pop();
  EXPECT_EQ(stack.top(), 42);
}

TEST(StackTest, Push) {
  dn::stack<int> dn_stack;
  std::stack<int> std_stack;

  for (int i = 0; i < 100; ++i) {
    dn_stack.push(i);
    std_stack.push(i);
    EXPECT_EQ(dn_stack.top(), std_stack.top());
    EXPECT_EQ(dn_stack.size(), std_stack.size());
  }
}

TEST(StackTest, Pop) {
  dn::stack<int> dn_stack;
  std::stack<int> std_stack;

  for (int i = 0; i < 10; ++i) {
    dn_stack.push(i);
    std_stack.push(i);
  }

  while (!dn_stack.empty()) {
    EXPECT_EQ(dn_stack.top(), std_stack.top());
    dn_stack.pop();
    std_stack.pop();
    EXPECT_EQ(dn_stack.size(), std_stack.size());
  }
}

TEST(StackTest, Swap) {
  dn::stack<int> stack1{1, 2, 3};
  dn::stack<int> stack2{4, 5, 6, 7};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 4);
  EXPECT_EQ(stack1.top(), 7);
  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack2.top(), 3);
}

TEST(StackTest, InsertManyBack) {
  dn::stack<int> stack;
  stack.insert_many_back(1, 2, 3, 4, 5);

  EXPECT_EQ(stack.size(), 5);
  EXPECT_EQ(stack.top(), 5);

  stack.pop();
  EXPECT_EQ(stack.top(), 4);

  stack.insert_many_back(6, 7);
  EXPECT_EQ(stack.size(), 6);
  EXPECT_EQ(stack.top(), 7);
}

TEST(StackTest, LargeNumberOfElements) {
  dn::stack<int> dn_stack;
  std::stack<int> std_stack;

  const int count = 10000;
  for (int i = 0; i < count; ++i) {
    dn_stack.push(i);
    std_stack.push(i);
  }

  EXPECT_EQ(dn_stack.size(), std_stack.size());
  EXPECT_EQ(dn_stack.top(), std_stack.top());

  for (int i = 0; i < count; ++i) {
    EXPECT_EQ(dn_stack.top(), std_stack.top());
    dn_stack.pop();
    std_stack.pop();
  }

  EXPECT_TRUE(dn_stack.empty());
  EXPECT_TRUE(std_stack.empty());
}

TEST(StackTest, StringType) {
  dn::stack<std::string> dn_stack;
  std::stack<std::string> std_stack;

  dn_stack.push("hello");
  dn_stack.push("world");
  std_stack.push("hello");
  std_stack.push("world");

  EXPECT_EQ(dn_stack.top(), std_stack.top());
  dn_stack.pop();
  std_stack.pop();
  EXPECT_EQ(dn_stack.top(), std_stack.top());
}

TEST(StackTest, SelfAssignment) {
  dn::stack<int> stack{1, 2, 3};
  dn::stack<int>& stack_ref = stack;
  stack_ref = std::move(stack);

  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack.top(), 3);
}

TEST(StackTest, CopyEmptyStack) {
  dn::stack<int> empty_stack;
  dn::stack<int> copy(empty_stack);

  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(copy.size(), 0);
}

TEST(StackTest, MoveEmptyStack) {
  dn::stack<int> empty_stack;
  dn::stack<int> moved(std::move(empty_stack));

  EXPECT_TRUE(empty_stack.empty());
  EXPECT_TRUE(moved.empty());
}

TEST(StackTest, InsertManyBackEmpty) {
  dn::stack<int> stack;
  stack.insert_many_back();

  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, SwapWithSelf) {
  dn::stack<int> stack{1, 2, 3};
  stack.swap(stack);

  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack.top(), 3);
}

TEST(StackTest, ConstTop) {
  const dn::stack<int> stack{1, 2, 3};
  EXPECT_EQ(stack.top(), 3);
  EXPECT_EQ(stack.size(), 3);
  EXPECT_FALSE(stack.empty());
}

TEST(StackTest, SequentialOperations) {
  dn::stack<int> stack;

  stack.push(1);
  stack.push(2);
  stack.push(3);
  EXPECT_EQ(stack.top(), 3);

  stack.pop();
  EXPECT_EQ(stack.top(), 2);

  stack.push(4);
  stack.push(5);
  EXPECT_EQ(stack.top(), 5);
  EXPECT_EQ(stack.size(), 4);
}
