#pragma once

#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

namespace kata {

// Recency list (front = most recent) + hash map from key to list node.
template <class K, class V>
class LRU {
public:
    explicit LRU(std::size_t capacity) : capacity_{capacity} {}

    void update(K key, V value) {
        if (auto it = lookup_.find(key); it != lookup_.end()) {
            it->second->second = std::move(value);
            items_.splice(items_.begin(), items_, it->second);
            return;
        }
        items_.emplace_front(key, std::move(value));
        lookup_.emplace(std::move(key), items_.begin());
        if (items_.size() > capacity_) {
            lookup_.erase(items_.back().first);
            items_.pop_back();
        }
    }

    std::optional<V> get(const K& key) {
        auto it = lookup_.find(key);
        if (it == lookup_.end()) return std::nullopt;
        items_.splice(items_.begin(), items_, it->second);
        return it->second->second;
    }

private:
    using Entry = std::pair<K, V>;

    std::size_t capacity_;
    std::list<Entry> items_;
    std::unordered_map<K, typename std::list<Entry>::iterator> lookup_;
};

}  // namespace kata
