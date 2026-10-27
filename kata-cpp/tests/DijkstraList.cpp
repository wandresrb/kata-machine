#include "DijkstraList.hpp"

#include <cstddef>
#include <vector>

#include "fixtures/graph.hpp"
#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(dijkstra_list) {
    expect_eq(kata::dijkstra_list(0, 6, kata::fixtures::list1),
              std::vector<std::size_t>{0, 1, 4, 5, 6});
}
