#include "MinHeap.hpp"

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(min_heap) {
    kata::MinHeap heap;

    expect_eq(heap.length(), 0);

    heap.insert(5);
    heap.insert(3);
    heap.insert(69);
    heap.insert(420);
    heap.insert(4);
    heap.insert(1);
    heap.insert(8);
    heap.insert(7);

    expect_eq(heap.length(), 8);
    expect_eq(heap.remove(), 1);
    expect_eq(heap.remove(), 3);
    expect_eq(heap.remove(), 4);
    expect_eq(heap.remove(), 5);
    expect_eq(heap.length(), 4);
    expect_eq(heap.remove(), 7);
    expect_eq(heap.remove(), 8);
    expect_eq(heap.remove(), 69);
    expect_eq(heap.remove(), 420);
    expect_eq(heap.length(), 0);
}
