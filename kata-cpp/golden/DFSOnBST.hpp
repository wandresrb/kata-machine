#pragma once

#include <kata/types.hpp>

namespace kata {

// Uses the BST ordering: only one branch is explored per level.
inline bool dfs(const BinaryNode<int>& head, int needle) {
    for (const BinaryNode<int>* cur = &head; cur;) {
        if (cur->value == needle) return true;
        cur = needle < cur->value ? cur->left.get() : cur->right.get();
    }
    return false;
}

}  // namespace kata
