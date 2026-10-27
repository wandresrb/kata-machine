#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

namespace kata {

// next pointers own the nodes; prev pointers and tail_ are non-owning.
template <class T>
class DoublyLinkedList {
public:
    DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    ~DoublyLinkedList() {
        while (head_) head_ = std::move(head_->next);
    }

    void prepend(T item) { insert_at(std::move(item), 0); }

    void insert_at(T item, std::size_t idx) {
        if (idx > length_) return;
        Node* after = idx == length_ ? nullptr : node_at(idx);
        Node* before = after ? after->prev : tail_;
        std::unique_ptr<Node>& slot = before ? before->next : head_;

        auto node = std::make_unique<Node>(std::move(item), std::move(slot), before);
        Node* raw = node.get();
        slot = std::move(node);
        if (after) {
            after->prev = raw;
        } else {
            tail_ = raw;
        }
        ++length_;
    }

    void append(T item) { insert_at(std::move(item), length_); }

    std::optional<T> remove(const T& item) {
        for (Node* cur = head_.get(); cur; cur = cur->next.get()) {
            if (cur->value == item) return unlink(cur);
        }
        return std::nullopt;
    }

    [[nodiscard]] std::optional<T> get(std::size_t idx) const {
        if (idx >= length_) return std::nullopt;
        return node_at(idx)->value;
    }

    std::optional<T> remove_at(std::size_t idx) {
        if (idx >= length_) return std::nullopt;
        return unlink(node_at(idx));
    }

    [[nodiscard]] std::size_t length() const { return length_; }

private:
    struct Node {
        T value;
        std::unique_ptr<Node> next;
        Node* prev = nullptr;
    };

    // Walks from whichever end is closer. Precondition: idx < length_.
    Node* node_at(std::size_t idx) const {
        if (idx < length_ / 2) {
            Node* cur = head_.get();
            for (std::size_t i = 0; i < idx; ++i) cur = cur->next.get();
            return cur;
        }
        Node* cur = tail_;
        for (std::size_t i = length_ - 1; i > idx; --i) cur = cur->prev;
        return cur;
    }

    T unlink(Node* node) {
        Node* prev = node->prev;
        std::unique_ptr<Node>& owner = prev ? prev->next : head_;
        std::unique_ptr<Node> owned = std::move(owner);
        owner = std::move(owned->next);
        if (owner) {
            owner->prev = prev;
        } else {
            tail_ = prev;
        }
        --length_;
        return std::move(owned->value);
    }

    std::unique_ptr<Node> head_;
    Node* tail_ = nullptr;
    std::size_t length_ = 0;
};

}  // namespace kata
