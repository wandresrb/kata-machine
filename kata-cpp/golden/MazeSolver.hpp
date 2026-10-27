#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include <kata/types.hpp>

namespace kata {

namespace detail::maze {

constexpr std::array<Point, 4> directions{{{.x = -1, .y = 0}, {.x = 1, .y = 0}, {.x = 0, .y = -1}, {.x = 0, .y = 1}}};

struct Walker {
    const std::vector<std::string>& maze;
    char wall;
    Point end;
    std::vector<std::vector<bool>> seen;
    std::vector<Point> path;

    bool walk(Point p) {
        if (p.y < 0 || static_cast<std::size_t>(p.y) >= maze.size()) return false;
        const auto y = static_cast<std::size_t>(p.y);
        if (p.x < 0 || static_cast<std::size_t>(p.x) >= maze[y].size()) return false;
        const auto x = static_cast<std::size_t>(p.x);
        if (maze[y][x] == wall || seen[y][x]) return false;

        seen[y][x] = true;
        path.push_back(p);
        if (p == end) return true;
        for (const auto [dx, dy] : directions) {
            if (walk({.x = p.x + dx, .y = p.y + dy})) return true;
        }
        path.pop_back();
        return false;
    }
};

}  // namespace detail::maze

inline std::vector<Point> solve(const std::vector<std::string>& maze, char wall, Point start, Point end) {
    detail::maze::Walker walker{.maze = maze, .wall = wall, .end = end, .seen = {}, .path = {}};
    for (const auto& row : maze) walker.seen.emplace_back(row.size(), false);
    walker.walk(start);
    return std::move(walker.path);
}

}  // namespace kata
