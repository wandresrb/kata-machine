mod common;

use kata::code::prims_list::prims;
use kata::types::{GraphEdge, WeightedAdjacencyList};

fn edges(list: &[(usize, u32)]) -> Vec<GraphEdge> {
    list.iter()
        .map(|&(to, weight)| GraphEdge { to, weight })
        .collect()
}

/// The TS test compares edge order too, but that order is an artifact of the
/// reference implementation. Here each node's edges are compared as a set:
/// both sides are sorted by `(to, weight)` before comparing.
fn normalize(mut list: WeightedAdjacencyList) -> WeightedAdjacencyList {
    for node in &mut list {
        node.sort_by_key(|e| (e.to, e.weight));
    }
    list
}

#[test]
fn prims_list() {
    // there is only one right answer for this graph
    let expected = vec![
        edges(&[(2, 1), (1, 3)]),
        edges(&[(0, 3), (4, 1)]),
        edges(&[(0, 1)]),
        edges(&[(6, 1)]),
        edges(&[(1, 1), (5, 2)]),
        edges(&[(4, 2), (6, 1)]),
        edges(&[(5, 1), (3, 1)]),
    ];

    let mst = prims(&common::list1()).expect("list1 is connected");
    assert_eq!(normalize(mst), normalize(expected));
}
