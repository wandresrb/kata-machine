#pragma once

// Exact copies of src/__tests__/tree.ts. Each call builds a fresh tree.

#include <memory>
#include <utility>

#include <kata/types.hpp>

namespace kata::fixtures {

using Node = BinaryNode<int>;
using NodePtr = std::unique_ptr<Node>;

inline NodePtr node(int value, NodePtr left = nullptr, NodePtr right = nullptr) {
    return std::make_unique<Node>(value, std::move(left), std::move(right));
}

//            20
//        /        \
//      10          50
//     /  \        /   \
//    5    15     30    100
//     \         /  \
//      7       29   45
inline NodePtr tree() {
    return node(20,
                node(10,
                     node(5, nullptr, node(7)),
                     node(15)),
                node(50,
                     node(30, node(29), node(45)),
                     node(100)));
}

//            20
//        /        \
//      10          50
//     /  \        /
//    5    15     30
//     \         /  \
//      7       29   45
//             /       \
//            21        49
inline NodePtr tree2() {
    return node(20,
                node(10,
                     node(5, nullptr, node(7)),
                     node(15)),
                node(50,
                     node(30,
                          node(29, node(21)),
                          node(45, nullptr, node(49))),
                     nullptr));
}

}  // namespace kata::fixtures
