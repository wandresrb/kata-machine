#include "PrimsList.hpp"

#include <algorithm>
#include <utility>

#include "fixtures/graph.hpp"
#include "kata_test.hpp"

using kata::test::expect_eq;

// The TS test compares each node's edge list in order, which depends on the
// order a particular implementation happened to discover edges. Here every
// node's edges are compared as an order-insensitive set: both sides are
// sorted by (to, weight) before comparing.
static kata::WeightedAdjacencyList sorted_edges(kata::WeightedAdjacencyList graph) {
    for (auto& edges : graph) {
        std::ranges::sort(edges, {}, [](const kata::GraphEdge& e) { return std::pair{e.to, e.weight}; });
    }
    return graph;
}

TEST(prims_list) {
    // there is only one right answer for this graph
    const kata::WeightedAdjacencyList expected = {
        {{.to = 2, .weight = 1}, {.to = 1, .weight = 3}},
        {{.to = 0, .weight = 3}, {.to = 4, .weight = 1}},
        {{.to = 0, .weight = 1}},
        {{.to = 6, .weight = 1}},
        {{.to = 1, .weight = 1}, {.to = 5, .weight = 2}},
        {{.to = 4, .weight = 2}, {.to = 6, .weight = 1}},
        {{.to = 5, .weight = 1}, {.to = 3, .weight = 1}},
    };

    expect_eq(kata::prims(kata::fixtures::list1).transform(sorted_edges), sorted_edges(expected));
}
