#include "../dn_queue.h"

#include <gtest/gtest.h>

#include <queue>
#include <string>

TEST(QueueTest, DefaultConstructor) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  EXPECT_TRUE(dn_q.empty());
  EXPECT_TRUE(stl_q.empty());
  EXPECT_EQ(dn_q.size(), stl_q.size());
}

TEST(QueueTest, InitializerQueueConstructor) {
  dn::queue<std::string> dn_q = {"one", "two", "three"};
  std::queue<std::string> stl_q({"one", "two", "three"});

  EXPECT_FALSE(dn_q.empty());
  EXPECT_FALSE(stl_q.empty());
  EXPECT_EQ(dn_q.size(), stl_q.size());
  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());
}

TEST(QueueTest, CopyConstructor) {
  dn::queue<std::string> original = {"a", "b", "c"};
  dn::queue<std::string> copy(original);

  std::queue<std::string> stl_original({"a", "b", "c"});
  std::queue<std::string> stl_copy(stl_original);

  EXPECT_EQ(copy.size(), stl_copy.size());
  EXPECT_EQ(copy.front(), stl_copy.front());
  EXPECT_EQ(copy.back(), stl_copy.back());
}

TEST(QueueTest, MoveConstructor) {
  dn::queue<std::string> original = {"move", "test"};
  dn::queue<std::string> moved(std::move(original));

  std::queue<std::string> stl_original({"move", "test"});
  std::queue<std::string> stl_moved(std::move(stl_original));

  EXPECT_TRUE(original.empty());
  EXPECT_TRUE(stl_original.empty());
  EXPECT_EQ(moved.size(), stl_moved.size());
  EXPECT_EQ(moved.front(), stl_moved.front());
}

TEST(QueueTest, MoveAssignment) {
  dn::queue<std::string> original = {"assignment", "test"};
  dn::queue<std::string> target;
  target = std::move(original);

  std::queue<std::string> stl_original({"assignment", "test"});
  std::queue<std::string> stl_target;
  stl_target = std::move(stl_original);

  EXPECT_TRUE(original.empty());
  EXPECT_TRUE(stl_original.empty());
  EXPECT_EQ(target.size(), stl_target.size());
  EXPECT_EQ(target.front(), stl_target.front());
}

TEST(QueueTest, Front) {
  dn::queue<std::string> dn_q = {"first", "second", "third"};
  std::queue<std::string> stl_q({"first", "second", "third"});

  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.front(), "first");
  EXPECT_EQ(stl_q.front(), "first");
}

TEST(QueueTest, Back) {
  dn::queue<std::string> dn_q = {"first", "second", "third"};
  std::queue<std::string> stl_q({"first", "second", "third"});

  EXPECT_EQ(dn_q.back(), stl_q.back());
  EXPECT_EQ(dn_q.back(), "third");
  EXPECT_EQ(stl_q.back(), "third");
}

TEST(QueueTest, Empty) {
  dn::queue<std::string> empty_q;
  dn::queue<std::string> non_empty_q = {"not", "empty"};

  std::queue<std::string> stl_empty_q;
  std::queue<std::string> stl_non_empty_q({"not", "empty"});

  EXPECT_TRUE(empty_q.empty());
  EXPECT_TRUE(stl_empty_q.empty());
  EXPECT_FALSE(non_empty_q.empty());
  EXPECT_FALSE(stl_non_empty_q.empty());
}

TEST(QueueTest, Size) {
  dn::queue<std::string> dn_q = {"one", "two", "three", "four"};
  std::queue<std::string> stl_q({"one", "two", "three", "four"});

  EXPECT_EQ(dn_q.size(), stl_q.size());
  EXPECT_EQ(dn_q.size(), 4);
}

TEST(QueueTest, Push) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  dn_q.push("first");
  stl_q.push("first");

  EXPECT_EQ(dn_q.size(), stl_q.size());
  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());

  dn_q.push("second");
  stl_q.push("second");

  EXPECT_EQ(dn_q.size(), stl_q.size());
  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());
}

TEST(QueueTest, Pop) {
  dn::queue<std::string> dn_q = {"to", "be", "popped"};
  std::queue<std::string> stl_q({"to", "be", "popped"});

  dn_q.pop();
  stl_q.pop();

  EXPECT_EQ(dn_q.size(), stl_q.size());
  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());

  dn_q.pop();
  stl_q.pop();

  EXPECT_EQ(dn_q.size(), stl_q.size());
  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());
}

TEST(QueueTest, Swap) {
  dn::queue<std::string> dn_q1 = {"queue", "one"};
  dn::queue<std::string> dn_q2 = {"queue", "two", "items"};

  std::queue<std::string> stl_q1({"queue", "one"});
  std::queue<std::string> stl_q2({"queue", "two", "items"});

  dn_q1.swap(dn_q2);
  stl_q1.swap(stl_q2);

  EXPECT_EQ(dn_q1.size(), stl_q1.size());
  EXPECT_EQ(dn_q2.size(), stl_q2.size());
  EXPECT_EQ(dn_q1.front(), stl_q1.front());
  EXPECT_EQ(dn_q2.front(), stl_q2.front());
}

TEST(QueueTest, InsertManyBack) {
  dn::queue<std::string> dn_q = {"initial"};
  std::queue<std::string> stl_q({"initial"});

  dn_q.insert_many_back("first", "second", "third");
  stl_q.push("first");
  stl_q.push("second");
  stl_q.push("third");

  EXPECT_EQ(dn_q.size(), stl_q.size());
  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());

  dn::queue<std::string> dn_temp = dn_q;
  std::queue<std::string> stl_temp = stl_q;

  while (!dn_temp.empty() && !stl_temp.empty()) {
    EXPECT_EQ(dn_temp.front(), stl_temp.front());
    dn_temp.pop();
    stl_temp.pop();
  }
}

TEST(QueueTest, CombinedOperations) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  dn_q.push("first");
  dn_q.push("second");
  dn_q.push("third");

  stl_q.push("first");
  stl_q.push("second");
  stl_q.push("third");

  EXPECT_EQ(dn_q.front(), "first");
  EXPECT_EQ(dn_q.back(), "third");
  EXPECT_EQ(stl_q.front(), "first");
  EXPECT_EQ(stl_q.back(), "third");

  dn_q.pop();
  stl_q.pop();

  EXPECT_EQ(dn_q.front(), "second");
  EXPECT_EQ(dn_q.back(), "third");
  EXPECT_EQ(stl_q.front(), "second");
  EXPECT_EQ(stl_q.back(), "third");

  dn_q.insert_many_back("fourth", "fifth");
  stl_q.push("fourth");
  stl_q.push("fifth");

  EXPECT_EQ(dn_q.size(), 4);
  EXPECT_EQ(stl_q.size(), 4);
  EXPECT_EQ(dn_q.back(), "fifth");
  EXPECT_EQ(stl_q.back(), "fifth");
}

TEST(QueueTest, MemoryHandlingLargeQueue) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  const int large_size = 10000;
  for (int i = 0; i < large_size; ++i) {
    std::string value = "element_" + std::to_string(i);
    dn_q.push(value);
    stl_q.push(value);
  }

  EXPECT_EQ(dn_q.size(), large_size);
  EXPECT_EQ(stl_q.size(), large_size);
  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());

  for (int i = 0; i < large_size; ++i) {
    dn_q.pop();
    stl_q.pop();
  }

  EXPECT_TRUE(dn_q.empty());
  EXPECT_TRUE(stl_q.empty());
}

TEST(QueueTest, MemoryHandlingRepeatedOperations) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  for (int cycle = 0; cycle < 100; ++cycle) {
    for (int i = 0; i < 100; ++i) {
      std::string value =
          "cycle_" + std::to_string(cycle) + "_elem_" + std::to_string(i);
      dn_q.push(value);
      stl_q.push(value);
    }

    EXPECT_EQ(dn_q.size(), stl_q.size());

    for (int i = 0; i < 50; ++i) {
      dn_q.pop();
      stl_q.pop();
    }

    EXPECT_EQ(dn_q.size(), stl_q.size());
  }
}

TEST(QueueTest, FrontOnEmptyQueue) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  EXPECT_TRUE(dn_q.empty());
  EXPECT_TRUE(stl_q.empty());
}

TEST(QueueTest, BackOnEmptyQueue) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  EXPECT_TRUE(dn_q.empty());
  EXPECT_TRUE(stl_q.empty());
}

TEST(QueueTest, PopOnEmptyQueue) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  EXPECT_TRUE(dn_q.empty());
  EXPECT_TRUE(stl_q.empty());
}

TEST(QueueTest, SwapWithSelf) {
  dn::queue<std::string> dn_q = {"swap", "self"};
  std::queue<std::string> stl_q({"swap", "self"});

  dn_q.swap(dn_q);
  stl_q.swap(stl_q);

  EXPECT_EQ(dn_q.size(), 2);
  EXPECT_EQ(stl_q.size(), 2);
  EXPECT_EQ(dn_q.front(), "swap");
  EXPECT_EQ(stl_q.front(), "swap");
}

TEST(QueueTest, MoveFromTemporary) {
  dn::queue<std::string> dn_temp{"temp", "queue"};
  dn::queue<std::string> dn_q = std::move(dn_temp);

  std::queue<std::string> stl_temp({"temp", "queue"});
  std::queue<std::string> stl_q = std::move(stl_temp);

  EXPECT_EQ(dn_q.size(), 2);
  EXPECT_EQ(stl_q.size(), 2);
  EXPECT_EQ(dn_q.front(), "temp");
  EXPECT_EQ(stl_q.front(), "temp");
}

TEST(QueueTest, CopyConstructorTest) {
  dn::queue<std::string> original = {"copy", "test"};
  dn::queue<std::string> copy(original);

  std::queue<std::string> stl_original({"copy", "test"});
  std::queue<std::string> stl_copy(stl_original);

  EXPECT_EQ(copy.size(), stl_copy.size());
  EXPECT_EQ(copy.front(), stl_copy.front());
  EXPECT_EQ(copy.back(), stl_copy.back());
  EXPECT_EQ(original.size(), 2);
  EXPECT_EQ(stl_original.size(), 2);
}

TEST(QueueTest, DestructorSimple) {
  {
    dn::queue<std::string> dn_q = {"test1", "test2", "test3"};
    std::queue<std::string> stl_q({"test1", "test2", "test3"});

    EXPECT_EQ(dn_q.size(), 3);
    EXPECT_EQ(stl_q.size(), 3);
  }
}

TEST(QueueTest, InsertManyBackVariousTypes) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  const char* cstr = "c_string";
  std::string str = "std_string";
  char arr[] = "char_array";

  dn_q.insert_many_back(cstr, str, arr);
  stl_q.push(cstr);
  stl_q.push(str);
  stl_q.push(arr);

  EXPECT_EQ(dn_q.size(), stl_q.size());
  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());
}

TEST(QueueTest, ExceptionSafety) {
  dn::queue<std::string> dn_q;

  for (int i = 0; i < 100; ++i) {
    dn_q.push("test_" + std::to_string(i));
  }

  EXPECT_EQ(dn_q.size(), 100);
  EXPECT_EQ(dn_q.front(), "test_0");
  EXPECT_EQ(dn_q.back(), "test_99");
}

TEST(QueueTest, MovePreservesOrder) {
  dn::queue<std::string> original = {"first", "second", "third"};
  dn::queue<std::string> moved = std::move(original);

  std::queue<std::string> stl_original({"first", "second", "third"});
  std::queue<std::string> stl_moved = std::move(stl_original);

  EXPECT_EQ(moved.front(), "first");
  moved.pop();
  EXPECT_EQ(moved.front(), "second");
  moved.pop();
  EXPECT_EQ(moved.front(), "third");

  EXPECT_EQ(stl_moved.front(), "first");
  stl_moved.pop();
  EXPECT_EQ(stl_moved.front(), "second");
  stl_moved.pop();
  EXPECT_EQ(stl_moved.front(), "third");
}

TEST(QueueTest, DifferentDataTypes) {
  dn::queue<int> dn_int_q;
  std::queue<int> stl_int_q;

  dn_int_q.push(1);
  dn_int_q.push(2);
  stl_int_q.push(1);
  stl_int_q.push(2);

  EXPECT_EQ(dn_int_q.front(), stl_int_q.front());
  EXPECT_EQ(dn_int_q.back(), stl_int_q.back());

  dn::queue<double> dn_double_q;
  std::queue<double> stl_double_q;

  dn_double_q.push(1.5);
  dn_double_q.push(2.5);
  stl_double_q.push(1.5);
  stl_double_q.push(2.5);

  EXPECT_EQ(dn_double_q.front(), stl_double_q.front());
  EXPECT_EQ(dn_double_q.back(), stl_double_q.back());
}

TEST(QueueTest, ClearBehavior) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 10; ++j) {
      std::string value =
          "round_" + std::to_string(i) + "_elem_" + std::to_string(j);
      dn_q.push(value);
      stl_q.push(value);
    }

    EXPECT_EQ(dn_q.size(), stl_q.size());

    while (!dn_q.empty()) {
      dn_q.pop();
      stl_q.pop();
    }

    EXPECT_TRUE(dn_q.empty());
  }
}

TEST(QueueTest, InsertManyBackEmpty) {
  dn::queue<std::string> dn_q = {"existing"};
  std::queue<std::string> stl_q({"existing"});

  dn_q.insert_many_back();

  EXPECT_EQ(dn_q.size(), stl_q.size());
  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());
}

TEST(QueueTest, EmptyQueueOperations) {
  dn::queue<std::string> dn_q;
  std::queue<std::string> stl_q;

  EXPECT_TRUE(dn_q.empty());
  EXPECT_TRUE(stl_q.empty());
  EXPECT_EQ(dn_q.size(), 0);
  EXPECT_EQ(stl_q.size(), 0);

  dn_q.push("only");
  stl_q.push("only");

  EXPECT_EQ(dn_q.front(), stl_q.front());
  EXPECT_EQ(dn_q.back(), stl_q.back());
  EXPECT_EQ(dn_q.size(), 1);
}
