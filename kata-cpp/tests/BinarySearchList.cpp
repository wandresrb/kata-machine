#include "BinarySearchList.hpp"

#include <array>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(bs_list) {
    constexpr std::array foo{1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420};
    expect_eq(kata::bs_list(foo, 69), true);
    expect_eq(kata::bs_list(foo, 1336), false);
    expect_eq(kata::bs_list(foo, 69420), true);
    expect_eq(kata::bs_list(foo, 69421), false);
    expect_eq(kata::bs_list(foo, 1), true);
    expect_eq(kata::bs_list(foo, 0), false);
}
