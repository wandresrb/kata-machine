#include "BTPreOrder.hpp"

#include <vector>

#include "fixtures/tree.hpp"
#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(pre_order) {
    const auto tree = kata::fixtures::tree();
    expect_eq(kata::pre_order_search(*tree), std::vector{20, 10, 5, 7, 15, 50, 30, 29, 45, 100});
}
