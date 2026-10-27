#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

namespace kata {

template <class T>
class SinglyLinkedList {
public:
    SinglyLinkedList() = default;
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
    SinglyLinkedList(SinglyLinkedList&&) noexcept = default;
    SinglyLinkedList& operator=(SinglyLinkedList&&) noexcept = default;
    // Unlink iteratively so long lists don't blow the stack via recursive dtors.
    ~SinglyLinkedList() {
        while (head_) head_ = std::move(head_->next);
    }

    void prepend(T item) { insert_at(std::move(item), 0); }

    void insert_at(T item, std::size_t idx) {
        if (idx > length_) return;
        std::unique_ptr<Node>& slot = link_at(idx);
        slot = std::make_unique<Node>(std::move(item), std::move(slot));
        ++length_;
    }

    void append(T item) { insert_at(std::move(item), length_); }

    std::optional<T> remove(const T& item) {
        std::unique_ptr<Node>* link = &head_;
        while (*link && (*link)->value != item) link = &(*link)->next;
        if (!*link) return std::nullopt;
        return unlink(*link);
    }

    [[nodiscard]] std::optional<T> get(std::size_t idx) const {
        if (idx >= length_) return std::nullopt;
        const Node* cur = head_.get();
        for (std::size_t i = 0; i < idx; ++i) cur = cur->next.get();
        return cur->value;
    }

    std::optional<T> remove_at(std::size_t idx) {
        if (idx >= length_) return std::nullopt;
        return unlink(link_at(idx));
    }

    [[nodiscard]] std::size_t length() const { return length_; }

private:
    struct Node {
        T value;
        std::unique_ptr<Node> next;
    };

    // The owning pointer that points at node `idx` (idx == length_ -> the null tail link).
    std::unique_ptr<Node>& link_at(std::size_t idx) {
        std::unique_ptr<Node>* link = &head_;
        for (std::size_t i = 0; i < idx; ++i) link = &(*link)->next;
        return *link;
    }

    T unlink(std::unique_ptr<Node>& link) {
        std::unique_ptr<Node> node = std::move(link);
        link = std::move(node->next);
        --length_;
        return std::move(node->value);
    }

    std::unique_ptr<Node> head_;
    std::size_t length_ = 0;
};

}  // namespace kata
