#include "LRU.hpp"

#include <optional>
#include <string>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(lru) {
    using std::nullopt;
    kata::LRU<std::string, int> lru(3);

    expect_eq(lru.get("foo"), nullopt);
    lru.update("foo", 69);
    expect_eq(lru.get("foo"), 69);

    lru.update("bar", 420);
    expect_eq(lru.get("bar"), 420);

    lru.update("baz", 1337);
    expect_eq(lru.get("baz"), 1337);

    lru.update("ball", 69420);
    expect_eq(lru.get("ball"), 69420);
    expect_eq(lru.get("foo"), nullopt);
    expect_eq(lru.get("bar"), 420);
    lru.update("foo", 69);
    expect_eq(lru.get("bar"), 420);
    expect_eq(lru.get("foo"), 69);

    // shouldn't of been deleted, but since bar was get'd, bar was added to the
    // front of the list, so baz became the end
    expect_eq(lru.get("baz"), nullopt);
}
