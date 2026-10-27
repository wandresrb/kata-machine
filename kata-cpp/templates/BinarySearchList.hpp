#pragma once

#include <span>

namespace kata {

// `haystack` is sorted ascending.
inline bool bs_list([[maybe_unused]] std::span<const int> haystack, [[maybe_unused]] int needle) {
    return false;
}

}  // namespace kata
