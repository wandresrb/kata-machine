#pragma once

#include <cstddef>
#include <optional>

namespace kata {

class MinHeap {
public:
    void insert([[maybe_unused]] int value) {}

    // Removes and returns the smallest value.
    std::optional<int> remove() { return std::nullopt; }

    [[nodiscard]] std::size_t length() const { return 0; }

private:
    // your state here
};

}  // namespace kata
