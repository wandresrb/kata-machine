#pragma once

#include <cstddef>
#include <optional>

namespace kata {

// Growable circular buffer: pop() removes the OLDEST item, get(0) is the oldest.
template <class T>
class RingBuffer {
public:
    void push([[maybe_unused]] T item) {}

    std::optional<T> pop() { return std::nullopt; }

    [[nodiscard]] std::optional<T> get([[maybe_unused]] std::size_t idx) const { return std::nullopt; }

    [[nodiscard]] std::size_t length() const { return 0; }

private:
    // your state here
};

}  // namespace kata
