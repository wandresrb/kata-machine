#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

namespace kata {

template <class T>
class Stack {
public:
    Stack() = default;
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    ~Stack() {
        while (head_) head_ = std::move(head_->prev);
    }

    void push(T item) {
        head_ = std::make_unique<Node>(std::move(item), std::move(head_));
        ++length_;
    }

    std::optional<T> pop() {
        if (!head_) return std::nullopt;
        std::unique_ptr<Node> old = std::move(head_);
        head_ = std::move(old->prev);
        --length_;
        return std::move(old->value);
    }

    [[nodiscard]] std::optional<T> peek() const {
        if (!head_) return std::nullopt;
        return head_->value;
    }

    [[nodiscard]] std::size_t length() const { return length_; }

private:
    struct Node {
        T value;
        std::unique_ptr<Node> prev;
    };

    std::unique_ptr<Node> head_;
    std::size_t length_ = 0;
};

}  // namespace kata
