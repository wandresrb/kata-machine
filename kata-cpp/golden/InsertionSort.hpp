#pragma once

#include <cstddef>
#include <span>

namespace kata {

inline void insertion_sort(std::span<int> arr) {
    for (std::size_t i = 1; i < arr.size(); ++i) {
        const int key = arr[i];
        std::size_t j = i;
        for (; j > 0 && arr[j - 1] > key; --j) arr[j] = arr[j - 1];
        arr[j] = key;
    }
}

}  // namespace kata
