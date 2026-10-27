#pragma once

#include <cstddef>
#include <span>
#include <utility>

namespace kata {

namespace detail {
// Lomuto partition around the last element; returns the pivot's final index.
inline std::size_t partition(std::span<int> arr) {
    const int pivot = arr.back();
    std::size_t store = 0;
    for (std::size_t i = 0; i + 1 < arr.size(); ++i) {
        if (arr[i] <= pivot) std::swap(arr[i], arr[store++]);
    }
    std::swap(arr[store], arr.back());
    return store;
}
}  // namespace detail

inline void quick_sort(std::span<int> arr) {
    if (arr.size() < 2) return;
    const std::size_t p = detail::partition(arr);
    quick_sort(arr.first(p));
    quick_sort(arr.subspan(p + 1));
}

}  // namespace kata
