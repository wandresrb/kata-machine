#include "DFSOnBST.hpp"

#include "fixtures/tree.hpp"
#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(dfs_on_bst) {
    const auto tree = kata::fixtures::tree();
    expect_eq(kata::dfs(*tree, 45), true);
    expect_eq(kata::dfs(*tree, 7), true);
    expect_eq(kata::dfs(*tree, 69), false);
}
