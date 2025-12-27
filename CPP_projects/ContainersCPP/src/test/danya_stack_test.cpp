#include "../danya_stack.h"

#include <gtest/gtest.h>

#include <stack>
#include <string>

TEST(StackTest, DefaultConstructor) {
  danya::stack<int> danya_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(danya_stack.empty(), std_stack.empty());
  EXPECT_EQ(danya_stack.size(), std_stack.size());
}

TEST(StackTest, InitializerListConstructor) {
  danya::stack<int> danya_stack{1, 2, 3, 4, 5};
  std::stack<int> std_stack;
  for (int i = 1; i <= 5; ++i) std_stack.push(i);

  EXPECT_EQ(danya_stack.size(), std_stack.size());
  while (!danya_stack.empty()) {
    EXPECT_EQ(danya_stack.top(), std_stack.top());
    danya_stack.pop();
    std_stack.pop();
  }
}

TEST(StackTest, CopyConstructor) {
  danya::stack<int> original{1, 2, 3};
  danya::stack<int> copy(original);

  EXPECT_EQ(original.size(), copy.size());
  while (!original.empty()) {
    EXPECT_EQ(original.top(), copy.top());
    original.pop();
    copy.pop();
  }
}

TEST(StackTest, MoveConstructor) {
  danya::stack<int> original{1, 2, 3};
  danya::stack<int> moved(std::move(original));

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.top(), 3);
}

TEST(StackTest, MoveAssignment) {
  danya::stack<int> original{1, 2, 3};
  danya::stack<int> target;
  target = std::move(original);

  EXPECT_TRUE(original.empty());
  EXPECT_EQ(target.size(), 3);
  EXPECT_EQ(target.top(), 3);
}

TEST(StackTest, Empty) {
  danya::stack<int> empty_stack;
  danya::stack<int> non_empty_stack{1};

  EXPECT_TRUE(empty_stack.empty());
  EXPECT_FALSE(non_empty_stack.empty());
}

TEST(StackTest, Size) {
  danya::stack<int> stack;
  EXPECT_EQ(stack.size(), 0);

  for (int i = 1; i <= 10; ++i) {
    stack.push(i);
    EXPECT_EQ(stack.size(), i);
  }
}

TEST(StackTest, Top) {
  danya::stack<int> stack;
  stack.push(42);
  EXPECT_EQ(stack.top(), 42);

  stack.push(100);
  EXPECT_EQ(stack.top(), 100);

  stack.pop();
  EXPECT_EQ(stack.top(), 42);
}

TEST(StackTest, Push) {
  danya::stack<int> danya_stack;
  std::stack<int> std_stack;

  for (int i = 0; i < 100; ++i) {
    danya_stack.push(i);
    std_stack.push(i);
    EXPECT_EQ(danya_stack.top(), std_stack.top());
    EXPECT_EQ(danya_stack.size(), std_stack.size());
  }
}

TEST(StackTest, Pop) {
  danya::stack<int> danya_stack;
  std::stack<int> std_stack;

  for (int i = 0; i < 10; ++i) {
    danya_stack.push(i);
    std_stack.push(i);
  }

  while (!danya_stack.empty()) {
    EXPECT_EQ(danya_stack.top(), std_stack.top());
    danya_stack.pop();
    std_stack.pop();
    EXPECT_EQ(danya_stack.size(), std_stack.size());
  }
}

TEST(StackTest, Swap) {
  danya::stack<int> stack1{1, 2, 3};
  danya::stack<int> stack2{4, 5, 6, 7};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 4);
  EXPECT_EQ(stack1.top(), 7);
  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack2.top(), 3);
}

TEST(StackTest, InsertManyBack) {
  danya::stack<int> stack;
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
  danya::stack<int> danya_stack;
  std::stack<int> std_stack;

  const int count = 10000;
  for (int i = 0; i < count; ++i) {
    danya_stack.push(i);
    std_stack.push(i);
  }

  EXPECT_EQ(danya_stack.size(), std_stack.size());
  EXPECT_EQ(danya_stack.top(), std_stack.top());

  for (int i = 0; i < count; ++i) {
    EXPECT_EQ(danya_stack.top(), std_stack.top());
    danya_stack.pop();
    std_stack.pop();
  }

  EXPECT_TRUE(danya_stack.empty());
  EXPECT_TRUE(std_stack.empty());
}

TEST(StackTest, StringType) {
  danya::stack<std::string> danya_stack;
  std::stack<std::string> std_stack;

  danya_stack.push("hello");
  danya_stack.push("world");
  std_stack.push("hello");
  std_stack.push("world");

  EXPECT_EQ(danya_stack.top(), std_stack.top());
  danya_stack.pop();
  std_stack.pop();
  EXPECT_EQ(danya_stack.top(), std_stack.top());
}

TEST(StackTest, SelfAssignment) {
  danya::stack<int> stack{1, 2, 3};
  danya::stack<int>& stack_ref = stack;
  stack_ref = std::move(stack);

  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack.top(), 3);
}

TEST(StackTest, CopyEmptyStack) {
  danya::stack<int> empty_stack;
  danya::stack<int> copy(empty_stack);

  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(copy.size(), 0);
}

TEST(StackTest, MoveEmptyStack) {
  danya::stack<int> empty_stack;
  danya::stack<int> moved(std::move(empty_stack));

  EXPECT_TRUE(empty_stack.empty());
  EXPECT_TRUE(moved.empty());
}

TEST(StackTest, InsertManyBackEmpty) {
  danya::stack<int> stack;
  stack.insert_many_back();

  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, SwapWithSelf) {
  danya::stack<int> stack{1, 2, 3};
  stack.swap(stack);

  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack.top(), 3);
}

TEST(StackTest, ConstTop) {
  const danya::stack<int> stack{1, 2, 3};
  EXPECT_EQ(stack.top(), 3);
  EXPECT_EQ(stack.size(), 3);
  EXPECT_FALSE(stack.empty());
}

TEST(StackTest, SequentialOperations) {
  danya::stack<int> stack;

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
