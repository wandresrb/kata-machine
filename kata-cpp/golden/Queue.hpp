#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

namespace kata {

// Singly linked FIFO: owning head_, non-owning tail_.
template <class T>
class Queue {
public:
    Queue() = default;
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    ~Queue() {
        while (head_) head_ = std::move(head_->next);
    }

    void enqueue(T item) {
        auto node = std::make_unique<Node>(std::move(item), nullptr);
        Node* raw = node.get();
        if (tail_) {
            tail_->next = std::move(node);
        } else {
            head_ = std::move(node);
        }
        tail_ = raw;
        ++length_;
    }

    std::optional<T> deque() {
        if (!head_) return std::nullopt;
        std::unique_ptr<Node> old = std::move(head_);
        head_ = std::move(old->next);
        if (!head_) tail_ = nullptr;
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
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head_;
    Node* tail_ = nullptr;
    std::size_t length_ = 0;
};

}  // namespace kata
