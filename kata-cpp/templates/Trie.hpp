#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace kata {

class Trie {
public:
    void insert([[maybe_unused]] std::string_view word) {}

    // Every inserted word starting with `prefix` (any order).
    [[nodiscard]] std::vector<std::string> find([[maybe_unused]] std::string_view prefix) const { return {}; }

    void remove([[maybe_unused]] std::string_view word) {}

private:
    // your state here
};

}  // namespace kata
