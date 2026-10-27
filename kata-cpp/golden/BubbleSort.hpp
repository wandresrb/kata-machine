#pragma once

#include <cstddef>
#include <span>
#include <utility>

namespace kata {

inline void bubble_sort(std::span<int> arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        for (std::size_t j = 0; j + 1 < arr.size() - i; ++j) {
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
        }
    }
}

}  // namespace kata
