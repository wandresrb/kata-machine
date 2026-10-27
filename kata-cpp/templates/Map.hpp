#pragma once

#include <cstddef>
#include <functional>
#include <optional>

namespace kata {

// Hand-made hash map (don't wrap std::unordered_map). Hash the key with std::hash<K>.
template <class K, class V>
class Map {
public:
    [[nodiscard]] std::optional<V> get([[maybe_unused]] const K& key) const { return std::nullopt; }

    void set([[maybe_unused]] K key, [[maybe_unused]] V value) {}

    std::optional<V> remove([[maybe_unused]] const K& key) { return std::nullopt; }

    [[nodiscard]] std::size_t size() const { return 0; }

private:
    // your state here
};

}  // namespace kata
