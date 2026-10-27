#pragma once

// Exact copies of src/__tests__/graph.ts.

#include <kata/types.hpp>

namespace kata::fixtures {

//      (1) --- (4) ---- (5)
//    /  |       |       /|
// (0)   | ------|------- |
//    \  |/      |        |
//      (2) --- (3) ---- (6)
inline const WeightedAdjacencyList list1 = {
    /* 0 */ {{.to = 1, .weight = 3}, {.to = 2, .weight = 1}},
    /* 1 */ {{.to = 0, .weight = 3}, {.to = 2, .weight = 4}, {.to = 4, .weight = 1}},
    /* 2 */ {{.to = 1, .weight = 4}, {.to = 3, .weight = 7}, {.to = 0, .weight = 1}},
    /* 3 */ {{.to = 2, .weight = 7}, {.to = 4, .weight = 5}, {.to = 6, .weight = 1}},
    /* 4 */ {{.to = 1, .weight = 1}, {.to = 3, .weight = 5}, {.to = 5, .weight = 2}},
    /* 5 */ {{.to = 6, .weight = 1}, {.to = 4, .weight = 2}, {.to = 2, .weight = 18}},
    /* 6 */ {{.to = 3, .weight = 1}, {.to = 5, .weight = 1}},
};

//     >(1)<--->(4) ---->(5)
//    /          |       /|
// (0)     ------|------- |
//    \   v      v        v
//     >(2) --> (3) <----(6)
inline const WeightedAdjacencyList list2 = {
    /* 0 */ {{.to = 1, .weight = 3}, {.to = 2, .weight = 1}},
    /* 1 */ {{.to = 4, .weight = 1}},
    /* 2 */ {{.to = 3, .weight = 7}},
    /* 3 */ {},
    /* 4 */ {{.to = 1, .weight = 1}, {.to = 3, .weight = 5}, {.to = 5, .weight = 2}},
    /* 5 */ {{.to = 2, .weight = 18}, {.to = 6, .weight = 1}},
    /* 6 */ {{.to = 3, .weight = 1}},
};

//     >(1)<--->(4) ---->(5)
//    /          |       /|
// (0)     ------|------- |
//    \   v      v        v
//     >(2) --> (3) <----(6)
// (copied verbatim from graph.ts, including its quirks: row 2 has its weight
// in column 2 and row 6 has a self-loop)
inline const WeightedAdjacencyMatrix matrix2 = {
    {0, 3, 1, 0, 0, 0, 0},      // 0
    {0, 0, 0, 0, 1, 0, 0},      // 1
    {0, 0, 7, 0, 0, 0, 0},      // 2
    {0, 0, 0, 0, 0, 0, 0},      // 3
    {0, 1, 0, 5, 0, 2, 0},      // 4
    {0, 0, 18, 0, 0, 0, 1},     // 5
    {0, 0, 0, 1, 0, 0, 1},      // 6
};

}  // namespace kata::fixtures
