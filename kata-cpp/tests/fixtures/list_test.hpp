#pragma once

// Port of src/__tests__/ListTest.ts, shared by ArrayList / SinglyLinkedList /
// DoublyLinkedList.

#include <kata/types.hpp>

#include "kata_test.hpp"

namespace kata::fixtures {

template <List<int> L>
void test_list(L& list) {
    using kata::test::expect_eq;
    using std::nullopt;

    list.append(5);
    list.append(7);
    list.append(9);

    expect_eq(list.get(2), 9);
    expect_eq(list.remove_at(1), 7);
    expect_eq(list.length(), 2);

    list.append(11);
    expect_eq(list.remove_at(1), 9);
    expect_eq(list.remove(9), nullopt);
    expect_eq(list.remove_at(0), 5);
    expect_eq(list.remove_at(0), 11);
    expect_eq(list.length(), 0);

    list.prepend(5);
    list.prepend(7);
    list.prepend(9);

    expect_eq(list.get(2), 5);
    expect_eq(list.get(0), 9);
    expect_eq(list.remove(9), 9);
    expect_eq(list.length(), 2);
    expect_eq(list.get(0), 7);
}

}  // namespace kata::fixtures
