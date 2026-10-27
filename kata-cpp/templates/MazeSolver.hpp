#pragma once

#include <string>
#include <vector>

#include <kata/types.hpp>

namespace kata {

// Path from `start` to `end` (both inclusive) moving up/down/left/right, never through `wall`.
inline std::vector<Point> solve([[maybe_unused]] const std::vector<std::string>& maze, [[maybe_unused]] char wall,
                                [[maybe_unused]] Point start, [[maybe_unused]] Point end) {
    return {};
}

}  // namespace kata
