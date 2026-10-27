#pragma once

#include <cstddef>
#include <vector>

#include <kata/types.hpp>

namespace kata {

// Shortest path from `source` to `sink` (inclusive).
inline std::vector<std::size_t> dijkstra_list([[maybe_unused]] std::size_t source, [[maybe_unused]] std::size_t sink,
                                              [[maybe_unused]] const WeightedAdjacencyList& arr) {
    return {};
}

}  // namespace kata
