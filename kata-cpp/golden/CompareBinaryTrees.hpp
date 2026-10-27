#pragma once

#include <kata/types.hpp>

namespace kata {

inline bool compare(const BinaryNode<int>* a, const BinaryNode<int>* b) {
    if (!a || !b) return a == b;
    return a->value == b->value && compare(a->left.get(), b->left.get()) &&
           compare(a->right.get(), b->right.get());
}

}  // namespace kata
