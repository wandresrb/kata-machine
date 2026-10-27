#include "Map.hpp"

#include <optional>
#include <string>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(map) {
    kata::Map<std::string, int> map;
    map.set("foo", 55);
    expect_eq(map.size(), 1);
    map.set("fool", 75);
    expect_eq(map.size(), 2);
    map.set("foolish", 105);
    expect_eq(map.size(), 3);
    map.set("bar", 69);
    expect_eq(map.size(), 4);

    expect_eq(map.get("bar"), 69);
    expect_eq(map.get("blaz"), std::nullopt);

    map.remove("barblabr");
    expect_eq(map.size(), 4);

    map.remove("bar");
    expect_eq(map.size(), 3);
    expect_eq(map.get("bar"), std::nullopt);
}
