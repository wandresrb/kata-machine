#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

namespace kata {

// A growable array backed by a manually managed buffer (no std::vector).
template <class T>
class ArrayList {
public:
    explicit ArrayList(std::size_t capacity) : capacity_{std::max<std::size_t>(capacity, 1)}, data_{std::make_unique<T[]>(capacity_)} {}

    void prepend(T item) { insert_at(std::move(item), 0); }

    void insert_at(T item, std::size_t idx) {
        if (idx > length_) return;
        grow_if_full();
        std::move_backward(data_.get() + idx, data_.get() + length_, data_.get() + length_ + 1);
        data_[idx] = std::move(item);
        ++length_;
    }

    void append(T item) { insert_at(std::move(item), length_); }

    std::optional<T> remove(const T& item) {
        T* const first = data_.get();
        T* const last = first + length_;
        T* const it = std::find(first, last, item);
        if (it == last) return std::nullopt;
        return remove_at(static_cast<std::size_t>(it - first));
    }

    [[nodiscard]] std::optional<T> get(std::size_t idx) const {
        if (idx >= length_) return std::nullopt;
        return data_[idx];
    }

    std::optional<T> remove_at(std::size_t idx) {
        if (idx >= length_) return std::nullopt;
        T out = std::move(data_[idx]);
        std::move(data_.get() + idx + 1, data_.get() + length_, data_.get() + idx);
        --length_;
        return out;
    }

    [[nodiscard]] std::size_t length() const { return length_; }

private:
    void grow_if_full() {
        if (length_ < capacity_) return;
        const std::size_t new_capacity = capacity_ * 2;
        auto bigger = std::make_unique<T[]>(new_capacity);
        std::move(data_.get(), data_.get() + length_, bigger.get());
        data_ = std::move(bigger);
        capacity_ = new_capacity;
    }

    std::size_t length_ = 0;
    std::size_t capacity_;
    std::unique_ptr<T[]> data_;
};

}  // namespace kata
