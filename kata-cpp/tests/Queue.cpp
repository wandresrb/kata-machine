#include "Queue.hpp"

#include <optional>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(queue) {
    kata::Queue<int> list;

    list.enqueue(5);
    list.enqueue(7);
    list.enqueue(9);

    expect_eq(list.deque(), 5);
    expect_eq(list.length(), 2);

    list.enqueue(11);
    expect_eq(list.deque(), 7);
    expect_eq(list.deque(), 9);
    expect_eq(list.peek(), 11);
    expect_eq(list.deque(), 11);
    expect_eq(list.deque(), std::nullopt);
    expect_eq(list.length(), 0);

    // just wanted to make sure that I could not blow up myself when i remove
    // everything
    list.enqueue(69);
    expect_eq(list.peek(), 69);
    expect_eq(list.length(), 1);
}
