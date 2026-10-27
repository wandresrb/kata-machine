#include "RingBuffer.hpp"

#include <optional>

#include "kata_test.hpp"

using kata::test::expect_eq;

TEST(ring_buffer) {
    kata::RingBuffer<int> buffer;

    buffer.push(5);
    expect_eq(buffer.pop(), 5);
    expect_eq(buffer.pop(), std::nullopt);

    buffer.push(42);
    buffer.push(9);
    expect_eq(buffer.pop(), 42);
    expect_eq(buffer.pop(), 9);
    expect_eq(buffer.pop(), std::nullopt);

    buffer.push(42);
    buffer.push(9);
    buffer.push(12);
    expect_eq(buffer.get(2), 12);
    expect_eq(buffer.get(1), 9);
    expect_eq(buffer.get(0), 42);
}
