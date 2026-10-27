use std::collections::VecDeque;

use crate::types::WeightedAdjacencyList;

pub fn bfs(graph: &WeightedAdjacencyList, source: usize, needle: usize) -> Option<Vec<usize>> {
    let mut seen = vec![false; graph.len()];
    let mut prev: Vec<Option<usize>> = vec![None; graph.len()];
    let mut queue = VecDeque::from([source]);
    seen[source] = true;

    while let Some(cur) = queue.pop_front() {
        if cur == needle {
            break;
        }
        for edge in &graph[cur] {
            if !seen[edge.to] {
                seen[edge.to] = true;
                prev[edge.to] = Some(cur);
                queue.push_back(edge.to);
            }
        }
    }

    if !seen[needle] {
        return None;
    }
    let mut path = vec![needle];
    let mut cur = needle;
    while let Some(p) = prev[cur] {
        path.push(p);
        cur = p;
    }
    path.reverse();
    Some(path)
}
