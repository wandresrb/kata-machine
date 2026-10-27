#pragma once

#include <kata/types.hpp>

namespace kata {

// Same shape and same values? Either pointer may be null.
inline bool compare([[maybe_unused]] const BinaryNode<int>* a, [[maybe_unused]] const BinaryNode<int>* b) {
    return false;
}

}  // namespace kata
