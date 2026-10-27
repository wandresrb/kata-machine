#include "BTBFS.hpp"

#include "fixtures/tree.hpp"
#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(bt_bfs) {
    const auto tree = kata::fixtures::tree();
    expect_eq(kata::bfs(*tree, 45), true);
    expect_eq(kata::bfs(*tree, 7), true);
    expect_eq(kata::bfs(*tree, 69), false);
}
