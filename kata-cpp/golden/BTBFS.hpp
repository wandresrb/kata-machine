#pragma once

#include <queue>

#include <kata/types.hpp>

namespace kata {

inline bool bfs(const BinaryNode<int>& head, int needle) {
    std::queue<const BinaryNode<int>*> q;
    q.push(&head);
    while (!q.empty()) {
        const auto* node = q.front();
        q.pop();
        if (node->value == needle) return true;
        if (node->left) q.push(node->left.get());
        if (node->right) q.push(node->right.get());
    }
    return false;
}

}  // namespace kata
