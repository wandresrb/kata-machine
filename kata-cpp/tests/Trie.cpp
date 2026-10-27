#include "Trie.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include "kata_test.hpp"

using kata::test::expect_eq;

static std::vector<std::string> sorted(std::vector<std::string> words) {
    std::ranges::sort(words);
    return words;
}

TEST(trie) {
    kata::Trie trie;
    trie.insert("foo");
    trie.insert("fool");
    trie.insert("foolish");
    trie.insert("bar");

    expect_eq(sorted(trie.find("fo")), std::vector<std::string>{"foo", "fool", "foolish"});

    trie.remove("fool");

    expect_eq(sorted(trie.find("fo")), std::vector<std::string>{"foo", "foolish"});
}
