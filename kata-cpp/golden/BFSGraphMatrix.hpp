#pragma once

#include <algorithm>
#include <cstddef>
#include <limits>
#include <optional>
#include <queue>
#include <vector>

#include <kata/types.hpp>

namespace kata {

inline std::optional<std::vector<std::size_t>> bfs(const WeightedAdjacencyMatrix& graph, std::size_t source,
                                                   std::size_t needle) {
    constexpr auto none = std::numeric_limits<std::size_t>::max();
    std::vector<bool> seen(graph.size(), false);
    std::vector<std::size_t> prev(graph.size(), none);

    std::queue<std::size_t> q;
    q.push(source);
    seen[source] = true;
    while (!q.empty()) {
        const std::size_t cur = q.front();
        q.pop();
        if (cur == needle) break;
        for (std::size_t to = 0; to < graph[cur].size(); ++to) {
            if (graph[cur][to] == 0 || seen[to]) continue;
            seen[to] = true;
            prev[to] = cur;
            q.push(to);
        }
    }
    if (!seen[needle]) return std::nullopt;

    std::vector<std::size_t> path;
    for (std::size_t cur = needle; cur != none; cur = prev[cur]) path.push_back(cur);
    std::ranges::reverse(path);
    return path;
}

}  // namespace kata
