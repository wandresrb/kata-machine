#include "Stack.hpp"

#include <optional>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(stack) {
    kata::Stack<int> list;

    list.push(5);
    list.push(7);
    list.push(9);

    expect_eq(list.pop(), 9);
    expect_eq(list.length(), 2);

    list.push(11);
    expect_eq(list.pop(), 11);
    expect_eq(list.pop(), 7);
    expect_eq(list.peek(), 5);
    expect_eq(list.pop(), 5);
    expect_eq(list.pop(), std::nullopt);

    // just wanted to make sure that I could not blow up myself when i remove
    // everything
    list.push(69);
    expect_eq(list.peek(), 69);
    expect_eq(list.length(), 1);
}
