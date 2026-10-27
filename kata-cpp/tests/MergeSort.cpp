#include "MergeSort.hpp"

#include <vector>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(merge_sort) {
    std::vector arr{9, 3, 7, 4, 69, 420, 42};
    kata::merge_sort(arr);
    expect_eq(arr, std::vector{3, 4, 7, 9, 42, 69, 420});
}
