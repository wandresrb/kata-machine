#include "BFSGraphMatrix.hpp"

#include <cstddef>
#include <optional>
#include <vector>

#include "fixtures/graph.hpp"
#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(bfs_graph_matrix) {
    using kata::fixtures::matrix2;
    expect_eq(kata::bfs(matrix2, 0, 6), std::vector<std::size_t>{0, 1, 4, 5, 6});
    expect_eq(kata::bfs(matrix2, 6, 0), std::nullopt);
}
