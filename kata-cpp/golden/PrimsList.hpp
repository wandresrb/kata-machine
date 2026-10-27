#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <queue>
#include <tuple>
#include <vector>

#include <kata/types.hpp>

namespace kata {

// Minimum spanning tree (undirected, each MST edge stored in both directions).
// Returns nullopt if the graph is not connected.
inline std::optional<WeightedAdjacencyList> prims(const WeightedAdjacencyList& list) {
    if (list.empty()) return WeightedAdjacencyList{};

    WeightedAdjacencyList mst(list.size());
    std::vector<bool> visited(list.size(), false);

    using Candidate = std::tuple<int, std::size_t, std::size_t>;  // (weight, from, to)
    std::priority_queue<Candidate, std::vector<Candidate>, std::greater<>> pq;

    auto visit = [&](std::size_t node) {
        visited[node] = true;
        for (const auto& [to, weight] : list[node]) {
            if (!visited[to]) pq.emplace(weight, node, to);
        }
    };

    visit(0);
    std::size_t added = 1;
    while (!pq.empty() && added < list.size()) {
        const auto [weight, from, to] = pq.top();
        pq.pop();
        if (visited[to]) continue;
        mst[from].push_back({.to = to, .weight = weight});
        mst[to].push_back({.to = from, .weight = weight});
        visit(to);
        ++added;
    }
    if (added != list.size()) return std::nullopt;
    return mst;
}

}  // namespace kata
