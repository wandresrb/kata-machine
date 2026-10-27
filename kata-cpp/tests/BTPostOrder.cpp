#include "BTPostOrder.hpp"

#include <vector>

#include "fixtures/tree.hpp"
#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(post_order) {
    const auto tree = kata::fixtures::tree();
    expect_eq(kata::post_order_search(*tree), std::vector{7, 5, 15, 10, 29, 45, 30, 100, 50, 20});
}
