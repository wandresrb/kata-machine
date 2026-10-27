#include "BubbleSort.hpp"

#include <vector>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(bubble_sort) {
    std::vector arr{9, 3, 7, 4, 69, 420, 42};
    kata::bubble_sort(arr);
    expect_eq(arr, std::vector{3, 4, 7, 9, 42, 69, 420});
}
