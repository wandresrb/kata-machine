#include "InsertionSort.hpp"

#include <vector>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(insertion_sort) {
    std::vector arr{9, 3, 7, 4, 69, 420, 42};
    kata::insertion_sort(arr);
    expect_eq(arr, std::vector{3, 4, 7, 9, 42, 69, 420});
}
