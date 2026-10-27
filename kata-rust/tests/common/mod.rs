//! Shared fixtures — exact ports of `src/__tests__/{tree,graph,ListTest}.ts`.
#![allow(dead_code)]

use kata::types::{BinaryNode, GraphEdge, List, WeightedAdjacencyList, WeightedAdjacencyMatrix};

fn node(
    value: i32,
    left: Option<BinaryNode<i32>>,
    right: Option<BinaryNode<i32>>,
) -> Option<BinaryNode<i32>> {
    Some(BinaryNode::new(value, left, right))
}

fn leaf(value: i32) -> Option<BinaryNode<i32>> {
    Some(BinaryNode::leaf(value))
}

//            20
//         /      \
//       10        50
//      /  \      /  \
//     5    15   30   100
//      \       /  \
//       7     29   45
pub fn tree() -> BinaryNode<i32> {
    BinaryNode::new(
        20,
        node(10, node(5, None, leaf(7)), leaf(15)),
        node(50, node(30, leaf(29), leaf(45)), leaf(100)),
    )
}

//            20
//         /      \
//       10        50
//      /  \      /
//     5    15   30
//      \       /  \
//       7     29   45
//            /       \
//           21        49
pub fn tree2() -> BinaryNode<i32> {
    BinaryNode::new(
        20,
        node(10, node(5, None, leaf(7)), leaf(15)),
        node(
            50,
            node(30, node(29, leaf(21), None), node(45, None, leaf(49))),
            None,
        ),
    )
}

fn edges(list: &[(usize, u32)]) -> Vec<GraphEdge> {
    list.iter()
        .map(|&(to, weight)| GraphEdge { to, weight })
        .collect()
}

//      (1) --- (4) ---- (5)
//    /  |       |       /|
// (0)   | ------|------- |
//    \  |/      |        |
//      (2) --- (3) ---- (6)
pub fn list1() -> WeightedAdjacencyList {
    vec![
        edges(&[(1, 3), (2, 1)]),
        edges(&[(0, 3), (2, 4), (4, 1)]),
        edges(&[(1, 4), (3, 7), (0, 1)]),
        edges(&[(2, 7), (4, 5), (6, 1)]),
        edges(&[(1, 1), (3, 5), (5, 2)]),
        edges(&[(6, 1), (4, 2), (2, 18)]),
        edges(&[(3, 1), (5, 1)]),
    ]
}

//     >(1)<--->(4) ---->(5)
//    /          |       /|
// (0)     ------|------- |
//    \   v      v        v
//     >(2) --> (3) <----(6)
pub fn list2() -> WeightedAdjacencyList {
    vec![
        edges(&[(1, 3), (2, 1)]),
        edges(&[(4, 1)]),
        edges(&[(3, 7)]),
        edges(&[]),
        edges(&[(1, 1), (3, 5), (5, 2)]),
        edges(&[(2, 18), (6, 1)]),
        edges(&[(3, 1)]),
    ]
}

//     >(1)<--->(4) ---->(5)
//    /          |       /|
// (0)     ------|------- |
//    \   v      v        v
//     >(2) --> (3) <----(6)
#[rustfmt::skip]
pub fn matrix2() -> WeightedAdjacencyMatrix {
    vec![
        vec![0, 3, 1,  0, 0, 0, 0], // 0
        vec![0, 0, 0,  0, 1, 0, 0],
        vec![0, 0, 7,  0, 0, 0, 0],
        vec![0, 0, 0,  0, 0, 0, 0],
        vec![0, 1, 0,  5, 0, 2, 0],
        vec![0, 0, 18, 0, 0, 0, 1],
        vec![0, 0, 0,  1, 0, 0, 1],
    ]
}

pub fn test_list<L: List<i32>>(list: &mut L) {
    list.append(5);
    list.append(7);
    list.append(9);

    assert_eq!(list.get(2), Some(9));
    assert_eq!(list.remove_at(1), Some(7));
    assert_eq!(list.len(), 2);

    list.append(11);
    assert_eq!(list.remove_at(1), Some(9));
    assert_eq!(list.remove(&9), None);
    assert_eq!(list.remove_at(0), Some(5));
    assert_eq!(list.remove_at(0), Some(11));
    assert_eq!(list.len(), 0);

    list.prepend(5);
    list.prepend(7);
    list.prepend(9);

    assert_eq!(list.get(2), Some(5));
    assert_eq!(list.get(0), Some(9));
    assert_eq!(list.remove(&9), Some(9));
    assert_eq!(list.len(), 2);
    assert_eq!(list.get(0), Some(7));
}
