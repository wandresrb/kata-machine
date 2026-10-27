#include "CompareBinaryTrees.hpp"

#include "fixtures/tree.hpp"
#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(compare_binary_trees) {
    const auto tree = kata::fixtures::tree();
    const auto tree2 = kata::fixtures::tree2();
    expect_eq(kata::compare(tree.get(), tree.get()), true);
    expect_eq(kata::compare(tree.get(), tree2.get()), false);
}
