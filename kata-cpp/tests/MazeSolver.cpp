#include "MazeSolver.hpp"

#include <cstddef>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "kata_test.hpp"

using kata::Point;
using kata::test::expect_eq;

// Marks every in-bounds point of `path` with '*' (port of drawPath in MazeSolver.ts).
static std::vector<std::string> draw_path(std::vector<std::string> maze, std::span<const Point> path) {
    for (const auto [x, y] : path) {
        if (y >= 0 && std::cmp_less(y, maze.size()) && x >= 0 && std::cmp_less(x, maze[static_cast<std::size_t>(y)].size())) {
            maze[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)] = '*';
        }
    }
    return maze;
}

TEST(maze_solver) {
    const std::vector<std::string> maze = {
        "xxxxxxxxxx x",
        "x        x x",
        "x        x x",
        "x xxxxxxxx x",
        "x          x",
        "x xxxxxxxxxx",
    };

    const std::vector<Point> maze_result = {
        {.x = 10, .y = 0}, {.x = 10, .y = 1}, {.x = 10, .y = 2}, {.x = 10, .y = 3},
        {.x = 10, .y = 4}, {.x = 9, .y = 4},  {.x = 8, .y = 4},  {.x = 7, .y = 4},
        {.x = 6, .y = 4},  {.x = 5, .y = 4},  {.x = 4, .y = 4},  {.x = 3, .y = 4},
        {.x = 2, .y = 4},  {.x = 1, .y = 4},  {.x = 1, .y = 5},
    };

    // there is only one path through
    const auto result = kata::solve(maze, 'x', {.x = 10, .y = 0}, {.x = 1, .y = 5});
    expect_eq(draw_path(maze, result), draw_path(maze, maze_result));
}
