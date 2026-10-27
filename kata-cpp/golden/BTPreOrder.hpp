#pragma once

#include <vector>

#include <kata/types.hpp>

namespace kata {

namespace detail::pre_order {
inline void walk(const BinaryNode<int>* node, std::vector<int>& path) {
    if (!node) return;
    path.push_back(node->value);
    walk(node->left.get(), path);
    walk(node->right.get(), path);
}
}  // namespace detail::pre_order

inline std::vector<int> pre_order_search(const BinaryNode<int>& head) {
    std::vector<int> path;
    detail::pre_order::walk(&head, path);
    return path;
}

}  // namespace kata
