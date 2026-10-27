use std::cmp::Reverse;
use std::collections::BinaryHeap;

use crate::types::WeightedAdjacencyList;

/// Shortest path from `source` to `sink` (empty if unreachable).
pub fn dijkstra_list(source: usize, sink: usize, arr: &WeightedAdjacencyList) -> Vec<usize> {
    let mut dist = vec![u64::MAX; arr.len()];
    let mut prev: Vec<Option<usize>> = vec![None; arr.len()];
    let mut heap = BinaryHeap::from([Reverse((0u64, source))]);
    dist[source] = 0;

    while let Some(Reverse((d, cur))) = heap.pop() {
        if d > dist[cur] {
            continue; // stale entry
        }
        if cur == sink {
            break;
        }
        for edge in &arr[cur] {
            let next = d + u64::from(edge.weight);
            if next < dist[edge.to] {
                dist[edge.to] = next;
                prev[edge.to] = Some(cur);
                heap.push(Reverse((next, edge.to)));
            }
        }
    }

    if dist[sink] == u64::MAX {
        return Vec::new();
    }
    let mut path = vec![sink];
    let mut cur = sink;
    while let Some(p) = prev[cur] {
        path.push(p);
        cur = p;
    }
    path.reverse();
    path
}
