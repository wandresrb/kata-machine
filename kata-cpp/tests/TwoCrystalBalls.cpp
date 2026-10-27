#include "TwoCrystalBalls.hpp"

#include <cstddef>
#include <optional>
#include <random>
#include <vector>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(two_crystal_balls) {
    constexpr std::size_t size = 10000;
    std::mt19937 rng{std::random_device{}()};
    const std::size_t idx = std::uniform_int_distribution<std::size_t>{0, size - 1}(rng);

    std::vector<bool> data(size, false);
    for (std::size_t i = idx; i < size; ++i) {
        data[i] = true;
    }

    expect_eq(kata::two_crystal_balls(data), idx);
    expect_eq(kata::two_crystal_balls(std::vector<bool>(821, false)), std::nullopt);
}
