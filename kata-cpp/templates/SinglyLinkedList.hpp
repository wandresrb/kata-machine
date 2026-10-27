#pragma once

#include <cstddef>
#include <optional>

namespace kata {

// Must satisfy kata::List<SinglyLinkedList<T>, T> (see include/kata/types.hpp).
template <class T>
class SinglyLinkedList {
public:
    SinglyLinkedList() = default;

    void prepend([[maybe_unused]] T item) {}

    void insert_at([[maybe_unused]] T item, [[maybe_unused]] std::size_t idx) {}

    void append([[maybe_unused]] T item) {}

    std::optional<T> remove([[maybe_unused]] const T& item) { return std::nullopt; }

    [[nodiscard]] std::optional<T> get([[maybe_unused]] std::size_t idx) const { return std::nullopt; }

    std::optional<T> remove_at([[maybe_unused]] std::size_t idx) { return std::nullopt; }

    [[nodiscard]] std::size_t length() const { return 0; }

private:
    // your state here
};

}  // namespace kata
