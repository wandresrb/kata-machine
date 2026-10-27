#pragma once

#include <cstddef>
#include <optional>
#include <vector>

namespace kata {

// Index of the first `true` (every value after it is also true), or nullopt if none.
inline std::optional<std::size_t> two_crystal_balls([[maybe_unused]] const std::vector<bool>& breaks) {
    return std::nullopt;
}

}  // namespace kata
