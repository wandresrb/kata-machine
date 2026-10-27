#pragma once

#include <cstddef>
#include <optional>

namespace kata {

template <class T>
class Queue {
public:
    void enqueue([[maybe_unused]] T item) {}

    std::optional<T> deque() { return std::nullopt; }

    [[nodiscard]] std::optional<T> peek() const { return std::nullopt; }

    [[nodiscard]] std::size_t length() const { return 0; }

private:
    // your state here
};

}  // namespace kata
