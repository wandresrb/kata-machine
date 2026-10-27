#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace kata {

// Circular FIFO buffer that doubles its capacity when full.
// get(i) is relative to the oldest element.
template <class T>
class RingBuffer {
public:
    explicit RingBuffer(std::size_t capacity = 4) : data_(capacity == 0 ? 1 : capacity) {}

    void push(T item) {
        if (length_ == data_.size()) grow();
        data_[(head_ + length_) % data_.size()] = std::move(item);
        ++length_;
    }

    std::optional<T> pop() {
        if (length_ == 0) return std::nullopt;
        T out = std::move(data_[head_]);
        head_ = (head_ + 1) % data_.size();
        --length_;
        return out;
    }

    [[nodiscard]] std::optional<T> get(std::size_t idx) const {
        if (idx >= length_) return std::nullopt;
        return data_[(head_ + idx) % data_.size()];
    }

    [[nodiscard]] std::size_t length() const { return length_; }

private:
    void grow() {
        std::vector<T> bigger(data_.size() * 2);
        for (std::size_t i = 0; i < length_; ++i) {
            bigger[i] = std::move(data_[(head_ + i) % data_.size()]);
        }
        data_ = std::move(bigger);
        head_ = 0;
    }

    std::vector<T> data_;
    std::size_t head_ = 0;
    std::size_t length_ = 0;
};

}  // namespace kata
