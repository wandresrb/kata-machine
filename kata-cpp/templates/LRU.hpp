#pragma once

#include <cstddef>
#include <optional>

namespace kata {

// Least-recently-used cache: get() and update() both mark the key as most recent.
template <class K, class V>
class LRU {
public:
    explicit LRU([[maybe_unused]] std::size_t capacity) {}

    void update([[maybe_unused]] K key, [[maybe_unused]] V value) {}

    std::optional<V> get([[maybe_unused]] const K& key) { return std::nullopt; }

private:
    // your state here
};

}  // namespace kata
