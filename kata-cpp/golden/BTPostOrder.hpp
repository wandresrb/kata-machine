#pragma once

#include <vector>

#include <kata/types.hpp>

namespace kata {

namespace detail::post_order {
inline void walk(const BinaryNode<int>* node, std::vector<int>& path) {
    if (!node) return;
    walk(node->left.get(), path);
    walk(node->right.get(), path);
    path.push_back(node->value);
}
}  // namespace detail::post_order

inline std::vector<int> post_order_search(const BinaryNode<int>& head) {
    std::vector<int> path;
    detail::post_order::walk(&head, path);
    return path;
}

}  // namespace kata
