#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#include <kata/types.hpp>

namespace kata {

// Returns the shortest path source -> sink (inclusive), or {} if unreachable.
inline std::vector<std::size_t> dijkstra_list(std::size_t source, std::size_t sink, const WeightedAdjacencyList& arr) {
    constexpr auto inf = std::numeric_limits<long long>::max();
    constexpr auto none = std::numeric_limits<std::size_t>::max();
    std::vector<long long> dist(arr.size(), inf);
    std::vector<std::size_t> prev(arr.size(), none);

    using Item = std::pair<long long, std::size_t>;  // (distance, node)
    std::priority_queue<Item, std::vector<Item>, std::greater<>> pq;
    dist[source] = 0;
    pq.emplace(0, source);
    while (!pq.empty()) {
        const auto [d, cur] = pq.top();
        pq.pop();
        if (d > dist[cur]) continue;  // stale entry
        for (const auto& [to, weight] : arr[cur]) {
            const long long next = d + weight;
            if (next < dist[to]) {
                dist[to] = next;
                prev[to] = cur;
                pq.emplace(next, to);
            }
        }
    }
    if (dist[sink] == inf) return {};

    std::vector<std::size_t> path;
    for (std::size_t cur = sink; cur != none; cur = prev[cur]) path.push_back(cur);
    std::ranges::reverse(path);
    return path;
}

}  // namespace kata
