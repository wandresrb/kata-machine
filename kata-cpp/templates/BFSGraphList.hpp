#pragma once

#include <cstddef>
#include <optional>
#include <vector>

#include <kata/types.hpp>

namespace kata {

// Path of nodes from `source` to `needle` (inclusive), or nullopt if unreachable.
inline std::optional<std::vector<std::size_t>> bfs([[maybe_unused]] const WeightedAdjacencyList& graph,
                                                   [[maybe_unused]] std::size_t source,
                                                   [[maybe_unused]] std::size_t needle) {
    return std::nullopt;
}

}  // namespace kata
