#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace kata {

// 26-way trie over lowercase ASCII letters.
class Trie {
public:
    void insert(std::string_view word) {
        Node* cur = &root_;
        for (const char c : word) {
            auto& child = cur->children[index(c)];
            if (!child) child = std::make_unique<Node>();
            cur = child.get();
        }
        cur->is_word = true;
    }

    [[nodiscard]] std::vector<std::string> find(std::string_view prefix) const {
        const Node* cur = &root_;
        for (const char c : prefix) {
            cur = cur->children[index(c)].get();
            if (!cur) return {};
        }
        std::vector<std::string> out;
        std::string word{prefix};
        collect(*cur, word, out);
        return out;
    }

    void remove(std::string_view word) { remove(root_, word); }

private:
    struct Node {
        bool is_word = false;
        std::array<std::unique_ptr<Node>, 26> children{};
    };

    static std::size_t index(char c) { return static_cast<std::size_t>(c - 'a'); }

    static void collect(const Node& node, std::string& word, std::vector<std::string>& out) {
        if (node.is_word) out.push_back(word);
        for (std::size_t i = 0; i < node.children.size(); ++i) {
            if (!node.children[i]) continue;
            word.push_back(static_cast<char>('a' + i));
            collect(*node.children[i], word, out);
            word.pop_back();
        }
    }

    // Returns true if `node` became useless (not a word, no children) and can be pruned.
    static bool remove(Node& node, std::string_view word) {
        if (word.empty()) {
            node.is_word = false;
        } else {
            auto& child = node.children[index(word.front())];
            if (child && remove(*child, word.substr(1))) child.reset();
        }
        return !node.is_word && std::ranges::none_of(node.children, [](const auto& c) { return c != nullptr; });
    }

    Node root_;
};

}  // namespace kata
