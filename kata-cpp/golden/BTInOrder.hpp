#pragma once

#include <vector>

#include <kata/types.hpp>

namespace kata {

namespace detail::in_order {
inline void walk(const BinaryNode<int>* node, std::vector<int>& path) {
    if (!node) return;
    walk(node->left.get(), path);
    path.push_back(node->value);
    walk(node->right.get(), path);
}
}  // namespace detail::in_order

inline std::vector<int> in_order_search(const BinaryNode<int>& head) {
    std::vector<int> path;
    detail::in_order::walk(&head, path);
    return path;
}

}  // namespace kata
