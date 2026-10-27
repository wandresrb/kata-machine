#pragma once

// Shared types for the C++ katas (port of src/global.d.ts).

#include <concepts>
#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

namespace kata {

struct Point {
    int x{};
    int y{};

    bool operator==(const Point&) const = default;
};

template <class T>
struct BinaryNode {
    T value;
    std::unique_ptr<BinaryNode> left;
    std::unique_ptr<BinaryNode> right;
};

struct GraphEdge {
    std::size_t to{};
    int weight{};

    bool operator==(const GraphEdge&) const = default;
};

// graph[from] holds the outgoing edges of node `from`.
using WeightedAdjacencyList = std::vector<std::vector<GraphEdge>>;
// matrix[from][to] is the edge weight; 0 means "no edge".
using WeightedAdjacencyMatrix = std::vector<std::vector<int>>;

// The interface every list kata (ArrayList, SinglyLinkedList, DoublyLinkedList)
// must satisfy. Port of the TS `List<T>` interface (`delete`/`remove` -> `remove`).
template <class L, class T>
concept List = requires(L list, const L& clist, T item, const T& citem, std::size_t idx) {
    list.prepend(item);
    list.append(item);
    list.insert_at(item, idx);
    { list.remove(citem) } -> std::same_as<std::optional<T>>;
    { list.remove_at(idx) } -> std::same_as<std::optional<T>>;
    { clist.get(idx) } -> std::same_as<std::optional<T>>;
    { clist.length() } -> std::convertible_to<std::size_t>;
};

}  // namespace kata
