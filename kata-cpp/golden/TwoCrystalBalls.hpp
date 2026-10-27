#pragma once

#include <cmath>
#include <cstddef>
#include <optional>
#include <vector>

namespace kata {

inline std::optional<std::size_t> two_crystal_balls(const std::vector<bool>& breaks) {
    const auto jump = static_cast<std::size_t>(std::sqrt(static_cast<double>(breaks.size())));
    if (jump == 0) return std::nullopt;

    std::size_t i = jump;
    while (i < breaks.size() && !breaks[i]) i += jump;

    // The first ball broke at i (or we ran off the end); walk the last block.
    for (std::size_t j = i - jump; j <= i && j < breaks.size(); ++j) {
        if (breaks[j]) return j;
    }
    return std::nullopt;
}

}  // namespace kata
