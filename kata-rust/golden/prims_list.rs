use std::cmp::Reverse;
use std::collections::BinaryHeap;

use crate::types::{GraphEdge, WeightedAdjacencyList};

/// Minimum spanning tree of an undirected graph, starting from node 0.
/// Returns `None` if the graph is not connected.
pub fn prims(list: &WeightedAdjacencyList) -> Option<WeightedAdjacencyList> {
    let mut mst: WeightedAdjacencyList = vec![Vec::new(); list.len()];
    if list.is_empty() {
        return Some(mst);
    }
    let mut visited = vec![false; list.len()];
    // (weight, from, to), cheapest first.
    let mut frontier = BinaryHeap::new();

    let visit = |node: usize, visited: &mut [bool], frontier: &mut BinaryHeap<_>| {
        visited[node] = true;
        for e in &list[node] {
            if !visited[e.to] {
                frontier.push(Reverse((e.weight, node, e.to)));
            }
        }
    };
    visit(0, &mut visited, &mut frontier);

    while let Some(Reverse((weight, from, to))) = frontier.pop() {
        if visited[to] {
            continue;
        }
        mst[from].push(GraphEdge { to, weight });
        mst[to].push(GraphEdge { to: from, weight });
        visit(to, &mut visited, &mut frontier);
    }

    visited.iter().all(|&v| v).then_some(mst)
}
