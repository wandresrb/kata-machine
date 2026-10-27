#pragma once

#include <cstddef>
#include <optional>
#include <vector>

#include <kata/types.hpp>

namespace kata {

namespace detail::dfs_graph {
inline bool walk(const WeightedAdjacencyList& graph, std::size_t cur, std::size_t needle, std::vector<bool>& seen,
                 std::vector<std::size_t>& path) {
    if (seen[cur]) return false;
    seen[cur] = true;
    path.push_back(cur);
    if (cur == needle) return true;
    for (const auto& edge : graph[cur]) {
        if (walk(graph, edge.to, needle, seen, path)) return true;
    }
    path.pop_back();
    return false;
}
}  // namespace detail::dfs_graph

inline std::optional<std::vector<std::size_t>> dfs(const WeightedAdjacencyList& graph, std::size_t source,
                                                   std::size_t needle) {
    std::vector<bool> seen(graph.size(), false);
    std::vector<std::size_t> path;
    if (!detail::dfs_graph::walk(graph, source, needle, seen, path)) return std::nullopt;
    return path;
}

}  // namespace kata
