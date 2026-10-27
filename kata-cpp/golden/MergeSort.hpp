#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <span>
#include <vector>

namespace kata {

inline void merge_sort(std::span<int> arr) {
    if (arr.size() < 2) return;
    const std::size_t mid = arr.size() / 2;
    auto left = arr.first(mid);
    auto right = arr.subspan(mid);
    merge_sort(left);
    merge_sort(right);

    std::vector<int> merged;
    merged.reserve(arr.size());
    std::ranges::merge(left, right, std::back_inserter(merged));
    std::ranges::copy(merged, arr.begin());
}

}  // namespace kata
