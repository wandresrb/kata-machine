#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace kata {

class MinHeap {
public:
    void insert(int value) {
        data_.push_back(value);
        heapify_up(data_.size() - 1);
    }

    std::optional<int> remove() {
        if (data_.empty()) return std::nullopt;
        const int out = data_.front();
        data_.front() = data_.back();
        data_.pop_back();
        heapify_down(0);
        return out;
    }

    [[nodiscard]] std::size_t length() const { return data_.size(); }

private:
    static std::size_t parent(std::size_t i) { return (i - 1) / 2; }
    static std::size_t left_child(std::size_t i) { return 2 * i + 1; }
    static std::size_t right_child(std::size_t i) { return 2 * i + 2; }

    void heapify_up(std::size_t i) {
        while (i > 0 && data_[parent(i)] > data_[i]) {
            std::swap(data_[parent(i)], data_[i]);
            i = parent(i);
        }
    }

    void heapify_down(std::size_t i) {
        for (;;) {
            std::size_t smallest = i;
            const std::size_t l = left_child(i);
            const std::size_t r = right_child(i);
            if (l < data_.size() && data_[l] < data_[smallest]) smallest = l;
            if (r < data_.size() && data_[r] < data_[smallest]) smallest = r;
            if (smallest == i) return;
            std::swap(data_[i], data_[smallest]);
            i = smallest;
        }
    }

    std::vector<int> data_;
};

}  // namespace kata
