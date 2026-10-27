#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

namespace kata {

// Separate-chaining hash map; rehashes when the load factor exceeds 0.75.
template <class K, class V, class Hash = std::hash<K>>
class Map {
public:
    [[nodiscard]] std::optional<V> get(const K& key) const {
        if (buckets_.empty()) return std::nullopt;
        const auto& bucket = bucket_for(key);
        const auto it = std::ranges::find(bucket, key, &Entry::first);
        if (it == bucket.end()) return std::nullopt;
        return it->second;
    }

    void set(K key, V value) {
        if (buckets_.empty() || static_cast<double>(size_ + 1) > 0.75 * static_cast<double>(buckets_.size())) {
            rehash(buckets_.empty() ? 8 : buckets_.size() * 2);
        }
        auto& bucket = bucket_for(key);
        if (auto it = std::ranges::find(bucket, key, &Entry::first); it != bucket.end()) {
            it->second = std::move(value);
            return;
        }
        bucket.emplace_back(std::move(key), std::move(value));
        ++size_;
    }

    std::optional<V> remove(const K& key) {
        if (buckets_.empty()) return std::nullopt;
        auto& bucket = bucket_for(key);
        const auto it = std::ranges::find(bucket, key, &Entry::first);
        if (it == bucket.end()) return std::nullopt;
        V out = std::move(it->second);
        bucket.erase(it);
        --size_;
        return out;
    }

    [[nodiscard]] std::size_t size() const { return size_; }

private:
    using Entry = std::pair<K, V>;
    using Bucket = std::vector<Entry>;

    Bucket& bucket_for(const K& key) { return buckets_[Hash{}(key) % buckets_.size()]; }
    const Bucket& bucket_for(const K& key) const { return buckets_[Hash{}(key) % buckets_.size()]; }

    void rehash(std::size_t bucket_count) {
        std::vector<Bucket> old = std::exchange(buckets_, std::vector<Bucket>(bucket_count));
        for (auto& bucket : old) {
            for (auto& entry : bucket) bucket_for(entry.first).push_back(std::move(entry));
        }
    }

    std::vector<Bucket> buckets_;
    std::size_t size_ = 0;
};

}  // namespace kata
