#pragma once

#include <span>

namespace kata {

inline bool linear_search(std::span<const int> haystack, int needle) {
    for (const int value : haystack) {
        if (value == needle) return true;
    }
    return false;
}

}  // namespace kata
