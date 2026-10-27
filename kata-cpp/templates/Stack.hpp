#pragma once

#include <cstddef>
#include <optional>

namespace kata {

template <class T>
class Stack {
public:
    void push([[maybe_unused]] T item) {}

    std::optional<T> pop() { return std::nullopt; }

    [[nodiscard]] std::optional<T> peek() const { return std::nullopt; }

    [[nodiscard]] std::size_t length() const { return 0; }

private:
    // your state here
};

}  // namespace kata
