#pragma once

#include <cstddef>
#include <span>

namespace kata {

inline bool bs_list(std::span<const int> haystack, int needle) {
    std::size_t lo = 0;
    std::size_t hi = haystack.size();  // [lo, hi)
    while (lo < hi) {
        const std::size_t mid = lo + (hi - lo) / 2;
        const int value = haystack[mid];
        if (value == needle) return true;
        if (value < needle) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return false;
}

}  // namespace kata
