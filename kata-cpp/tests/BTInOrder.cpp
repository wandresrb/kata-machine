#include "BTInOrder.hpp"

#include <vector>

#include "fixtures/tree.hpp"
#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(in_order) {
    const auto tree = kata::fixtures::tree();
    expect_eq(kata::in_order_search(*tree), std::vector{5, 7, 10, 15, 20, 29, 30, 45, 50, 100});
}
