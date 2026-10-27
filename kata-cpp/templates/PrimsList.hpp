#pragma once

#include <optional>

#include <kata/types.hpp>

namespace kata {

// Minimum spanning tree as an undirected adjacency list (each edge stored in both directions).
inline std::optional<WeightedAdjacencyList> prims([[maybe_unused]] const WeightedAdjacencyList& list) {
    return std::nullopt;
}

}  // namespace kata
